#include "exit2.h"

// fixme, do something with status value
// fime, refactor to exit and use   __builtin_unreachable();
// https://stackoverflow.com/questions/25408795/tell-gcc-that-a-function-call-will-not-return
void  exit2(int status) {
  (void)status;
  // extern const char __halt_main[];
  asm("j __halt_main");
}
