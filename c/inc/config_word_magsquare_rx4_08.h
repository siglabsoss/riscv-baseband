#ifndef __CONFIG_WORD_MAGSQUARE_RX4_08_H__
#define __CONFIG_WORD_MAGSQUARE_RX4_08_H__

VMEM_SECTION unsigned short config_word_magsquare_rx4_08 [32] = {
    0x5000, // magsquare
    0x5000,
    0x5000,
    0x5000,
    0x5000,
    0x5000,
    0x5000,
    0x5000,

    0x5555, 0x5555, // rx4

    0x0808,  // bs = 08
    0x0808,
    0x0808,
    0x0808,
    0x0808,
    0x0808,
    0x0808,
    0x0808,
 
    
    0x0202, // funnel   k8, k9
    // 0x0200, // funnel   k9, 
    0x0002,

    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

#endif
