#include "dma.h"
#include "csr_control.h" 
#include "sig_utils.h"

#define DMA_NOW (0xffffffff)

void dma_in_set(int start_address, int dma_len) {
	// set up input buffer to receive INPUT_BUF_START size
	CSR_WRITE(DMA_0_START_ADDR, start_address);
	CSR_WRITE(DMA_0_LENGTH, dma_len);
	CSR_WRITE(DMA_0_TIMER_VAL, DMA_NOW); // start right away
	CSR_WRITE_ZERO(DMA_0_PUSH_SCHEDULE);
}

void dma_out_set(int start_address, int dma_len) { 
	// set up input buffer to receive INPUT_BUF_START size
	CSR_WRITE(DMA_1_START_ADDR, start_address);
	CSR_WRITE(DMA_1_LENGTH, dma_len);
	CSR_WRITE(DMA_1_TIMER_VAL, DMA_NOW);  // start right away
    CSR_WRITE_ZERO(SLICER);
    CSR_WRITE_ZERO(DMA_1_PUSH_SCHEDULE);
}

int dma_in_check(int timeout){
	int helper;
	if (timeout == 0){
		while(1){
		    CSR_READ(mip, helper);

		    // clear because we are reading occupancy now
		    if(helper & DMA_0_ENABLE_BIT) {
		      CSR_WRITE_ZERO(DMA_0_INTERRUPT_CLEAR);
		      return TRUE;
		    }
		  }
	} else {
	  	for(int i = 1; i <= timeout; i++) {
		    CSR_READ(mip, helper);

		    // clear because we are reading occupancy now
		    if(helper & DMA_0_ENABLE_BIT) {
		      CSR_WRITE_ZERO(DMA_0_INTERRUPT_CLEAR);
		      return i;
		    }
		}
		return FALSE;

	}

}

int dma_out_check(int timeout){
	int helper;
	if (timeout == 0){  //block forever
	  	while(1) {
		    CSR_READ(mip, helper);

		    // clear because we are reading occupancy now
		    if(helper & DMA_1_ENABLE_BIT) {
		      CSR_WRITE_ZERO(DMA_1_INTERRUPT_CLEAR);
		      return TRUE;
		    }
		 }		
	} else {
	  	for(int i = 1; i <= timeout; i++) {
		    CSR_READ(mip, helper);

		    // clear because we are reading occupancy now
		    if(helper & DMA_1_ENABLE_BIT) {
		      CSR_WRITE_ZERO(DMA_1_INTERRUPT_CLEAR);
		      return i;
		    }
		}
		return FALSE;
	}

}

// output dma, same as out,set but will wait first
void dma_block_send(unsigned int dma_ptr, unsigned int word_count) {
  unsigned int occupancy;
  while(1) {
    CSR_READ(DMA_1_SCHEDULE_OCCUPANCY, occupancy);
    if( occupancy < DMA_1_SCHEDULE_DEPTH) {
      break;
    }
  }
  CSR_WRITE(DMA_1_START_ADDR, dma_ptr);
  CSR_WRITE(DMA_1_LENGTH, word_count);
  CSR_WRITE(DMA_1_TIMER_VAL, 0xffffffff);  // start right away
  CSR_WRITE_ZERO(SLICER);
  CSR_WRITE_ZERO(DMA_1_PUSH_SCHEDULE);
}

// do not pass limit more than 16
void dma_block_send_limit(const unsigned dma_ptr, const unsigned word_count, const unsigned limit) {
    unsigned int occupancy;
    while(1) {
        CSR_READ(DMA_1_SCHEDULE_OCCUPANCY, occupancy);
        if( occupancy < limit) {
            break;
        }
    }
    CSR_WRITE(DMA_1_START_ADDR, dma_ptr);
    CSR_WRITE(DMA_1_LENGTH, word_count);
    CSR_WRITE(DMA_1_TIMER_VAL, 0xffffffff);  // start right away
    CSR_WRITE_ZERO(SLICER);
    CSR_WRITE_ZERO(DMA_1_PUSH_SCHEDULE);
}

// output dma, same as out,set but will wait first
void dma_block_send_finalized(unsigned int dma_ptr, unsigned int word_count, unsigned finalized) {
  unsigned int occupancy;
  while(1) {
    CSR_READ(DMA_1_SCHEDULE_OCCUPANCY, occupancy);
    if( occupancy < DMA_1_SCHEDULE_DEPTH) {
      break;
    }
  }
  CSR_WRITE(DMA_1_START_ADDR, dma_ptr);
  CSR_WRITE(DMA_1_LENGTH, word_count);
  CSR_WRITE(DMA_1_TIMER_VAL, 0xffffffff);  // start right away
  CSR_WRITE_ZERO(SLICER);
  if(finalized) {
      CSR_WRITE(DMA_1_LAST_RTL, 1);
  }
  CSR_WRITE_ZERO(DMA_1_PUSH_SCHEDULE);
}

