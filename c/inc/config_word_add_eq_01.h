#ifndef __CONFIG_WORD_ADD_EQ_01_H__
#define __CONFIG_WORD_ADD_EQ_01_H__

VMEM_SECTION unsigned short config_word_add_eq_01 [32] = {
    0x5a66, // add
    0x5a66,
    0x5a66,
    0x5a66,
    0x5a66,
    0x5a66,
    0x5a66,
    0x5a66,

    0x0000, 0x0000, // non-rx4

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
