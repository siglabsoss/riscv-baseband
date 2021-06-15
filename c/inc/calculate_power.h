#ifndef __CALCULATE_POWER_H__
#define __CALCULATE_POWER_H__

#include <stdint.h>
#include <stdbool.h>

unsigned power_set_shift(const unsigned stage, const unsigned shift );
void power_shift_all(const unsigned a, const unsigned b, const unsigned c);
void power_choose_ideal_shift(unsigned s);
void power_smart_shift(const unsigned s);
void setup_calculate_power(void);
uint32_t calculate_power_runtime_0(void);
uint32_t calculate_power_runtime_1(void);
void judge_power_results(const uint64_t signal_power, const int signal_shift, char* advice, int* direction);
uint64_t calculate_power(const unsigned int source_row);

#endif
