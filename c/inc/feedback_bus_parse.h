#ifndef __FEEDBACK_BUS_PARSE_H__
#define __FEEDBACK_BUS_PARSE_H__

#include "circular_buffer_pow2.h"
#include "pipeline_work.h"
#include "feedback_bus.h"
#include "my_assert.h"
#include "subtract_timers.h"


// if the first number is a power of 2, the next number should be the same (ie 16 and 16)
// other wise it would be (11 and 16)
#ifndef FEEDBACK_BUS_USER_POINTERS
#define FEEDBACK_BUS_USER_POINTERS (46)
#endif
#ifndef FEEDBACK_BUS_USER_POINTERS_NEXT_POW2
#define FEEDBACK_BUS_USER_POINTERS_NEXT_POW2 (64)
#endif

/// This is stuff for a new, limited, memory manager
/// These must be defined before including, and you can only have one
/// inclusion of memory_manager.h per fpga
#define MEMORY_MANAGER_SIZE 1024
#define MEMORY_MANAGER_CHUNKS (FEEDBACK_BUS_USER_POINTERS)
#include "memory_manager.h"


void handle_header_flush_initial(pipeline_work_t* prev, pipeline_work_t* work, unsigned int *input);
unsigned int handle_header_flush_enduring(pipeline_work_t* prev, pipeline_work_t* work, unsigned int *input);

// before we just put a token into dma_schedule_in when we would queue a dma
// now we put a token in the lower 8 bits, and an optional value in the upper 24
// these are masks and shifts

#define DMA_FLAG_MASK 0xFF
#define DMA_DATA_MASK 0xFFFFFF00
#define DMA_DATA_SHIFT 8

#define FLAG_DMA_0_HEADER  (0)
#define FLAG_DMA_0_BODY    (1)
#define FLAG_DMA_1_HEADER  (2)
#define FLAG_DMA_1_BODY    (3)

// the body of a when header is in 0
#define FLAG_DMA_0_MAPMOV_NEXT_BODY  (4)
// the body of a mapmov when header is in 1
#define FLAG_DMA_1_MAPMOV_NEXT_BODY  (5)

// disables this module from setting x3, x4 debug registers
// put this in your main.c before including this file to enable
//
// #define FB_ENABLE_SET_REG

#ifndef FB_ENABLE_SET_REG
#define FBSET_REG(x,y)
#else
#define FBSET_REG(x,y) SET_REG(x,y)
#endif

#define SABOTAGE_1_MAX_VALUE 128
#define SABOTAGE_1_MAX_VALUE_MASK 0x7f

#define FB_RING_BUFFER_SIZE (64)

// pad these extra
VMEM_SECTION unsigned int buf0_header[16+1024+SABOTAGE_1_MAX_VALUE];
VMEM_SECTION unsigned int buf1_header[16+1024+SABOTAGE_1_MAX_VALUE];
VMEM_SECTION unsigned int fb_parse_reset_junk[16];


// warning, VMEM_DMA_ADDRESS() cannot be used, here so these vars must be set at runtime
static unsigned int buf0_header_dma;
static unsigned int buf1_header_dma;// = VMEM_DMA_ADDRESS(buf1_header);

static unsigned int* buf0_body = buf0_header+16;
static unsigned int* buf1_body = buf1_header+16;

static unsigned int buf0_body_dma;// = VMEM_DMA_ADDRESS(buf0_body);
static unsigned int buf1_body_dma;// = VMEM_DMA_ADDRESS(buf1_body);

static unsigned int dumping_zeros_mode;
static unsigned int dumping_zeros_counted;

static unsigned int pending_input_sabotage_mode_1;
static unsigned int pending_input_sabotage_mode_1_val;


circular_buf_pow2_t __fb_ring_queue = CIRBUF_POW2_STATIC_CONSTRUCTOR(__fb_ring_queue, FB_RING_BUFFER_SIZE);
circular_buf_pow2_t* fb_ring_queue = &__fb_ring_queue;

//! This buffer is added to every time we schedule an input DMA
//! The occupancy of this buffer should always be identical to the DMA_IN occupany in hardare
//! If hardware occupancy is lower, that means something has finished

circular_buf_pow2_t __dma_schedule_in = CIRBUF_POW2_STATIC_CONSTRUCTOR(__dma_schedule_in, 4);
circular_buf_pow2_t* dma_schedule_in = &__dma_schedule_in;



pipeline_work_t __dma_in_work;
pipeline_work_t* dma_in_work = &__dma_in_work;

pipeline_work_t __parse_work;
pipeline_work_t* parse_work = &__parse_work;

// int dma_next;
unsigned int dma_in_expected_occupany;

unsigned int mapmov_total_size;
unsigned int mapmov_total_chunks;
unsigned int mapmov_this_chunk;     // index of most recent chunk to be handed to userland
unsigned int mapmov_chunk_enqueued; // index of most recent chunk to be given to dma in
unsigned int mapmov_fft_size;
unsigned int mapmov_pause_operations;

// copies when passed to user
unsigned int global_vtype;
unsigned int global_stype;

// body signal
int dma_in_body_signal = -1;

// mapmov signal
int dma_in_mapmov_signal = -1;
int dma_in_mapmov_header_signal = -1; // similar to a "mapmov active"


// number of times we opened a frame and got a invalid type
unsigned int error_incorrect_types = 0;
// ringbus packet got an odd number of words
unsigned int error_odd_rb_length = 0;
// vector length must be larger than 16
unsigned int error_small_vector_length = 0;

unsigned int error_large_vector_length = 0;

unsigned int error_unhandled_vector_vtype = 0;

unsigned int error_unhandled_stream_stype = 0;

unsigned int error_fired_with_unset_callback = 0;

unsigned int error_ringbus_queue_full = 0;

unsigned int pending_report_ringbus_queue_full_flag = 0;

unsigned int types_handled[4];

typedef void (*fb_vector_callback_t)(unsigned int*, unsigned int *, unsigned int, unsigned int);
typedef void (*fb_stream_callback_t)(unsigned int*, unsigned int *, unsigned int, unsigned int);
typedef void (*fb_mapmov_callback_t)(unsigned int*, unsigned int, unsigned int, unsigned int, unsigned int);

