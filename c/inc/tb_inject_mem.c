#include "tb_inject_mem.h"
#include "pass_fail.h"
#include "tb_inject_mask.h"

#include <stdint.h>


unsigned int get_tb_seed(void) {
    return *pass_fail_0;
}



bool get_is_verilator(void) {
    const uint32_t load = *pass_fail_1;
    return (load>>TBI_IS_VERILATOR_SHIFT)&TBI_IS_VERILATOR_MASK;
}



///
/// Returns the id of this board in a multi higgs verilator example
///
int get_higgs_id(void) {
    const int32_t id = ((*pass_fail_1)>>TBI_HIGGS_ID_SHIFT)&TBI_HIGGS_ID_MASK;

    if( id == 0 ) {
        return -1;
    }

    return id - 1;
}
