#include "fixed_iir.h"


///
/// Ported from js:
/// let irr = (a, b, g) => {
///  a[0] = g * (b[0] - a[0]) + a[0];
///  a[1] = g * (b[1] - a[1]) + a[1];
/// };
///
/// This version is fixed point
/// The value of the filter gain is
///   g / (2**shift)
///
/// In practice I found that gain should not be much larger than 65535
/// This comes from the fact that we use int32_t internally to represent the result
/// of this eq:
///   (gain * the current value).
///   this would be 0x7fff * 0x7fff  at worst case or ~1 Billion.
///   This is safly under 2 Billion limit of int32_t
///

/// With a gain scalad against 65535, use a shift of 16
// see also fixed_iir_16()

/// @param[in,out] a - filter state, updated by this function
/// @param[in] b     - update
/// @param[in] g     - gain of the filter
/// @param[in] shift - shift applied before state is re-written
void fixed_iir(uint32_t* const a, const uint32_t* const b, const int32_t g, const uint32_t shift) {
    const int16_t a_r = (*a&0xffff);
    const int16_t a_i = (((*a)>>16)&0xffff);

    const int16_t b_r = (*b&0xffff);
    const int16_t b_i = (((*b)>>16)&0xffff);


    int32_t result_r = (g * (b_r - a_r)) >> shift;
    int32_t result_i = (g * (b_i - a_i)) >> shift;
    
    result_r += a_r;
    result_i += a_i;

    *a = (((result_i)<<16)&0xffff0000) | ((result_r)&0xffff);
}


void fixed_iir_16(uint32_t* const a, const uint32_t* const b, const int32_t g) {
    const int16_t a_r = (*a&0xffff);
    const int16_t a_i = (((*a)>>16)&0xffff);

    const int16_t b_r = (*b&0xffff);
    const int16_t b_i = (((*b)>>16)&0xffff);


    int32_t result_r = (g * (b_r - a_r)) >> 16;   // 16 is shift, and comes from function name
    int32_t result_i = (g * (b_i - a_i)) >> 16;   // 16 is shift, and comes from function name
    
    result_r += a_r;
    result_i += a_i;

    *a = (((result_i)<<16)&0xffff0000) | ((result_r)&0xffff);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"

/// int32 version of filter (no real/imag packing)
/// state is an int64_t but updates are int32_t
/// @param[in,out] a - filter state, updated by this function
/// @param[in] b     - update
/// @param[in] g     - gain of the filter
void __attribute__((always_inline)) i32_fixed_iir_16(int64_t* const a, const int32_t b, const int32_t g) {
    int64_t result   = ((int64_t)g * (int64_t)(b - *a)) >> 16;   // 16 is shift, and comes from function name
    
    result += *a;
    
    *a = result;
}

#pragma GCC diagnostic pop