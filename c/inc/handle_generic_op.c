#include "handle_generic_op.h"
#include "ringbus.h"
#include "sig_utils.h"

static generic_callback_simple_t simple_callback = 0;
static generic_callback_ring_t ring_callback = 0;
static generic_callback_dual_t dual_callback = 0;
static generic_callback_post_t post_callback = 0;

void handle_generic_register_get_pointer(const generic_callback_simple_t fn) {
    simple_callback = fn;
}
void handle_generic_register_ring(const generic_callback_ring_t fn) {
    ring_callback = fn;
}
void handle_generic_register_dual_callback(const generic_callback_dual_t fn) {
    dual_callback = fn;
}
void handle_generic_register_post_callback(const generic_callback_post_t fn) {
    post_callback = fn;
}



static uint32_t handle_generic_storage = 0;
static int32_t handle_generic_storage_op = -1;

void handle_generic_callback_original(const unsigned int data) {

    if( unlikely(simple_callback == 0) ) {
        return;
    }

    const uint32_t dmode = (data >> 16) & 0xff; // 8 bits
    const uint32_t data_16 = data & 0xffff; // 16 bits

    const uint32_t op   = dmode&0x7;        // 3 bits
    const uint32_t high = (dmode&0x8) >> 3; // 1 bit
    const uint32_t sel  = (dmode&0xf0)>>4; // 4 bits

    const uint32_t op_sel = dmode&(0x7|0xf0); // op and sel put together

    // _printf("%s%x\n", "handle generic got ", data);

    // SET_REG(x3, 0xdead0000);

    if(high == 0) {
        handle_generic_storage = data_16;
        handle_generic_storage_op = (uint32_t)op_sel;
        return;
    }

    // SET_REG(x3, 0xdead0001);

    // if high == 1
    if(unlikely((uint32_t)handle_generic_storage_op != op_sel)) {
        // got back to back non matching ops. dropping
        handle_generic_storage_op = -1;
        return;
    }

    // SET_REG(x3, 0xdead0002);
    // SET_REG(x3, sel);
    // SET_REG(x3, 0xdead0003);
    // SET_REG(x3, op);
    // SET_REG(x3, 0xdead0004);

    uint32_t* const p = simple_callback(sel);
    if( unlikely(p == 0) ) {
        return;
    }

    const uint32_t full_value = ((data_16<<16)&0xffff0000) | (handle_generic_storage);

    uint32_t capture_low;
    uint32_t capture_high;

    // SET_REG(x3, full_value);
    // SET_REG(x3, 0xdead0005);


    switch(op) {
        case GENERIC_OP_RESET:  // reset
            *p = 0;
            break;
        case GENERIC_OP_ADD:  // add
            *p += full_value;
            break;
        case GENERIC_OP_SUB:  // subtract
            *p -= full_value;
            break;
        case GENERIC_OP_SET: // set
            *p = full_value;
            break;
        case GENERIC_OP_GET:
            if( unlikely(ring_callback == 0) ) {
                return;
            }
            capture_low = *p;
            // SET_REG(x3, capture_low);
            // SET_REG(x3, 0xdead0006);
            capture_high = (capture_low >> 16) & 0xffff;
            capture_low = capture_low & 0xffff;
            ring_callback(GENERIC_READBACK_PCCMD |           (op_sel<<16) | capture_low);
            ring_callback(GENERIC_READBACK_PCCMD | 0x80000 | (op_sel<<16) | capture_high);
            break;
    }

    if( likely(post_callback != 0) ) {
        post_callback(sel, op, full_value);
    }
}

void handle_generic_callback_dual(const unsigned int data) {

    if( unlikely(dual_callback == 0) ) {
        return;
    }

    const uint32_t dmode = (data >> 16) & 0xff; // 8 bits
    const uint32_t data_16 = data & 0xffff; // 16 bits

    const uint32_t op   = dmode&0x7;        // 3 bits
    const uint32_t high = (dmode&0x8) >> 3; // 1 bit
    const uint32_t sel  = (dmode&0xf0)>>4; // 4 bits

    const uint32_t op_sel = dmode&(0x7|0xf0); // op and sel put together

    // _printf("%s%x\n", "handle generic got ", data);

    // SET_REG(x3, 0xdead0000);

    if(high == 0) {
        handle_generic_storage = data_16;
        handle_generic_storage_op = (uint32_t)op_sel;
        return;
    }

    // SET_REG(x3, 0xdead0001);

    // if high == 1
    if( unlikely((uint32_t)handle_generic_storage_op != op_sel) ) {
        // got back to back non matching ops. dropping
        handle_generic_storage_op = -1;
        return;
    }

    // SET_REG(x3, 0xdead0002);
    // SET_REG(x3, sel);
    // SET_REG(x3, 0xdead0003);
    // SET_REG(x3, op);
    // SET_REG(x3, 0xdead0004);

    const uint32_t full_value = ((data_16<<16)&0xffff0000) | (handle_generic_storage);

    dual_callback(sel, op, full_value);
}

// See GenericOperator.cpp : op()
void g_op(uint32_t* const r0,
          uint32_t* const r1,
          const char operation,
          const uint32_t _sel,
          const uint32_t _val,
          const uint32_t _rb_type) {

    uint32_t op;
    switch(operation) {
        case 'z':
            op = GENERIC_OP_RESET;
            break;
        case 'a':
            op = GENERIC_OP_ADD;
            break;
        case 'u':
            op = GENERIC_OP_SUB;
            break;
        case 's':
            op = GENERIC_OP_SET;
            break;
            
        default:
        case 'g':
            op = GENERIC_OP_GET;
            break;
    }

    const uint32_t val_low = _val & 0xffff;
    const uint32_t val_high = (_val >> 16) & 0xffff;


    const uint32_t sel = _sel & 0xf;

    const uint32_t op_sel      = (op | (sel<<4)) << 16;
    const uint32_t op_sel_high = op_sel | 0x80000;
    
    *r0 = op_sel      | val_low  | _rb_type;
    *r1 = op_sel_high | val_high | _rb_type;
}
