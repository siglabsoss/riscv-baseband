
#define EXCLUDE_PRINTF
#include "tb_debug.h"
#undef EXCLUDE_PRINTF

#include "uart_driver.h"
#include "csr_control.h"
#include "vmem.h"

// #include <string.h>


void setup_debug(void) {
    *uart_clock_divider = 0;
}

void dump_vmem_cpu(const uint8_t tag, const unsigned int* cpu, const unsigned int length) {
    dump_vmem_dma(tag, VMEM_DMA_ADDRESS(cpu), length);
}
void dump_vmem_row(const uint8_t tag, const unsigned int row, const unsigned int length) {
    dump_vmem_dma(tag, VMEM_ROW_ADDRESS_TO_DMA(row), length);
}

// heads up
// due to how 
// do not pass 0 for length, will result in all vmem dumped 
void dump_vmem_dma(const uint8_t tag, const unsigned int addr, const unsigned int length) {

    const unsigned int length_one = length - 1;

    uart_put_char(3);
    uart_put_char(7);
    uart_put_char(tag);
    uart_put_char(addr & 0xFF);
    uart_put_char((addr >> 8) & 0xFF);
    uart_put_char(length_one & 0xFF);
    uart_put_char((length_one >> 8) & 0xFF);
}

void block_until_dump_done(void) {
    while(UART_WRITE_OCCUPANCY() != 0) {
    }
    return;
}

unsigned dump_remaining(void) {
    return UART_WRITE_OCCUPANCY();
}

void dump_imem_words(const uint8_t tag, const unsigned int* _addr, const unsigned int length) {
    const unsigned int length_one = length - 1;
    const unsigned int addr = (unsigned int) _addr;

    uart_put_char(6);
    uart_put_char(7);
    uart_put_char(tag);
    uart_put_char(addr & 0xFF);
    uart_put_char((addr >> 8) & 0xFF);
    uart_put_char(length_one & 0xFF);
    uart_put_char((length_one >> 8) & 0xFF);
}

void dump_imem_bytes(const uint8_t tag, const uint8_t* _addr, const unsigned int length) {
    const unsigned int length_one = length - 1;
    const unsigned int addr = (unsigned int) _addr;

    uart_put_char(7);
    uart_put_char(7);
    uart_put_char(tag);
    uart_put_char(addr & 0xFF);
    uart_put_char((addr >> 8) & 0xFF);
    uart_put_char(length_one & 0xFF);
    uart_put_char((length_one >> 8) & 0xFF);
}

void dump_imem_bytes_printf(const uint8_t* _addr, const unsigned int length) {
    const unsigned int length_one = length - 1;
    const unsigned int addr = (unsigned int) _addr;

    uart_put_char(8);
    uart_put_char(7);
    uart_put_char(0);
    uart_put_char(addr & 0xFF);
    uart_put_char((addr >> 8) & 0xFF);
    uart_put_char(length_one & 0xFF);
    uart_put_char((length_one >> 8) & 0xFF);
}

void _printf(const char* fmt, ...);

void _puts(const char* msg) {
    _printf("%s\n", msg);
}












void __disabled_tb_debug_void(void) {}
unsigned __disabled_dump_unsigned(void) {return 0;}

