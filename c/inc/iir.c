#include "iir.h"
#include "coarse_sync.h"
#include "vmem.h"

void xbb_iir(
    const unsigned cfg_cmul_location,
    const unsigned cfg_add_location,
    const unsigned input_state_location,
    const unsigned input_new_measure_location,
    const unsigned coeff_state_location,
    const unsigned coeff_new_measure_location,
    const unsigned output_location) {

    xbb_conj_multi(cfg_cmul_location, input_state_location, coeff_state_location, input_state_location);
    xbb_conj_multi(cfg_cmul_location, input_new_measure_location, coeff_new_measure_location, input_new_measure_location);

    xbb_add(cfg_add_location, input_state_location, input_new_measure_location, output_location);
}




void xbb_iir_one_row(
    const unsigned cfg_cmul_location,
    const unsigned cfg_add_location,
    const unsigned input_state_location,
    const unsigned input_new_measure_location,
    const unsigned coeff_state_one_row_location,
    const unsigned coeff_new_measure_one_row_location,
    const unsigned output_location) {

    xbb_conj_multi_const(cfg_cmul_location, input_state_location, coeff_state_one_row_location, input_state_location);
    xbb_conj_multi_const(cfg_cmul_location, input_new_measure_location, coeff_new_measure_one_row_location, input_new_measure_location);

    xbb_add(cfg_add_location, input_state_location, input_new_measure_location, output_location);
}
