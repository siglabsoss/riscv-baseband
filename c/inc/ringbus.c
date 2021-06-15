#include "ringbus.h"
#include "csr_control.h"
#include "apb_bus.h"
#include "bootloader.h"
#include "extended_ringbus.h"
#include "dma.h"
#include "vmem.h"
#include "ringbus2_pre.h"


unsigned int global_dma_data_len;

/*
// Example of a callback 

void mask_callback(unsigned int data) {
    register volatile unsigned int x3 asm("x3") __attribute__((unused));  // for debug
    register volatile unsigned int x4 asm("x4") __attribute__((unused));  // for debug
    x4 = data;
}

// Example of a registered callback 

ring_register_callback(&mask_callback, MASK_CMD);

*/
void (*ringbus_callback[RINGBUS_MAX_CALLBACKS])(unsigned int);
unsigned int ringbus_callback_compare[RINGBUS_MAX_CALLBACKS];
unsigned int callback_valid = 0;

void ring_register_callback(void (*cb)(unsigned int), unsigned int mask) {
    if(callback_valid < RINGBUS_MAX_CALLBACKS) {
        ringbus_callback[callback_valid] = cb;
        ringbus_callback_compare[callback_valid] = mask;
        callback_valid++;
    }
}

void send_cmd(Ringbus *ringbus){
    CSR_WRITE(RINGBUS_WRITE_ADDR, ringbus->addr);
    CSR_WRITE(RINGBUS_WRITE_DATA, ringbus->data);
    CSR_WRITE_ZERO(RINGBUS_WRITE_EN);
}

void read_cmd(Ringbus *ringbus){
    CSR_WRITE_ZERO(RINGBUS_INTERRUPT_CLEAR);
    CSR_READ(RINGBUS_READ_DATA, ringbus->data);
}


// normally we would include ringbus2_post.h but due to bad .c/h isolation
// I will just copy this here
#define RING_ADDR_PC_RB_TEST_COPY   (((RING_ENUM_PC   - OUR_RING_ENUM - 1) + (RING_BUS_LENGTH*2)) % RING_BUS_LENGTH)

// previously this read the ringbus.addr from the input data
// however it was masked wrong and actually replied to the WRONG fpga
// causing a chain which eventually hit eth
// now we hardcode back to eth
void _ring_test(const unsigned int data){
    Ringbus ringbus;
    ringbus.addr = RING_ADDR_PC_RB_TEST_COPY;
    ringbus.data = data;
    send_cmd(&ringbus);
}

#undef RING_ADDR_PC_RB_TEST_COPY

void _dma_in(unsigned int data){
    CSR_WRITE(DMA_0_START_ADDR, 0);
    CSR_WRITE(DMA_0_LENGTH, data);
    CSR_WRITE(DMA_0_TIMER_VAL, START_IMMED_TIME);
    CSR_WRITE_ZERO(DMA_0_PUSH_SCHEDULE);
    global_dma_data_len = data;
    INTERRUPT_WAIT_CLEAR_DMA_0();
}

void _dma_out(unsigned int data){
    CSR_WRITE(DMA_1_START_ADDR, 0);
    CSR_WRITE(DMA_1_LENGTH, data);
    CSR_WRITE(DMA_1_TIMER_VAL, START_IMMED_TIME);
    CSR_WRITE_ZERO(DMA_1_PUSH_SCHEDULE);
    global_dma_data_len = data;
    INTERRUPT_WAIT_CLEAR_DMA_1();
}


#if (OUR_RING_ENUM != RING_ENUM_CS20) && (OUR_RING_ENUM != RING_ENUM_CS31)
#define INCLUDE_EXTENDED_RB
#endif

#ifdef INCLUDE_EXTENDED_RB

////////////////////////////
//
//  Extended Functions

void _erb_write_vmem_sequence(unsigned int start_addr, unsigned int length, unsigned int start_value) {
    SET_REG(x4, 0xdead);
    SET_REG(x4, start_addr);
    SET_REG(x4, length);
    SET_REG(x4, start_value);

    if(length > 64*1024) {
        length = 64*1024;
    }
    unsigned int count = start_value;
    unsigned int end_addr = start_addr + length;
    for(unsigned int i = start_addr; i < end_addr; i++) {
        vector_memory[i] = count++;
    }
}

