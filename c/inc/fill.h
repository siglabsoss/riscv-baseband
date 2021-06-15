#ifndef __FILL_H__
#define __FILL_H__

#include <stdint.h>

void vmem_fill_low(const unsigned start_row, const unsigned rows, const uint16_t value);

void vmem_slow_fill_row(const unsigned row, const uint32_t value);
void vmem_fill_prep(const unsigned work_rows, const uint32_t value);
void vmem_fill_run(const unsigned work_rows, const unsigned start_row, const unsigned rows);

#endif
