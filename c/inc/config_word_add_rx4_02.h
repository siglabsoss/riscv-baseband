#ifndef __CONFIG_WORD_ADD_RX4_02_H__
#define __CONFIG_WORD_ADD_RX4_02_H__

VMEM_SECTION unsigned short config_word_add_rx4_02 [32] = {
    0x5a66, // add
    0x5a66,
    0x5a66,
    0x5a66,
    0x5a66,
    0x5a66,
    0x5a66,
    0x5a66,

    0x5555, 0x5555, // non-rx4

    0x0202,  // bs = 0f
    0x0202,
    0x0202,
    0x0202,
    0x0202,
    0x0202,
    0x0202,
    0x0202,
 
    
    0x0202, // funnel   k8, k9
    // 0x0200, // funnel   k9, 
    0x0002,

    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

#endif