// void (*dispatch_vector_type)(unsigned int*, unsigned int *, unsigned int, unsigned int) = 0;

fb_vector_callback_t dispatch_vector_type_callback = 0;
fb_stream_callback_t dispatch_stream_type_callback = 0;
fb_mapmov_callback_t dispatch_mapmov_callback = 0;

void fb_queue_ring_eth(const unsigned int word) {
    const int ret = circular_buf2_put(fb_ring_queue, word);

    // if there was an error inserting, we drop it
    // we bump a counter, and also we set a flag to send ourselves later
    if( ret == -1 ) {
        pending_report_ringbus_queue_full_flag = 1;
        error_ringbus_queue_full++;
    }
}

// how long should rb be suppressed for
#ifndef RB_SUPRESSION_DELAY
#define RB_SUPRESSION_DELAY (125000000)
#endif

// over what period to trigger a supression
#ifndef RB_SUPRESSION_CHECK
#define RB_SUPRESSION_CHECK (125000000/4)
#endif

// how many in the period trigger a supression
#ifndef RB_SUPRESSION_COUNT
#define RB_SUPRESSION_COUNT (8)
#endif

unsigned int first_eth_supression = 0;
unsigned int eth_supression_start = 0;
unsigned int eth_supression_count = 0;
unsigned int eth_supression_state = 0;
unsigned int eth_supression_supressed = 0;

void fb_queue_ring_eth_suppressed(unsigned int word) {

    bool queue = false;
    unsigned int now;
    CSR_READ(TIMER_VALUE, now);

    switch(eth_supression_state) {
        default:
        case 0:
            first_eth_supression = now;
            eth_supression_state = 1;
            eth_supression_count = 1;
            queue = true;
            break;
        case 1:
            // it took longer than the period, so just go back and reset everything
            // ie they are coming slow and its ok
            if( subtract_timers(now, first_eth_supression) >= RB_SUPRESSION_CHECK ) {
                queue = true;
                eth_supression_state = 0;
            } else {
                eth_supression_count++;
                
                if( eth_supression_count >= RB_SUPRESSION_COUNT ) {
                    eth_supression_start = now;
                    queue = false;
                    eth_supression_state = 2;
                    eth_supression_supressed = 1;
                } else {
                    queue = true;
                }
            }
            break;
        case 2:
            // it's been longer than the timer, send this one and reset and go back to state 0
            if( subtract_timers(now, eth_supression_start) >= RB_SUPRESSION_DELAY ) {
                queue = true;
                eth_supression_state = 0;
            } else {
                // still came too early, block it
                queue = false;
                eth_supression_supressed++;
            }
            break;
    }

    if( queue ) {
        fb_queue_ring_eth(word);
    }
}


void fb_register_vector_callback(fb_vector_callback_t ptr) {
    dispatch_vector_type_callback = ptr;
}

void fb_register_stream_callback(fb_stream_callback_t ptr) {
    dispatch_stream_type_callback = ptr;
}

void fb_register_mapmov_callback(fb_mapmov_callback_t ptr) {
    dispatch_mapmov_callback = ptr;
}

void fb_pause_mapmov(void) {
    mapmov_pause_operations = 1;
}

void fb_unpause_mapmov(void) {
    mapmov_pause_operations = 0;
}

void trig_dma_header_in(unsigned int idx) {
    // dma next is simple for now

    if( idx == 0 ) {
        circular_buf2_put(dma_schedule_in, FLAG_DMA_0_HEADER);
        dma_in_set(buf0_header_dma, 16);
        return;
    } 
    if( idx == 1 ) {
        circular_buf2_put(dma_schedule_in, FLAG_DMA_1_HEADER);
        dma_in_set(buf1_header_dma, 16);
        return;
    }
}

void trig_dma_body_in(unsigned int idx, unsigned int length) {
    if( idx == 0 ) {
        circular_buf2_put(dma_schedule_in, FLAG_DMA_0_BODY);
        dma_in_set(buf0_body_dma, length);
        return;
    }
    if( idx == 1 ) {
        circular_buf2_put(dma_schedule_in, FLAG_DMA_1_BODY);
        dma_in_set(buf1_body_dma, length);
        return;
    }
}

void trig_dma_header_after_flush(unsigned int idx, unsigned int offset) {

    if( idx == 0 ) {
        circular_buf2_put(dma_schedule_in, FLAG_DMA_0_HEADER);
        dma_in_set(buf0_header_dma+offset, 16-offset);
        return;
    }
    if( idx == 1 ) {
        circular_buf2_put(dma_schedule_in, FLAG_DMA_1_HEADER);
        dma_in_set(buf1_header_dma+offset, 16-offset);
        return;
    }
}


///
/// Trigger a mapmov body.  this does not touch dma_in_expected_occupany
/// pass in the A/B buffer index in which the header of the mapmov buffer is in
/// this allocate new memory from the memory manager
///
void trig_mapmov_body_in(unsigned int idx, unsigned int length) {
    // pull a memory, if it's not ok, we assert
    int mem = memory_manger_get();

    // we got the header, and it is buffer index
    // we will put the body in a different place
    
    if( mem == -1 ) {
        MY_ASSERT(mem != -1);
        return;
    }

    // cast to unsigned
    unsigned int mem_bits = mem;

    // don't need to mask because left shift always has zeros
    mem_bits = (mem_bits << DMA_DATA_SHIFT);

    if( idx == 0 ) {
        circular_buf2_put(dma_schedule_in, mem_bits|FLAG_DMA_0_MAPMOV_NEXT_BODY);
        dma_in_set(mem, length);
        return;
    }
    if( idx == 1 ) {
        circular_buf2_put(dma_schedule_in, mem_bits|FLAG_DMA_1_MAPMOV_NEXT_BODY);
        dma_in_set(mem, length);
        return;
    }
}