// two addresses
// one with a "go", which must be non zero.  zero to clear
// the other is just a shift register

// how many items in the shift register. note this limits
// how many arguments you can have
///////////
//
//
//  assume you have 3 functions (numbers are argument, 1 index)
//     
//    a(a1)
//    b(a1, a2)
//    c(a1, a2, a3)
//    d(a1, a2, a3, a4)
//  
//  when you define them, we pass arguments from the SR like this:
//   (numbers refer to SR0..SR4)
//
//    a(0)
//    b(1,0)
//    c(2,1,0)
//    d(3,2,1,0)
//    e(4,3,2,1,0)
//
//   This way, a user who calls a, does 1 shift in, and then executes
//   A user who calls C, will shift in a1, then a2, then a3 in that order
//   This is the same order as writing left to write on paper.
//
//   Finally a different address is used for execute.  This address must be non zero
//   This index selects a-d
//
//   User sends zero or 1-3 arguments in left to right order.
//   Then user sends the command of the function to exeute
//   
//   FIXME: add a 16 bit loader for SR which would allow for full setting of 32 bit values in SR
//   can keep exising exe() function with no changes and call existing functions with a wider bit range
//   

#define EXTENDED_RINGBUS_SR_LEN (5)
// shortcuts for args
#define SR0 _erb_sr[(EXTENDED_RINGBUS_SR_LEN-1)]
#define SR1 _erb_sr[(EXTENDED_RINGBUS_SR_LEN-2)]
#define SR2 _erb_sr[(EXTENDED_RINGBUS_SR_LEN-3)]
#define SR3 _erb_sr[(EXTENDED_RINGBUS_SR_LEN-4)]
#define SR4 _erb_sr[(EXTENDED_RINGBUS_SR_LEN-5)]
unsigned int _erb_sr[EXTENDED_RINGBUS_SR_LEN];
void _extended_ringbus_exe(unsigned int data) {
    switch(data) {
        case ERB_RESET:
            SR0 = SR1 = SR2 = SR3 = SR4 = 0;
            break;
        case ERB_DMA_BLOCK_SEND:
            dma_block_send(SR1, SR0);
            break;
        case ERB_DMA_BLOCK_SEND_TIMER:
            dma_block_send_timer(SR2, SR1, SR0); // fixme
            break;
        case ERB_DMA_BLOCK_GET:
            dma_block_get(SR1, SR0);
            break;
        case ERB_SEND_RING: {
            // warning this will not block and is not safe
            Ringbus rb;
            rb.addr = SR1;
            rb.data = SR0;
            send_cmd(&rb);
            break;
        }
        case ERB_WRITE_VMEM_SEQUENCE:
            _erb_write_vmem_sequence(SR2, SR1, SR0);
            break;

    }
}

void _extended_ringbus_sr(unsigned int data) {
    SR4 = SR3;
    SR3 = SR2;
    SR2 = SR1;
    SR1 = SR0;
    SR0 = data;
    // _erb_sr[3] = _erb_sr[2];
    // _erb_sr[2] = _erb_sr[1];
    // _erb_sr[1] = _erb_sr[0];
    // _erb_sr[0] = data;

}
#undef SR0
#undef SR1
#undef SR2
#undef SR3
#undef SR4

#endif

#if (OUR_RING_ENUM != RING_ENUM_CS20) && (OUR_RING_ENUM != RING_ENUM_CS31)
#define INCLUDE_PASS_STREAM_DATA
#endif


#ifdef INCLUDE_PASS_STREAM_DATA

