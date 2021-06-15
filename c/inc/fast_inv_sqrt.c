#include "fast_inv_sqrt.h"
#include <stdint.h>

// see https://en.wikipedia.org/wiki/Fast_inverse_square_root
//     https://stackoverflow.com/questions/21010586/normalizing-spatial-vectors-without-square-root
float fast_inv_sqrt( const float number )
{   
    const float x2 = number * 0.5F;
    const float threehalfs = 1.5F;

    union {
        float f;
        uint32_t i;
    } conv = {number}; // member 'f' set to value of 'number'.
    conv.i  = 0x5f3759df - ( conv.i >> 1 );
    conv.f  *= ( threehalfs - ( x2 * conv.f * conv.f ) );
    return conv.f;
}