void trig_multiple_mapmov_body(unsigned int header_location) {

    unsigned int mm_avail;
    unsigned int dma_in_avail;
    unsigned int buffer_occupancy;

    while(1) {

        mm_avail = memory_manager_available();

        buffer_occupancy = circular_buf2_occupancy(dma_schedule_in);

        // 4 here is size of buffer_occupancy
        dma_in_avail = 4 - buffer_occupancy;

        if( 
                mm_avail > 0               // room in memory manager
            &&  dma_in_avail > 0           // room in dma in buffer
            &&  mapmov_chunk_enqueued < mapmov_total_chunks  // not finished with body
            )  {
            // FBSET_REG(x3, 0x9000 | mapmov_chunk_enqueued );
            // FBSET_REG(x3, 0x8000 | mm_avail );
            // FBSET_REG(x3, 0x8000 | dma_in_avail );
            // FBSET_REG(x3, 0x8000 | mapmov_chunk_enqueued );
            trig_mapmov_body_in(header_location, mapmov_fft_size);
            dma_in_expected_occupany++;
            mapmov_chunk_enqueued++;
        } else {
            break;
        }

    }
}

// we only queue 1 to start
void setup_dma_in(void) {
    CIRBUF_POW2_RUNTIME_INITIALIZE(__dma_schedule_in);
    // dma_next = 0;
    trig_dma_header_in(0);
    dma_in_expected_occupany = 1;
    dumping_zeros_counted = 0;
    dumping_zeros_mode = 0;
}

void ring_block_send(unsigned int tty, unsigned int data) {
  unsigned int occupancy;

  while(1)
  {
   CSR_READ(RINGBUS_SCHEDULE_OCCUPANCY, occupancy);
   if(occupancy < RINGBUS_SCHEDULE_DEPTH)
   {
    break;
   }
  }

  CSR_WRITE(RINGBUS_WRITE_ADDR, tty);
  CSR_WRITE(RINGBUS_WRITE_DATA, data);
  CSR_WRITE(RINGBUS_WRITE_EN, 0);
}


// dma is allowed to get to this +1
unsigned int dma_in_allowed_additional_occupancy = 0;

#ifdef FBPARSE_USE_DEBUG
const char* fb_dma_trig_name[] = {"FLAG_DMA_0_HEADER","FLAG_DMA_0_BODY","FLAG_DMA_1_HEADER","FLAG_DMA_1_BODY","FLAG_DMA_0_MAPMOV_NEXT_BODY","FLAG_DMA_1_MAPMOV_NEXT_BODY"};
#endif

// Setup here is a bit weird
// unlike previous pipeline work projects
// pet_dma_in() is NOT the only fn that schedules an input DMA
// because we need to look at the contents of the dma in order to choose the length of the
// next input DMA, the pet_parse() fn will directly trigger a DMA in some cases
// we use dma_in_body_signal as a 2nd signal to signal downstream when pet_dma_in()
// detects that one of the special DMA's (scheduled by pet_parse()) has finished


void pet_dma_in(void) {
    pipeline_work_t* work = dma_in_work; // work
    // pipeline_work_t* prev = work->prev;
    // pipeline_work_t* next = work->next;
    int error;
    unsigned int occupancy;
    unsigned int just_finished_combined;
    unsigned int just_finished_idx;
    unsigned int just_finished_data;
    CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, occupancy); //DMA_1_SCHEDULE_DEPTH

    if( mapmov_pause_operations ) {
        return;
    }

    // a dma finished!
    // only enter if  dma_in_mapmov_signal is -1 which protects us from the case where
    // we previously received a body for mapmov, however mapmov_pause_operations has prevented us
    // from consuming the signal.  in that case we just wait
    if( occupancy < dma_in_expected_occupany) {
        error = circular_buf2_get(dma_schedule_in, &just_finished_combined); MY_ASSERT(error == 0);
        
        //ring_block_send_eth(just_finished_combined);

        // pull apart the old and new data here
        just_finished_idx = just_finished_combined & DMA_FLAG_MASK;
        just_finished_data = (just_finished_combined & DMA_DATA_MASK) >> DMA_DATA_SHIFT;
        
        // drop this because we handled it
        dma_in_expected_occupany--;

        FBSET_REG(x3, 0xf000);

        FBSET_REG(x4, just_finished_idx);

        switch(just_finished_idx) {
            case FLAG_DMA_0_HEADER:
                HOLD(A);  // signal downstream we have something in A
                // work->a_empty = 0;
                FBSET_REG(x3, 0xf001);
                FBSET_REG(x3, (0xf001 << 16) | work->state);
                break;
            case FLAG_DMA_0_BODY:
                dma_in_body_signal = 0;
                FBSET_REG(x3, 0xf002);
                break;
            case FLAG_DMA_1_HEADER:
                HOLD(B);  // signal downstream we have something in B
                // work->b_empty = 0; // signal downstream we have something
                FBSET_REG(x3, 0xf003);
                FBSET_REG(x3, work->b_empty);
                break;
            case FLAG_DMA_1_BODY:
                dma_in_body_signal = 1;
                FBSET_REG(x3, 0xf004);
                break;
            case FLAG_DMA_0_MAPMOV_NEXT_BODY:
                dma_in_mapmov_header_signal = 0;
                dma_in_mapmov_signal = just_finished_data;
                FBSET_REG(x3, 0xf005);
                break;
            case FLAG_DMA_1_MAPMOV_NEXT_BODY:
                dma_in_mapmov_header_signal = 1;
                dma_in_mapmov_signal = just_finished_data;
                FBSET_REG(x3, 0xf006);
                break;
            default:
                ring_block_send_eth(APP_ASSERT_PCCMD | 4);
                break;
        }

#ifdef FBPARSE_USE_DEBUG
    const char* as_string = fb_dma_trig_name[just_finished_idx];
    _printf("%s%s\n", "Dma trig: ", as_string);

    // dump_vmem_cpu(20, input_buffer, 16);
#endif

        return;
    }

    if( 
        (    occupancy == 0                             // dma in is empty
          || dma_in_allowed_additional_occupancy == 1)   // or we have this extra capacity
        && (dma_in_mapmov_header_signal == -1)          // and we are NOT in a mapmov
        && (dumping_zeros_mode == 0)
        ) {


        FBSET_REG(x3, 0xa000 | dma_in_allowed_additional_occupancy );

        if( work->state == 0 ) {
            FBSET_REG(x3, 0xd000);
            FBSET_REG(x4, work->a_empty);
            FBSET_REG(x4, work->b_empty);
            if(work->b_empty==1) {
                FBSET_REG(x3, 0xd001);
                trig_dma_header_in(1);
                dma_in_expected_occupany++;
                dma_in_allowed_additional_occupancy = 0;
            }
            FLIP_STATE();
            return; // important to return here, or else the next if would double execute
        }

        if( work->state == 1 ) {
            FBSET_REG(x3, 0xd002);
            // FBSET_REG(x4, work->a_empty);
            // FBSET_REG(x4, work->b_empty);
            if(work->a_empty==1) {
                FBSET_REG(x3, 0xd003);
                trig_dma_header_in(0);
                dma_in_expected_occupany++;
                dma_in_allowed_additional_occupancy = 0;
            }
            FLIP_STATE();
            return;
        }

    }

}

