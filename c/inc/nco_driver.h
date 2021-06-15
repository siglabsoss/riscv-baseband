#ifndef NCO_BUFFER_SIZE
#define NCO_BUFFER_SIZE  (1280)
#endif

#include "vmem.h"
#include "csr_control.h"
#include "circular_buffer_pow2.h"

#define NCO_BUFFER_COUNT (2)
#define NCO_CIRCULAR_BUFFER_SIZE (2)
#define NCO_MAX_OCCUPANCY (2)

VMEM_SECTION unsigned int nco_buf[NCO_BUFFER_SIZE*NCO_BUFFER_COUNT];

unsigned int* nco_cpu[NCO_BUFFER_COUNT];


circular_buf_pow2_t __nco_for_schedule =
CIRBUF_POW2_STATIC_CONSTRUCTOR(__nco_for_schedule, NCO_CIRCULAR_BUFFER_SIZE);
circular_buf_pow2_t* nco_for_schedule = &__nco_for_schedule;
//
// circular_buf_pow2_t __nco_for_use =
// CIRBUF_POW2_STATIC_CONSTRUCTOR(__nco_for_use, NCO_CIRCULAR_BUFFER_SIZE);
// circular_buf_pow2_t* nco_for_use = &__nco_for_use;

circular_buf_pow2_t __nco_for_next =
CIRBUF_POW2_STATIC_CONSTRUCTOR(__nco_for_next, NCO_CIRCULAR_BUFFER_SIZE);
circular_buf_pow2_t* nco_for_next = &__nco_for_next;






void init_nco(void)
{

    CIRBUF_POW2_RUNTIME_INITIALIZE(__nco_for_schedule);
    // CIRBUF_POW2_RUNTIME_INITIALIZE(__nco_for_use);
    CIRBUF_POW2_RUNTIME_INITIALIZE(__nco_for_next);

    for(int i = 0; i < NCO_BUFFER_COUNT; i++) {
        
        nco_cpu[i] = nco_buf + NCO_BUFFER_SIZE*i;
        circular_buf2_put(nco_for_next, i);
    }

    
}

unsigned int nco_schedule_next_cfo(const unsigned int _nco_length, const unsigned int _init_angle, const unsigned int _delta_angle) {

  unsigned int nco_occupancy;
  CSR_READ(DMA_2_SCHEDULE_OCCUPANCY, nco_occupancy);

  
  
  if (nco_occupancy >= NCO_MAX_OCCUPANCY) {

    return 0;

  }
  else
  {
    int error;
    unsigned int nco_next;
    error = circular_buf2_get(nco_for_next, &nco_next);
    
    if(error!=-1)
    {   
        int error1;
        error1 = circular_buf2_put(nco_for_schedule, nco_next);

       

        if(error1!=-1)
        {             
            CSR_WRITE(NCO_START_ANGLE, _init_angle);
            CSR_WRITE(NCO_LENGTH, _nco_length);
            CSR_WRITE(NCO_DELTA, _delta_angle); 
            CSR_WRITE_ZERO(NCO_PUSH_SCHEDULE);

            CSR_WRITE(DMA_2_START_ADDR, VMEM_DMA_ADDRESS(nco_cpu[nco_next]));
            CSR_WRITE(DMA_2_LENGTH, _nco_length);
            CSR_WRITE(DMA_2_TIMER_VAL, 0xffffffff);  // start right away
            CSR_WRITE_ZERO(DMA_2_PUSH_SCHEDULE);

            return 1;

        }
        else
        {
            return 0;
        }
        
    }
    else{
        return 0;
    }

  }

 
}


int nco_ready(unsigned* cpu_pointer) {

    
    unsigned int nco_occupancy;
    CSR_READ(DMA_2_SCHEDULE_OCCUPANCY, nco_occupancy);

    const int expected_nco_occupancy = circular_buf2_occupancy(nco_for_schedule);
    const int occupancy_diff = expected_nco_occupancy - (int)nco_occupancy;
    
    if (occupancy_diff > 0) 
     {
        int error;
        unsigned int completed_nco;
        error = circular_buf2_get(nco_for_schedule, &completed_nco);
        (void)error;
         *cpu_pointer = (unsigned int)nco_cpu[completed_nco];
        return completed_nco;
     
    }
    else
    {
        return -1;
    }
}




void nco_done(unsigned ready) {

    int error;
    (void)error;
    error = circular_buf2_put(nco_for_next, ready);


}
