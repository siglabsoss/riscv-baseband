#include "coarse_sync.h"
#include "csr_control.h"
#include "vmem.h"
#include "atan.h"

// #include "flush_config_word.h"


void trig_dma_in_cs(unsigned int start_address, unsigned int timer_start, unsigned int DMA_size) 
{

    CSR_WRITE(DMA_0_START_ADDR, start_address);
    CSR_WRITE(DMA_0_LENGTH, DMA_size);
    CSR_WRITE(DMA_0_TIMER_VAL, timer_start); // start right away
    CSR_WRITE(DMA_0_PUSH_SCHEDULE, 0);   // any value

}

void xbb_cfo_estimation(CFO_Results *CFO_results, unsigned int cfg_conj_multi_location, unsigned int cfg_cmul_rx4_location, unsigned int input_conj_multi_location_0, unsigned int input_conj_multi_location_1, unsigned int all_one_location, unsigned int output_conj_multi_location, unsigned int row_num_cfo, unsigned int bank_address_onetone_calculation_location, unsigned int permutation_address_onetone_calculation_location)
{
  xbb_conj_multi_add(cfg_conj_multi_location, cfg_cmul_rx4_location, input_conj_multi_location_0, input_conj_multi_location_1, all_one_location, output_conj_multi_location, row_num_cfo, bank_address_onetone_calculation_location, permutation_address_onetone_calculation_location);

  CFO_results->cfo_complex=vector_memory[(output_conj_multi_location+9)*16];

  CFO_results->cfo_angle = fxpt_atan2(((CFO_results->cfo_complex>>16)&0xffff), (CFO_results->cfo_complex & 0xffff));

  if(CFO_results->cfo_angle>=0x8000)
    CFO_results->cfo_estimate = (((0x10000-CFO_results->cfo_angle)*32000)>>16);
  else
    CFO_results->cfo_estimate = (((CFO_results->cfo_angle)*32000)>>16)*(-1);

}

