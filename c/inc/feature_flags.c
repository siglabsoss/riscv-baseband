#include "feature_flags.h"
#include "ringbus.h"
#include "static_hash.h"
#include "csr_control.h"

// seems weird but ringbus2_post is messed up it should not have c in a .h
// this workaround allows us to only get the macros
#define VERILATE_TESTBENCH
#include "ringbus2_pre.h"
#include "ringbus2_post.h"
#undef VERILATE_TESTBENCH

#define STATIC_HASH_24(s) (STATIC_HASH(s)&0xffffff)

void feature_flags_callback_a(unsigned int data) {
    (void)data;
    CSR_WRITE(RINGBUS_WRITE_ADDR, RING_ADDR_PC);
    CSR_WRITE(RINGBUS_WRITE_DATA, 0xdeadbeef);
    CSR_WRITE_ZERO(RINGBUS_WRITE_EN);
}


void feature_flags_report(void) {

}

// Call this from the bootloader 
// not the bitfile, but the code that came inside the bitfile
void feature_flags_report_bitfile(void) {
    uint32_t empty_bitfile_feature = STATIC_HASH_24("FRESH_BITFILES");
    // ring_block_send_eth(empty_bitfile_feature);
        CSR_WRITE(RINGBUS_WRITE_ADDR, RING_ADDR_PC);
    CSR_WRITE(RINGBUS_WRITE_DATA, FEATURE_FLAGS_REP_DONE_PCCMD|empty_bitfile_feature);
    CSR_WRITE_ZERO(RINGBUS_WRITE_EN);
}


// call at runtime from your main, only once
void setup_feature_flags(void) {

    ring_register_callback(&feature_flags_callback_a, FEATURE_FLAGS_A_CMD);
}

