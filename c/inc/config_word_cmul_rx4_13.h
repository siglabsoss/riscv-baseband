#ifndef __CONFIG_WORD_CMUL_RX4_13_H__
#define __CONFIG_WORD_CMUL_RX4_13_H__

VMEM_SECTION unsigned short config_word_cmul_rx4_13 [32] = {
    0x4451, // cmul
    0x4451,
    0x4451,
    0x4451,
    0x4451,
    0x4451,
    0x4451,
    0x4451,

    0x5555, 0x5555, // rx4

    0x1313,  // barrel shift (8 bits)
    0x1313,
    0x1313,
    0x1313,
    0x1313,
    0x1313,
    0x1313,
    0x1313,

    
    0x0202, // funnel   k8, k9
    // 0x0200, // funnel   k9, 
    0x0002,

    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

#endif
