dmem_vector_1k
====
Easy way to include a vector of 1024 elements of the same value at compile time.

If you want this where x is any value:
```cpp
uint32_t mag_filter_pilot_estimate[1024] = {x,x,x,x,...};
```
Do this
```cpp

#define INCLUDE_VECTOR_AS mag_filter_pilot_estimate
#define INCLUDE_TYPE_AS uint32_t
#define VECTOR_INITIAL_VALUE 0x0f000
#include "dmem_vector_1k.h"
```




