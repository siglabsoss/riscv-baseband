#ifndef __DO_FORWARD_STREAM_H__
#define __DO_FORWARD_STREAM_H__

#include "fill.h"
#include "xbaseband.h"
#include "apb_bus.h"
#include "csr_control.h"
#include "vmem.h"
#include "dma.h"
#include "ringbus2_pre.h"
#include "ringbus2_post.h"
#include "ringbus.h"

#define STREAM_CHUNK (1024)

#ifndef STREAM_BUFFERS
#define STREAM_BUFFERS (64)
#endif

#ifndef STALL_AFTER_OUTPUT
#define STALL_AFTER_OUTPUT (400)
#endif

#define BUFFER_SIZE (STREAM_CHUNK*STREAM_BUFFERS)


// stream buffer
VMEM_SECTION unsigned int stream_buffer[BUFFER_SIZE];

unsigned int dma_in_dma_ptr;
unsigned int dma_in_trig_next = 0;
unsigned int dma_out_trig_next = 0;
unsigned int in_expected_occupany = 2;
unsigned int out_expected_occupany = 2;

// this only works with buffers number = 2
// #define FLIP_BIT(x) ((x)^0x1)

unsigned int dma_idx_to_ptr(unsigned int idx) {
  return dma_in_dma_ptr + (idx * STREAM_CHUNK);
}

// convert a dma_ptr to an index
unsigned int dma_ptr_to_idx(unsigned int ptr) {
  return (ptr - dma_in_dma_ptr) / STREAM_CHUNK;
}

// void trig_dma_in_next() {
//   dma_block_get(dma_idx_to_ptr(dma_in_trig_next), STREAM_CHUNK);

//   dma_in_trig_next = FLIP_BIT(dma_in_trig_next);
// }

void trig_dma_in(unsigned int idx) {
  dma_block_get(dma_idx_to_ptr(idx), STREAM_CHUNK);
}

void trig_dma_out(unsigned int idx) {
  dma_block_send(dma_idx_to_ptr(idx), STREAM_CHUNK);
}

void trig_dma_in_total() {
    unsigned int addr = VMEM_DMA_ADDRESS(stream_buffer);
    dma_block_get(addr, BUFFER_SIZE);
}

unsigned int allowed_to_capture = 0;

// callback from ringbus
void unblock_capture_stream(unsigned int data) {
    allowed_to_capture = 1;
}


void no_exit_capture(int wait_for_trigger) {

    Ringbus ringbus;

    ring_register_callback(&unblock_capture_stream, EDGE_EDGE_IN);

    if( wait_for_trigger ) {
        while(!allowed_to_capture) {
            check_ring(&ringbus);
        }
    }

  
    CSR_WRITE(DMA_0_FLUSH_SCHEDULE, 0);
    CSR_WRITE(DMA_1_FLUSH_SCHEDULE, 0);
    CSR_WRITE(DMA_2_FLUSH_SCHEDULE, 0);
  
    CSR_WRITE(GPIO_WRITE_EN, LED_GPIO_BIT);
    // CSR_SET_BITS(GPIO_WRITE, LED_GPIO_BIT);
    CSR_CLEAR_BITS(GPIO_WRITE, LED_GPIO_BIT);
  
  
    dma_in_dma_ptr = VMEM_DMA_ADDRESS(stream_buffer);
  
    unsigned int in_occupancy;
    unsigned int out_occupancy;
    unsigned int flip;
  
    // im afraid that when the fpga boots there will be fifos filled with stale data
    // this is my best guess at how to clear it out
    // the goal here is to get continuous data
    trig_dma_in(0);
    trig_dma_in(0);
    trig_dma_in_total();
  
  
    dma_in_trig_next = 0; // we did 0,1 so next is 0
  
  
    unsigned int forwards = 0;

  while(1) {

      CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, in_occupancy);
      CSR_READ(DMA_1_SCHEDULE_OCCUPANCY, out_occupancy);

      if( in_occupancy == 0 ) {

        // notify we are done
        ring_block_send_eth(DEBUG_10_PCCMD | (OUR_RING_ENUM<<24) | STREAM_BUFFERS );

        for(unsigned int i = 0; i < 10; i++) {
            STALL(10);
        }


        for(unsigned int i = 0; i < STREAM_BUFFERS; i++) {
            trig_dma_out(i);

            do {
                check_ring(&ringbus);
                CSR_READ(DMA_1_SCHEDULE_OCCUPANCY, out_occupancy);
            } while(out_occupancy != 0);

            for(unsigned int j = 0; j < STALL_AFTER_OUTPUT; j++) {
                STALL(10);
            }

        }

        // stall forever until we re-write to support multiple trigger
        allowed_to_capture = 0;
        while(1) {
            check_ring(&ringbus);
        }


        // #ifdef FORWARD_REPORT_CHUNK
        // ring_block_send_eth(forwards);
        // forwards++;
        // #endif
      }

      SET_REG(x3, 0xff000000);
      SET_REG(x3, in_occupancy);
      SET_REG(x3, out_occupancy);

      check_ring(&ringbus);

  }

}

#endif