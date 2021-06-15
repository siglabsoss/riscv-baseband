#ifndef __CONFIG_WORD_CONJ_RX4_0F_H__
#define __CONFIG_WORD_CONJ_RX4_0F_H__

VMEM_SECTION unsigned short config_word_conj_rx4_0f [32] = {
    0x4451, // conj
    0x4451,
    0x4451,
    0x4451,
    0x4451,
    0x4451,
    0x4451,
    0x4451,

    0x5555, 0x5555, // non-rx4

    0x0f0f,  // bs = 0f
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
 
    
    0x0202, // funnel   k8, k9
    // 0x0200, // funnel   k9, 
    0x0002,

    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

#endif
