#include <stdint.h>

#define BOOTLOAD_FUNCTION_SECTION __attribute__((section(".bootload_fun.data"))) GCC_ALIGNED_64



#ifndef BLFUN_DATA_SIZE
#define BLFUN_DATA_SIZE (512)
#endif


BOOTLOAD_FUNCTION_SECTION uint8_t bl_function_data[BLFUN_DATA_SIZE];

