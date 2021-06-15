#ifndef __ATAN__
#define __ATAN__


#include <stdint.h>

static inline int16_t s16_nabs(const int16_t j);

/**
 * Q15 (1.0.15 fixed point) multiplication. Various common rounding modes are in
 * the function definition for reference (and preference).
 *
 * @param j 16-bit signed integer representing -1 to (1 - (2**-15)), inclusive
 * @param k same format as j
 * @return product of j and k, in same format
 */
static inline int16_t q15_mul(const int16_t j, const int16_t k);

/**
 * Q15 (1.0.15 fixed point) division (non-saturating). Be careful when using
 * this function, as it does not behave well when the result is out-of-range.
 *
 * Value is not defined if numerator is greater than or equal to denominator.
 *
 * @param numer 16-bit signed integer representing -1 to (1 - (2**-15))
 * @param denom same format as numer; must be greater than numerator
 * @return numer / denom in same format as numer and denom
 */
static inline int16_t q15_div(const int16_t numer, const int16_t denom);

/**
 * 16-bit fixed point four-quadrant arctangent. Given some Cartesian vector
 * (x, y), find the angle subtended by the vector and the positive x-axis.
 *
 * The value returned is in units of 1/65536ths of one turn. This allows the use
 * of the full 16-bit unsigned range to represent a turn. e.g. 0x0000 is 0
 * radians, 0x8000 is pi radians, and 0xFFFF is (65535 / 32768) * pi radians.
 *
 * Because the magnitude of the input vector does not change the angle it
 * represents, the inputs can be in any signed 16-bit fixed-point format.
 *
 * @param y y-coordinate in signed 16-bit
 * @param x x-coordinate in signed 16-bit
 * @return angle in (val / 32768) * pi radian increments from 0x0000 to 0xFFFF
 */
uint16_t fxpt_atan2(const int16_t y, const int16_t x);

#endif