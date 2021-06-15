#include "nco_data.h"
#include "xbaseband.h"
#include "apb_bus.h"
#include "csr_control.h"
#include "pass_fail.h"
#include "dma.h"


void make_nco(
    const unsigned int nco_loc,
    const unsigned int nco_length,
    const unsigned int init_angle,
    const unsigned int delta_angle) {

  CSR_WRITE(NCO_START_ANGLE, init_angle);
  CSR_WRITE(NCO_LENGTH, nco_length);
  CSR_WRITE(NCO_DELTA, delta_angle); 
  CSR_WRITE_ZERO(NCO_PUSH_SCHEDULE);

  CSR_WRITE(DMA_2_START_ADDR, nco_loc);
  CSR_WRITE(DMA_2_LENGTH, nco_length);
  CSR_WRITE(DMA_2_TIMER_VAL, 0xffffffff);  // start right away
  CSR_WRITE_ZERO(DMA_2_PUSH_SCHEDULE);

  // unsigned int occupancy;
  // while(1) {
  //   CSR_READ(DMA_2_SCHEDULE_OCCUPANCY, occupancy);
  //   if(occupancy == 0) {//DMA_2_SCHEDULE_DEPTH
  //     break;
  //   }
  // }
}
