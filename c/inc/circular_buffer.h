#ifndef __CIRCULAR_BUFFER_H__
#define __CURCULAR_BUFFER_H__

// https://embeddedartistry.com/blog/2017/4/6/circular-buffers-in-cc
// usage, see higgs_sdr_rev2/sim/verilator/test_cir_buf/override/fpgas/grav/eth/c/src/main.c

typedef struct {
    unsigned int* buffer;
    unsigned int head;
    unsigned int tail;
    unsigned int size; // of the (unsigned int* buffer)
    unsigned int size_minus;
    unsigned int occupancy;
} circular_buf_t;

int circular_buf_reset(circular_buf_t* cbuf);

/////////////////////
//
// currently this is half way between a size+1 full detection, and an extra flag for full detection
//
// if you pass size of 5, the storage buffer MUST be size 5,
// however the circular_buf_t will only hold 4 items (due to "full" detection)
int __attribute__((deprecated)) circular_buf_initialize(circular_buf_t* cbuf, unsigned int* storage, unsigned int size) {
    cbuf->size = size;
    cbuf->buffer = storage;
    return circular_buf_reset(cbuf); // returns error code, 0 for success
}

unsigned int circular_buf_empty(circular_buf_t* cbuf)
{
    // We define empty as head == tail
    return cbuf->occupancy==0;
}

unsigned int circular_buf_full(circular_buf_t* cbuf)
{
    return cbuf->occupancy >= cbuf->size_minus;
}

unsigned int circular_buf_occupancy(circular_buf_t* cbuf)
{
    return cbuf->occupancy;
}


int circular_buf_reset(circular_buf_t* cbuf)
{
    int r = -1;

    if(cbuf)
    {
        cbuf->head = 0;
        cbuf->tail = 0;
        cbuf->occupancy = 0;
        cbuf->size_minus = cbuf->size-1; // precalculate this for later
        r = 0;
    }

    return r;
}

// will return error if buffer is full
// we can add an additional put which allows overwrite
int circular_buf_put(circular_buf_t* cbuf, unsigned int data)
{
    int r = -1;

    if( !circular_buf_full(cbuf) )
    {
        cbuf->buffer[cbuf->head] = data;
        cbuf->head = (cbuf->head + 1) % cbuf->size;

        cbuf->occupancy++;

        // I think this is enabling overwriting behaviour
        // which we never get to?
        // if(cbuf->head == cbuf->tail)
        // {
        //     cbuf->tail = (cbuf->tail + 1) % cbuf->size;
        // }

        r = 0;
    }

    return r;
}

int circular_buf_get(circular_buf_t* cbuf, unsigned int* data)
{
    int r = -1;

    if( !circular_buf_empty(cbuf) )
    {
        *data = cbuf->buffer[cbuf->tail];
        cbuf->tail = (cbuf->tail + 1) % cbuf->size;

        cbuf->occupancy--;

        r = 0;
    } else {
        *data = 0;
    }

    return r;
}

int circular_buf_peek(circular_buf_t* cbuf, unsigned int* data)
{
    int r = -1;

    if( !circular_buf_empty(cbuf) )
    {
        *data = cbuf->buffer[cbuf->tail];
        r = 0;
    }

    return r;
}





#endif