#include "random.h"


// a very simple hash function
//
// pass in *state as a cpu_pointer to some memory, and len for how many words
// to xorshift
unsigned int xorshift32(const unsigned int initial, const unsigned int* const state, const unsigned int len)
{
  /* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
  unsigned int hash = initial;
  for(unsigned int i = 0; i < len; i++) {
    hash += state[i];
    hash ^= hash << 13;
    hash ^= hash >> 17;
    hash ^= hash << 5;
  }
  return hash;
}

// initial random state
unsigned int simple_random_state = 0xfeadbeef;

unsigned int simple_random(void) {
    simple_random_state = xorshift32(0, &simple_random_state, 1);

    // unfortunately if xorshift32 returns 0, it will be stuck at 0 forever, and return 0
    // for all future calls to random
    if(simple_random_state == 0) {
        simple_random_state = 0x9c047bbd; // different start point because why not
    }
    return simple_random_state;
}

// pass any value as a seed to our simple random.
// because of the if check above, we can even pass a 0 here
// which will be caught by the if-check above and forced to a different value, allowing
// for noraml random operation
void simple_random_seed(const unsigned int val) {
    simple_random_state = val;
}