void dma_send_finalized(unsigned int dma_ptr, unsigned int word_count, unsigned finalized) {
  CSR_WRITE(DMA_1_START_ADDR, dma_ptr);
  CSR_WRITE(DMA_1_LENGTH, word_count);
  CSR_WRITE(DMA_1_TIMER_VAL, 0xffffffff);  // start right away
  CSR_WRITE_ZERO(SLICER);
  if(finalized) {
      CSR_WRITE(DMA_1_LAST_RTL, 1);
  }
  CSR_WRITE_ZERO(DMA_1_PUSH_SCHEDULE);
}


void dma_block_send_reverse(unsigned int dma_ptr, unsigned int word_count) {
  unsigned int occupancy;
  while(1) {
    CSR_READ(DMA_1_SCHEDULE_OCCUPANCY, occupancy);
    if( occupancy < DMA_1_SCHEDULE_DEPTH) {
      break;
    }
  }
  CSR_WRITE(DMA_1_START_ADDR, dma_ptr);
  CSR_WRITE(DMA_1_LENGTH, word_count);
  CSR_WRITE(DMA_1_TIMER_VAL, 0xffffffff);  // start right away
  CSR_WRITE_ZERO(SLICER);
  CSR_WRITE(DMA_1_REVERSE, 1);
  CSR_WRITE_ZERO(DMA_1_PUSH_SCHEDULE);
  CSR_WRITE(DMA_1_REVERSE, 0);
  
}

void dma_block_send_timer(unsigned int dma_ptr, unsigned int word_count, unsigned timer_val) {
  unsigned int occupancy;
  while(1) {
    CSR_READ(DMA_1_SCHEDULE_OCCUPANCY, occupancy);
    if( occupancy < DMA_1_SCHEDULE_DEPTH) {
      break;
    }
  }
  CSR_WRITE(DMA_1_START_ADDR, dma_ptr);
  CSR_WRITE(DMA_1_LENGTH, word_count);
  CSR_WRITE(DMA_1_TIMER_VAL, timer_val);
  CSR_WRITE_ZERO(SLICER);
  CSR_WRITE_ZERO(DMA_1_PUSH_SCHEDULE);
}


// input dma
void dma_block_get(unsigned int dma_ptr, unsigned int word_count) {
  unsigned int occupancy;
  while(1) {
    CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, occupancy);
    if( occupancy < DMA_0_SCHEDULE_DEPTH) {
      break;
    }
  }
  CSR_WRITE(DMA_0_START_ADDR, dma_ptr);
  CSR_WRITE(DMA_0_LENGTH, word_count);
  CSR_WRITE(DMA_0_TIMER_VAL, 0xffffffff);  // start right away
  CSR_WRITE_ZERO(DMA_0_PUSH_SCHEDULE);
}

void dma_run_till_last(void) {
    unsigned int occupancy;
    while(1) {
        CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, occupancy);
        if( occupancy < DMA_0_SCHEDULE_DEPTH) {
            break;
        }
    }
    CSR_WRITE(DMA_0_LAST_RTL, 0x1);
    CSR_WRITE_ZERO(DMA_0_PUSH_SCHEDULE);
}

// WARNING this will reset any in-progress input DMA's you have
// this is best run at the beginning of a FPGA's life
// this fn schedules as many input dma's as possible, over and over
// on the junk memory
// it will always run until the run_time (measured in TIMER_VALUE)
// even if no input dma's come, or they are STILL coming
void flush_input_dma(unsigned int dma_junk, unsigned int junk_len, unsigned int run_time)
{
    CSR_WRITE_ZERO(DMA_0_FLUSH_SCHEDULE);

    unsigned int then;
    unsigned int now;
    unsigned int occupancy;
    CSR_READ(TIMER_VALUE, then);

    do {
        CSR_READ(TIMER_VALUE, now);

        CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, occupancy);
        if( occupancy < DMA_0_SCHEDULE_DEPTH) {
            dma_in_set(dma_junk, junk_len);
        }
    } while(now-then < (run_time) );

    CSR_WRITE_ZERO(DMA_0_FLUSH_SCHEDULE);
}
