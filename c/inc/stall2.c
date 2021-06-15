#include "stall2.h"

void stall2(const unsigned int x) {
    for(unsigned i = 0; i < x; i++) {
        asm("nop");
    }
}