void xbb_conj_multi_add(
    unsigned int cfg_conj_multi_location,
    unsigned int cfg_cmul_rx4_location,
    unsigned int input_conj_multi_location_0,
    unsigned int input_conj_multi_location_1,
    unsigned int all_one_location,
    unsigned int output_conj_multi_location,
    unsigned int row_num_cfo,
    unsigned int bank_address_onetone_calculation_location,
    unsigned int permutation_address_onetone_calculation_location)
{

    //stage -1  --- conjugate complex multiplication
    MVXV_KNOP(V0, cfg_conj_multi_location);
    VNOP_LK14(V0);

    // FLUSH_CONFIG_WORD(V15);


    MVXV_KNOP(V1, input_conj_multi_location_0);
    MVXV_KNOP(V2, input_conj_multi_location_1);
    MVXV_KNOP(V3, output_conj_multi_location);
    MVXV_KNOP(V4, 1);

    for(unsigned index_row=0; index_row<row_num_cfo;index_row++)
    {
        ADD_LK8(V1, V1, V4, 0);
        ADD_LK9(V2, V2, V4, 0);
    }

    for(unsigned index_row=0; index_row<row_num_cfo;index_row++)
    {
        ADD_SK1(V3, V3, V4, 0);
    }  

    //stage 0
    MVXV_KNOP(V0, cfg_cmul_rx4_location);
    VNOP_LK14(V0);

    // FLUSH_CONFIG_WORD(V15);
    
    MVXV_KNOP(V1, all_one_location);
    MVXV_KNOP(V2, output_conj_multi_location);
    MVXV_KNOP(V3, output_conj_multi_location+4);
    MVXV_KNOP(V4, 1);
    MVXV_KNOP(V5, 1-(1<<12)); 

    for(unsigned index_row=0; index_row<row_num_cfo;index_row++)
    {
        VNOP_LK8(V1);
        ADD_LK9(V2, V2, V4, 0);
    }

    for(unsigned index_row=0; index_row<row_num_cfo;index_row++)
    {
        ADD_SK1(V3, V3, V5, 0);
    }  

    //stage 1
    MVXV_KNOP(V1, all_one_location);
    MVXV_KNOP(V2, output_conj_multi_location+4);
    MVXV_KNOP(V3, output_conj_multi_location+8);

    MVXV_KNOP(V7, bank_address_onetone_calculation_location);
    VNOP_LK15(V7);
    MVK15V_KNOP(V7,0);
    ADD_KNOP(V2, V2, V7, 0);
   
    VNOP_LK8(V1);
    VNOP_LK9(V2);
    VNOP_SK1(V3);

    //stage 2

    MVXV_KNOP(V1, all_one_location);
    MVXV_KNOP(V2, output_conj_multi_location+8);
    MVXV_KNOP(V3, output_conj_multi_location+9);
   
    MVXV_KNOP(V12, permutation_address_onetone_calculation_location);
    VNOP_LK15(V12);
    MVK15V_KNOP(V12,0);
    ADD_KNOP(V2, V12, V2, 0);
   
    VNOP_LK8(V1);
    VNOP_LK9(V2);
    VNOP_SK1(V3);

    STALL(10);
    STALL(10);
    STALL(10);
    STALL(10);
    STALL(10);

}
 

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
///
/// 1024 long vector multiply which allows you to specify config word
///
/// @param cfg_conj_multi_location
/// @param input_conj_multi_location_0  input 0, row pointer
/// @param input_conj_multi_location_1  input 1, row pointer
/// @param output_conj_multi_location   output, row pointer
void __attribute__((always_inline)) xbb_conj_multi(
    unsigned int cfg_conj_multi_location,
    unsigned int input_conj_multi_location_0,
    unsigned int input_conj_multi_location_1,
    unsigned int output_conj_multi_location)
{
   unsigned int start_clk, end_clk;
   CSR_READ(TIMER_VALUE, start_clk);

   MVXV_KNOP(V0, cfg_conj_multi_location);
   VNOP_LK14(V0);

   // FLUSH_CONFIG_WORD(V15);

   MVXV_KNOP(V1, input_conj_multi_location_0);
   MVXV_KNOP(V2, input_conj_multi_location_1);
   MVXV_KNOP(V3, output_conj_multi_location);
   MVXV_KNOP(V4, 1);
   
   int latency = 4;

   for(int index = 0; index<latency; index++)
   {
     ADD_LK8(V1, V1, V4, 0);
     ADD_LK9(V2, V2, V4, 0);
   }

   for(int index = 0; index<64-latency; index++)
   {

     ADD_LK8(V1, V1, V4, 0);
     ADD_LK9(V2, V2, V4, 0);
     ADD_SK1(V3, V3, V4, 0);
    
   }

   for(int index = 0; index<latency; index++)
   {
      ADD_SK1(V3, V3, V4, 0);
   }


   STALL(10);
   STALL(10);
   STALL(10);

   CSR_READ(TIMER_VALUE, end_clk);

   // ring_block_send_eth(end_clk-start_clk);
}

#pragma GCC diagnostic pop



///
/// 1024 long vector multiply which allows you to specify config word
///
/// @param cfg_conj_multi_location
/// @param input_conj_multi_location_0  input 0, row pointer
/// @param input_conj_multi_location_1  input 1, row pointer
/// @param output_conj_multi_location   output, row pointer
void xbb_add(
    unsigned int cfg_data,
    unsigned int input_0,
    unsigned int input_1,
    unsigned int output)
{
   // unsigned int start_clk, end_clk;
   // CSR_READ(TIMER_VALUE, start_clk);

   MVXV_KNOP(V0, cfg_data);
   VNOP_LK14(V0);

   // FLUSH_CONFIG_WORD(V15);

   MVXV_KNOP(V1, input_0);
   MVXV_KNOP(V2, input_1);
   MVXV_KNOP(V3, output);
   MVXV_KNOP(V4, 1);
   
   int latency = 4;

   for(int index = 0; index<latency; index++)
   {
     ADD_LK8(V1, V1, V4, 0);
     ADD_LK9(V2, V2, V4, 0);
   }

   for(int index = 0; index<64-latency; index++)
   {

     ADD_LK8(V1, V1, V4, 0);
     ADD_LK9(V2, V2, V4, 0);
     ADD_SK1(V3, V3, V4, 0);
    
   }

   for(int index = 0; index<latency; index++)
   {
      ADD_SK1(V3, V3, V4, 0);
   }


   STALL(10);
   STALL(10);
   STALL(10);

   // CSR_READ(TIMER_VALUE, end_clk);

   // ring_block_send_eth(end_clk-start_clk);
}





