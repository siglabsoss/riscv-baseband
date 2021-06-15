#ifndef __VMEM_COPY_H__
#define __VMEM_COPY_H__

#include <stdbool.h>
#include <stdint.h>

void vmem_copy_rows(const unsigned int input_rows, const unsigned int output_rows, const unsigned int rows);
void vmem_interleave_copy_repeat(const unsigned int input_row_a, const unsigned int input_row_b, const unsigned int output_row, const unsigned int rows, const unsigned int predicate);
void vmem_copy_words_slow(const unsigned int input_dma, const unsigned int output_dma, const unsigned int words);
bool vmem_copy_words(const unsigned int input_dma, const unsigned int output_dma, const unsigned int words, const unsigned int garbage_row);
bool vmem_copy_words_input_aligned(const unsigned int input_dma, const unsigned int output_dma, const unsigned int words, const unsigned int garbage_row);
#endif