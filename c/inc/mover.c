/* 	mover.c
	author: Daniel Lomeli
	description: Works on a concept of a broadcast schedule.  Schedules are written to vector registers through a supplied scratchpad memory location.

*/
#include "mover.h"
#include "csr_control.h"

/*
V0 - src_addr
V1 - src add
V2 - dst addr
V3 - dst add
*/

// same as mover_load_vmem, except that the output address has output_offset_row added
// passing 0 would result in the same output
void mover_load_offset_output(const VmemSchedule* const schedule, const unsigned int output_offset_row) {
    mover_load_vmem(schedule);

    MVXV_KNOP(V4, output_offset_row);
    ADD_KNOP(V2, V2, V4, 0);
}

void mover_load_offset_input(const VmemSchedule* const schedule, const unsigned int input_offset_row) {
	mover_load_vmem(schedule);

	MVXV_KNOP(V4, input_offset_row);
	ADD_KNOP(V0, V0, V4, 0);
}

// same function as mover_schedule, but assumes a VmemSchedule object is already in vmem
// pass in a cpu pointer to this object
void mover_load_vmem(const VmemSchedule* const schedule) {
    unsigned int v0_vmem_row;
    unsigned int v1_vmem_row;
    unsigned int v2_vmem_row;
    unsigned int v3_vmem_row;
    v0_vmem_row = VMEM_ROW_ADDRESS( schedule->src_addr );
    v1_vmem_row = VMEM_ROW_ADDRESS( schedule->src_add );
    v2_vmem_row = VMEM_ROW_ADDRESS( schedule->dst_addr );
    v3_vmem_row = VMEM_ROW_ADDRESS( schedule->dst_add );

    MVXV_KNOP(V0, v0_vmem_row);
    VNOP_LK15(V0);
    MVK15V_KNOP(V0, 0x0);

    MVXV_KNOP(V1, v1_vmem_row);
    VNOP_LK15(V1);
    MVK15V_KNOP(V1, 0x0);

    MVXV_KNOP(V2, v2_vmem_row);
    VNOP_LK15(V2);
    MVK15V_KNOP(V2, 0x0);

    MVXV_KNOP(V3, v3_vmem_row);
    VNOP_LK15(V3);
    MVK15V_KNOP(V3, 0x0);
}


// Loads data from a schedule object into V0,V1,V2,V3 by way of the scratch address
// inputs:
//    Schedule pointer (from dmem)
//    scratch_addr     (dma pointer)

void mover_schedule(const Schedule* const schedule, const unsigned int scratch_addr){
    // scratch_addr - temporary scratchpad address where data is loaded destined for vector registers.
    // garbage_addr - a corruptable memory location where data can safely be chucked.

    // convert dma pointer to a row pointer
    unsigned int vmem_addr = VMEM_DMA_ADDRESS_TO_ROW(scratch_addr);

    for (unsigned int i = 0; i < NSLICES; i++){
        vector_memory[scratch_addr+i] =  schedule[i].src_addr;
    }

    MVXV_KNOP(V0, vmem_addr);
    VNOP_LK15(V0);
    MVK15V_KNOP(V0, 0x0);

    for (unsigned int i = 0; i < NSLICES; i++){
        vector_memory[scratch_addr+i] =  schedule[i].src_add;
    }

    MVXV_KNOP(V1, vmem_addr);
    VNOP_LK15(V1);
    MVK15V_KNOP(V1, 0x0);

    for (unsigned int i = 0; i < NSLICES; i++){
        vector_memory[scratch_addr+i] =  schedule[i].dst_addr;
    }

    MVXV_KNOP(V2, vmem_addr);
    VNOP_LK15(V2);
    MVK15V_KNOP(V2, 0x0);

    for (unsigned int i = 0; i < NSLICES; i++){
        vector_memory[scratch_addr+i] =  schedule[i].dst_add;
    }

    MVXV_KNOP(V3, vmem_addr);
    VNOP_LK15(V3);
    MVK15V_KNOP(V3, 0x0);
}


