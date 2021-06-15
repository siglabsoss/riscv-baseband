#ifndef __CONFIG_WORD_MAGSQUARE_RX4_03_H__
#define __CONFIG_WORD_MAGSQUARE_RX4_03_H__

VMEM_SECTION unsigned short config_word_magsquare_rx4_03 [32] = {
    0x5000, // magsquare
    0x5000,
    0x5000,
    0x5000,
    0x5000,
    0x5000,
    0x5000,
    0x5000,

    0x5555, 0x5555, // rx4

    0x0303,  // bs = 03
    0x0303,
    0x0303,
    0x0303,
    0x0303,
    0x0303,
    0x0303,
    0x0303,
 
    
    0x0202, // funnel   k8, k9
    // 0x0200, // funnel   k9, 
    0x0002,

    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

#endif
