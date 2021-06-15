#ifndef __IIR_H__
#define __IIR_H__

void xbb_iir(
    const unsigned cfg_cmul_location,
    const unsigned cfg_add_location,
    const unsigned input_state_location,
    const unsigned input_new_measure_location,
    const unsigned coeff_state_location,
    const unsigned coeff_new_measure_location,
    const unsigned output_location);




void xbb_iir_one_row(
    const unsigned cfg_cmul_location,
    const unsigned cfg_add_location,
    const unsigned input_state_location,
    const unsigned input_new_measure_location,
    const unsigned coeff_state_one_row_location,
    const unsigned coeff_new_measure_one_row_location,
    const unsigned output_location);


#endif
