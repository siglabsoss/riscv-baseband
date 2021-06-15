#ifndef __SOFT_RINGBUS_H__
#define __SOFT_RINGBUS_H__


// #define ALLOCATE_SOFT_RINGBUS(x)
// circular_buf_pow2_t __soft_ring_queue = CIRBUF_POW2_STATIC_CONSTRUCTOR(__soft_ring_queue, x);
// circular_buf_pow2_t* soft_ring_queue = &__soft_ring_queue;




void soft_queue_ring_eth(const unsigned int word);
void setup_soft_ring(const unsigned int max_occupancy, const unsigned int tries);
void pet_soft_ring(void);

#endif
