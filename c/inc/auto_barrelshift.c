#include "auto_barrelshift.h"
#include "copy_config.h"

#define SQ3X(x) ((int64_t)(((int64_t)x))*(((int64_t)x))*((int64_t)3l))


int run_auto_bs(auto_bs_t* const s, const unsigned* const data_src_cpu ) {
    if( s->count < s->max_freq ) {
        s->count++;
        return s->prev_shift;
    }
    s->count = 0;

    const int shift = run_auto_bs_core(s, data_src_cpu);


    if( shift != s->prev_shift ) {
        copy_set_barrel(s->cfg_source, s->cfg_dest, shift);
        s->prev_shift = shift;
    }

    return shift;
}



int run_auto_bs_core(auto_bs_t* const s, const unsigned* const data_src_cpu ) {
    // load from vmem to dmem once to be less expensive
    unsigned load[3];
    load[0] = data_src_cpu[s->idx[0]];
    load[1] = data_src_cpu[s->idx[1]];
    load[2] = data_src_cpu[s->idx[2]];



    // int64_t re = 0;
    // int64_t im = 0;

    int64_t mag_squared = 0;

    for(int i = 0; i < 3; i++) {
        const int64_t re =  (int16_t) ((load[i]) & 0xffff);
        const int64_t im =  (int16_t)(((load[i])>>16) & 0xffff);
        mag_squared += (re*re)+(im*im);
    }

    // const int64_t mag_squared = (re*re)+(im*im);



    // x            0x5
    // 0x40         0x6
    // 0x80         0x7
    // 0x100        0x8
    // 0x200        0x9
    // 0x400        0xa
    // 0x800        0xb
    // 0x1000       0xd
    // 0x2000       0xc
    // 0x4000       0xe
    // 0x8000       0xf

    int shift = 0x10; // default for large values

    if( mag_squared < SQ3X(0x20)  ) {
        shift = 0x5;
    } else if( mag_squared < SQ3X(0x40)  ) {
        shift = 0x6;
    } else if( mag_squared < SQ3X(0x80l) ) {
        shift = 0x7;
    } else if( mag_squared < SQ3X(0x100l) ) {
        shift = 0x8;
    } else if( mag_squared < SQ3X(0x200l) ) {
        shift = 0x9;
    } else if( mag_squared < SQ3X(0x400l) ) {
        shift = 0xa;
    } else if( mag_squared < SQ3X(0x800l) ) {
        shift = 0xb;
    } else if( mag_squared < SQ3X(0x1000l) ) {
        shift = 0xc;
    } else if( mag_squared < SQ3X(0x2000l) ) {
        shift = 0xd;
    } else if( mag_squared < SQ3X(0x4000l) ) {
        shift = 0xe;
    } else if( mag_squared < SQ3X(0x8000l) ) {
        shift = 0xf;
    }

    return shift+1;
}
