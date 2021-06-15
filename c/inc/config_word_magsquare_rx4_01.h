#ifndef __CONFIG_WORD_MAGSQUARE_RX4_01_H__
#define __CONFIG_WORD_MAGSQUARE_RX4_01_H__

VMEM_SECTION unsigned short config_word_magsquare_rx4_01 [32] = {
    0x5000, // magsquare
    0x5000,
    0x5000,
    0x5000,
    0x5000,
    0x5000,
    0x5000,
    0x5000,

    0x5555, 0x5555, // rx4

    0x0101,  // bs = 01
    0x0101,
    0x0101,
    0x0101,
    0x0101,
    0x0101,
    0x0101,
    0x0101,
 
    
    0x0202, // funnel   k8, k9
    // 0x0200, // funnel   k9, 
    0x0002,

    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

#endif