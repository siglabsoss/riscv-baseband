#include "xbaseband.h"
#include "apb_bus.h"
#include "csr_control.h"
#include "pass_fail.h"
#include "dma.h"
#include "fill.h"
#include "mover.h"
#include "mapper.h"
#include "ringbus.h"
#include "circular_buffer.h"
#include "feedback_bus.h"

#ifndef __TEST_DIRECT_INJECT_H__
#define __TEST_DIRECT_INJECT_H__

VMEM_SECTION uint32_t test_direct_inject_data[1024];

void no_exit_test_inject(void) {
    // unsigned int rtn;
    // Ringbus ringbus;


    dma_in_set(VMEM_DMA_ADDRESS(test_direct_inject_data), 1024);


    for(int i = 0; i < 800; i++) {
        STALL(40);
    }


    unsigned int occupancy;
    while(1) {
        CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, occupancy);
        if( occupancy == 0) {
            break;
        }
    }
    ring_block_send_eth(0xffffffff);


    for(int i = 0; i < 1024; i++) {
        ring_block_send_eth(test_direct_inject_data[i]);
    }
}

#endif