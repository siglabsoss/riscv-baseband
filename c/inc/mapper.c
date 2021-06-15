/* 	mapper.c
	author: Daniel Lomeli
	description: Works on a concept of a broadcast schedule.  Schedules are written to vector memory.
*/
#include "mapper.h"

#define TRUE    (0x1)
#define FALSE   (0x0)

#define QPSK_POS (0x5a81) //+0.7
#define QPSK_NEG (0xa57e) //-0.7

#define POS_ONE (0x7FFF) //+1
#define NEG_ONE (0x8001) //-1

#define BASE_POINTER_REG   (0x0)
#define REG1               (0x1)
#define REG2               (0x2)
#define RESULT_REG         (0x3)
#define DEST_POINTER_REG   (0x4)

#define PERM_REG           (0x9)

// register volatile unsigned int x3 asm("x3");

// pass a positive signed 16 bit number, 2's compliment is taken automatically for negative
Table mapper_qpsk_table_gain(unsigned int t_addr, short gain){

    // mask 15 bits here
    unsigned int pos_point = 0x7fff & gain;
    // mask 16 bits here
    unsigned int neg_point = ((~pos_point)+1) & 0xffff;

    for (unsigned int i = 0; i < NSLICES; i++){
        vector_memory[t_addr+i+NSLICES*0] = (pos_point << 16 | pos_point); 
        vector_memory[t_addr+i+NSLICES*1] = (pos_point << 16 | neg_point); 
        vector_memory[t_addr+i+NSLICES*2] = (neg_point << 16 | pos_point); 
        vector_memory[t_addr+i+NSLICES*3] = (neg_point << 16 | neg_point); 
    }

    return (Table) {TABLE_T_MAP, t_addr, 4*NSLICES};
}


// "Constructor" for the Table type
// accepts a dma pointer
// creates for 4 rows in vmem. where the rows are:
//
//  pos / pos
//  pos / neg
//  neg / pos
//  neg / neg
Table mapper_qpsk_table(unsigned int t_addr){

    for (unsigned int i = 0; i < NSLICES; i++){
        vector_memory[t_addr+i+NSLICES*0] = (QPSK_POS << 16 | QPSK_POS); 
        vector_memory[t_addr+i+NSLICES*1] = (QPSK_POS << 16 | QPSK_NEG); 
        vector_memory[t_addr+i+NSLICES*2] = (QPSK_NEG << 16 | QPSK_POS); 
        vector_memory[t_addr+i+NSLICES*3] = (QPSK_NEG << 16 | QPSK_NEG); 
    }

    return (Table) {TABLE_T_MAP, t_addr, 4*NSLICES};
}

Table mapper_bpsk_table(unsigned int t_addr){

    for (unsigned int i = 0; i < NSLICES; i++){
        vector_memory[t_addr+i+NSLICES*0] = POS_ONE << 16; 
        vector_memory[t_addr+i+NSLICES*1] = NEG_ONE << 16; 
    }

    MVXV_KNOP(BASE_POINTER_REG, t_addr/NSLICES);

    return (Table) {TABLE_T_MAP, t_addr, 2*NSLICES}; 
}

Table mapper_debug_qpsk_table(unsigned int t_addr){

    for (unsigned int i = 0; i < NSLICES; i++){
        vector_memory[t_addr+i+NSLICES*0] = 0xF0000003;
        vector_memory[t_addr+i+NSLICES*1] = 0xF0000002;
        vector_memory[t_addr+i+NSLICES*2] = 0xF0000001;
        vector_memory[t_addr+i+NSLICES*3] = 0xF0000000;
    }

    return (Table) {TABLE_T_MAP, t_addr, 4*NSLICES};
}

// accepts:
//  a table pointer
//  destination address (dma pointer)
//  index (dma pointer) to a single location in vmem
//
//  take a 32 bit word.  Split it into 16 words
//  the first bit from each short is used to make up the first constellation point, etc
//
//  1 value is read from index, while 16 values are written top d_addr
//  if calling this more than once at a time, d_addr MUST increment by 16 with each call
void mapper_load_qpsk(Table * table, unsigned int d_addr, unsigned int index) {

    unsigned int data;
    
    unsigned int pred0, pred1;

    // load literal 1 and literal 2 into vregs
    MVXV_KNOP(REG1, 0x1);
    MVXV_KNOP(REG2, 0x2);

    // load pointer to qpsk table into RESULT_REG
    // this is pointing at the first row
    MVXV_KNOP(RESULT_REG, table->addr/NSLICES);
    MVXV_KNOP(DEST_POINTER_REG, d_addr/NSLICES);

    data = vector_memory[index];

    // "bit-splitter"/transpose into 2 16-bit vectors 
    // this creates two predicates which we use to 
    pred0 =  data&0x0000FFFF;
    pred1 = (data&0xFFFF0000) >> 16;

    // add literal 1 to the input address if pred0 bit is set
    ADD_KNOP(RESULT_REG, RESULT_REG, REG1, pred0);
    ADD_KNOP(RESULT_REG, RESULT_REG, REG2, pred1);

    // load values of the QPSK table at each of the calculated addresses into K13
    VNOP_LK13(RESULT_REG);

    // store final values to output memory
    VNOP_SK13(DEST_POINTER_REG);
}

void mapper_rload_bpsk(Table * table, unsigned int d_addr, unsigned int index){ 
    
    int row0;

    MVXV_KNOP(REG1, 0x1);

    MVXV_KNOP(RESULT_REG, table->addr/NSLICES);
    MVXV_KNOP(DEST_POINTER_REG, d_addr/NSLICES);

    row0 = vector_memory[index];

    // "bit-splitter"/transpose into 2 16-bit vectors 

    ADD_KNOP(RESULT_REG, RESULT_REG, REG1, row0);
    // move table value to mapped memory
    VNOP_LK13(RESULT_REG);
    // MVK15V_KNOP(DEBUG_REG, 0x0);
    VNOP_SK13(DEST_POINTER_REG);
}

void mapper_lload_bpsk(Table * table, unsigned int d_addr, unsigned int index){ 

    int row0;

    MVXV_KNOP(REG1, 0x1);

    MVXV_KNOP(RESULT_REG, table->addr/NSLICES);
    MVXV_KNOP(DEST_POINTER_REG, d_addr/NSLICES);

    row0 = vector_memory[index];

    // "bit-splitter"/transpose into 2 16-bit vectors 
    row0 = (row0&0xFFFF0000) >> 16;

    ADD_KNOP(RESULT_REG, RESULT_REG, REG1, row0);
    // move table value to mapped memory
    VNOP_LK13(RESULT_REG);
    // MVK15V_KNOP(DEBUG_REG, 0x0);
    VNOP_SK13(DEST_POINTER_REG);
}
