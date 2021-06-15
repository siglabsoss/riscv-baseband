#ifndef __PIPELINE_WORK_H__
#define __PIPELINE_WORK_H__

#include "sig_utils.h"

// https://stackoverflow.com/questions/3988041/how-to-define-a-typedef-struct-containing-pointers-to-itself

typedef struct pipeline_work_t pipeline_work_t;

struct pipeline_work_t {
    pipeline_work_t *prev;
    pipeline_work_t *next;
    unsigned int state;
    unsigned int a_empty;
    unsigned int b_empty;
    unsigned int* cpu[2]; 
    unsigned int dma[2];
    unsigned int vmem_row[2];

};

// set the cpu pointer for buffer a or b
void pipeline_work_set_buffer(pipeline_work_t* work, unsigned int index, unsigned int *cpu_ptr) {
    work->cpu[index] = cpu_ptr;
    work->dma[index] = VMEM_DMA_ADDRESS(cpu_ptr);
    work->vmem_row[index] = VMEM_ROW_ADDRESS(cpu_ptr);
}

void pipeline_work_initialize(pipeline_work_t* work, unsigned int* cpu_a, unsigned int* cpu_b) {
    work->state = 0;
    pipeline_work_set_buffer(work, 0, cpu_a);
    pipeline_work_set_buffer(work, 1, cpu_b);
    // work->cpu[0] = cpu_a;
    // work->dma[0] = VMEM_DMA_ADDRESS(cpu_a);
    // work->vmem_row[0] = VMEM_ROW_ADDRESS(cpu_a);


    // work->cpu[1] = cpu_b;
    // work->dma[1] = VMEM_DMA_ADDRESS(cpu_b);
    // work->vmem_row[1] = VMEM_ROW_ADDRESS(cpu_b);

    work->a_empty = 1;
    work->b_empty = 1;
}


///////////////////////////
//
//  HOLD()
//
//  Mark your a or b buffer as full, signal to downstream that it is ready to be worked on
//
//
//  Usage:
//    HOLD()
//    HOLD(A)
//    HOLD(a)
//    HOLD(0)
//    HOLD(B)
//    HOLD(1)
//    HOLD_THIS(variable_name)
//
// 

#define RELEASE(x) RELEASE_ ## x()

#define HOLD(x) __HOLD_ ## x()

#define __HOLD_() HOLD_THIS(work->state)

#define __HOLD_a() HOLD_A()
#define __HOLD_A() HOLD_A()
#define __HOLD_0() HOLD_A()

#define __HOLD_b() HOLD_B()
#define __HOLD_B() HOLD_B()
#define __HOLD_1() HOLD_B()

#define HOLD_A() work->a_empty=0
#define HOLD_B() work->b_empty=0

#define RELEASE_A() work->a_empty=1
#define RELEASE_B() work->b_empty=1

#define HOLD_THIS(x) if((x)==0){work->a_empty=0;}else{work->b_empty=0;}

#define HOLD_FROM_PREV() if(work->state==0){prev->a_empty=0;}else{prev->b_empty=0;}
#define RELEASE_TO_PREV() if(work->state==0){prev->a_empty=1;}else{prev->b_empty=1;}
#define RELEASE_AUTO() if(work->state==0){work->a_empty=1;}else{work->b_empty=1;}

#define FLIP_STATE() work->state = (work->state+1)&0x1

#endif
