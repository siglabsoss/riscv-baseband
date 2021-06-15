// this file is included by all fpgas allowing a bootload on any of them with
// the same code

#ifndef __VERIFY_FFT_COMMON_H__
#define __VERIFY_FFT_COMMON_H__

#include "flush_config_word_data.h"
#include "flush_config_word.h"
// includes a lot of constants
#define FFT_1024_INCLUDE_VERIFICATION
#include "fft_1024_3914.h"








// declare as global
VMalloc mgr;


// #define VECTOR_REPORT_ADDRESS 0x13400

void report_test_results(unsigned int data)
{
  unsigned int occupancy;

  while(1)
  {
   CSR_READ(RINGBUS_SCHEDULE_OCCUPANCY, occupancy);
   if(occupancy < RINGBUS_SCHEDULE_DEPTH)
   {
    break;
   }
  }

  CSR_WRITE(RINGBUS_WRITE_ADDR, RING_ADDR_PC);
  CSR_WRITE(RINGBUS_WRITE_DATA, data);
  CSR_WRITE(RINGBUS_WRITE_EN, 0);
}


// unsigned int xorshift32(unsigned int state*, unsigned int len)
unsigned int simple_hash(unsigned int *state, unsigned int len)
{
  /* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
  unsigned int hash = 0;
  for(unsigned int i = 0; i < len; i++) {
    hash += state[i];
    hash ^= hash << 13;
    hash ^= hash >> 17;
    hash ^= hash << 5;
  }
  return hash;
}


// test if the lib passes all 3 tests
void test1(void) {
  init_VMalloc(&mgr);

  if( VMALLOC_CHUNK_SIZE != 4096) {
    while(1){}; // if stuck here vmalloc has changed
  }


  // has temp 0,1,2,3
  // unsigned int tmp_row0 = VMEM_ROW_ADDRESS(vmalloc_single(&mgr));
  // unsigned int tmp_row1 = VMEM_ROW_ADDRESS(vmalloc_single(&mgr));
  // unsigned int tmp_row2 = VMEM_ROW_ADDRESS(vmalloc_single(&mgr));
  // unsigned int tmp_row3 = VMEM_ROW_ADDRESS(vmalloc_single(&mgr));

  unsigned int output_row1 = VMEM_ROW_ADDRESS(vmalloc_single(&mgr));
  unsigned int output_row2 = VMEM_ROW_ADDRESS(vmalloc_single(&mgr));
  unsigned int output_row3 = VMEM_ROW_ADDRESS(vmalloc_single(&mgr));

  unsigned int* input_ptr1 = vmalloc_single(&mgr);
  unsigned int* input_ptr2 = vmalloc_single(&mgr);
  unsigned int* input_ptr3 = vmalloc_single(&mgr);


  // this modifies the input, so we need to copy it before running
  for(unsigned int i = 0; i < 1024; i++) {
    input_ptr1[i] = first_input_fft_data[i];
  }

  // copy to next location
  for(unsigned int i = 0; i < 1024; i++) {
    input_ptr2[i] = second_input_fft_data[i];
  }

  for(unsigned int i = 0; i < 1024; i++) {
    input_ptr3[i] = third_input_fft_data[i];
  }

  report_test_results(0xf0000001); // test start

  unsigned int a,b;

  CSR_READ(TIMER_VALUE, a);


  fft1024_t first_plan = get_fft1024_plan(
    VMEM_ROW_ADDRESS(input_ptr1), // input
    // tmp_row0,  // tmp
    // tmp_row1,
    // tmp_row2,
    // tmp_row3,
    output_row1         // output
    );

  fft_1024_run(&first_plan);

  fft1024_t second_plan = get_fft1024_plan(
    VMEM_ROW_ADDRESS(input_ptr2), // input
    // tmp_row0,  // tmp
    // tmp_row1,
    // tmp_row2,
    // tmp_row3,
    output_row2         // output
    );

  fft_1024_run(&second_plan);



  fft1024_t third_plan = get_fft1024_plan(
    VMEM_ROW_ADDRESS(input_ptr3), // input
    // tmp_row0,  // tmp
    // tmp_row1,
    // tmp_row2,
    // tmp_row3,
    output_row3         // output
    );

  fft_1024_run(&third_plan);

  CSR_READ(TIMER_VALUE, b);

  report_test_results(b-a); // test end


  int fail = 0;

  int res_flag = fft_1024_result_check(
    VMEM_ROW_ADDRESS(first_expected_fft_results_4),
    output_row1,
    1024);

  if(res_flag != 1) {
    fail |= 1<<0;
  }



  res_flag = fft_1024_result_check(
    VMEM_ROW_ADDRESS(third_expected_fft_results_4),
    output_row3,
    1024);

  if(res_flag != 1) {
    fail |= 1<<1;
  }

  res_flag = fft_1024_result_check(
    VMEM_ROW_ADDRESS(second_expected_fft_results_4),
    output_row2,
    1024);

  if(res_flag != 1) {
    fail |= 1<<2;
  }

  if(fail == 0) {
    report_test_results(0xf0000003); // pass
  } else {
    report_test_results(0xf0000004); // fail
  }

}


int main(void)
{
  Ringbus ringbus;
  
  unsigned int all_results = 0;
  unsigned int test = 0;

  report_test_results(0xdeadbeef);
 
  // test = test0();
  // all_results |= (test==0)<<0;

  while(1) {
    test1();
    check_ring(&ringbus);
  }
  // all_results |= (test==0)<<1;

  // test = test2();
  // all_results |= (test==0)<<2;

  // test = test3();
  // all_results |= (test==0)<<3;

  // test = test4();
  // all_results |= (test==0)<<4;


  // report_test_results(test);
  // report_test_results(all_results);




  CSR_WRITE(GPIO_WRITE_EN, LED_GPIO_BIT);
  CSR_WRITE(GPIO_WRITE, LED_GPIO_BIT);

  while(1) {
    CSR_WRITE(GPIO_WRITE, LED_GPIO_BIT);
      check_ring(&ringbus);
    for(int j = 0; j < 100000; j++) {  // 10000
      check_ring(&ringbus);
    }
    CSR_WRITE(GPIO_WRITE, 0);
    for(int j = 0; j < 1000000; j++) {  // 1000000
      check_ring(&ringbus);
    }
  }


  return 0;
}








#endif