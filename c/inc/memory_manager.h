#ifndef __MEMORY_MANAGER_H__
#define __MEMORY_MANAGER_H__

///
/// This file enables malloc/vmalloc for a some vmem
/// At compile time, you choose memory size and chunks
/// provides "malloc like" allocation of those N chunks
/// has a for loop over MEMORY_MANAGER_CHUNKS so keep that number small
/// like 8 or less
///
/// This is written so that only one can be referenced globally
/// however we could name-mangle the sizes into the types and names
/// if we really needed to
///
/// Both of these return / consume DMA pointers
/// int memory_manger_get()
/// void memory_manger_free(const unsigned int p)
///
/// unsigned int memory_manager_available()
/// 

#define MM_DISABLE_SET_REG

#ifdef MM_DISABLE_SET_REG
#define MMSET_REG(x,y)
#else
#define MMSET_REG(x,y) SET_REG(x,y)
#endif

// include 
#include "vmem.h"

#ifndef MEMORY_MANAGER_SIZE
#error "you must define MEMORY_MANAGER_SIZE"
#endif


#ifndef MEMORY_MANAGER_CHUNKS
#error "you must define MEMORY_MANAGER_CHUNKS"
#endif

#ifdef _MM_SIZE
#error "are you including this file twice?"
#endif

// update the large switch below
#if MEMORY_MANAGER_CHUNKS > 64
#error "This class must be updated for larger than 8 values"
#endif

#define _MM_SIZE ((MEMORY_MANAGER_SIZE)*(MEMORY_MANAGER_CHUNKS))


//! debug
#ifdef MEMORY_MANAGER_DEBUG_JUNK_VMEM
VMEM_SECTION unsigned int _memory_manager_chunka[16];
VMEM_SECTION unsigned int _memory_manager_chunkb[7];
#endif



VMEM_SECTION unsigned int _memory_manager_chunks[_MM_SIZE];


//! debug
#ifdef MEMORY_MANAGER_DEBUG_JUNK_VMEM
VMEM_SECTION unsigned int _memory_manager_chunkz[32];
VMEM_SECTION unsigned int _memory_manager_chunky[4];
#endif


typedef struct memory_manager_struct {
  unsigned int full[MEMORY_MANAGER_CHUNKS];

  // dma address of each chunk
  unsigned int chunk_dma_address[MEMORY_MANAGER_CHUNKS];
  
  unsigned int dma_base; // dma base pointer (same as chunk_dma_address[0])
  unsigned int available;

  unsigned int double_free_count; // error tracking
  unsigned int illegal_free_count; // error tracking

} MMStruct;

static MMStruct _mgr;

void init_memory_manager(void) {

    MMSET_REG(x3, 0x11110000);
    MMSET_REG(x3, &_mgr);
    
    for(unsigned int i = 0; i < MEMORY_MANAGER_CHUNKS; i++) {
        _mgr.full[i] = 0;
        unsigned int *cpu = _memory_manager_chunks + (MEMORY_MANAGER_SIZE*i);
        _mgr.chunk_dma_address[i] = VMEM_DMA_ADDRESS(cpu);
    }

    // do this after loop
    _mgr.dma_base = _mgr.chunk_dma_address[0];
    _mgr.available = MEMORY_MANAGER_CHUNKS;


    _mgr.double_free_count = 0;
    _mgr.illegal_free_count = 0;
}

