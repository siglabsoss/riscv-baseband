#include "ringbus.h"
#include "ringbus2_pre.h"
#define EXCLUDE_RINGBUS2_FUNCTIONS
#include "ringbus2_post.h"


#include "csr_control.h"
#include "soft_ringbus.h"

#include "circular_buffer_pow2.h"

extern circular_buf_pow2_t __soft_ring_queue;
extern circular_buf_pow2_t* soft_ring_queue;

static unsigned int pending_report_ringbus_queue_full_flag = 0;
static unsigned int error_ringbus_queue_full = 0;

void soft_queue_ring_eth(const unsigned int word) {
    const int ret = circular_buf2_put(soft_ring_queue, word);

    // if there was an error inserting, we drop it
    // we bump a counter, and also we set a flag to send ourselves later
    if( ret == -1 ) {
        pending_report_ringbus_queue_full_flag = 1;
        error_ringbus_queue_full++;
    }
}

// ringbus occupancy CSR must be less than this or we will not push data
static unsigned srb_max_occupany = 2;
static unsigned send_tries = 4;

void setup_soft_ring(const unsigned int max_occupancy, const unsigned int tries) {
    srb_max_occupany =  max_occupancy;
    send_tries = tries;
}

// unsigned int fb_parse_last_send = 0;
void pet_soft_ring(void) {
    // unsigned int now;
    // unsigned int ttl;
    unsigned int data;
    unsigned int occupancy;



    for(unsigned i = 0; i < send_tries; i++) {

        if( soft_ring_queue->occupancy > 0 ) { // how full is fifo?

            // if( soft_ring_queue->occupancy > (soft_ring_queue->size+3) ) {
            //     ring_block_send_eth(TX_USERDATA_ERROR | ((soft_ring_queue->occupancy & 0xffff)<<8)     | 0x15 );
            //     break;
            // }

            CSR_READ(RINGBUS_SCHEDULE_OCCUPANCY, occupancy); // how full is ringbus queue?

            if( occupancy < srb_max_occupany ) {
                circular_buf2_get(soft_ring_queue, &data);

                CSR_WRITE(RINGBUS_WRITE_ADDR, RING_ADDR_PC);
                CSR_WRITE(RINGBUS_WRITE_DATA, data);
                // CSR_READ(TIMER_VALUE, fb_parse_last_send); // read right before send
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
        if( soft_ring_queue->occupancy < (soft_ring_queue->size >> 1) ) {
              soft_queue_ring_eth(
                  TX_USERDATA_ERROR
                | 0xc
                | ((error_ringbus_queue_full << 8) & 0xffff00)
            );
              pending_report_ringbus_queue_full_flag = 0;
        }
        
    }
}