void xbb_conj_multi_const(unsigned int cfg_conj_multi_location, unsigned int input_conj_multi_location_0, unsigned int input_conj_multi_location_1, unsigned int output_conj_multi_location)
{
   unsigned int start_clk, end_clk;
   CSR_READ(TIMER_VALUE, start_clk);

   MVXV_KNOP(V0, cfg_conj_multi_location);
   VNOP_LK14(V0);

   // FLUSH_CONFIG_WORD(V15);

   MVXV_KNOP(V1, input_conj_multi_location_0);
   MVXV_KNOP(V2, input_conj_multi_location_1);
   MVXV_KNOP(V3, output_conj_multi_location);
   MVXV_KNOP(V4, 1);
   
   int latency = 4;

   for(int index = 0; index<latency; index++)
   {
     ADD_LK8(V1, V1, V4, 0);
     VNOP_LK9(V2);
   }

   for(int index = 0; index<64-latency; index++)
   {

     ADD_LK8(V1, V1, V4, 0);
     VNOP_LK9(V2);
     ADD_SK1(V3, V3, V4, 0);
    
   }

   for(int index = 0; index<latency; index++)
   {
      ADD_SK1(V3, V3, V4, 0);
   }


   STALL(10);
   STALL(10);
   STALL(10);

   CSR_READ(TIMER_VALUE, end_clk);

   // ring_block_send_eth(end_clk-start_clk);
}


void xbb_conj_multi_80(unsigned int cfg_conj_multi_location, unsigned int input_conj_multi_location_0, unsigned int input_conj_multi_location_1, unsigned int output_conj_multi_location)
{
   unsigned int start_clk, end_clk;
   CSR_READ(TIMER_VALUE, start_clk);

   MVXV_KNOP(V0, cfg_conj_multi_location);
   VNOP_LK14(V0);


   MVXV_KNOP(V1, input_conj_multi_location_0);
   MVXV_KNOP(V2, input_conj_multi_location_1);
   MVXV_KNOP(V3, output_conj_multi_location);
   MVXV_KNOP(V4, 1);
   
   int latency = 4;

   for(int index = 0; index<latency; index++)
   {
     ADD_LK8(V1, V1, V4, 0);
     ADD_LK9(V2, V2, V4, 0);
   }

   for(int index = 0; index<80-latency; index++)
   {

     ADD_LK8(V1, V1, V4, 0);
     ADD_LK9(V2, V2, V4, 0);
     ADD_SK1(V3, V3, V4, 0);
    
   }

   for(int index = 0; index<latency; index++)
   {
      ADD_SK1(V3, V3, V4, 0);
   }


   STALL(10);
   STALL(10);
   STALL(10);
   STALL(10);
   STALL(10);

   CSR_READ(TIMER_VALUE, end_clk);

   // ring_block_send_eth(end_clk-start_clk);
}