void mover_roll(const unsigned int lines){
/*
V0 - src_addr
V1 - src add
V2 - dst addr
V3 - dst add
*/
    if (lines < 4){

        for (unsigned int i = 0; i < lines; i++){

            ADD_LK13(V0, V0, V1, 0x0);
            ADD_SK13(V2, V2, V3, 0x0);
        }

    } else {

        for (unsigned int i = 0; i < 4; i++){
            ADD_LK13(V0, V0, V1, 0x0);
        }

        for (unsigned int i = 0; i < lines-4; i++){

            ADD_LK13(V0, V0, V1, 0x0);
            ADD_SK13(V2, V2, V3, 0x0);
        }

        for (unsigned int i = 0; i < 4; i++){
            ADD_SK13(V2, V2, V3, 0x0);
        }
    }


}

void mover_unroll(const unsigned int lines){
    // reverse the roll
    for (unsigned int i = 0; i < lines; i++){
        VNOP_LK13(V0);
        VNOP_SK13(V2);

        ADD_KNOP(V0, V0, V1, 0x0);

        SUB_KNOP(V2, V2, V3, 0x0);
    }

}

void mover_load_vmem_row_single(const VmemSchedule* const schedule, const unsigned int input_row) {
    // only cares about loading unique destination address which contains permutation and row
    // input row is set by input_row
    unsigned int v2_vmem_row;
    
    v2_vmem_row = VMEM_ROW_ADDRESS( schedule->dst_addr );
    MVXV_KNOP(V2, v2_vmem_row);

    MVXV_KNOP(V0, input_row);
    VNOP_LK13(V0);          // dataPath bypass
    
    VNOP_LK15(V2);
    MVK15V_KNOP(V2, 0x0);
    VNOP_SK13(V2);

}



/*
V0 - src_addr
V2 - dst addr (plus permutation for store)
V5 - schedule width offset (in rows) = 4
V6 - Stores loaded words from input
V7 - Stores words before it is written to output
*/

// Note V6 and V7 could both be V6 with no issues
void mover_roll3(const VmemSchedule* const schedule, const unsigned int schedules) {
    unsigned int v0_vmem_row;
    unsigned int v2_vmem_row;
    
    v0_vmem_row = VMEM_ROW_ADDRESS( schedule->src_addr );
    v2_vmem_row = VMEM_ROW_ADDRESS( schedule->dst_addr );

    // MVXV_KNOP(V4, input_offset_row);

    MVXV_KNOP(V5, 4);

    MVXV_KNOP(V0, v0_vmem_row);
    MVXV_KNOP(V2, v2_vmem_row);


    for(unsigned i = 0; i < (schedules/2); i++) {
    
        ADD_LK15(V0, V0, V5);
        MVK15V_KNOP(V7, 0x0);
        VNOP_LK13(V7);

        ADD_LK15(V0, V0, V5);
        MVK15V_KNOP(V8, 0x0);
        VNOP_LK13(V8);

        ADD_LK15(V2, V2, V5);
        MVK15V_KNOP(V9, 0x0);
        VNOP_SK13(V9);

        ADD_LK15(V2, V2, V5);
        MVK15V_KNOP(V10, 0x0);
        VNOP_SK13(V10);

    }
}


void mover_roll2(const VmemSchedule* const schedule, const unsigned int schedules) {
    unsigned int v0_vmem_row;
    unsigned int v2_vmem_row;
    
    v0_vmem_row = VMEM_ROW_ADDRESS( schedule->src_addr );
    v2_vmem_row = VMEM_ROW_ADDRESS( schedule->dst_addr );

    MVXV_KNOP(V5, 4);

    MVXV_KNOP(V0, v0_vmem_row);
    MVXV_KNOP(V2, v2_vmem_row);


    for(unsigned i = 0; i < schedules; i++) {

                                // bump V0 by 4 to prepare for next load
        ADD_LK15(V0, V0, V5);   // Treat V0 as pointer, load vmem (data) at this address into K15B
        MVK15V_KNOP(V6, 0x0);   // move bank to register
        VNOP_LK13(V6);          // Load (dataPath bypass)

                                // bump V2 by 4 to prepare for next load
        ADD_LK15(V2, V2, V5);   // Treat V2 pointer.  load vmem (permutations) at this address
        MVK15V_KNOP(V7, 0x0);
        VNOP_SK13(V7);          // Store using permutation store
    }

}


