#ifndef __VECTOR_ADD__
#define __VECTOR_ADD__

#include <stdint.h>

void vector_add_scalar(const unsigned input_row, const unsigned scalar, const unsigned iterations, const unsigned stride );


void vector_add_scalar_predicate(
    const unsigned input_row,
    const unsigned scalar,
    const unsigned iterations,
    const unsigned stride,
    const uint16_t* predicates );

#endif