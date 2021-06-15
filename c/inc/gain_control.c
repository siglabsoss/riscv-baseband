#include "gain_control.h"
#include "csr_control.h"

void _set_vga_channel(unsigned int vga_channel, unsigned int clock_delay,
                                                unsigned int gain){
    unsigned int mosi;
    unsigned int sclk;
    unsigned int cs_n;
    unsigned int dsa_channel;

    if(vga_channel == CHANNEL_A){
        mosi = VGA_CTRL_A_MOSI;
        sclk = VGA_CTRL_A_SCLK;
        cs_n = VGA_CTRL_A_CS_N;
        dsa_channel = DSA_CTRL_A;
    }
    else{
        mosi = VGA_CTRL_B_MOSI;
        sclk = VGA_CTRL_B_SCLK;
        cs_n = VGA_CTRL_B_CS_N;
        dsa_channel = DSA_CTRL_B;
    }
    // In this case, it is better to enable all GPIO pins as opposed to
    // selectively enabling certain pin because all disabled pins will go to
    // zero. This is not ideal for pins that are active low i.e TX and reset
    // pins
    CSR_WRITE(GPIO_WRITE_EN, ALL_GPIO_PIN);
    for(unsigned int i = 16; i-- > 0;){
        // Change data bit MOSI
        if((gain>>i)&1){
            CSR_CLEAR_BITS(GPIO_WRITE, sclk|cs_n);
            CSR_SET_BITS(GPIO_WRITE, mosi);
        }
        else{
            CSR_CLEAR_BITS(GPIO_WRITE, sclk|mosi|cs_n);
        }

        // Hold data bit MOSI for positive and negative clock cycle
        for(unsigned int j = 0; j < clock_delay; j++){
            asm("nop");
        }
        CSR_SET_BITS(GPIO_WRITE, sclk);
        for(unsigned int j = 0; j < clock_delay; j++){
            asm("nop");
        }
    }
    CSR_CLEAR_BITS(GPIO_WRITE, sclk|mosi);
    CSR_SET_BITS(GPIO_WRITE, cs_n|dsa_channel);
}

void __attribute__((deprecated)) set_vga_gain(unsigned int data){
    unsigned int clock_delay = 400;
    unsigned int vga_channel = data&CHANNEL_A;

    _set_vga_channel(vga_channel, clock_delay, data);
}

void __attribute__((deprecated)) set_dsa_gain(unsigned int data){
    unsigned int dsa_channel = data&CHANNEL_A;

    CSR_WRITE(GPIO_WRITE_EN, ALL_GPIO_PIN);
    if(dsa_channel == CHANNEL_A){
        CSR_SET_BITS(GPIO_WRITE, data&DSA_CTRL_A);
        CSR_CLEAR_BITS(GPIO_WRITE, (~data)&DSA_CTRL_A);
    }
    else{
        CSR_SET_BITS(GPIO_WRITE, data);
        CSR_CLEAR_BITS(GPIO_WRITE, (~data)&DSA_CTRL_B);
    }
}

void __attribute__((deprecated)) disable_dac(unsigned int data){
    (void)data;
    CSR_CLEAR_BITS(GPIO_WRITE, DAC_RESETN_BIT);
    CSR_CLEAR_BITS(GPIO_WRITE, DAC_SDENN_BIT);
}

// pass 0 in data for enabling DAC
// pass 1 in data to disable DAC
void __attribute__((deprecated)) config_dac(unsigned int data){
    unsigned int clock_delay = 400;
    CSR_WRITE(GPIO_WRITE_EN, ALL_GPIO_PIN);
    for(unsigned int j = 0; j < clock_delay; j++){
      asm("nop");
    };
    CSR_SET_BITS(GPIO_WRITE, DAC_RESETN_BIT);
    for(unsigned int i = 24; i-- > 0;){
        // Change data bit DAC_SDIO_BIT
        if((data>>i)&1){
            CSR_CLEAR_BITS(GPIO_WRITE, DAC_SCLK_BIT|DAC_SDENN_BIT);
            CSR_SET_BITS(GPIO_WRITE, DAC_SDIO_BIT);
        }
        else{
            CSR_CLEAR_BITS(GPIO_WRITE, DAC_SCLK_BIT|DAC_SDIO_BIT|DAC_SDENN_BIT);
        }

        // Hold data bit DAC_SDIO_BIT for positive and negative clock cycle
        for(unsigned int j = 0; j < clock_delay; j++){
            asm("nop");
        }
        CSR_SET_BITS(GPIO_WRITE, DAC_SCLK_BIT);
        for(unsigned int j = 0; j < clock_delay; j++){
            asm("nop");
        }
    }

    for(unsigned int k = 0; k < 2; k++){
        if(!k){
            CSR_CLEAR_BITS(GPIO_WRITE, DAC_SDIO_BIT|DAC_SCLK_BIT);
        }
    };

    CSR_SET_BITS(GPIO_WRITE, DAC_SDENN_BIT);
}