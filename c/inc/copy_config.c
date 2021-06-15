


#include "vmem.h"
#include "xbaseband.h"
#include "copy_config.h"

///
/// Copies a config word
/// pass as cpu pointers
/// during copy barrel shift is set to specified number
// returns 1 for error, no copy is done in this case
int copy_set_barrel(const unsigned short* cpu_source, const unsigned short* cpu_dest, const unsigned int shift) {
    // was re-written from:
    // ok if(shift >= 0) and (shift <= 15)
    //
    if( shift > 0x15 ) {
        return 1;
    }

    const unsigned source_row = VMEM_ROW_ADDRESS(cpu_source);
    const unsigned dest_row = VMEM_ROW_ADDRESS(cpu_dest);
    const unsigned dest_dma = VMEM_DMA_ADDRESS(cpu_dest);

    MVXV_KNOP(V0, source_row);
    MVXV_KNOP(V1, dest_row);
    MVXV_KNOP(V2, 1);
    
   
    ADD_LK13(V0, V0, V2, 0);
    ADD_SK13(V1, V1, V2, 0);


    const unsigned int shift_word = (shift<<24) | (shift<<16) | (shift<<8) | shift;
    for(int index = 5; index < 9; index++) {
        vector_memory[dest_dma+index] = shift_word;
    }

    return 0;
}
