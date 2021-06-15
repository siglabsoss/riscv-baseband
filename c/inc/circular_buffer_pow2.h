#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

// for ARRAY_SIZE
#include "sig_utils.h"
#include "compile_assert.h"


// https://embeddedartistry.com/blog/2017/4/6/circular-buffers-in-cc
// usage, see higgs_sdr_rev2/sim/verilator/test_cir_buf/override/fpgas/grav/eth/c/src/main.c

typedef struct {
    unsigned int* buffer;
    unsigned int head;
    unsigned int tail;
    unsigned int size; // of the (unsigned int* buffer)
    unsigned int size_pow2_mask;
    // unsigned int size_minus;
    unsigned int occupancy;
} circular_buf_pow2_t;


// does not accept 0
// will compile time assert if value is not a power of 2
#define COMPILE_ASSERT_IS_POW_2(x) \
COMPILE_ASSERT_2( \
(x == 0x1) | \
(x == 0x2) | \
(x == 0x4) | \
(x == 0x8) | \
(x == 0x10) | \
(x == 0x20) | \
(x == 0x40) | \
(x == 0x80) | \
(x == 0x100) | \
(x == 0x200) | \
(x == 0x400) | \
(x == 0x800) | \
(x == 0x1000) | \
(x == 0x2000) | \
(x == 0x4000) | \
(x == 0x8000) | \
(x == 0x10000) | \
(x == 0x20000) | \
(x == 0x40000) | \
(x == 0x80000) | \
(x == 0x100000) | \
(x == 0x200000) | \
(x == 0x400000) | \
(x == 0x800000) | \
(x == 0x1000000) | \
(x == 0x2000000) | \
(x == 0x4000000) | \
(x == 0x8000000) | \
(x == 0x10000000) | \
(x == 0x20000000) | \
(x == 0x40000000) | \
(x == 0x80000000) )

// #define CIR_BUF_POW2_CONSTRUCTOR(name, capacity)
// circular_buf_pow2_t name;
// unsigned int _ ## name ## _storage[capacity];

#define CIRBUF_POW2_STORAGE_NAME(name) __ ## name ## _storage


// actual hacked macro
// this does not do any compile time static assertion to check for capacity
#define CIRBUF_POW2_STATIC_CONSTRUCTOR_UNSAFE(name, capacity) \
{0}; \
unsigned int CIRBUF_POW2_STORAGE_NAME(name)[capacity]; \

// hacked macro which finishes up the line
// this macro should be global because if it ever leaves scope
// both the constructed array AND the storage will be on the stack
#define CIRBUF_POW2_STATIC_CONSTRUCTOR(name, capacity) \
CIRBUF_POW2_STATIC_CONSTRUCTOR_UNSAFE(name, capacity) \
COMPILE_ASSERT_IS_POW_2(capacity)


#define CIRBUF_POW2_RUNTIME_INITIALIZE(name) \
circular_buf2_initialize(&name, CIRBUF_POW2_STORAGE_NAME(name), ARRAY_SIZE(CIRBUF_POW2_STORAGE_NAME(name)) );

int circular_buf2_reset(circular_buf_pow2_t* cbuf);

// pas a number which is a power of 2
// Pass a power of 2, if not found 0xffffffff is returned
int circular_buf2_get_pow2(const unsigned int size);

/////////////////////
//
// pass size = to capacity!!!
//
// size must be a pow2, this function will HANG if not pow2
// this will while(1) block forever if params are wrong, or an errir happened in circular_buf2_reset (cbuf was null)
// will never return upon failure
void circular_buf2_initialize(circular_buf_pow2_t* const cbuf, unsigned int* const storage, const unsigned int size);

unsigned int circular_buf2_empty(const circular_buf_pow2_t* const cbuf);

unsigned int circular_buf2_full(const circular_buf_pow2_t* const cbuf);

unsigned int circular_buf2_occupancy(const circular_buf_pow2_t* const cbuf);

// returns 0 for success, -1 for fail
int circular_buf2_reset(circular_buf_pow2_t* const cbuf);

// will return error if buffer is full
// we can add an additional put which allows overwrite
int circular_buf2_put(circular_buf_pow2_t* const cbuf, const unsigned int data);

int circular_buf2_get(circular_buf_pow2_t* const cbuf, unsigned int* const data);

int circular_buf2_drop(circular_buf_pow2_t* const cbuf);

int circular_buf2_peek(const circular_buf_pow2_t* const cbuf, unsigned int* const data);

int circular_buf2_peek_n(const circular_buf_pow2_t* const cbuf, unsigned int* const data, const unsigned int n);




#endif