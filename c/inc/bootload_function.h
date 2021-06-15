#include <stdint.h>

// #define BOOTLOAD_FUNCTION_SECTION __attribute__((section(".bootload_fun.data"))) GCC_ALIGNED_64



#ifndef BLFUN_DATA_SIZE
#define BLFUN_DATA_SIZE (512)
#endif


// this allows us to pin the bootloader to a specific address
#define BLFUN_SECTION_ENTRY_FUNCTION __attribute__((section(".blfun.entry")))
#define BLFUN_SECTION __attribute__((section(".blfun")))
#define BLFUN_VARIABLE_SECTION __attribute__((section(".blfun.data")))



// BOOTLOAD_FUNCTION_SECTION uint8_t bl_function_data[BLFUN_DATA_SIZE];

