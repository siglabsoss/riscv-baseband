#ifndef __VECTOR_MULTIPLY__
#define __VECTOR_MULTIPLY__

#include "vmem.h"

#ifndef VECTOR_MULTIPLY_DONT_INCLUDE_CFG_WORDS
#include "config_word_cmul_eq_0f.h"
#include "config_word_conj_eq_0f.h"
#include "config_word_add_eq_00.h"
#endif

void vector_multiply_1024(const unsigned int is_conj, const unsigned int input_data_fft, const unsigned int input_data_nco, const unsigned int output_data_location);
void cfg_vector_multiply_1024(const unsigned int cfg_row, const unsigned int input_data_fft, const unsigned int input_data_nco, const unsigned int output_data_location);
void vector_add_1024(const unsigned int input_data_fft, const unsigned int input_data_nco, const unsigned int output_data_location);

#endif