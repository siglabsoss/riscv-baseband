#include "circular_shift.h"

#include <limits.h> // for CHAR_BIT

uint16_t rol16(uint16_t n, unsigned shift) {
    const unsigned int mask = (CHAR_BIT*sizeof(n) - 1);  // assumes width is a power of 2.

    shift &= mask;
    return (n<<shift) | (n>>( (-shift)&mask ));
}


uint16_t ror16(uint16_t n, unsigned shift) {
    const unsigned int mask = (CHAR_BIT*sizeof(n) - 1);

    shift &= mask;
    return (n>>shift) | (n<<( (-shift)&mask ));
}
