////////////
//
//  Bootloader
//
//  Only one function may be BOOTLOADER_SECTION_ENTRY_FUNCTION.
//  Other functions should be BOOTLOADER_SECTION, and global variables
//  should be BOOTLOADER_VARIABLE_SECTION
//





/////////////
// 
//  Vmem
//
//  Due to an oversight I am hacking on vmem bootloading afterwards
//
//  The bootloader will sent all zeros for the the entire dmem section
//  this would corrupt the bootloader, but the bootloader will protect the stack
//  and not overwrite that.
//  the address of the next byte after the dmem section will jump up to vector mem
//  this way the existing bootloader can just do a single stream and get the whole thing
// 
//  the bootloader will protect itself
//  after the address of 


// bootloader won't write above this amount
#define BOOTLOADER_LARGEST_STACK  0x7900

// this is where a seam is
#define BOOTLOADER_ADDRESS_START  0x7c00




#include "bootloader.h"
#include "csr_control.h"
#include "apb_bus.h"

// This function modifies the write location of a pointer
// this allows us to have a "seam" in the memory, meaning that
// at a specific input address, the output address jumps up to vmem
BOOTLOADER_SECTION void bootload_address_seam(volatile unsigned int** addr) {
    if((unsigned int) *addr == BOOTLOADER_ADDRESS_START) {
        *addr = (volatile unsigned int*) 0x40000;
    }
}

BOOTLOADER_VARIABLE_SECTION int ringbus_report = -1;

// forward declare
void no_exit_bootload_eth_from_dma(unsigned int total_word_count);

// call this from your main with how many bytes to load
// do not mark any other functions with this tag
BOOTLOADER_SECTION_ENTRY_FUNCTION void no_exit_bootload(
            unsigned int total_word_count,
            unsigned int is_eth) {

    unsigned int occupancy;
    unsigned int volatile *write_location = (unsigned int *) 0x0;
    unsigned int memory_data;
    unsigned int written_words = 0;
    // register volatile unsigned int x3 asm("x3");

    if(is_eth) {
        no_exit_bootload_eth_from_dma(total_word_count);
    }

    DISABLE_MACHINE_INTERRUPTS(); // we will poll

    if(ringbus_report != -1) {
        CSR_WRITE(RINGBUS_WRITE_ADDR, (unsigned)ringbus_report);
    }

    // Wipe all of VMEM.  this allows bootloading python to send least amount of data as possible
    // this loop takes 2ms of real time. so bootloader MUST wait
    // after sending first ringbus cmd (the one with the size)
    // unroll this loop x16
    for(unsigned int i = 0; i < 0x10000; i+=16) {
        vector_memory[i +  0] = 0;
        vector_memory[i +  1] = 0;
        vector_memory[i +  2] = 0;
        vector_memory[i +  3] = 0;
        vector_memory[i +  4] = 0;
        vector_memory[i +  5] = 0;
        vector_memory[i +  6] = 0;
        vector_memory[i +  7] = 0;
        vector_memory[i +  8] = 0;
        vector_memory[i +  9] = 0;
        vector_memory[i + 10] = 0;
        vector_memory[i + 11] = 0;
        vector_memory[i + 12] = 0;
        vector_memory[i + 13] = 0;
        vector_memory[i + 14] = 0;
        vector_memory[i + 15] = 0;
        // SET_REG(x3, i);
    }


    while(1) {
        CSR_READ(RINGBUS_READ_OCCUPANCY, occupancy);
        if(occupancy)
        {
            CSR_READ(RINGBUS_READ_DATA, memory_data);
            // x3 = memory_data;

            if((unsigned int)write_location >= BOOTLOADER_LARGEST_STACK && (unsigned int)write_location < BOOTLOADER_ADDRESS_START) {
                // do nothing
                // this is the bootloader protecting itself and the current stack
                // the python file is sending zeros during this section. we can increase BOOTLOADER_LARGEST_STACK
                // or calculate it on the fly (even better) without changing python
            } else {
                *write_location = memory_data;
            }  
            write_location++;

            // apply seam
            bootload_address_seam(&write_location);

            if(ringbus_report != -1 ){
                CSR_WRITE(RINGBUS_WRITE_DATA, (unsigned int) write_location);
                CSR_WRITE(RINGBUS_WRITE_EN, 0);
                CSR_WRITE(RINGBUS_WRITE_DATA, memory_data);
                CSR_WRITE(RINGBUS_WRITE_EN, 0);
            }

            written_words++;
        }

        if(written_words == total_word_count) {
            ringbus_report = -1; // clever
            CSR_WRITE_ZERO(DMA_0_FLUSH_SCHEDULE);
            CSR_WRITE_ZERO(DMA_1_FLUSH_SCHEDULE);
            CSR_WRITE_ZERO(RINGBUS_INTERRUPT_CLEAR);
            CSR_WRITE_ZERO(RINGBUS_2_INTERRUPT_CLEAR);
            CSR_WRITE_ZERO(DMA_0_INTERRUPT_CLEAR);
            CSR_WRITE_ZERO(DMA_1_INTERRUPT_CLEAR);
            CSR_WRITE_ZERO(DMA_2_INTERRUPT_CLEAR);
            asm("j 0");
        }
    }
}

