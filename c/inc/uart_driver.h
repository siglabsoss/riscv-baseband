#ifndef __UART_DRIVER_H__
#define __UART_DRIVER_H__

void uart_put_char(const char value);
void uart_put_char_interrupt(const char value);
char uart_get_char(int *error);
unsigned uart_get_occupancy(void);

#endif
