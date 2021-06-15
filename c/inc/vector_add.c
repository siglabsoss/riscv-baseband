#include "vector_add.h"

#include "xbaseband.h"
#include "vmem.h"

/*

V0  source
V1  scalar
V2  stride
V3  tmp

*/


/// In-place modify of vector memory
/// The same scalar value gets added to vmem with a stride and iteration
/// This is only good for the lower 16 bits

void vector_add_scalar(
    const unsigned input_row,
    const unsigned scalar,
    const unsigned iterations,
    const unsigned stride ) {

    MVXV_KNOP(V0, input_row);
    MVXV_KNOP(V1, scalar);
    MVXV_KNOP(V2, stride);

    for(unsigned i = 0; i < iterations; i++) {

        VNOP_LK15(V0);           // Load memory pointed to by V0 into k15
        MVK15V_KNOP(V3, 0x0);    // k15 goes to V3 tmp register

        ADD_KNOP(V3, V3, V1);    // V3 gets the scalar value in V1 added to it

        MVVK15_KNOP(V3);         // k15 gets the value of V3

        ADD_SK15(V0, V0, V2);    // k15 goes to memory pointed to by V0, V0 bumps for next loop
    }
}


void vector_add_scalar_predicate(
    const unsigned input_row,
    const unsigned scalar,
    const unsigned iterations,
    const unsigned stride,
    const uint16_t* predicates ) {

    MVXV_KNOP(V0, input_row);
    MVXV_KNOP(V1, scalar);
    MVXV_KNOP(V2, stride);

    for(unsigned i = 0; i < iterations; i++) {

        VNOP_LK15(V0);           // Load memory pointed to by V0 into k15
        MVK15V_KNOP(V3, 0x0);    // k15 goes to V3 tmp register

        ADD_KNOP(V3, V3, V1, predicates[i]);    // V3 gets the scalar value in V1 added to it

        MVVK15_KNOP(V3);         // k15 gets the value of V3

        ADD_SK15(V0, V0, V2);    // k15 goes to memory pointed to by V0, V0 bumps for next loop
    }
}
