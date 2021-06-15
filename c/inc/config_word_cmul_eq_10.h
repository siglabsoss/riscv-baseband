#ifndef __CONFIG_WORD_CMUL_EQ_10_H__
#define __CONFIG_WORD_CMUL_EQ_10_H__

VMEM_SECTION unsigned short config_word_cmul_eq_10 [32] = {
    0x4451, // cmul
    0x4451,
    0x4451,
    0x4451,
    0x4451,
    0x4451,
    0x4451,
    0x4451,

    0x0000, 0x0000, // non-rx4

    0x1010,  // bs = 0f
    0x1010,
    0x1010,
    0x1010,
    0x1010,
    0x1010,
    0x1010,
    0x1010,
 
    
    0x0202, // funnel   k8, k9
    // 0x0200, // funnel   k9, 
    0x0002,

    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

#endif