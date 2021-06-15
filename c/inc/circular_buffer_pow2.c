#include "circular_buffer_pow2.h"

#ifdef VERILATE_TESTBENCH
#define __RISCV_INLINE
#else
#define __RISCV_INLINE __attribute__((always_inline))
#endif



// pas a number which is a power of 2
// Pass a power of 2, if not found 0xffffffff is returned
int circular_buf2_get_pow2(const unsigned int size) {
    unsigned int found = 0;
    unsigned int found_at = 0;
    for(unsigned int i = 0; i < 32; i++) {
        if(0x1U<<i == size) {
            found = 1;
            found_at = i;
            break;
        }
    }

    if(!found) {
        return 0xffffffff;
    }
    return found_at;
    
}

/////////////////////
//
// pass size = to capacity!!!
//
// size must be a pow2, this function will HANG if not pow2
// this will while(1) block forever if params are wrong, or an errir happened in circular_buf2_reset (cbuf was null)
// will never return upon failure
void circular_buf2_initialize(circular_buf_pow2_t* const cbuf, unsigned int* const storage, const unsigned int size) {
    
    unsigned pow2_search = circular_buf2_get_pow2(size);

    if(pow2_search == 0xffffffff || size == 0) {
        while(1) {;} // HANG FOREVER if non power2 is used, this is our way of "Asserting"
    }

    // even though we go through all that to find the pow2_search with a for()
    // we just throw it away, turns out it's more efficient to calculat a bitmask from
    // size itself, not the pow2

    // if size is 1024, this will create a bitmask of 0x3ff (10 1's in a row)
    // which we can use instead of %
    cbuf->size_pow2_mask = size - 1;

    cbuf->size = size;
    cbuf->buffer = storage;
    
    unsigned int reset_error_code;
    reset_error_code = circular_buf2_reset(cbuf);
    if(reset_error_code != 0 ) {
        // reset threw an error, just lock
        while(1) {;}
    }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"

inline unsigned int __RISCV_INLINE circular_buf2_empty(const circular_buf_pow2_t* const cbuf)
{
    // We define empty as head == tail
    return cbuf->occupancy==0;
}

unsigned int __RISCV_INLINE circular_buf2_full(const circular_buf_pow2_t* const cbuf)
{
    return cbuf->occupancy >= cbuf->size;
}

unsigned int __RISCV_INLINE circular_buf2_occupancy(const circular_buf_pow2_t* const cbuf)
{
    return cbuf->occupancy;
}

#pragma GCC diagnostic pop


// returns 0 for success, -1 for fail
int circular_buf2_reset(circular_buf_pow2_t* const cbuf)
{
    int r = -1;

    if(cbuf)
    {
        cbuf->head = 0;
        cbuf->tail = 0;
        cbuf->occupancy = 0;
        // cbuf->size_minus = cbuf->size-1; // precalculate this for later
        r = 0;
    }

    return r;
}

// will return error if buffer is full
// we can add an additional put which allows overwrite
int circular_buf2_put(circular_buf_pow2_t* const cbuf, const unsigned int data)
{
    if( !(cbuf->occupancy >= cbuf->size) )
    {
        cbuf->buffer[cbuf->head] = data;
        cbuf->head = (cbuf->head + 1) & cbuf->size_pow2_mask; // mask instead of mod

        cbuf->occupancy++;

        // I think this is enabling overwriting behaviour
        // which we never get to?
        // if(cbuf->head == cbuf->tail)
        // {
        //     cbuf->tail = (cbuf->tail + 1) % cbuf->size;
        // }

        return 0;
    }

    return -1;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"

int __RISCV_INLINE circular_buf2_drop(circular_buf_pow2_t* const cbuf)
{
    if( !(cbuf->occupancy==0) )
    {
        cbuf->tail = (cbuf->tail + 1) & cbuf->size_pow2_mask; // mask instead of mod

        cbuf->occupancy--;

        return 0;
    }

    return -1;
}

int __RISCV_INLINE circular_buf2_get(circular_buf_pow2_t* const cbuf, unsigned int* const data)
{
    if( !(cbuf->occupancy==0) )
    {
        *data = cbuf->buffer[cbuf->tail];
        cbuf->tail = (cbuf->tail + 1) & cbuf->size_pow2_mask; // mask instead of mod

        cbuf->occupancy--;

        return 0;
    }

    return -1;
}

int __RISCV_INLINE circular_buf2_peek(const circular_buf_pow2_t* const cbuf, unsigned int* const data)
{
    if( !(cbuf->occupancy==0) )
    {
        *data = cbuf->buffer[cbuf->tail];
        return 0;
    }

    return -1;
}
#pragma GCC diagnostic pop


int circular_buf2_peek_n(const circular_buf_pow2_t* const cbuf, unsigned int* const data, const unsigned int n)
{
    if( n == 0 ) {
        return circular_buf2_peek(cbuf, data);
    }

    // do a shallow copy
    // this will copy all of the meta variables
    // but the buffer* will point to the same data
    // because "get" does not destroy the data
    // we just call get enough times on the copy
    // and this makes our peekn work without
    // writing any new logic
    circular_buf_pow2_t copy = *cbuf;

    int r = 0;

    unsigned int data2;

    for(unsigned i = 0; i <= n; i++) {
        r = circular_buf2_get(&copy, &data2);

        if( r != 0 ) {
            return r;
        }
    }

    *data = data2;


    return r;
}