// at this point, type is already set in stone
void __attribute__((optimize("Os"))) handle_header_ringbus(unsigned int *input) {
    

    unsigned int length;
    // unsigned int type = 3;
    // very expensive to read members from this *frame as it resides in VMEM
    // so each and every item we read, copy to a local variable, and stop using *frame
    // a {} scope could prevent you from getting at frame twice
    feedback_frame_ringbus_t* frame = (feedback_frame_ringbus_t*) input;
    length = frame->length;
    

    // in words, will be 
    unsigned int rb_length = length - FRAME_PRIMITIVE_WORDS;
    // unsigned int packed_ringbus_messages = rb_length/2;

    // FBSET_REG(x3, 0xcafe);
    // FBSET_REG(x3, packed_ringbus_messages);

    // check if it's odd
    if( rb_length & 0x1 )  {
        error_odd_rb_length++;
        return;
    }


    // Note:
    // the first word is actually an ENUM type when it comes over the wire (not direct ttl)
    // we have to look up who it's bound for to
    // figure out ttl for peer
    // Note: we do expensive *frame reads in loop but only what we need
    unsigned int ttl;
    for(unsigned int i = 0; i < rb_length; i+=2) {
        unsigned int frame_rb_enum = frame->packed_ring[i];
        unsigned int frame_rb_data = frame->packed_ring[i+1];

        // FBSET_REG(x3, frame_rb_enum);
        FBSET_REG(x4, frame_rb_data);
        ttl = ring_enum_to_addr(frame_rb_enum);
        // FBSET_REG(x3, ttl);

        ring_block_send(ttl, frame_rb_data);
    }


}


// vector_length is number of words past *body that are valid
void handle_body_stream(unsigned int *header, unsigned int *body, unsigned int stream_length) {
    // unsigned int length; //length = stream_length+16; // if needed back calculate
    unsigned int stype; // stream type
    {
        feedback_frame_stream_t* frame = (feedback_frame_stream_t*) header;
        stype = frame->stype;
    }

    FBSET_REG(x3, 0xeff000 | stype);

    if(dispatch_stream_type_callback != 0 ) {
        global_stype = stype;
        (*dispatch_stream_type_callback)(header, body, stream_length, stype);
    } else  {
        error_fired_with_unset_callback++;
    }
}

// vector_length already has 16 subtracted
void handle_body_vector(unsigned int *header, unsigned int *body, unsigned int vector_length) {

    // unsigned int length; //length = vector_length+16; // if needed back calculate
    unsigned int vtype; // vector type
    {
        feedback_frame_vector_t* frame = (feedback_frame_vector_t*) header;
        vtype = frame->vtype;
    }
    FBSET_REG(x3, 0xeee000 | vtype);

    ///
    /// Handle some feedback bus types internally
    /// These handled types ALSO call out to the user type
    ///

    // default to true, will set to false
    int internally_handled = 1;

    switch(vtype) {
        case FEEDBACK_VEC_STATUS_REPLY:
            fb_queue_ring_eth(FEEDBACK_ALIVE);
            break;

        ///
        /// default case lets us know we did NOT internally handle this
        /// this is only used for error handling
        /// we still pass the message on in case user application also wants it
        default:
            internally_handled = 0;
            break;
    }

    if(dispatch_vector_type_callback != 0 ) {
        global_vtype = vtype;
        (*dispatch_vector_type_callback)(header, body, vector_length, vtype);
    } else {
        if( internally_handled == 0 ) {
            error_fired_with_unset_callback++;
        }
    }
}

void handle_body_vector_userdata(unsigned int *cpu_header, unsigned int dma_body, unsigned int chunk_length) {
    // unsigned int length; //length = vector_length+16; // if needed back calculate
    // unsigned int vtype; // vector type
    // {
    //     feedback_frame_vector_t* frame = (feedback_frame_vector_t*) header;
    //     vtype = frame->vtype;
    // }
    FBSET_REG(x3, 0xe1e000 | FEEDBACK_VEC_TX_USER_DATA);
    FBSET_REG(x3, 0xe10000 | mapmov_this_chunk );
    FBSET_REG(x3, 0xe11000 | mapmov_total_chunks );


    if(dispatch_vector_type_callback != 0 ) {
        (*dispatch_mapmov_callback)(cpu_header, dma_body, chunk_length, mapmov_this_chunk, mapmov_total_chunks);
    } else {
        error_fired_with_unset_callback++;
    }

    // mapmov_total_chunks
    mapmov_this_chunk++;
}

void fb_release_userdata_dma_pointer(unsigned int dma_p) {
    memory_manger_free(dma_p);
}

void fb_vector_default(void) {
    fb_queue_ring_eth(TX_USERDATA_ERROR | ((global_vtype & 0xffff0000)>>8) | 0x11 );
    fb_queue_ring_eth(TX_USERDATA_ERROR | ((global_vtype & 0xffff)<<8)     | 0x12 );
    error_unhandled_vector_vtype++;
}

void fb_stream_default(void) {
    fb_queue_ring_eth(TX_USERDATA_ERROR | ((global_stype & 0xffff0000)>>8) | 0x13 );
    fb_queue_ring_eth(TX_USERDATA_ERROR | ((global_stype & 0xffff)<<8)     | 0x14 );
    error_unhandled_stream_stype++;
}