void _pass_rx_data(unsigned int data_len){
    Ringbus _ringbus;
    Ringbus *ringbus = &_ringbus;
    unsigned int ringbus_occupancy;
    unsigned int idma_en = 0;
    unsigned int last_fpga = 4;
    unsigned int current_fpga = 0;
    while(current_fpga != last_fpga){
        CSR_READ(RINGBUS_SCHEDULE_OCCUPANCY, ringbus_occupancy);
        if((ringbus_occupancy < 2) && (current_fpga != last_fpga) &&
                                      !idma_en ){
            ringbus->addr = current_fpga + 1;
            ringbus->data = DMA_IN_CMD|data_len;
            send_cmd(ringbus);
            idma_en = 1;
        }
        CSR_READ(RINGBUS_SCHEDULE_OCCUPANCY, ringbus_occupancy);
        if((ringbus_occupancy < 2) && (current_fpga != last_fpga) &&
                                      idma_en){
            ringbus->addr = current_fpga;
            ringbus->data = DMA_OUT_CMD|data_len;
            send_cmd(ringbus);
            idma_en = 0;
            current_fpga++;
        }
        CSR_READ(RINGBUS_SCHEDULE_OCCUPANCY, ringbus_occupancy);
        if(current_fpga == last_fpga){
            ringbus->addr = current_fpga;
            ringbus->data = DMA_OUT_CMD|data_len;
            send_cmd(ringbus);
        }
    }
}

void _stream_packet(unsigned int data_len){
    Ringbus _ringbus;
    Ringbus *ringbus = &_ringbus;
    unsigned int odma_occupancy;
    unsigned int ringbus_occupancy;
    unsigned int read_interrupt;
    unsigned int cycle_delay = 25000;
    unsigned int idma_start_addr = 0;
    unsigned int dma_packet_size = 367;
    global_dma_data_len = data_len;
    unsigned int pass_data_counter = global_dma_data_len;
    unsigned int timer_a, timer_b;

    while((pass_data_counter > 0) && (pass_data_counter < 0x10000)){
        CSR_READ(DMA_1_SCHEDULE_OCCUPANCY, odma_occupancy);
        CSR_READ(RINGBUS_SCHEDULE_OCCUPANCY, ringbus_occupancy);
        if((odma_occupancy < 2) && (ringbus_occupancy < 2)){
            ringbus->addr = 0;
            ringbus->data = DMA_IN_CMD|dma_packet_size;
            send_cmd(ringbus);

            CSR_WRITE(DMA_1_START_ADDR, idma_start_addr);
            CSR_WRITE(DMA_1_LENGTH, dma_packet_size);
            CSR_WRITE(DMA_1_TIMER_VAL, START_IMMED_TIME);
            CSR_WRITE_ZERO(DMA_1_PUSH_SCHEDULE);
            CSR_READ(TIMER_VALUE, timer_a);

            pass_data_counter -= dma_packet_size;
            idma_start_addr += dma_packet_size;
            _pass_rx_data(dma_packet_size);

            while(1) {
                CSR_READ(TIMER_VALUE, timer_b);
                if(timer_b - timer_a > cycle_delay) {
                    break;
                }
            }
            
        }

        CSR_READ(mip, read_interrupt);
        if(read_interrupt & DMA_1_ENABLE_BIT) {
            CSR_WRITE_ZERO(DMA_1_INTERRUPT_CLEAR);
        }
    }
}

#endif

#if OUR_RING_ENUM == RING_ENUM_CS00

void _reset_adc_counter(unsigned int enable_pin){
    unsigned int delay = 0x64;

    CSR_SET_BITS(GPIO_WRITE_EN, enable_pin);
    CSR_SET_BITS(GPIO_WRITE, RESET_ADC_COUNTER);
    for(unsigned int i = 0; i < delay; i++){};
    CSR_CLEAR_BITS(GPIO_WRITE, RESET_ADC_COUNTER);
}

void _en_adc_counter(unsigned int enable_pin){
    CSR_SET_BITS(GPIO_WRITE_EN, enable_pin);
    CSR_SET_BITS(GPIO_WRITE, ADC_COUNTER_BIT);
}

void _disable_adc_counter(unsigned int enable_pin){
    CSR_SET_BITS(GPIO_WRITE_EN, enable_pin);
    CSR_CLEAR_BITS(GPIO_WRITE, ADC_COUNTER_BIT);
}

#endif


// flush any or all of DMA "schedule"
// use lowest 3 bits as flags for each dma
void _dma_flush_reset(unsigned int data) {
    if( data & 0x1 ) {
        CSR_WRITE_ZERO(DMA_0_FLUSH_SCHEDULE);
    }
    if( data & 0x2 ) {
        CSR_WRITE_ZERO(DMA_1_FLUSH_SCHEDULE);
    }
    if( data & 0x4 ) {
        CSR_WRITE_ZERO(DMA_2_FLUSH_SCHEDULE);
    }
}


