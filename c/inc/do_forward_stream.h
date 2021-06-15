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
#include "check_bootload.h"
#include "pipeline_work.h"
#include "circular_buffer_pow2.h"
#include "random.h"

#ifndef STREAM_CHUNK
#define STREAM_CHUNK 1024
#endif

#define STREAM_BUFFERS 2


// stream buffer
VMEM_SECTION unsigned int stream_buffer[STREAM_CHUNK*STREAM_BUFFERS];

unsigned int dma_in_dma_ptr;
unsigned int in_expected_occupany = 0;
unsigned int out_expected_occupany = 0;

unsigned int dma_idx_to_ptr(unsigned int idx) {
  return dma_in_dma_ptr + (idx * STREAM_CHUNK);
}

// convert a dma_ptr to an index
unsigned int dma_ptr_to_idx(unsigned int ptr) {
  return (ptr - dma_in_dma_ptr) / STREAM_CHUNK;
}


pipeline_work_t __work_in;
pipeline_work_t* work_in = &__work_in;

pipeline_work_t __work_out;
pipeline_work_t* work_out = &__work_out;

circular_buf_pow2_t __dma_schedule_in = CIRBUF_POW2_STATIC_CONSTRUCTOR(__dma_schedule_in, 2);
circular_buf_pow2_t* dma_schedule_in = &__dma_schedule_in;

circular_buf_pow2_t __dma_schedule_out = CIRBUF_POW2_STATIC_CONSTRUCTOR(__dma_schedule_out, 2);
circular_buf_pow2_t* dma_schedule_out = &__dma_schedule_out;


void trig_dma_in(unsigned int idx) {
  circular_buf2_put(dma_schedule_in, idx);
  in_expected_occupany++;

  dma_block_get(dma_idx_to_ptr(idx), STREAM_CHUNK);
}

void trig_dma_out(unsigned int idx) {
  circular_buf2_put(dma_schedule_out, idx);
  out_expected_occupany++;

  dma_block_send(dma_idx_to_ptr(idx), STREAM_CHUNK);
}



void pet_in(void) {
    int error;
    unsigned int in_occupancy;
    pipeline_work_t* work = work_in; // work
    CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, in_occupancy);

    unsigned int just_finished_idx;

    if( in_occupancy < in_expected_occupany ) {
        error = circular_buf2_get(dma_schedule_in, &just_finished_idx);
        (void)error;

        // SET_REG(x3, 0xa0000000);

        in_expected_occupany--;

        switch(just_finished_idx) {
            case 0:
                // SET_REG(x3, 0xb0000000);
                HOLD(A);
                break;
            case 1:
                // SET_REG(x3, 0xb0000001);
                HOLD(B);
                break;
            default:
                break;
        }
    }
}

void pet_out(void) {
    int error;
    // unsigned int in_occupancy;
    unsigned int out_occupancy;
    pipeline_work_t* work = work_out; // work
    pipeline_work_t* prev = work_in;

    // if previous is full, but we are empty
    if( !prev->a_empty && work->a_empty ) {
        HOLD(A);
        trig_dma_out(0);
        // SET_REG(x3, 0xc0000000);
    }

    if( !prev->b_empty && work->b_empty ) {
        HOLD(B);
        trig_dma_out(1);
        // SET_REG(x3, 0xc0000001);
    }

    unsigned int just_finished_idx;
    CSR_READ(DMA_1_SCHEDULE_OCCUPANCY, out_occupancy);

    // SET_REG(x3, 0xf0000000 | out_occupancy);

    if( out_occupancy < out_expected_occupany ) {
        error = circular_buf2_get(dma_schedule_out, &just_finished_idx);
        (void)error;

        // SET_REG(x3, 0xd0000000);

        out_expected_occupany--;

        switch(just_finished_idx) {
            case 0:
                // SET_REG(x3, 0xe0000000);
                RELEASE(A);
                prev->a_empty = 1;
                trig_dma_in(0);
                break;
            case 1:
                // SET_REG(x3, 0xe0000001);
                RELEASE(B);
                prev->b_empty = 1;
                trig_dma_in(1);
                break;
            default:
                break;
        }
    }
}

#ifdef BLINK_WHILE_FORWARD_RATE
int blink_counter = 0;
void forward_blink(void) {
    blink_counter++;

    if( blink_counter == BLINK_WHILE_FORWARD_RATE ) {
        CSR_CLEAR_BITS(GPIO_WRITE, LED_GPIO_BIT);
    }

    if( blink_counter == (BLINK_WHILE_FORWARD_RATE + (BLINK_WHILE_FORWARD_RATE*3)) ) {
        CSR_SET_BITS(GPIO_WRITE, LED_GPIO_BIT);
        blink_counter = 0;
    }
}
#endif

#ifdef DO_FORWARD_BACKPRESSURE
unsigned int mod_stall;
unsigned int mod_size;
unsigned int stall_max = 200;
unsigned int stall_min = 1;
// unsigned int size_max = 600;
// unsigned int size_min = 15;
#endif

void no_exit_stream(void) {
  // unsigned int mover_working_on = 0;
  CIRBUF_POW2_RUNTIME_INITIALIZE(__dma_schedule_in);
  CIRBUF_POW2_RUNTIME_INITIALIZE(__dma_schedule_out);

  CSR_WRITE(DMA_0_FLUSH_SCHEDULE, 0);
  CSR_WRITE(DMA_1_FLUSH_SCHEDULE, 0);
  CSR_WRITE(DMA_2_FLUSH_SCHEDULE, 0);

  CSR_WRITE(GPIO_WRITE_EN, LED_GPIO_BIT);
  // CSR_SET_BITS(GPIO_WRITE, LED_GPIO_BIT);
  CSR_CLEAR_BITS(GPIO_WRITE, LED_GPIO_BIT);

  // ring_block_send_eth(mover_working_on);
  // mover_working_on = FLIP_BIT(mover_working_on);
  // ring_block_send_eth(mover_working_on);
  // mover_working_on = FLIP_BIT(mover_working_on);
  // ring_block_send_eth(mover_working_on);
  // mover_working_on = FLIP_BIT(mover_working_on);
  // ring_block_send_eth(mover_working_on);

  dma_in_dma_ptr = VMEM_DMA_ADDRESS(stream_buffer);

  pipeline_work_initialize(work_in,  0, 0);
  pipeline_work_initialize(work_out, 0, 0);


  trig_dma_in(0);
  trig_dma_in(1);

  Ringbus ringbus;

  // unsigned int forwards = 0;

  ring_register_callback(&check_bootload_status, CHECK_BOOTLOAD_CMD);

#ifdef DO_FORWARD_BACKPRESSURE
#ifdef MOD_STALL_UPPER
  mod_stall = MOD_STALL_UPPER;
#else
  mod_stall = (simple_random() % (stall_max - stall_min)) + stall_min;
#endif
  // mod_size = (simple_random() % (size_max - size_min)) + size_min;
  unsigned stall_amount;
  unsigned luck;
#endif

  while(1) {

      pet_in();
      pet_out();

#ifdef BLINK_WHILE_FORWARD_RATE
      forward_blink();
#endif

      #ifdef RUN_LOOP_CALLBACK
      RUN_LOOP_CALLBACK
      #endif


      check_ring(&ringbus);

#ifdef DO_FORWARD_BACKPRESSURE
      luck = simple_random() % 10;

      if( luck < DO_FORWARD_LUCK_CHANCE ) {
          for (unsigned int i = 0; i < DO_FORWARD_LUCK_STALL; i++) {
                STALL(1);
          }
      }
#endif

  }

}

#endif