// returns non zero number of bytes to read next
// if error returns -1
// used for both vector or stream types as they are the same
int handle_header_vector_or_stream(unsigned int *input, unsigned int vs_type) {
    unsigned int length;
    feedback_frame_ringbus_t* frame = (feedback_frame_ringbus_t*) input;
    length = frame->length;

    // must be LARGER than 16
    // vector of size 0 makes no sense?
    if (length < FEEDBACK_HEADER_WORDS) {
        fb_queue_ring_eth_suppressed(TX_USERDATA_ERROR | 0x100 | 0xe );
        for(int i = 0; i < 24; i++) {
            uint32_t word = input[i];
            fb_queue_ring_eth(TX_USERDATA_ERROR | ((word & 0xffff0000)>>8) | 0x16 );
            fb_queue_ring_eth(TX_USERDATA_ERROR | ((word & 0xffff)<<8)     | 0x17 );
        }
        error_small_vector_length++;
        return -1;
    }

    unsigned int vector_length = length - FEEDBACK_HEADER_WORDS;


    if( vs_type == FEEDBACK_VEC_TX_USER_DATA ) {
        // if a mapmov, a very large limit
        if (vector_length > FEEDBACK_MAPMOV_MAX_LENGTH) {
            fb_queue_ring_eth_suppressed(TX_USERDATA_ERROR | 0x200 | 0xe );
            error_large_vector_length++;
            return -1;
        }
    } else {
        // if anything else, 1024 limit
        if (vector_length > FEEDBACK_BODY_WORDS) {
            fb_queue_ring_eth_suppressed(TX_USERDATA_ERROR | 0x300 | 0xe );
            error_large_vector_length++;
            return -1;
        }
    }


    return vector_length;
    // trig_dma_body_in
}

