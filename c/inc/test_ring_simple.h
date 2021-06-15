#ifndef __TEST_RING_SIMPLE_H__
#define __TEST_RING_SIMPLE_H__



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
#include "random.h"
#include "ringbus2_pre.h"
#include "ringbus2_post.h"


unsigned int got_seed = 0;

// TB sends us a seed, so we apply it
void get_seed_cb(unsigned int data) {
  simple_random_seed(data);
  ring_block_send_eth( (OUR_RING_ENUM<<16) | data);
  // ring_block_send_eth( OUR_RING_ENUM );
  got_seed = 1;
}


int main(void)
{
  // unsigned int rtn;
  Ringbus ringbus;

  // register callback (Reuse this cmd value)
  ring_register_callback(&get_seed_cb, EDGE_EDGE_IN);

  // unsigned int vmem_input_dma_ptr = VMEM_DMA_ADDRESS(vmem_input);

  // setup vmalloc
  // init_VMalloc(&mgr);

  CSR_WRITE(DMA_0_FLUSH_SCHEDULE, 0);
  CSR_WRITE(DMA_1_FLUSH_SCHEDULE, 0);

  for(unsigned int j = 0; j < 7000; j++) {
         asm("nop");
   }


  ring_block_send_eth(0xdead0000 | OUR_RING_ENUM); // boot

  while(got_seed == 0) {
    check_ring(&ringbus);
  }

}



#endif
