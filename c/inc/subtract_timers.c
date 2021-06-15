#include <subtract_timers.h>

// returns result of a-b while including roll over
unsigned int subtract_timers(unsigned int a, unsigned int b) {
  if (a < b) {
      // time rollover(overflow)
      return (0xFFFFFFFF - b) + 1 + a;
    } else {
      return a - b;
    }
}