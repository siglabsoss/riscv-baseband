#ifndef __RANDOM_H__
#define __RANDOM_H__


unsigned int xorshift32(const unsigned int initial, const unsigned int* const state, const unsigned int len);
unsigned int simple_random(void);
void simple_random_seed(const unsigned int val);

#endif