///
///  Flow:
///    we re-enter this function multiple times
///    depending on previous state, different paths are taken
///    a header comes in, is parsed
///    after the header is finished the code queues up the body (length ahead of time is not known)
///    
///    after full body has arrived from DMA, then pet_dma_in will set dma_in_body_signal
///    which tells this loop where to parse the body
///
void pet_parse(void) {
    pipeline_work_t* work = parse_work; // work
    pipeline_work_t* prev = work->prev;
    // pipeline_work_t* next = work->next;
    unsigned int consume_idx;
    static unsigned int cached_length;
    static unsigned int cached_type;
    static unsigned int cached_vs_type; // v and s type are at same location

    consume_idx = work->state;
    unsigned int* input_buffer = prev->cpu[consume_idx];

    // handle our special, (not normal flow signal) dma_in_body_signal, first
    // this is set when a BODY dma has just finished
    if(dma_in_body_signal != -1) {

        // we have a body and we know what slot it's in
        unsigned int* input_buffer_frame_body = prev->cpu[dma_in_body_signal];

#ifdef FBPARSE_USE_DEBUG
        dump_vmem_cpu(1, input_buffer_frame_body, 16);
#endif

        FBSET_REG(x3, 0xb000 | dma_in_body_signal);
        // is it ok to not read dma_in_body_signal? and instead rely that work->state is stable
        // 
        FBSET_REG(x3,0xee000 | cached_type);
        switch(cached_type) {
            case FEEDBACK_TYPE_VECTOR:
                // FBSET_REG(x4, input_buffer_frame_body[0]);
                // FBSET_REG(x4, input_buffer_frame_body[1]);
                // FBSET_REG(x4, input_buffer_frame_body[2]);
                // FBSET_REG(x4, input_buffer_frame_body[3]);
                // FBSET_REG(x4, input_buffer_frame_body[16]);
                // FBSET_REG(x4, input_buffer_frame_body[17]);
                // FBSET_REG(x4, input_buffer_frame_body[18]);
                // FBSET_REG(x4, input_buffer_frame_body[19]);
            
                // first pointer is to the header
                // second pointer is to the body.. in our current implementation these are back 2 back
                // however if we wanted to split the memory we would need to edit this
                handle_body_vector(input_buffer_frame_body, input_buffer_frame_body+FEEDBACK_HEADER_WORDS, cached_length);
                types_handled[cached_type]++;
                break;
            case FEEDBACK_TYPE_STREAM:
                handle_body_stream(input_buffer_frame_body, input_buffer_frame_body+FEEDBACK_HEADER_WORDS, cached_length);
                types_handled[cached_type]++;
                break;
            case FEEDBACK_TYPE_FLUSH:
                // do nothing
                break;
            default:
                break;
        }
        RELEASE_TO_PREV();
        RELEASE_AUTO();
        FLIP_STATE();
        dma_in_body_signal = -1;
        return;
    } // it was body
    // flip last


    if( dma_in_mapmov_signal != -1 ) {

        if(mapmov_pause_operations) {
            // return early, don't update any counters or call any functions
            // this will leave dma_in_mapmov_signal still set
            // so next time around we will re-enter this function
            return;
        }

        types_handled[FEEDBACK_TYPE_VECTOR]++;

        // dma_in_mapmov_header_signal will also be set at the same time
        // unsigned int *header, unsigned int *body, unsigned int vector_length

        unsigned int* cpu_buffer_head = prev->cpu[dma_in_mapmov_header_signal];
        unsigned int dma_buffer_body = dma_in_mapmov_signal;

        handle_body_vector_userdata( cpu_buffer_head, dma_buffer_body, mapmov_fft_size);

        if(mapmov_this_chunk == mapmov_total_chunks) {
            // we just gave the last pointer to user-land
            RELEASE_TO_PREV();
            RELEASE_AUTO();
            FLIP_STATE();
            dma_in_mapmov_header_signal = -1; // set this to -1
        } else {
            // not done, check if we can queue more input dma
            trig_multiple_mapmov_body(dma_in_mapmov_header_signal);
            
        }


        // keep resetting this signal. however we leave dma_in_mapmov_header_signal set
        // so other parts can use it, we will reset both when we are done
        dma_in_mapmov_signal = -1;
        return;
    }


    
    // Check current process for available space
    if (work->state == 0){
        if (prev->a_empty == 1){
            // FBSET_REG(x3, 0xc004);
            return;  // nothing in dma a
        }
        if (work->a_empty == 0){
            // FBSET_REG(x3, 0xc005);
            return; //  something in fft a
        }
        
        HOLD(A);  // hold fft a
        // prev->a_empty = 1; // release dma a (ONLY VALID IF WE DON'T EXIT)
        // work->a_empty = 0;  // hold fft a
        FBSET_REG(x3, 0xc000);
    }

    if (work->state == 1){
        if (prev->b_empty == 1){
            // FBSET_REG(x3, 0xc002);
            return; // nothing in dma b
        }
        if (work->b_empty == 0){
            // FBSET_REG(x3, 0xc003);
            return; // something in fft b
        }
        // RELEASE_TO_PREV(); //  release dma b
        HOLD(B); // hold fft b
        // prev->b_empty = 1; //  release dma b
        // work->b_empty = 0; // hold fft b
        FBSET_REG(x3, 0xc001);
    }


    // do something with the data
    // Cache this value
    cached_type = input_buffer[FEEDBACK_WORD_OFFSET];

    FBSET_REG(x3, 0xe000 | cached_type);

    // ring_block_send_eth(0xe000 | cached_type);

    int next_dma_read;


    if( dumping_zeros_mode != 0 ) {
        unsigned int perfect_align = handle_header_flush_enduring(prev, work, input_buffer);
        if(!perfect_align) {
            FBSET_REG(x3, 0x4700);
            return;
        } else {
            FBSET_REG(x3, 0x4800);
        }
    }
#ifdef FBPARSE_USE_DEBUG
    _printf("%s%d\n", "fb type ", cached_type);
    dump_vmem_cpu(20, input_buffer, 16);
#endif

    switch(cached_type) {
        case FEEDBACK_TYPE_STREAM:
        case FEEDBACK_TYPE_VECTOR:
            // cache this type
            cached_vs_type = input_buffer[FEEDBACK_VECTOR_VTYPE_OFFSET];

            // returns -1 for error
            // returns 0 for header only messages (which WON'T get passed to cs11 currently)
            // returns 1 or larger for a body read
            next_dma_read = handle_header_vector_or_stream(input_buffer, cached_vs_type);
            if( next_dma_read > 0 ) {
                // packet requires a ready for the body

                if( cached_vs_type == FEEDBACK_VEC_TX_USER_DATA ) {
                    ///
                    /// We just got a mapmov header
                    /// first we set all these globals
                    /// next we enqueue as many dma in as we can hold
                    /// the next time a dma finishes we will come into the code above, but still in this function
                    /// when we pass to user function we will update mapmov_this_chunk

                    mapmov_total_size = next_dma_read;
                    mapmov_fft_size = 1024; // change this for trim
                    mapmov_total_chunks = mapmov_total_size / mapmov_fft_size;
                    mapmov_this_chunk = 0;
                    mapmov_chunk_enqueued = 0;

                    // ring_block_send_eth(mapmov_total_size);
                    // ring_block_send_eth(mapmov_total_chunks);

                    
                    // this function updates dma_in_expected_occupany
                    trig_multiple_mapmov_body(work->state);

                    // trig_mapmov_body_in(work->state, mapmov_fft_size);
                } else {
                    // normal operation
                    FBSET_REG(x3, 0xff06 + work->state);
                    trig_dma_body_in(work->state, next_dma_read);
                    FBSET_REG(x3, 0xdd000000 + next_dma_read);
                    dma_in_expected_occupany++;
                    dma_in_allowed_additional_occupancy = 1;
                }
                // shared between user data and normal body operation

            } else {
                // we either had an error or a zero length body (ie header only message)
                // in this case we release the buffers and move on

                // we don't need to report any errors here, they were already reported

                RELEASE_TO_PREV();
                RELEASE_AUTO();
                FLIP_STATE();
                cached_length = 0; // either a -1 or a 0 means we write zero here
                return;
            }
                
            cached_length = next_dma_read; // always set even if 0
            // these types should not release, they will do it once dma_in_body_signal is set
            break;
        case FEEDBACK_TYPE_RINGBUS:
            handle_header_ringbus(input_buffer);
            types_handled[cached_type]++; // bump handled count here because rb type has no body
            // work->a_empty = 1;
            // FBSET_REG(x3, dma_in_work->a_empty);
            RELEASE_TO_PREV();  // release dma a or b signaling to dma that it can fill this spot,
                                // we don't do this for vector types with a body because they will be 
                                // scheduling an additional DMA in the same buffer so it's still held 
            RELEASE_AUTO();
            FLIP_STATE();
            return;
            // FBSET_REG(x3, dma_in_work->a_empty);
            break;
        case FEEDBACK_TYPE_UNJAM:
            // do nothing
            // types_handled[cached_type]++; // bump handled count here because rb type has no body
            RELEASE_TO_PREV();
            RELEASE_AUTO();
            FLIP_STATE();
            return;
            break;
        case FEEDBACK_TYPE_FLUSH:
            // we just got a header with zero type.
            // we need to examine the current 16
            if( dumping_zeros_mode == 0 ) {
                handle_header_flush_initial(prev, work, input_buffer);
            }
            
            return;
            // FBSET_REG(x3, dma_in_work->a_empty);
            break;

        default:
            fb_queue_ring_eth_suppressed(TX_USERDATA_ERROR | ((cached_type & 0xffff0000)>>8) | 0x0f );
            fb_queue_ring_eth_suppressed(TX_USERDATA_ERROR | ((cached_type & 0xffff)<<8)     | 0x10 );

            RELEASE_TO_PREV();
            RELEASE_AUTO();
            FLIP_STATE();
            error_incorrect_types++;
            break;
    }
}

void notify_finish_flushing_zeros(void) {
    fb_queue_ring_eth(
          TX_USERDATA_ERROR
        | 0xb
        | ((dumping_zeros_counted << 8) & 0xffff00)

        );
}

