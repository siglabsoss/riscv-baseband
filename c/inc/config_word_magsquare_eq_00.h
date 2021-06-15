#ifndef __CONFIG_WORD_MAGSQUARE_EQ_00_H__
#define __CONFIG_WORD_MAGSQUARE_EQ_00_H__

VMEM_SECTION unsigned short config_word_magsquare_eq_00 [32] = {
    0x5000, // magsquare
    0x5000,
    0x5000,
    0x5000,
    0x5000,
    0x5000,
    0x5000,
    0x5000,

    0x0000, 0x0000, // non-rx4

    0x0000,  // bs = 0f
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
 
    
    0x0202, // funnel   k8, k9
    // 0x0200, // funnel   k9, 
    0x0002,

    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

#endif