static void (*catch_incoming_callback)(unsigned int) = 0;

// call with 0 (null pointer) to disable
void ringbus_catch_incoming_callback(void (*cb)(unsigned int)) {
    catch_incoming_callback = cb;
}




////////////////////
///
///  Do not add to this function unless every build ever should have this code
///  Instead, use ring_register_callback() and pass a function
///

/// Note I am adding FEATURE_FLAGS_CMD
/// The goal is that a newly flashed, "empty", fpga has a certain signature
/// once you bootload, the signature should change
/// this allows easier flow for us

void execute_cmd(const unsigned int type, const unsigned int data){
    // register volatile unsigned int x4 asm("x4");  // for debug
    // x3 = 0xf0f0f0f0;
    switch(type){
        case RING_TEST_CMD:
            _ring_test(data);
            break;
        case BOOTLOADER_CMD:
            no_exit_bootload(data, 0);
            break;
        case DMA_IN_CMD:
            _dma_in(data);
            break;
        case DMA_OUT_CMD:
            _dma_out(data);
            break;
#ifdef INCLUDE_PASS_STREAM_DATA
        case PASS_DATA_CMD:
            _pass_rx_data(data);
            break;
        case DMA_OUT_PACKET_CMD:
            _stream_packet(data);
            break;
#endif

#if OUR_RING_ENUM == RING_ENUM_CS00
        case RESET_ADC_COUNTER_CMD:
            _reset_adc_counter(data);
            break;
        case EN_ADC_COUNTER_CMD:
            _en_adc_counter(data);
            break;
        case DISAB_ADC_COUNTER_CMD:
            _disable_adc_counter(data);
            break;
#endif

#ifdef INCLUDE_EXTENDED_RB
        case EXTENDED_SR_CMD:
            _extended_ringbus_sr(data);
            break;
        case EXTENDED_EXECUTE_CMD:
            _extended_ringbus_exe(data);
            break;
#endif
        case DMA_FLUSH_RESET_CMD:
            _dma_flush_reset(data);
            break;

            // B version means inside code that came with bootloader
        // case FEATURE_FLAGS_B_CMD:
        //     feature_flags_report_bitfile();
        //     break;
    }

    // we assume that switch() above didn't get anything
    // first callback that matches will fire, ie don't have identical mask
    // values for different callbacks
    for(unsigned int i = 0; i < callback_valid; i++) //
    {
        if(type == ringbus_callback_compare[i]) {
            // x3 = type;
            (*ringbus_callback[i])(data);
            break;
        }
    }

    if(catch_incoming_callback) {
        catch_incoming_callback( (type | data) );
    }
}

// global array, (to keep off the stack)
// we used this in check_ring()
// do not read this anywhere else
static unsigned drain_rb[RINGBUS_SCHEDULE_DEPTH];

void check_ring(Ringbus *ringbus){
    (void)ringbus;
    unsigned int occupancy;

    // read occupancy once
    CSR_READ(RINGBUS_READ_OCCUPANCY, occupancy);

    if( occupancy == 0 ) {
        return;
    }

    // emtpy out the verilog fifo as fast as possible
    for(unsigned int i = 0; i < occupancy; i++) {
        CSR_READ(RINGBUS_READ_DATA, drain_rb[i]);
    }

    // now that verilog fifo is empty
    // dispatch each ring, this can be very slow
    // depending on how long each callback takes to execute
    for(unsigned int i = 0; i < occupancy; i++) {
        const unsigned int type = (drain_rb[i])&TYPE_MASK;
        const unsigned int data = (drain_rb[i])&DATA_MASK;
        execute_cmd(type, data);
    }
}

// "send" a ringbus to ourself
// this does not actually send the word out to ringbus
// just consumes locally
void inject_ringbus(const unsigned int word) {
    const unsigned int type = (word)&TYPE_MASK;
    const unsigned int data = (word)&DATA_MASK;

    execute_cmd(type, data);
}
