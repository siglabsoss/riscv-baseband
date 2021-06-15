#include "check_bootload.h"
#include "dma.h"
#include "ringbus.h"
#include "csr_control.h"

// forward declare.  this file must be included after
// ringbus2_post.h so this all works out
void ring_block_send_eth(unsigned int data);



// static char bootload_id_storage[REGISTER_BOOTLOAD_SIZE];

static void blocking_readback(void) {
    SET_REG(x4, 0xfeed0000);
    SET_REG(x4, 0x44444444);
    // CHECK_ID_PCCMD;
}

static unsigned _past_self_sync = 0;

void check_bootload_status(unsigned int word) {
    if( word == 0 ) {
        ring_block_send_eth(CHECK_BOOTLOAD_PCCMD | OUR_RING_ENUM);
        return;
    }
    if( word == 1) {
        blocking_readback();
        return;
    }
    if( word == 2) {
        ring_block_send_eth(CHECK_BOOTLOAD_PCCMD | (_past_self_sync<<8) | OUR_RING_ENUM);
        return;
    }
}

void check_bootload_set_past_sync(const unsigned x) {
    _past_self_sync = x;
}



// FIXME read COMPILE_FOLDER into id_storage
// and then read back out to application when requested!
void register_bootload(const char* x, const unsigned int version) {
    (void)x;
    (void)version;
#ifdef COMPILE_FOLDER
    SET_REG(x4, 0x44000000);

    const char* s = COMPILE_FOLDER;

    // int len = 0;
    char c = s[0];
    unsigned index = 0;
    while(c != 0) {

        SET_REG(x4, c);
        index++;
        c = s[index];
    }

    SET_REG(x4, 0x44000001);
    // SET_REG(x4, index);
    // SET_REG(x4, (unsigned int)s);
    // SET_REG(x4, 0x44000002);
    // SET_REG(x4, (unsigned int)s[0]);
    // SET_REG(x4, (unsigned int)s[1]);
    // SET_REG(x4, (unsigned int)s[2]);
    // SET_REG(x4, 0x44000003);
#endif
}