void xbb_onetone_calculation(unsigned int cfg_onetone_calculation_location, unsigned int input_onetone_calculation_location, unsigned int exp_data_location, unsigned int output_onetone_calculation_location, unsigned int bank_address_onetone_calculation_location, unsigned int permutation_address_onetone_calculation_location, unsigned int all_one_location)
{
   
   unsigned int start_clk, end_clk;
   CSR_READ(TIMER_VALUE, start_clk);

   MVXV_KNOP(V0, cfg_onetone_calculation_location);
   VNOP_LK14(V0);

   // FLUSH_CONFIG_WORD(V15);

   /// stage 0
   MVXV_KNOP(V1, exp_data_location);
   MVXV_KNOP(V2, input_onetone_calculation_location);
   MVXV_KNOP(V3, output_onetone_calculation_location);
   MVXV_KNOP(V4, 1);
   MVXV_KNOP(V5, 1-(1<<12));
   
   int latency_0 = 4;
   
   for(int index=0; index<latency_0; index++)
   {
    ADD_LK8(V1, V1, V4, 0);
    ADD_LK9(V2, V2, V4, 0);
   }

   for(int index=0; index<64-latency_0; index++)
   {
    ADD_LK8(V1, V1, V4, 0);
    ADD_LK9(V2, V2, V4, 0);
    ADD_SK1(V3, V3, V5, 0);
   }

   for(int index=0; index<latency_0; index++)
   {
    ADD_SK1(V3, V3, V5, 0);
   }

   ///stage 1
   MVXV_KNOP(V1, all_one_location);
   MVXV_KNOP(V2, output_onetone_calculation_location);
   MVXV_KNOP(V3, output_onetone_calculation_location);
   MVXV_KNOP(V8, 4);
   MVXV_KNOP(V5, 1-(1<<12));
   
   MVXV_KNOP(V7, bank_address_onetone_calculation_location);
   VNOP_LK15(V7);
   MVK15V_KNOP(V7,0);
   ADD_KNOP(V2, V2, V7, 0);
   
   int latency_1=4;

   for(int index=0; index<latency_1; index++)
   {
    VNOP_LK8(V1);
    ADD_LK9(V2, V2, V8, 0);
   }

   for(int index=0;index<16-latency_1;index++)
   {
    VNOP_LK8(V1);
    ADD_LK9(V2, V2, V8, 0);
    ADD_SK1(V3, V3, V5, 0);
   }

   for(int index=0;index<latency_1;index++)
   {
    ADD_SK1(V3, V3, V5, 0);
   }

   ///stage 2
   MVXV_KNOP(V2, output_onetone_calculation_location);
   MVXV_KNOP(V3, output_onetone_calculation_location);
   MVXV_KNOP(V8, 4);
   MVXV_KNOP(V5, 1-(1<<12));

   ADD_KNOP(V2, V2, V7, 0);
   
   for(int index=0; index<4; index++)
   {
    VNOP_LK8(V1);
    ADD_LK9(V2, V2, V8, 0);
   }

   for(int index=0; index<4; index++)
   {
    ADD_SK1(V3, V3, V5, 0);
   }

   ///stage 3
   MVXV_KNOP(V2, output_onetone_calculation_location);
   MVXV_KNOP(V3, output_onetone_calculation_location);
   MVXV_KNOP(V8, 4);
   MVXV_KNOP(V5, 1-(1<<12));

   ADD_KNOP(V2, V2, V7, 0);

   VNOP_LK8(V1);
   ADD_LK9(V2, V2, V8, 0);
   ADD_SK1(V3, V3, V5, 0);

   ///stage 4
   MVXV_KNOP(V2, output_onetone_calculation_location);
   MVXV_KNOP(V3, output_onetone_calculation_location);
   
   MVXV_KNOP(V12, permutation_address_onetone_calculation_location);
   VNOP_LK15(V12);
   MVK15V_KNOP(V12,0);
   ADD_KNOP(V2, V12, V2, 0);
   
   VNOP_LK8(V1);
   VNOP_LK9(V2);
   VNOP_SK1(V3);
   

   STALL(10);
   STALL(10);
   STALL(10);


   CSR_READ(TIMER_VALUE, end_clk);

   // ring_block_send_eth(end_clk-start_clk);

}

int result_check_tolerance(unsigned int benchmark_start_row, unsigned int result_start_row, unsigned int total_sample, int diff_th)
{
  
  int result0, result1;
  int flag=1;
  int diff_real;

  for(unsigned index=0; index<total_sample;index++)
  {
    // ring_block_send_eth(index);
    result0=vector_memory[benchmark_start_row*16+index];
    STALL(10);
    STALL(10);
    STALL(10);
    

    
    
    result1=vector_memory[(result_start_row+index)*16];
    STALL(10);
    STALL(10);
    STALL(10);

    

    diff_real=result1-result0;

    


    if (diff_real>640)
        diff_real=diff_real-1280;
    else if(diff_real<(640*(-1)))
        diff_real=diff_real+1280;

    // ring_block_send_eth(diff_real);


    


    if((diff_real>diff_th)||(diff_real<(-1*diff_th)))
    {
      flag=0;
      break;
    }
  }

  return flag;
}