// returns perfect alignment
// if we hit zeros, the first thing that is called is handle_header_flush_initial() this will always consume 16 words
// this means any flushing of zeros must be at least 16 long
// afterwards, this function gets called.  This function will loop through 16 words, loading them into imem
// if a non zero value is found, we shift the memory we just loaded into imem so that it's aligned at the zero byte mark
//    once the memory is shifted, we queue the remaining bytes of the header using trig_dma_header_after_flush()
//    we clear the dumping_zeros_mode flag, and the code outside will trigget a header as normal
//    even though it's actually a fractional header, the code works fine
//
// if a non zero value is found at position 0, we don't need to do any shifting
// this also means we DONT want to trigger a fractional header because we already have all of it
// in this case we skip the move and instead return 1, and clear the dumping_zeros_mode flag
// this allows the calling function pet_dma_in() to continue along, use the exiting cached_type value
// and everything is fine
unsigned int handle_header_flush_enduring(pipeline_work_t* prev, pipeline_work_t* work, unsigned int *input) {

    int found = -1;
    unsigned int loaded[FEEDBACK_HEADER_WORDS];

    // loop through and look for non zero values
    for(int i = 0; i < FEEDBACK_HEADER_WORDS; i++) {
        loaded[i] = input[i];

        if( loaded[i] ) {
            if( found == -1 ) {
                found = i;
            }
        } else {
            if( found == -1 ) {
                dumping_zeros_counted++;
            }
        }
    }

#ifdef FBPARSE_USE_DEBUG
    _printf("%s%d\n", "zeros enduring: ", found);
#endif

    if( found != -1 ) {
        FBSET_REG(x3, 0x4000);
        FBSET_REG(x3, 0x4500);
        FBSET_REG(x3, found);

        if( found == 0 ) {
            // skip move
            notify_finish_flushing_zeros();

            dumping_zeros_mode = 0;
            dma_in_allowed_additional_occupancy = 0;
            return 1;
        } else {
            int output = 0;
            for(int i = found; i < FEEDBACK_HEADER_WORDS; i++) {
                input[output] = loaded[i];
                output++;
            }

            RELEASE_TO_PREV();
            RELEASE_AUTO();

            trig_dma_header_after_flush(work->state, FEEDBACK_HEADER_WORDS-found);
            dma_in_expected_occupany++;
            dumping_zeros_mode = 0;
            dma_in_allowed_additional_occupancy = 0;

            notify_finish_flushing_zeros();
            return 0;
        }

    } else {
        FBSET_REG(x3, 0x4000);
        FBSET_REG(x3, 0x4600);
        FBSET_REG(x3, 0x4000 | dumping_zeros_counted);

        RELEASE_TO_PREV();
        RELEASE_AUTO();

        trig_dma_header_in(work->state);
        dma_in_expected_occupany++;
        dma_in_allowed_additional_occupancy = 0;
        return 0;
    }
}


// look at every value to find first non zero
void handle_header_flush_initial(pipeline_work_t* prev, pipeline_work_t* work, unsigned int *input) {
    (void)input;

#ifdef FBPARSE_USE_DEBUG
    _printf("%s\n", "zeros found");
#endif

    if(dumping_zeros_mode == 0) {
        fb_queue_ring_eth(TX_USERDATA_ERROR | 0xa);
    }
    dumping_zeros_mode = 1;
    dumping_zeros_counted = 16;

    FBSET_REG(x3, 0x4000);
    FBSET_REG(x3, 0x4400);
    FBSET_REG(x3, 0x4000 | dumping_zeros_counted);


    RELEASE_TO_PREV();
    RELEASE_AUTO();

    trig_dma_header_in(work->state);
    dma_in_expected_occupany++;
    dma_in_allowed_additional_occupancy = 0;
}


void sabotage_callback(unsigned int word) {
    uint32_t dmode = (word & 0x00ff0000)>>16;
    uint32_t data =  word & 0x0000ffff;
    switch(dmode) {
        case 0:
            break;
        case 1:
            pending_input_sabotage_mode_1 = 1;
            pending_input_sabotage_mode_1_val = (data & SABOTAGE_1_MAX_VALUE_MASK);
            break;
        default:
            break;
    }
}

void setup_work(void) {
    pipeline_work_initialize(dma_in_work, buf0_header, buf1_header);
    pipeline_work_initialize(parse_work, 0, 0);

    dma_in_work->prev = 0;
    dma_in_work->next = parse_work;
    parse_work->prev = dma_in_work;
    parse_work->next = 0;

    dma_in_body_signal = -1;

}

// setup variables and other stuff to do once at boot
// do this first as other parts rely on this
void setup_vars(void) {
    buf0_header_dma = VMEM_DMA_ADDRESS(buf0_header);
    buf1_header_dma = VMEM_DMA_ADDRESS(buf1_header);
    buf0_body_dma = VMEM_DMA_ADDRESS(buf0_body);
    buf1_body_dma = VMEM_DMA_ADDRESS(buf1_body);

    mapmov_total_size = 0;
    mapmov_total_chunks = 0;
    mapmov_this_chunk = 0;

    dma_in_body_signal = -1;
    dma_in_mapmov_signal = -1;
    dma_in_mapmov_header_signal = -1;
    mapmov_pause_operations = 0;


    pending_input_sabotage_mode_1 = 0;
    pending_input_sabotage_mode_1_val = 0;

    // ringbus queue
    CIRBUF_POW2_RUNTIME_INITIALIZE(__fb_ring_queue);
}