// should be larger than largest vmem/dma that we will be using
#define DMA_WORKING_VMEM (64)
#define DMA_IN_EXPECTED_OCCUPANCY (4)
#define DMA_IN_COUNT (8)
#define DMA_IN_LEN (2)
#define DMA_IN_OFFSET (16)

// mask here must be (DMA_IN_COUNT-1)
#define DMA_IN_NEXT_FOR(given) (((given)+1) & (DMA_IN_COUNT-1))
#define DMA_IN_START(x) (DMA_IN_OFFSET+(DMA_IN_LEN*(x)))
BOOTLOADER_VARIABLE_SECTION unsigned int bl_dma_in_last;
BOOTLOADER_VARIABLE_SECTION unsigned int bl_dma_in_last_consumed;

BOOTLOADER_SECTION inline void bl_trig_in(void)
{
    // one to trig is next is last+1
  unsigned int dma_in_next = DMA_IN_NEXT_FOR(bl_dma_in_last);

  // SET_REG(x3, 0xb0000000 | dma_in_next);
  // SET_REG(x3, 0xc0000000 | DMA_IN_START(dma_in_next));
  // at this point we are triggering a future DMA which dooms the memoryu
  // we need to check if we overflowd

  // the DMA_IN_START() macro here converts the index to a DMApointer
  CSR_WRITE(DMA_0_START_ADDR, DMA_IN_START(dma_in_next));
  // CSR_WRITE(DMA_0_LENGTH, DMA_IN_LEN);
  // CSR_WRITE(DMA_0_TIMER_VAL, 0xffffffff);  // start right away
  CSR_WRITE_ZERO(DMA_0_PUSH_SCHEDULE); // any value

  bl_dma_in_last = dma_in_next;
}

