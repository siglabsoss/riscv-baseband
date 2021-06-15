#ifndef __SIG_BRANCH_PREDICTION__
#define __SIG_BRANCH_PREDICTION__

// see http://blog.man7.org/2012/10/how-much-do-builtinexpect-likely-and.html
#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)

#endif