void __attribute__((optimize("Os"))) fb_dump_errors(unsigned int data) {
    (void)data;
    // note these are masked with 5 f's
    fb_queue_ring_eth( TX_FB_REPORT_PCCMD | (0x00000000) | (error_incorrect_types & 0x000fffff)  );
    fb_queue_ring_eth( TX_FB_REPORT_PCCMD | (0x00100000) | (error_odd_rb_length & 0x000fffff)  );
    fb_queue_ring_eth( TX_FB_REPORT_PCCMD | (0x00200000) | (error_small_vector_length & 0x000fffff)  );
    fb_queue_ring_eth( TX_FB_REPORT_PCCMD | (0x00300000) | (error_large_vector_length & 0x000fffff)  );
    fb_queue_ring_eth( TX_FB_REPORT_PCCMD | (0x00400000) | (error_unhandled_vector_vtype & 0x000fffff)  );
    fb_queue_ring_eth( TX_FB_REPORT_PCCMD | (0x00500000) | (error_unhandled_stream_stype & 0x000fffff)  );
    fb_queue_ring_eth( TX_FB_REPORT_PCCMD | (0x00600000) | (error_fired_with_unset_callback & 0x000fffff)  );
    fb_queue_ring_eth( TX_FB_REPORT_PCCMD | (0x00700000) | (types_handled[FEEDBACK_TYPE_STREAM] & 0x000fffff)  );
    fb_queue_ring_eth( TX_FB_REPORT_PCCMD | (0x00800000) | (types_handled[FEEDBACK_TYPE_VECTOR] & 0x000fffff)  );
    fb_queue_ring_eth( TX_FB_REPORT_PCCMD | (0x00900000) | (types_handled[FEEDBACK_TYPE_RINGBUS] & 0x000fffff)  );
    fb_queue_ring_eth( TX_FB_REPORT_PCCMD | (0x00a00000) | (error_ringbus_queue_full & 0x000fffff)  );
}

void __attribute__((optimize("Os"))) fb_dump_status(unsigned int data) {
    (void)data;
    
    int inc = 0x00000000;

    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (mapmov_total_size & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (mapmov_total_chunks & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (mapmov_this_chunk & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (mapmov_chunk_enqueued & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (mapmov_fft_size & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (mapmov_pause_operations & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (dma_in_body_signal & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (dma_in_mapmov_signal & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (dma_in_mapmov_header_signal & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (dma_in_allowed_additional_occupancy & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (dma_in_expected_occupany & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (dumping_zeros_mode & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (dumping_zeros_counted & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (dma_schedule_in->occupancy & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (dma_in_work->state & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (dma_in_work->a_empty & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (dma_in_work->b_empty & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (parse_work->state & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (parse_work->a_empty & 0x0000ffff)  ); inc += 0x00010000;
    fb_queue_ring_eth( TX_FB_REPORT2_PCCMD | inc | (parse_work->b_empty & 0x0000ffff)  ); inc += 0x00010000;

}

// FIXME: this seems broken, but it's ok if its here and we don't use it
void reset_fb_callback(unsigned int data) {
    if( data == 1 ) {
        CSR_WRITE_ZERO(DMA_0_FLUSH_SCHEDULE);
    }
    if( data == 2 ) {
        flush_input_dma(VMEM_DMA_ADDRESS(fb_parse_reset_junk), 16, 8192);
    }
    if( data == 3 ) {
        dma_in_work->state = 0;
        dma_in_work->a_empty = 1;
        dma_in_work->b_empty = 1;
        
        parse_work->state = 0;
        parse_work->a_empty = 1;
        parse_work->b_empty = 1;
    }
    // CSR_WRITE_ZERO(DMA_0_FLUSH_SCHEDULE);
    // flush_input_dma(VMEM_DMA_ADDRESS(fb_parse_reset_junk), 16, 8192);
    // setup_work();
}

inline unsigned int fb_parse_subtract_timers(unsigned int a, unsigned int b) {
  if (a < b) {
      // time rollover(overflow)
      return (0xFFFFFFFF - b) + 1 + a;
    } else {
      return a - b;
    }
}

// #define FB_PARSE_MINIMUM_RING_TIMING (3000)
// ringbus occupancy CSR must be less than this or we will not push data
#define FB_PARSE_MAXIMUM_RING_OCCUPANCY (2)
unsigned int fb_parse_last_send = 0;
void fb_parse_pet_pending_ring(void) {
    // unsigned int now;
    // unsigned int ttl;
    unsigned int data;
    unsigned int occupancy;

    for(int i = 0; i < 100; i++) {

        if( fb_ring_queue->occupancy > 0 ) { // how full is fifo?

            if( fb_ring_queue->occupancy > (FB_RING_BUFFER_SIZE+3) ) {
                ring_block_send_eth(TX_USERDATA_ERROR | ((fb_ring_queue->occupancy & 0xffff)<<8)     | 0x15 );
                break;
            }

            CSR_READ(RINGBUS_SCHEDULE_OCCUPANCY, occupancy); // how full is ringbus queue?

            if( occupancy < FB_PARSE_MAXIMUM_RING_OCCUPANCY ) {
                circular_buf2_get(fb_ring_queue, &data);

                CSR_WRITE(RINGBUS_WRITE_ADDR, RING_ADDR_PC);
                CSR_WRITE(RINGBUS_WRITE_DATA, data);
                CSR_READ(TIMER_VALUE, fb_parse_last_send); // read right before send
                CSR_WRITE_ZERO(RINGBUS_WRITE_EN);
            } else {
                break;
            }
        } else {
            break;
        }
    
    }

    // because this is a buffer, it's possible to over fill it
    // in that case we set a flag, and count how many times it's happened
    // once the buffer is half empty (to be conservative) we add a message
    // to the buffer reporting that we did an overflow. then we clear the flag
    if( pending_report_ringbus_queue_full_flag ) {
        // if less than half full, we can report there was an overflow
        if( fb_ring_queue->occupancy < (fb_ring_queue->size >> 1) ) {
              fb_queue_ring_eth(
                  TX_USERDATA_ERROR
                | 0xc
                | ((error_ringbus_queue_full << 8) & 0xffff00)
            );
              pending_report_ringbus_queue_full_flag = 0;
        }
        
    }
}

void fb_parse_setup(void) {
    setup_vars();
    init_memory_manager();
    setup_dma_in();
    setup_work();

    parse_work->state = 0;

    ring_register_callback(&fb_dump_errors, TX_REPORT_ERRORS_CMD);
    ring_register_callback(&fb_dump_status, FB_REPORT_STATUS_CMD);
    ring_register_callback(&reset_fb_callback, FB_BUS_RESET_CMD);
    ring_register_callback(&sabotage_callback, SABOTAGE_CMD);
}

void pet_fb_parse(void) {
    pet_dma_in();
    pet_parse();
    fb_parse_pet_pending_ring();

    for(int i = 0; dumping_zeros_mode && i < 4; i++) {
        pet_dma_in();
        pet_parse();
    }
}


#undef FB_ENABLE_SET_REG
#endif