// this switch saves cpu at the cost of imem instructions
// this is practical for up to 64 I'd say but managing is a pain
int __attribute__((optimize("Os"))) memory_manger_index_for_ptr(const unsigned int p) {
    const unsigned int offset = p - _mgr.dma_base;
    MMSET_REG(x3,0xfeedfeed);
    MMSET_REG(x3,offset);
    switch(offset) {
        case MEMORY_MANAGER_SIZE*0:
            return 0;
            break;
        case MEMORY_MANAGER_SIZE*1:
            return 1;
            break;
        case MEMORY_MANAGER_SIZE*2:
            return 2;
            break;
        case MEMORY_MANAGER_SIZE*3:
            return 3;
            break;
        case MEMORY_MANAGER_SIZE*4:
            return 4;
            break;
        case MEMORY_MANAGER_SIZE*5:
            return 5;
            break;
        case MEMORY_MANAGER_SIZE*6:
            return 6;
            break;
        case MEMORY_MANAGER_SIZE*7:
            return 7;
            break;
        case MEMORY_MANAGER_SIZE*8:
            return 8;
            break;
        case MEMORY_MANAGER_SIZE*9:
            return 9;
            break;
        case MEMORY_MANAGER_SIZE*10:
            return 10;
            break;
        case MEMORY_MANAGER_SIZE*11:
            return 11;
            break;
        case MEMORY_MANAGER_SIZE*12:
            return 12;
            break;
        case MEMORY_MANAGER_SIZE*13:
            return 13;
            break;
        case MEMORY_MANAGER_SIZE*14:
            return 14;
            break;
        case MEMORY_MANAGER_SIZE*15:
            return 15;
            break;
#if MEMORY_MANAGER_CHUNKS > 16
        case MEMORY_MANAGER_SIZE*16:
            return 16;
            break;
        case MEMORY_MANAGER_SIZE*17:
            return 17;
            break;
        case MEMORY_MANAGER_SIZE*18:
            return 18;
            break;
        case MEMORY_MANAGER_SIZE*19:
            return 19;
            break;
        case MEMORY_MANAGER_SIZE*20:
            return 20;
            break;
        case MEMORY_MANAGER_SIZE*21:
            return 21;
            break;
        case MEMORY_MANAGER_SIZE*22:
            return 22;
            break;
        case MEMORY_MANAGER_SIZE*23:
            return 23;
            break;
        case MEMORY_MANAGER_SIZE*24:
            return 24;
            break;
        case MEMORY_MANAGER_SIZE*25:
            return 25;
            break;
        case MEMORY_MANAGER_SIZE*26:
            return 26;
            break;
        case MEMORY_MANAGER_SIZE*27:
            return 27;
            break;
        case MEMORY_MANAGER_SIZE*28:
            return 28;
            break;
        case MEMORY_MANAGER_SIZE*29:
            return 29;
            break;
        case MEMORY_MANAGER_SIZE*30:
            return 30;
            break;
        case MEMORY_MANAGER_SIZE*31:
            return 31;
            break;
#endif
#if MEMORY_MANAGER_CHUNKS > 32
        case MEMORY_MANAGER_SIZE*32:
            return 32;
            break;
        case MEMORY_MANAGER_SIZE*33:
            return 33;
            break;
        case MEMORY_MANAGER_SIZE*34:
            return 34;
            break;
        case MEMORY_MANAGER_SIZE*35:
            return 35;
            break;
        case MEMORY_MANAGER_SIZE*36:
            return 36;
            break;
        case MEMORY_MANAGER_SIZE*37:
            return 37;
            break;
        case MEMORY_MANAGER_SIZE*38:
            return 38;
            break;
        case MEMORY_MANAGER_SIZE*39:
            return 39;
            break;
        case MEMORY_MANAGER_SIZE*40:
            return 40;
            break;
        case MEMORY_MANAGER_SIZE*41:
            return 41;
            break;
        case MEMORY_MANAGER_SIZE*42:
            return 42;
            break;
        case MEMORY_MANAGER_SIZE*43:
            return 43;
            break;
        case MEMORY_MANAGER_SIZE*44:
            return 44;
            break;
        case MEMORY_MANAGER_SIZE*45:
            return 45;
            break;
        case MEMORY_MANAGER_SIZE*46:
            return 46;
            break;
        case MEMORY_MANAGER_SIZE*47:
            return 47;
            break;
        case MEMORY_MANAGER_SIZE*48:
            return 48;
            break;
        case MEMORY_MANAGER_SIZE*49:
            return 49;
            break;
        case MEMORY_MANAGER_SIZE*50:
            return 50;
            break;
        case MEMORY_MANAGER_SIZE*51:
            return 51;
            break;
        case MEMORY_MANAGER_SIZE*52:
            return 52;
            break;
        case MEMORY_MANAGER_SIZE*53:
            return 53;
            break;
        case MEMORY_MANAGER_SIZE*54:
            return 54;
            break;
        case MEMORY_MANAGER_SIZE*55:
            return 55;
            break;
        case MEMORY_MANAGER_SIZE*56:
            return 56;
            break;
        case MEMORY_MANAGER_SIZE*57:
            return 57;
            break;
        case MEMORY_MANAGER_SIZE*58:
            return 58;
            break;
        case MEMORY_MANAGER_SIZE*59:
            return 59;
            break;
        case MEMORY_MANAGER_SIZE*60:
            return 60;
            break;
        case MEMORY_MANAGER_SIZE*61:
            return 61;
            break;
        case MEMORY_MANAGER_SIZE*62:
            return 62;
            break;
        case MEMORY_MANAGER_SIZE*63:
            return 63;
#endif
            break;
        default:
            break;
    }
    return -1;
}

///
/// this malloc returns -1 for failure (normal malloc returns 0)
/// this is becase we are returning DMA pointers for ease and so that means
/// that 0 is a valid dma pointer to return
int __attribute__ ((warn_unused_result)) memory_manger_get(void) {
    if (_mgr.available == 0) {
        // return a "null pointer"
        // when we are full
        return -1;
    }
    // how to avoid? In c++ I would use a hash map
    // in the other direction I used a 
    for(unsigned int i = 0; i < MEMORY_MANAGER_CHUNKS; ++i) {
        if(_mgr.full[i] == 0) {
            MMSET_REG(x4, 0xaaaa0000);
            MMSET_REG(x4, i);
            _mgr.available--;
            _mgr.full[i] = 1;
            return _mgr.chunk_dma_address[i];
        }
    }

    // should never get here
    return -1;
}


void memory_manger_free(const unsigned int p) {
    const int index = memory_manger_index_for_ptr(p);
    MMSET_REG(x3, 0xdeaddead);
    MMSET_REG(x3, p);
    MMSET_REG(x3, index);
    if( index == -1 ) {
        _mgr.illegal_free_count++;
        return; // do nothing because we were passed an invalid pointer
    }

    if( _mgr.full[index] != 1 ) {
        // error condition, this happens when full is 0 aka empty
        // in this case we did a double
        _mgr.double_free_count++;
    } else {
        _mgr.available++;
    }

    _mgr.full[index] = 0;


}


unsigned int memory_manager_available(void) {
    return _mgr.available;
}


// define a global imem struct static
// define setup
// define allocate free
// define capactiy left
// integrate and test
// parse should call
// callback(int *header, int* body, int index, int max_index)

// when index == 0 is only time header is valid, if you need stuff copy it
// next N calls will be for the same header, guarenteed





// Leave these as comments that way we can know if double include
// #undef MEMORY_MANAGER_SIZE
// #undef MEMORY_MANAGER_CHUNKS
// #undef _SIZE

#undef MM_DISABLE_SET_REG
#endif