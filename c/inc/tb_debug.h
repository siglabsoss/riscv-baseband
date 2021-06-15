#ifndef __TB_DEBUG_H__
#define __TB_DEBUG_H__

#include <stdint.h>
#include <stdarg.h>

#define PRINTF_MAX_FORMATS (32)

typedef struct __attribute__((__packed__)) hoist_t {
    const uint8_t* format;
    unsigned length;
    void *saved[PRINTF_MAX_FORMATS];
} hoist_t;






void setup_debug(void);
void dump_vmem_cpu(const uint8_t tag, const unsigned int* cpu, const unsigned int length);
void dump_vmem_dma(const uint8_t tag, const unsigned int dma, const unsigned int length);
void dump_vmem_row(const uint8_t tag, const unsigned int row, const unsigned int length);
void block_until_dump_done(void);
unsigned dump_remaining(void);
void dump_imem_words(const uint8_t tag, const unsigned int* addr, const unsigned int length);
void dump_imem_bytes(const uint8_t tag, const uint8_t* _addr, const unsigned int length);
void dump_imem_bytes_printf(const uint8_t* _addr, const unsigned int length);
void _puts(const char* msg);



/// seems like this _printf function doesn't work correctly if it's in a different
/// compilation unit
/// instead of fixing this, we just include it only one time, in main.c
/// when tb_debug.c includes it, we set this so we only get one copy
#ifndef EXCLUDE_PRINTF

///
/// Call this just like normal printf
/// DO NOT USE %%  just don't
void _printf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    int runs = 0;

    hoist_t hoist;
    hoist.format = (const uint8_t*)fmt;
    hoist.length = 0;

    unsigned intgr = 0;
 
    while (*fmt != '\0') {
        // SET_REG(x3, 0xffffffff);
        // SET_REG(x3, runs);
        switch(*fmt) {
            case '%':
                intgr = va_arg(args, unsigned);
                // SET_REG(x4, intgr);
                hoist.saved[hoist.length] = (void*)intgr;
                hoist.length++;
                break;
        }
        ++fmt;
        ++runs;

        if( hoist.length == PRINTF_MAX_FORMATS ) {
            break;
        }
    }

    dump_imem_bytes_printf((const uint8_t*)&hoist, sizeof(hoist));
    block_until_dump_done();
 
    va_end(args);
}

#endif








#ifdef DISABLE_TB_DEBUG
#define setup_debug(...)             __disabled_tb_debug_void()
#define dump_vmem_cpu(...)           __disabled_tb_debug_void()
#define dump_vmem_dma(...)           __disabled_tb_debug_void()
#define dump_vmem_row(...)           __disabled_tb_debug_void()
#define block_until_dump_done(...)   __disabled_tb_debug_void()
#define dump_remaining(...)          __disabled_dump_unsigned()
#define dump_imem_words(...)         __disabled_tb_debug_void()
#define dump_imem_bytes(...)         __disabled_tb_debug_void()
#define dump_imem_bytes_printf(...)  __disabled_tb_debug_void()
#define _printf(...)                 __disabled_tb_debug_void()
#define _puts(...)                   __disabled_tb_debug_void()

void __disabled_tb_debug_void(void);
unsigned __disabled_dump_unsigned(void);
#endif











#endif
