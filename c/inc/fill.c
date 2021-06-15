#include "fill.h"
#include "xbaseband.h"
#include "vmem.h"
#include "csr_control.h"


// register volatile unsigned int x4 asm("x4");

// value is only 16 bits (only the real part)
// 
void vmem_fill_low(const unsigned start_row, const unsigned rows, const uint16_t value) {
    MVXV_KNOP(V0, start_row);
    MVXV_KNOP(V1, 1);
    MVXV_KNOP(V2, value);  //fill value
    for (unsigned i = 0; i < rows; i++) {
        MVVK15_KNOP(V2);  //vmem[V0] <= k15 <= vreg[V2] 
        VNOP_SK15(V0);
        ADD_KNOP(V0, V0, V1, 0x0);
    }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"

inline void __attribute__((always_inline)) vmem_fill_low_single(const unsigned start_row, const uint16_t value) {
    MVXV_KNOP(V14, start_row);
    MVXV_KNOP(V15, value);  //fill value

    MVVK15_KNOP(V15);  //vmem[V0] <= k15 <= vreg[V2] 
    VNOP_SK15(V14);
}

#pragma GCC diagnostic pop


#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")

void vmem_slow_fill_row(const unsigned row, const uint32_t value) {
    uint32_t* p = (uint32_t*)REVERSE_VMEM_ROW_ADDRESS(row);
    for(unsigned i = 0; i < 16; i++) {
        p[i] = value;
    }
}

// pass a vmem row that is 3 rows long that we can write to
void vmem_fill_prep(const unsigned work_rows, const uint32_t value) {
    vmem_slow_fill_row(work_rows, value);
    // uint32_t* p = (uint32_t*)REVERSE_VMEM_ROW_ADDRESS(work_row);
    // for(unsigned i = 0; i < 16; i++) {
    //     p[i] = value;
    // }
    // MVXV_KNOP(V0, work_row);
    // MVXV_KNOP(V2, value);  //fill value

    // VNOP_LK13(V2);
    // MVK15V_KNOP(V7, 0x0);
    // VNOP_SK13(V7);
}

#pragma GCC pop_options

// static VMEM_SECTION unsigned src_adr[16];
// static VMEM_SECTION unsigned dst_adr[16];


// tricky
// we need to have memory that has vmem addresses in it, in order to do this correctly
// FIXME this is way too much work, just use vmem_slow_fill and then vmem copy
void vmem_fill_run(const unsigned work_rows, const unsigned start_row, const unsigned rows) {

    // we need memory that has pointers to our start and dest
    // here we calculate the memory address of THOSE memories
    const unsigned source_ptr_ptr = work_rows + 1;
    const unsigned dest_ptr_ptr = work_rows + 2;

    // load 16 copies of our start address into vmem
    vmem_fill_low_single(source_ptr_ptr, (uint16_t)work_rows);

    // see mover.c::mover_roll2()

    MVXV_KNOP(V5, 0);

    MVXV_KNOP(V0, source_ptr_ptr);  // load V0 to the pointer of memory where our source pointers are
    MVXV_KNOP(V2, dest_ptr_ptr);    // load V2 to the pointer of memory where our dest pointers are

    for(unsigned i = 0; i < rows; i++ ) {
        // load 16 copies of our dest address into vmem, plus i
        vmem_fill_low_single(dest_ptr_ptr, (uint16_t)start_row+i);


        ADD_LK15(V0, V0, V5);   // Treat V0 as pointer, load vmem (data) at this address into K15B
        MVK15V_KNOP(V6, 0x0);   // move bank to register
        VNOP_LK13(V6);          // Load (dataPath bypass)


        ADD_LK15(V2, V2, V5);   // Treat V2 pointer.  load vmem (permutations) at this address
        MVK15V_KNOP(V7, 0x0);
        VNOP_SK13(V7);          // Store using permutation store
    }
}


/*
example usage:


void vmem_fill_zero(int base, int size) {
    vmem_fill(base, size, 0);
}

void vmem_fill_1024_zero(int base) {
    vmem_fill(base, 1024, 0);
}

void vmem_fill_beginning_1024_zero(void) {
    vmem_fill(0, 1024, 0);
}

void vmem_fill_beginning_128_zero(void) {
    vmem_fill(0, 128, 0);
}
*/
