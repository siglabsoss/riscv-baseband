////////////////////////
//
// Shared edge-to-edge test
// see higgs_sdr_rev2/sim/verilator/verify_edge/*
//
// if you cd to the above directory there are make commands
//
//   make edge_test
//



#ifndef __VERIFY_EDGE_TEST_H__
#define __VERIFY_EDGE_TEST_H__

#include "fill.h"
#include "xbaseband.h"
#include "apb_bus.h"
#include "csr_control.h"
#include "pass_fail.h"
#include "ringbus.h"

#include "ringbus2_pre.h"
#include "ringbus2_post.h"




VMEM_SECTION unsigned int golden_data[1024];
VMEM_SECTION unsigned int input_data[1024];
VMEM_SECTION unsigned int junk_data[1024];



unsigned int counter;
unsigned int flag;
unsigned int edge_edge_test_in;
unsigned int edge_edge_test_out;

void edge_in_callback(unsigned int data) {
    counter = 0;
    flag = 0;
    edge_edge_test_in = data;
}

void edge_out_callback(unsigned int data) {
    counter = 0;
    flag = 0;
    edge_edge_test_out = data;
}


void dump_dma_in(unsigned int junk) {
    CSR_WRITE (DMA_0_START_ADDR, junk);
    CSR_WRITE (DMA_0_LENGTH, 1024);
    CSR_WRITE (DMA_0_TIMER_VAL, 0xffffffff);
    CSR_WRITE (DMA_0_PUSH_SCHEDULE, 0); //any value

    // wait
    for(unsigned int i = 0; i < 2048; i++) {
        asm("nop");
    }

    CSR_WRITE(DMA_0_FLUSH_SCHEDULE, 0);
}

unsigned int blink_offtime;
unsigned int blink_ontime;
unsigned int blink_counter = 0;

void set_blink(unsigned int type) {
        switch(type){
        case 0:
            blink_offtime = 2;
            blink_ontime = 0;
            break;
        case 1:
            blink_offtime = 100000;
            blink_ontime = 1000000;
            break;
        case 2:
            blink_offtime = 20000;
            blink_ontime = 400000;
            break;
        case 3:
            blink_offtime = 10000;
            blink_ontime = 100000;
            break;
        case 4:
            blink_offtime = 0;
            blink_ontime = 2;
            break;
    }
}

void do_blink() {
    if( blink_counter == blink_offtime ) {
        CSR_WRITE(GPIO_WRITE, 0);
    }
    if( blink_counter >= blink_ontime) {
        CSR_WRITE(GPIO_WRITE, LED_GPIO_BIT);
        blink_counter = 0;
    }
    blink_counter++;
}

int main(void)
{
    Ringbus ringbus;
    unsigned int dma_out_start_addr;
    unsigned int dma_in_start_addr;
    unsigned int data_len;
    unsigned int start_time;
    unsigned int junk_location = VMEM_DMA_ADDRESS(junk_data);

    dma_out_start_addr = VMEM_DMA_ADDRESS(golden_data);
    dma_in_start_addr = VMEM_DMA_ADDRESS(input_data);
    data_len = 1024;
    start_time = 0xffffffff;

    unsigned int occupancy;
    unsigned int h1;

    // setup callbacks
    ring_register_callback(&edge_in_callback, EDGE_EDGE_IN);
    ring_register_callback(&edge_out_callback, EDGE_EDGE_OUT);

    dump_dma_in(junk_location);

    CSR_WRITE(DMA_1_FLUSH_SCHEDULE, 0);
    CSR_WRITE(DMA_0_FLUSH_SCHEDULE, 0);

    // Filling vector memory with golden results

    for (int i = 0; i < data_len; i++) {
        vector_memory[i + VMEM_DMA_ADDRESS(golden_data)] = i;
    }

    check_ring(&ringbus);

    CSR_WRITE(GPIO_WRITE_EN, LED_GPIO_BIT);

    set_blink(4); // solid on

    while(1) {

        if (edge_edge_test_in == 1) {
            edge_edge_test_in = 0;

            // Start receiving data .. currently, eth is not sending anything
            check_ring(&ringbus);
            CSR_WRITE (DMA_0_START_ADDR, dma_in_start_addr); // start writing after 1024 locations, as they have the golden result
            CSR_WRITE (DMA_0_LENGTH, data_len);
            CSR_WRITE (DMA_0_TIMER_VAL, start_time);
            CSR_WRITE (DMA_0_PUSH_SCHEDULE, 0); //any value

            // checking for dma in task completion
            while(1) {
                CSR_READ(mip, h1);

                set_blink(2); // fast blink while waiting
                do_blink();

                if(h1 & DMA_0_ENABLE_BIT) {
                    CSR_WRITE(DMA_0_INTERRUPT_CLEAR, 0);

                    for (int i = 0; i < data_len; i++) {
                        if (golden_data[i] != input_data[i]) {
                            CSR_WRITE(GPIO_WRITE, LED_GPIO_BIT);
                            set_blink(3); // faster blink, error detected

                            if (flag == 0) {
                                ringbus.addr = RING_ADDR_PC;
                                ringbus.data = 0xdead0000 | OUR_RING_ENUM;
                                send_cmd (&ringbus);
                            }
                            flag = 1;
                            check_ring(&ringbus);
                        }
                    }

                    if (flag == 0) {
                        ringbus.addr = RING_ADDR_PC;
                        ringbus.data = 0xbabe0000 | OUR_RING_ENUM;
                        send_cmd (&ringbus);
                        flag = 1;
                    }
                    dump_dma_in(junk_location);
                    break; // exit while(1)
                }
                check_ring(&ringbus);
            } // while

        } else if (edge_edge_test_out == 1) {
            edge_edge_test_out = 0;
            set_blink(1); // slow blink, we were asked to do output (note it sticks here during 100% success)
            CSR_READ(DMA_1_SCHEDULE_OCCUPANCY, occupancy);
            check_ring(&ringbus);

            CSR_WRITE(DMA_1_START_ADDR, dma_out_start_addr);
            CSR_WRITE(DMA_1_LENGTH, data_len);
            CSR_WRITE(DMA_1_TIMER_VAL, start_time);
            CSR_WRITE(DMA_1_PUSH_SCHEDULE, 0);
        }

        do_blink();
        check_ring(&ringbus);
    }
}











#endif
