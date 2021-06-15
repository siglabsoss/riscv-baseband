#include "corrupt_dma.h"
#include "dma.h"

// forward declare.  this file must be included after
// ringbus2_post.h so this all works out
void ring_block_send_eth(unsigned int data);

void corrupt_dma_callback(const unsigned int word) {
    const unsigned int dmode =      (word & 0x00ff0000) >> 16;
    const unsigned int dlow       =  word & 0x0000ffff;

    if( dmode ) {
        dma_block_send_finalized(0, dlow, 1);
    } else {
        dma_block_send(0, dlow);
    }

    ring_block_send_eth(0x09000000);
}