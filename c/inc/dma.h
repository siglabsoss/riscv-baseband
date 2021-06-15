#ifndef __DMA_H__
#define __DMA_H__

void dma_in_set(int start_address, int dma_len);

void dma_out_set(int start_address, int dma_len);

int dma_in_check(int timeout);

int dma_out_check(int timeout);

void dma_block_send(unsigned int dma_ptr, unsigned int word_count);
void dma_send_finalized(unsigned int dma_ptr, unsigned int word_count, unsigned finalized);
void dma_block_send_finalized(unsigned int dma_ptr, unsigned int word_count, unsigned finalized);
void dma_block_send_reverse(unsigned int dma_ptr, unsigned int word_count);
void dma_block_send_timer(unsigned int dma_ptr, unsigned int word_count, unsigned timer_val);
void dma_block_get(unsigned int dma_ptr, unsigned int word_count);
void dma_run_till_last(void);

void dma_block_send_limit(const unsigned dma_ptr, const unsigned word_count, const unsigned limit);
    
// warning this will reset occupancy
void flush_input_dma(unsigned int dma_junk, unsigned int junk_len, unsigned int run_time);

#endif /* __DMA_H__ */
