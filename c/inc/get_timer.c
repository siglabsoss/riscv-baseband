#include "get_timer.h"
#include "ringbus.h"
#include "csr_control.h"

// forward declare.  this file must be included after
// ringbus2_post.h so this all works out
void ring_block_send_eth(unsigned int data);


void readback_timer_callback(const unsigned int word) {
    unsigned timer;
    CSR_READ(TIMER_VALUE, timer);

    if(word == 0) {
        const unsigned hi = (timer>>16) & 0xffff;
        const unsigned low = timer & 0xffff;

        const unsigned us = (OUR_RING_ENUM&0xf)<<20;

        ring_block_send_eth(TIMER_RESULT_PCCMD | us | 0x00000 | low);
        ring_block_send_eth(TIMER_RESULT_PCCMD | us | 0x10000 | hi);
    }
}
