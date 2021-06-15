#ifndef __COARSE_SYNC_H__
#define __COARSE_SYNC_H__

typedef struct CFO_RESULTS {
    unsigned int cfo_complex;
    unsigned int cfo_angle;
    unsigned int cfo_estimate;
} CFO_Results;

void trig_dma_in_cs(unsigned int start_address, unsigned int timer_start, unsigned int DMA_size);
int result_check_tolerance(unsigned int benchmark_start_row, unsigned int result_start_row, unsigned int total_sample, int diff_th);
void xbb_cfo_estimation(CFO_Results *CFO_results, unsigned int cfg_conj_multi_location, unsigned int cfg_cmul_rx4_location, unsigned int input_conj_multi_location_0, unsigned int input_conj_multi_location_1, unsigned int all_one_location, unsigned int output_conj_multi_location, unsigned int row_num_cfo, unsigned int bank_address_onetone_calculation_location, unsigned int permutation_address_onetone_calculation_location);
void xbb_conj_multi_add(unsigned int cfg_conj_multi_location, unsigned int cfg_cmul_rx4_location, unsigned int input_conj_multi_location_0, unsigned int input_conj_multi_location_1, unsigned int all_one_location, unsigned int output_conj_multi_location, unsigned int row_num_cfo, unsigned int bank_address_onetone_calculation_location, unsigned int permutation_address_onetone_calculation_location);
void xbb_conj_multi(unsigned int cfg_conj_multi_location, unsigned int input_conj_multi_location_0, unsigned int input_conj_multi_location_1, unsigned int output_conj_multi_location);
void xbb_conj_multi_const(unsigned int cfg_conj_multi_location, unsigned int input_conj_multi_location_0, unsigned int input_conj_multi_location_1, unsigned int output_conj_multi_location);
void xbb_conj_multi_80(unsigned int cfg_conj_multi_location, unsigned int input_conj_multi_location_0, unsigned int input_conj_multi_location_1, unsigned int output_conj_multi_location);
void xbb_conj_multi_const(unsigned int cfg_conj_multi_location, unsigned int input_conj_multi_location_0, unsigned int input_conj_multi_location_1, unsigned int output_conj_multi_location);
void xbb_onetone_calculation(unsigned int cfg_onetone_calculation_location, unsigned int input_onetone_calculation_location, unsigned int exp_data_location, unsigned int output_onetone_calculation_location, unsigned int bank_address_onetone_calculation_location, unsigned int permutation_address_onetone_calculation_location, unsigned int all_one_location);
void xbb_add(unsigned int cfg_data, unsigned int input_0, unsigned int input_1, unsigned int output);


#endif