BOOTLOADER_SECTION void no_exit_bootload_eth_from_dma(
            unsigned int total_word_count) {
    unsigned int volatile *write_location = (unsigned int *) 0x0;
    unsigned int memory_data;
    unsigned int ringbus_ttl;
    unsigned int written_words = 0;
    // unsigned int dma_in_expected_occupancy;
    unsigned int ring_send_pending = 0;
    // register volatile unsigned int x3 asm("x3");

    DISABLE_MACHINE_INTERRUPTS(); // we will poll

    // flush schedule that eth was using, and setup our own
    CSR_WRITE_ZERO(DMA_0_FLUSH_SCHEDULE);
    CSR_WRITE_ZERO(DMA_1_FLUSH_SCHEDULE);

    // we need to set these every time due to re-bootloading
    bl_dma_in_last = DMA_IN_COUNT-1;
    bl_dma_in_last_consumed = DMA_IN_COUNT-1;

    // bootloader will never change these values
    // so set them once, now, and we don't have to set them for any other dma in
    CSR_WRITE(DMA_0_LENGTH, DMA_IN_LEN);
    CSR_WRITE(DMA_0_TIMER_VAL, 0xffffffff);  // start right away

    for(unsigned int i = 0; i < 4; i++) {
        bl_trig_in();
    }

    // SET_REG(x3, total_word_count);
    
    // dma_in_expected_occupancy = 4;

    // Wipe all of VMEM.  this allows bootloading python to send least amount of data as possible
    // this loop takes 2ms of real time. so bootloader MUST wait
    // after sending first ringbus cmd (the one with the size)
    // 32 is a keepout range
    // for(unsigned int i = DMA_WORKING_VMEM; i < 0x4000; i++) {
    //     vector_memory[i] = 0;
    // }


    while(1) {

        unsigned int occupancy;
        CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, occupancy);
        unsigned int i;

        // SET_REG(x3, 0xa0000000 | occupancy);
        for(i=occupancy;i<DMA_IN_EXPECTED_OCCUPANCY;i++) {
            bl_trig_in(); // this can be earler for better performance
            ring_send_pending++;
        }

        while(ring_send_pending) {
            ring_send_pending--;
            bl_dma_in_last_consumed = DMA_IN_NEXT_FOR(bl_dma_in_last_consumed);
            // SET_REG(x3, bl_dma_in_last_consumed);
            unsigned int mem_start = DMA_IN_START(bl_dma_in_last_consumed);
            // SET_REG(x3, mem_start);
            ringbus_ttl = vector_memory[mem_start];
            if(ringbus_ttl != 0) {
                break; // PC sent a ringbus message that was not for us, sadly we drop it
            }
            // +1 here is to read the ringbus address
            memory_data = vector_memory[mem_start+1];
            // SET_REG(x3, memory_data);
            if((unsigned int)write_location >= BOOTLOADER_LARGEST_STACK || (unsigned int)write_location >= BOOTLOADER_ADDRESS_START) {
                // do nothing
                // this is the bootloader protecting itself and the current stack
                // the python file is sending zeros during this section. we can increase BOOTLOADER_LARGEST_STACK
                // or calculate it on the fly (even better) without changing python
                // Eth bootloader will never bootload VMEM and just eat any addresses above that line
                // SET_REG(x3, 0xffffffff);
            } else {
                *write_location = memory_data;
                // SET_REG(x3, memory_data);
                // SET_REG(x4, write_location);
            }
            write_location++;
            written_words++;


            if(written_words == total_word_count) {
                CSR_WRITE_ZERO(DMA_0_FLUSH_SCHEDULE);
                CSR_WRITE_ZERO(DMA_1_FLUSH_SCHEDULE);
                CSR_WRITE_ZERO(RINGBUS_INTERRUPT_CLEAR);
                CSR_WRITE_ZERO(RINGBUS_2_INTERRUPT_CLEAR);
                CSR_WRITE_ZERO(DMA_0_INTERRUPT_CLEAR);
                CSR_WRITE_ZERO(DMA_1_INTERRUPT_CLEAR);
                CSR_WRITE_ZERO(DMA_2_INTERRUPT_CLEAR);
                // finish clearning VMEM that we were just writing to
                // for(unsigned int i = 0; i < DMA_WORKING_VMEM; i++) {
                //     vector_memory[i] = 0;
                // }
                // reset
                asm("j 0");
            }
        }

    }
}

// BOOTLOADER_SECTION void bootload_eth(unsigned int start_index,
//                                      unsigned int size){
//     unsigned int volatile *write_location = (unsigned int *) 0x0;

//     DISABLE_MACHINE_INTERRUPTS();

//     for(unsigned int i = 0; i < size; i++){
//         *write_location = vector_memory[start_index + i];
//         write_location++;
//         // FIXME:
//         // bootload_address_seam(&write_location);
//     }
    
//     asm("j 0");
// }