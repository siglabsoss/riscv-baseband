#ifndef __VMEM_H__
#define __VMEM_H__


#define VECTOR_MEM_START (0x40000)

#define MEM_MAP_START (0x80000)
#define MEM_MAP_BUMP (0x400)

#define vector_memory ((volatile unsigned int *) VECTOR_MEM_START)

// we have 4 byte words, and 16 vector slices, so memory must be 4*16=64 aligned
#define GCC_ALIGNED_64 __attribute__ ((aligned (64)))

#define VMEM_SECTION_OFFSET __attribute__((section(".vmem_offset.data"))) GCC_ALIGNED_64
#define VMEM_SECTION_CFG __attribute__((section(".vmem_cfg.data"))) GCC_ALIGNED_64
#define VMEM_SECTION __attribute__((section(".vmem_constant.data"))) GCC_ALIGNED_64


#define VMEM_SECTION_OFFSET_WORDS(x) \
VMEM_SECTION_OFFSET unsigned int __vmem_section_offset_words[x] = {}; \
unsigned int vmem_load_offset = x;

// this takes an address of a veriable declared with VMEM_SECTION
// and converts it to an address that vector slice can load
// we need to subtract the start of the vector memory
// from there we divide by 4 to convert from byte address to word address
// from there we divide by 16 for the number of vector slices
// this is a total divide of 64 or 6 bit shift.

// these should have been named _ROW_ originaly
//
#define VMEM_ADDRESS(x) VMEM_ROW_ADDRESS(x)
#define VMEM_ROW_ADDRESS(x) ((((unsigned int)(x))-VECTOR_MEM_START)>>6)

#define REVERSE_VMEM_ADDRESS(x) REVERSE_VMEM_ROW_ADDRESS(x)
#define REVERSE_VMEM_ROW_ADDRESS(x) ((unsigned int *)((((unsigned int)(x)) << 6) + VECTOR_MEM_START))

// takes an riscv address, and converts it into a DMA address
#define VMEM_DMA_ADDRESS(x) ((((unsigned int)(x))-VECTOR_MEM_START)>>2)

#define REVERSE_VMEM_DMA_ADDRESS(x) ((unsigned int *)(((unsigned int)((x)<<2))+VECTOR_MEM_START))

#define VMEM_DMA_ADDRESS_TO_ROW(x) (((unsigned int)(x))>>4)
#define VMEM_ROW_ADDRESS_TO_DMA(x) (((unsigned int)(x))<<4)


#endif
