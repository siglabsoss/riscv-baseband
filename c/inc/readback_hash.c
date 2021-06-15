#include "readback_hash.h"
#include "random.h"
#include "ringbus.h"


// forward declare
void ring_block_send_eth(unsigned int data);

// static so it will not be callable from other files
// however we can take a function pointer and pass outsidse of this file just fine
static void _hash_callback(unsigned int word) {

    unsigned int us = OUR_RING_ENUM;

    unsigned int hash;
    hash = xorshift32(1, &us, 1);
    hash = xorshift32(hash, &word, 1);

    unsigned int readback = READBACK_HASH_PCCMD | ((us&0xf)<<20) | (hash&0xfffff);


    ring_block_send_eth(readback);
}




void ringbus_enable_readback(const unsigned int enable) {
    if(enable) {
        ringbus_catch_incoming_callback(&_hash_callback);
    } else {
        ringbus_catch_incoming_callback(0);
     }
}
