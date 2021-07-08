#ifndef __SIG_UTILS_H__
#define __SIG_UTILS_H__

#include "stall.h"
#include "stall2.h"

// Tells you how long a c type array that was static declared with emtpy [] length
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

// y must be a power of 2 for this to work
//   x modulo y = ((x) & ((y) - 1))
//
#define BITWISE_MOD(x,y) ((x) & ((y) - 1))

#define _XSTR(s) _STR(s)
#define _STR(s) #s




// Random stuff
#define TRUE               (0x1)
#define FALSE              (0x0)
#ifndef SIG_UTILS_DO_NOT_DEFINE_NULL
#define NULL               ((void*)(0))
#endif
// see https://stackoverflow.com/questions/3437404/min-and-max-in-c for different
// version
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


// see http://blog.man7.org/2012/10/how-much-do-builtinexpect-likely-and.html
#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)


#endif
