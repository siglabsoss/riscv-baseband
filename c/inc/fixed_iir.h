#ifndef __FIXED_IIR_H__
#define __FIXED_IIR_H__

#include <stdint.h>

void fixed_iir(uint32_t* const a, const uint32_t* const b, const int32_t g, const uint32_t shift);
void fixed_iir_16(uint32_t* const a, const uint32_t* const b, const int32_t g);
void i32_fixed_iir_16(int64_t* const a, const int32_t b, const int32_t g);
#endif
