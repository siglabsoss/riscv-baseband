#include "uart_driver.h"
#include "csr_control.h"
// #include <stdint.h>

void uart_put_char(const char value) {
    uart_write[0] = value;
}



void uart_put_char_interrupt(const char value) {
    uart_write[0] = value;
    CSR_WRITE(GPIO_WRITE_EN, 1);
    CSR_WRITE(GPIO_WRITE, 1);
    for(int i = 0; i < 260; i++) {
        STALL(100);
    }
    CSR_WRITE(GPIO_WRITE, 0);

}


char uart_get_char(int *error) {
    const unsigned int read_occ = (uart_occupancy[0] & UART_RD_OCCUPANCY_MASK) >> UART_RD_OCCUPANCY_SHIFT;

    if( read_occ == 0 ) {
        *error = 1;
        return 0;
    } else {
        unsigned int data = uart_read[0];
        *error = 0;
        return data & 0xff;
    }
}

unsigned uart_get_occupancy(void) {
    const unsigned int read_occ = (uart_occupancy[0] & UART_RD_OCCUPANCY_MASK) >> UART_RD_OCCUPANCY_SHIFT;

    return read_occ;
}