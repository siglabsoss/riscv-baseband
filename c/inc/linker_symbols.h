#ifndef __LINKER_SYMBOLS_H__
#define __LINKER_SYMBOLS_H__

///////////////////////
//
// Hand copied list from linker script
// 
// Note you MUST put & before names here in order to get their value
// for instance
//
//   unsigned int foo = (unsigned int) &__imem_size ;
//
// see https://stackoverflow.com/a/40392131/836450


extern const volatile unsigned int START_LOC;
extern const volatile unsigned int PASS_FAIL_LEN;
extern const volatile unsigned int BOOT_LEN;
extern const volatile unsigned int __imem_size;
extern const volatile unsigned int __stack_size;
extern const volatile unsigned int DMEM_LEN;
extern const volatile unsigned int IMEM_LEN;
extern const volatile unsigned int __bss_vma_start;
extern const volatile unsigned int __dedicated_mem_end;
extern const volatile unsigned int __bss_vma_end;
extern const volatile unsigned int __sp_start;
extern const volatile unsigned int __pass_fail_0;
extern const volatile unsigned int __pass_fail_1;
extern const volatile unsigned int V_MEM_LEN;
extern const volatile unsigned int V_MEM_START;
extern const volatile unsigned int __vmem_start;
extern const volatile unsigned int __vmem_end;

#endif