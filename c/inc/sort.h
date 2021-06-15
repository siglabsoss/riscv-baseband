#ifndef __SORT_H__
#define __SORT_H__

#include <stdint.h>

void selection_sort_i32(int32_t* const a, const unsigned n);
void selection_sort_i64(int64_t* const a, const unsigned n);
void selection_sort_parallel_i32(int32_t* const a, int32_t* const b, const unsigned n);
void selection_sort_parallel_u64(uint64_t* const a, uint64_t* const b, const unsigned n);
void selection_sort_parallel_u64_u8(uint64_t* const a, uint8_t* const b, const unsigned n);
void selection_sort_parallel_u64_u32(uint64_t* const a, uint32_t* const b, const unsigned n);

#endif