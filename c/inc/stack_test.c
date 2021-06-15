#include "stack_test.h"
#include "linker_symbols.h"
#include "csr_control.h"

#define STACK_TEST_WORD 0x111b1111

/**
 * Fills the unused stack with a pattern. call stack_untouched afterwards
 * returns how many words it filled
 */
unsigned int fill_stack(void) {
    int sp_end = (unsigned int) &__sp_start - (unsigned int) &__stack_size;
    volatile unsigned int* writer = (volatile unsigned int*) sp_end;
    
    // calculate current stack pointer
    // writing near this (As we do below) is dangerous as we are using the stack as we go
    int sp0;
    GET_REG(x2, sp0);
    int sp_remaining = ((sp0 - sp_end)/4) - 1; // -1 should fill 1 less than absolute maximum of stack fill

    for(int i = 0; i < sp_remaining; i++) {
        *writer = STACK_TEST_WORD;
        writer++;
    }

    return sp_remaining;
}

/**
 * Returns the number of words that have been untouched after stack operations
 */
unsigned int stack_untouched(void) {
    int sp_end = (unsigned int) &__sp_start - (unsigned int) &__stack_size;
    volatile unsigned int* reader = (volatile unsigned int*) sp_end;
    // int sp0;
    // GET_REG(x2, sp0);
    // int sp_remaining = ((sp0 - sp_end)/4) - 1; // -1 should fill 1 less than absolute maximum of stack fill

    // where 0x800 is a small number larger than we will ever run
    for(int i = 0; i < 0x800; i++) {
        if( *reader != STACK_TEST_WORD ) {
            return i;
        }
        reader++;
    }
    return 0;
}
