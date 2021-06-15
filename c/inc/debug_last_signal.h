#ifndef __DEBUG_LAST_SIGNAL_H__
#define __DEBUG_LAST_SIGNAL_H__

#include "dma.h"
#include "vmem.h"
#include "csr_control.h"
#include "vmem_counter_alpha.h"
#include "subtract_timers.h"
#include "random.h"

uint32_t who;
uint32_t do_send = 0;
uint32_t do_recv = 0;
uint32_t tx_send = 0;

// uint32_t delay_time = 4000;
uint32_t delay_time = 100000000;

VMEM_SECTION uint32_t dma_memory[1024];

void setup_debug_last(uint32_t whoam) {
    who = whoam;

    switch(who) {
        case RING_ENUM_CS00:
            do_send = 0;
            do_recv = 0;
        break;
        case RING_ENUM_CS01:
            do_send = 0;
            do_recv = 0;
        break;
        case RING_ENUM_CS11:
            do_send = 0;
            do_recv = 0;
        break;
        case RING_ENUM_CS21:
            do_send = 0;
            do_recv = 0;
        break;
        case RING_ENUM_CS31:
            do_send = 0;
            do_recv = 0;
        break;
        case RING_ENUM_CS30:
            do_send = 0;
            do_recv = 0;
        break;
        case RING_ENUM_CS20:
            do_send = 1;
            do_recv = 0;
        break;
        case RING_ENUM_CS10:
            do_send = 0;
            do_recv = 1;
        break;
    }

    // built in stall for eth to get ready
    for(int i = 0; i < 800; i++) {
        STALL(40);
    }
}

uint32_t tx_queued = 0;
uint32_t rx_queued = 0;
uint32_t rx_state = 0;
uint32_t tx_state = 0;
uint32_t now = 0;
uint32_t tx_runs = 0;

uint32_t expected_occupancy = 0;


void pet_debug_tx() {
    uint32_t occupancy;
    uint32_t status;

    if(do_send) {

        if(!tx_queued) {
            CSR_READ(TIMER_VALUE, now);

            if(subtract_timers(now,tx_send) < delay_time ) {
                return;
            }

            tx_send = now;

            tx_queued = 1;
            
            if( tx_runs % 3 != 2 ) {
                dma_block_send_finalized(
                    VMEM_DMA_ADDRESS(vmem_counter_alpha),
                    vmem_counter_alpha_size,
                    1);
            } else {

                int bad_size;
                do {
                    // pick and make sure we don't pick 5 for random which would NOT corrupt
                    bad_size = vmem_counter_alpha_size-5+(simple_random()%9);
                }while(bad_size == 1024);

                dma_block_send_finalized(
                    VMEM_DMA_ADDRESS(vmem_counter_alpha),
                    bad_size,
                    1);
            }
        } else {
            if( tx_state == 0 ) {
                CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, occupancy);
                if( occupancy == 0 ) {
                    // reset
                    tx_queued = 0;
                    tx_state = 0;
                    tx_runs++;
                }
            }
        }

        // dma_block_send_finalized(
        //     VMEM_DMA_ADDRESS(vmem_counter_alpha),
        //     vmem_counter_alpha_size,
        //     1);

    }
}

void pet_debug_rx() {

    uint32_t occupancy;
    uint32_t status;

    if(do_recv) {
        if( !rx_queued ) {
            rx_queued = 1;

            dma_memory[0] = 0xffffffff;
            dma_memory[177] = 0xffffffff;
            dma_memory[1023] = 0xffffffff;

            dma_block_get(
                VMEM_DMA_ADDRESS(dma_memory),
                vmem_counter_alpha_size);
        } else {
            // wait until read is finished
            if(rx_state == 0) {
                CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, occupancy);
                if( occupancy == 0) {
                  rx_state = 1;
                }
            }
            // observe status
            if( rx_state == 1) {
                CSR_READ(DMA_0_STATUS, status);
                ring_block_send_eth(EDGE_EDGE_OUT | 0x010000 | status);

                uint32_t match0 = dma_memory[0] == vmem_counter_alpha_expected(0);
                uint32_t match1 = dma_memory[177] == vmem_counter_alpha_expected(177);
                uint32_t match2 = dma_memory[1023] == vmem_counter_alpha_expected(1023);

                if( match0 && match1 && match2 ) {
                    // ok
                    ring_block_send_eth(EDGE_EDGE_OUT | 0x030000);

                    // reset
                    rx_state = 0;
                    rx_queued = 0;
                } else {
                    // error
                    ring_block_send_eth(EDGE_EDGE_OUT | 0x020000 | match0 | match1 << 1 | match2 << 2);
                    rx_state = 2; // go to recovery
                }
            }

            // run till last to recover
            if( rx_state == 2 ) {
                dma_run_till_last();

                // do i need to block here?
                rx_state = 0;
                rx_queued = 0;
            }
        }
    }

}

void pet_debug_last() {
    pet_debug_tx();
    pet_debug_rx();
}


#endif