///
/// This is a legacy function I am including for now because I am merging code that uses this by name
/// if mover_load_vmem_row_single() is identical we shoul use that
///
void mover_load_vmem_offset_input_single(
    const VmemSchedule* const schedule,
    const unsigned int input_offset_row) {
    (void)input_offset_row;

/*
V0 - src_addr
V2 - dst addr
*/

    unsigned int v0_vmem_row;
    unsigned int v2_vmem_row;
    
    v0_vmem_row = VMEM_ROW_ADDRESS( schedule->src_addr );
    v2_vmem_row = VMEM_ROW_ADDRESS( schedule->dst_addr );
    
    
    MVXV_KNOP(V0, v0_vmem_row);
    MVXV_KNOP(V2, v2_vmem_row);

    
    VNOP_LK15(V0);          // vector register bank load path
    MVK15V_KNOP(V0, 0x0);   // move bank to register
    VNOP_LK13(V0);          // dataPath bypass

    VNOP_LK15(V2);
    MVK15V_KNOP(V2, 0x0);
    VNOP_SK13(V2);

}





// pass an array of 2 bit values, and will pack into a single 32 bit word
// in format that QPSK will accept
unsigned int mover_debug_load_qpsk(const unsigned int values[16]) {
    unsigned int out;

    out = 
    (values[0] & 0x1 ) << 0    | 
    (values[0] & 0x2 ) << (16-1)   |  
    (values[1] & 0x1 ) << 1    | 
    (values[1] & 0x2 ) << (17-1)   |  
    (values[2] & 0x1 ) << 2    | 
    (values[2] & 0x2 ) << (18-1)   |  
    (values[3] & 0x1 ) << 3    | 
    (values[3] & 0x2 ) << (19-1)   |  
    (values[4] & 0x1 ) << 4    | 
    (values[4] & 0x2 ) << (20-1)   |  
    (values[5] & 0x1 ) << 5    | 
    (values[5] & 0x2 ) << (21-1)   |  
    (values[6] & 0x1 ) << 6    | 
    (values[6] & 0x2 ) << (22-1)   |  
    (values[7] & 0x1 ) << 7    | 
    (values[7] & 0x2 ) << (23-1)   |  
    (values[8] & 0x1 ) << 8    | 
    (values[8] & 0x2 ) << (24-1)   |  
    (values[9] & 0x1 ) << 9    | 
    (values[9] & 0x2 ) << (25-1)   |  
    (values[10] & 0x1 ) << 10  |   
    (values[10] & 0x2 ) << (26-1)  |   
    (values[11] & 0x1 ) << 11  |   
    (values[11] & 0x2 ) << (27-1)  |   
    (values[12] & 0x1 ) << 12  |   
    (values[12] & 0x2 ) << (28-1)  |   
    (values[13] & 0x1 ) << 13  |   
    (values[13] & 0x2 ) << (29-1)  |   
    (values[14] & 0x1 ) << 14  |   
    (values[14] & 0x2 ) << (30-1)  |   
    (values[15] & 0x1 ) << 15  |   
    (values[15] & 0x2 ) << (31-1);

    return out;
}

void mover_copy(const unsigned int input_data, const unsigned int output_data, const unsigned int size){
    MVXV_KNOP(V2, input_data);
    MVXV_KNOP(V3, output_data);
    MVXV_KNOP(V4, 0x1);

    if (size < 8){
        for (unsigned int i = 0; i < size; i++){
            ADD_LK13(V2, V2, V4, 0x0);
            ADD_SK13(V3, V3, V4, 0x0);
        }

    } else {
        for (unsigned int i = 0; i < 4; i++){
            ADD_LK13(V2, V2, V4, 0x0);
        }

        for (unsigned int i = 0; i < size-4; i++){
            ADD_SK13(V3, V3, V4, 0x0);
            ADD_LK13(V2, V2, V4, 0x0);
        }

        for (unsigned int i = 0; i < 4; i++){
            ADD_SK13(V3, V3, V4, 0x0);
        }
    }
}