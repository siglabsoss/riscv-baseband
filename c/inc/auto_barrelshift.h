#ifndef __AUTO_BARRELSHIFT_H__
#define __AUTO_BARRELSHIFT_H__

#include <stdint.h>


//this is a FFT schedule
typedef struct auto_bs_t {
    unsigned idx[3];
    unsigned short* cfg_source;   // cpu pointer
    unsigned short* cfg_dest;     // cpu pointer
    unsigned max_freq;
    unsigned count;
    int prev_shift;
} auto_bs_t;


int run_auto_bs(auto_bs_t* const s, const unsigned* const data_src_cpu );
int run_auto_bs_core(auto_bs_t* const s, const unsigned* const data_src_cpu );


#endif
