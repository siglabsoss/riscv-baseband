#ifndef __CSR_CONTROL_H__
#define __CSR_CONTROL_H__

#include "xbaseband.h"
#define CSR_DMA_0_BASE (0xB08)
#define CSR_DMA_1_BASE (0xB18)
#define CSR_DMA_2_BASE (0xB28)
#define CSR_TIMER_BASE (0xE00)
#define CSR_RINGBUS_BASE (0xE10)
#define CSR_RINGBUS_2_BASE (0xE30)
#define CSR_GPIO_BASE (0xE20)
#define CSR_NCO_BASE (0xE40)
#define CSR_SLICER_BASE (0xE50)
#define CSR_SATDETECT_BASE (0xE60)
#define CSR_CS_BASE (0xE70)
#define CSR_MAPMOV_BASE (0xC00)
#define CSR_DENGINE (0xE80)

// input DMA chip to chip
#define DMA_0_START_ADDR          (CSR_DMA_0_BASE + 0)
#define DMA_0_LENGTH              (CSR_DMA_0_BASE + 1)
#define DMA_0_TIMER_VAL           (CSR_DMA_0_BASE + 2)
#define DMA_0_PUSH_SCHEDULE       (CSR_DMA_0_BASE + 3)
#define DMA_0_STATUS              (CSR_DMA_0_BASE + 4)
#define DMA_0_SCHEDULE_OCCUPANCY  (CSR_DMA_0_BASE + 5)
#define DMA_0_FLUSH_SCHEDULE      (CSR_DMA_0_BASE + 6)
#define DMA_0_INTERRUPT_CLEAR     (CSR_DMA_0_BASE + 7)
#define DMA_0_REVERSE             (CSR_DMA_0_BASE + 9)
#define DMA_0_LAST_RTL            (CSR_DMA_0_BASE + 10)
#define DMA_0_MCAUSE              (0xB)
#define DMA_0_ENABLE_BIT          (0x800)
#define DMA_0_SCHEDULE_DEPTH      (4)

// output DMA chip to chip
#define DMA_1_START_ADDR          (CSR_DMA_1_BASE + 0)
#define DMA_1_LENGTH              (CSR_DMA_1_BASE + 1)
#define DMA_1_TIMER_VAL           (CSR_DMA_1_BASE + 2)
#define SLICER                    (CSR_DMA_1_BASE + 8)
#define DMA_1_PUSH_SCHEDULE       (CSR_DMA_1_BASE + 3)
#define DMA_1_STATUS              (CSR_DMA_1_BASE + 4)
#define DMA_1_SCHEDULE_OCCUPANCY  (CSR_DMA_1_BASE + 5)
#define DMA_1_FLUSH_SCHEDULE      (CSR_DMA_1_BASE + 6)
#define DMA_1_INTERRUPT_CLEAR     (CSR_DMA_1_BASE + 7)
#define DMA_1_REVERSE             (CSR_DMA_1_BASE + 9)
#define DMA_1_LAST_RTL            (CSR_DMA_1_BASE + 10)
#define DEMAPPER_CONSTELLATION    (CSR_DMA_1_BASE + 11)
#define DEMAPPER_TWO_OVER_SIGMA_SQ (CSR_DMA_1_BASE + 12)
#define DMA_1_MCAUSE              (0xF)
#define DMA_1_ENABLE_BIT          (0x8000)
#define DMA_1_SCHEDULE_DEPTH      (4)

// input DMA from nco
#define DMA_2_START_ADDR          (CSR_DMA_2_BASE + 0)
#define DMA_2_LENGTH              (CSR_DMA_2_BASE + 1)
#define DMA_2_TIMER_VAL           (CSR_DMA_2_BASE + 2)
#define DMA_2_PUSH_SCHEDULE       (CSR_DMA_2_BASE + 3)
#define DMA_2_STATUS              (CSR_DMA_2_BASE + 4)
#define DMA_2_SCHEDULE_OCCUPANCY  (CSR_DMA_2_BASE + 5)
#define DMA_2_FLUSH_SCHEDULE      (CSR_DMA_2_BASE + 6)
#define DMA_2_INTERRUPT_CLEAR     (CSR_DMA_2_BASE + 7)
#define DMA_2_REVERSE             (CSR_DMA_2_BASE + 9)
#define DMA_2_LAST_RTL            (CSR_DMA_2_BASE + 10)
#define DMA_2_MCAUSE              (0xB)
#define DMA_2_ENABLE_BIT          (0x80000)
#define DMA_2_SCHEDULE_DEPTH      (4)

#define NCO_START_ANGLE           (CSR_NCO_BASE + 0)
#define NCO_LENGTH                (CSR_NCO_BASE + 1)
#define NCO_DELTA                 (CSR_NCO_BASE + 2)
#define NCO_PUSH_SCHEDULE         (CSR_NCO_BASE + 3)
#define NCO_STATUS                (CSR_NCO_BASE + 4)
#define NCO_SCHEDULE_OCCUPANCY    (CSR_NCO_BASE + 5)
#define NCO_FLUSH_SCHEDULE        (CSR_NCO_BASE + 6)
#define NCO_SCHEDULE_DEPTPH       (4)

#define MAPMOV_MOVER_ACTIVE       (CSR_MAPMOV_BASE + 0)
#define MAPMOV_TRIM_START         (CSR_MAPMOV_BASE + 32)
#define MAPMOV_TRIM_END           (CSR_MAPMOV_BASE + 33)
#define MAPMOV_PILOT_RAM_ADDR     (CSR_MAPMOV_BASE + 34)
#define MAPMOV_PILOT_RAM_WDATA    (CSR_MAPMOV_BASE + 35)
#define MAPMOV_PILOT_RAM_WE       (CSR_MAPMOV_BASE + 36)
#define MAPMOV_RESET              (CSR_MAPMOV_BASE + 37)
#define MAPMOV_ONE_VALUE          (CSR_MAPMOV_BASE + 38)
#define MAPMOV_ZERO_VALUE         (CSR_MAPMOV_BASE + 39)

// mcause will have bit 0x8000000 set for interrupts
// andd clear for traps
#define MCAUSE_INTERRUPT_FLAG           (0x7FFFFFFF)
#define MCAUSE_INTERRUPT_BIT            (0x80000000)

#define TIMER_VALUE                (CSR_TIMER_BASE + 0)
#define TIMER_CLEAR                (CSR_TIMER_BASE + 1)

#define START_IMMED_TIME (0xFFFFFFFF)
#define RINGBUS_WRITE_ADDR         (CSR_RINGBUS_BASE + 0)
#define RINGBUS_WRITE_DATA         (CSR_RINGBUS_BASE + 1)
#define RINGBUS_WRITE_EN           (CSR_RINGBUS_BASE + 2)
#define RINGBUS_WRITE_DONE         (CSR_RINGBUS_BASE + 3)
#define RINGBUS_INTERRUPT_CLEAR    (CSR_RINGBUS_BASE + 5)
#define RINGBUS_SCHEDULE_OCCUPANCY (CSR_RINGBUS_BASE + 6)
#define RINGBUS_FLUSH_SCHEDULE     (CSR_RINGBUS_BASE + 7)
#define RINGBUS_READ_DATA          (CSR_RINGBUS_BASE + 8)
#define RINGBUS_READ_OCCUPANCY     (CSR_RINGBUS_BASE + 9)
#define RINGBUS_READ_FLUSH         (CSR_RINGBUS_BASE + 10)
#define RINGBUS_ENABLE_BIT         (0x80000)
#define RINGBUS_SCHEDULE_DEPTH     (16)

#define RINGBUS_2_WRITE_ADDR         (CSR_RINGBUS_2_BASE + 0)
#define RINGBUS_2_WRITE_DATA         (CSR_RINGBUS_2_BASE + 1)
#define RINGBUS_2_WRITE_EN           (CSR_RINGBUS_2_BASE + 2)
#define RINGBUS_2_WRITE_DONE         (CSR_RINGBUS_2_BASE + 3)
#define RINGBUS_2_INTERRUPT_CLEAR    (CSR_RINGBUS_2_BASE + 5)
#define RINGBUS_2_SCHEDULE_OCCUPANCY (CSR_RINGBUS_2_BASE + 6)
#define RINGBUS_2_FLUSH_SCHEDULE     (CSR_RINGBUS_2_BASE + 7)
#define RINGBUS_2_READ_DATA          (CSR_RINGBUS_2_BASE + 8)
#define RINGBUS_2_READ_OCCUPANCY     (CSR_RINGBUS_2_BASE + 9)
#define RINGBUS_2_READ_FLUSH         (CSR_RINGBUS_2_BASE + 10)
#define RINGBUS_2_ENABLE_BIT         (0x80000000)
#define RINGBUS_2_SCHEDULE_DEPTH     (16)

//#define SLICER                    (CSR_SLICER_BASE + 0)
#define SATDETECT                 (CSR_SATDETECT_BASE + 0)

#define GPIO_WRITE                (CSR_GPIO_BASE + 0)
#define GPIO_WRITE_EN             (CSR_GPIO_BASE + 1)
#define GPIO_READ                 (CSR_GPIO_BASE + 2)

#define CS_STATUS                 (CSR_CS_BASE + 0)
#define CS_CONTROL                (CSR_CS_BASE + 1)

#define DENGINE_RESET                 (CSR_DENGINE_BASE + 0)
#define DENGINE_FUNC0_MIN_THRESHOLD   (CSR_DENGINE_BASE + 1)
#define DENGINE_FUNC0_MAX_THRESHOLD   (CSR_DENGINE_BASE + 2)
#define DENGINE_FUNC1_MIN_THRESHOLD   (CSR_DENGINE_BASE + 3)
#define DENGINE_FUNC1_MAX_THRESHOLD   (CSR_DENGINE_BASE + 4)

#define CSR_WRITE(addr,val) asm volatile("csrw "   _XSTR(addr)    ", %0" : : "r" (val))
#define CSR_WRITE_ZERO(addr) asm volatile("csrw "   _XSTR(addr)    ", zero" : : )
#define CSR_READ(addr,valout)  asm volatile("csrr  %0, " _XSTR(addr) : "=r" (valout) : )

// UART related defintions
#define UART_WRITE_ADDR         (0xF0000000)
#define UART_READ_ADDR          (0xF0000000)
// [20:16] Write occupancy [28:24] Read occupancy
#define UART_OCCUPANCY_ADDR     (0xF0000004)
#define UART_FRAME_ADDR         (0xF000000C)
#define UART_CLOCK_DIVIDER_ADDR (0xF0000008)

#define UART_RD_OCCUPANCY_MASK        (0xff000000)
#define UART_RD_OCCUPANCY_SHIFT       (24)

#define UART_WR_OCCUPANCY_MASK        (0xff0000)
#define UART_WR_OCCUPANCY_SHIFT       (16)

#define UART_SCHEDULE_DEPTH           (16)


#define uart_write ((volatile unsigned int *) UART_WRITE_ADDR)
#define uart_read ((volatile unsigned int *) UART_READ_ADDR)
#define uart_occupancy ((volatile unsigned int *) UART_OCCUPANCY_ADDR)
#define uart_clock_divider ((volatile unsigned int *) UART_CLOCK_DIVIDER_ADDR)

#define UART_READ_OCCUPANCY()  (UART_SCHEDULE_DEPTH-(((*uart_occupancy)&UART_RD_OCCUPANCY_MASK)>>UART_RD_OCCUPANCY_SHIFT))
#define UART_WRITE_OCCUPANCY() (UART_SCHEDULE_DEPTH-(((*uart_occupancy)&UART_WR_OCCUPANCY_MASK)>>UART_WR_OCCUPANCY_SHIFT))
////////////////////
//
// This modifies the CSR by OR ing the bitmask value
// the PREVIOUS value of what was in the CSR is returned in the previous_value
//
// Example:
//     CSR_WRITE(GPIO_WRITE, LED_GPIO_BIT);  // old way writes zeros to other bits
// Replaced with:
//     CSR_SET_BITS(GPIO_WRITE, LED_GPIO_BIT); // sets led bit, leaves other gpio aline
// or:
//     CSR_SET_BITS(GPIO_WRITE, LED_GPIO_BIT | 0x10); // all bits set at once
//
//
#define CSR_READ_SET_BITS(addr,bitmask,previous_value) \
\
asm volatile("csrrs  %0, " _XSTR(addr) ",%1 ": "=r" (previous_value) : "r" (bitmask) )

#define CSR_SET_BITS(addr,bitmask) \
\
asm volatile("csrrs  x0, " _XSTR(addr) ",%0 ": :"r" (bitmask) )

#define CSR_READ_CLEAR_BITS(addr,bitmask,previous_value) \
\
asm volatile("csrrc  %0, " _XSTR(addr) ",%1 ": "=r" (previous_value) : "r" (bitmask) )

#define CSR_CLEAR_BITS(addr,bitmask) \
\
asm volatile("csrrc  x0, " _XSTR(addr) ",%0 ": :"r" (bitmask) )


// can only be used for immediate values (not variables)
#define SET_HALF_REG(reg,val) \
\
asm volatile("lui  " _XSTR(reg) ", %0" : :"r" (val&0xfffff) )

// call with values or variables to set any register
// Stick to using x3,x4 because gcc will not be happy if others are touched
#define SET_REG(reg,val) \
\
asm volatile("addi  " _XSTR(reg) ", %0, 0" : :"r" (val) )


#define GET_REG(reg,valout) \
\
asm volatile("addi %0, " _XSTR(reg) " , 0" : "=r" (valout) : )


#define SET_HALF_REG_VAR(reg,val) SET_REG(reg,val)

// asm volatile("lui  x3,   (0xdeadbeef) & 0xfffff ");

// lui  a5,       %hi(__bss_vma_start)       // load msg(hi)
// addi a5, a5,   %lo(__bss_vma_start)       // load msg(lo)

// csrrs x3, 0xe20, a6


// below is our wfi replacement

#define INTERRUPT_WAIT_CLEAR(x,y) \
while(1) { \
  unsigned int helper; \
  CSR_READ(mip, helper); \
  if( helper & x ) { \
    CSR_WRITE(y,0); \
    break; \
  } \
}

#define INTERRUPT_WAIT(x) \
while(1) { \
  unsigned int helper; \
  CSR_READ(mip, helper); \
  if( helper & x ) { \
    break; \
  } \
}

#define INTERRUPT_WAIT_CLEAR_DMA_0() INTERRUPT_WAIT_CLEAR(DMA_0_ENABLE_BIT, DMA_0_INTERRUPT_CLEAR)
#define INTERRUPT_WAIT_CLEAR_DMA_1() INTERRUPT_WAIT_CLEAR(DMA_1_ENABLE_BIT, DMA_1_INTERRUPT_CLEAR)
#define INTERRUPT_WAIT_CLEAR_RINGBUS() INTERRUPT_WAIT_CLEAR(RINGBUS_ENABLE_BIT, RINGBUS_INTERRUPT_CLEAR)


// helpers


#define ENABLE_MACHINE_INTERRUPTS() \
CSR_WRITE(mie, DMA_0_ENABLE_BIT | DMA_1_ENABLE_BIT | RINGBUS_ENABLE_BIT); \
CSR_WRITE(mip, DMA_0_ENABLE_BIT | DMA_1_ENABLE_BIT | RINGBUS_ENABLE_BIT); \
CSR_WRITE(mstatus, 0x008);

#define DISABLE_MACHINE_INTERRUPTS() \
CSR_WRITE(mie, 0x000); \
CSR_WRITE(mip, 0x000); \
CSR_WRITE(mstatus, 0x000);



// Board specific stuff

// Every board has an LED here
#define BIT_21                (0x200000)
#define BIT_20                (0x100000)
#define BIT_19                (0x080000)
#define BIT_18                (0x040000)
#define BIT_17                (0x020000)
#define BIT_16                (0x010000)
#define BIT_15                (0x008000)
#define BIT_14                (0x004000)
#define BIT_13                (0x002000)
#define BIT_12                (0x001000)
#define BIT_11                (0x000800)
#define BIT_10                (0x000400)
#define BIT_09                (0x000200)
#define BIT_08                (0x000100)
#define BIT_07                (0x000080)
#define BIT_06                (0x000040)
#define BIT_05                (0x000020)
#define BIT_04                (0x000010)
#define BIT_03                (0x000008)
#define BIT_02                (0x000004)
#define BIT_01                (0x000002)
#define BIT_00                (0x000001)
#define ALL_GPIO_PIN          (0x3fffff)
#define LED_GPIO_BIT          BIT_21        // 21 = LED_BIT
#define DAC_SDIO_BIT          BIT_20        // 20 = DAC_CTRL_SDIO
#define DAC_SDENN_BIT         BIT_19        // 19 = DAC_CTRL_SDENN
#define DAC_SCLK_BIT          BIT_18        // 18 = DAC_CTRL_SCLK
#define DAC_RESETN_BIT        BIT_17        // 17 = DAC_CTRL_RESETN
#define TX_CHANNEL_A_BIT      BIT_16        // 16 = TX_3V3_A
#define TX_CHANNEL_B_BIT      BIT_15        // 15 = TX_3V3_B
#define DSA_CTRL_A            (0x007c00)    // 14:10 = DSA_CTRL_A
#define DSA_CTRL_B            (0x0003c0)    // 9:6 = DSA_CTRL_B
#define VGA_CTRL_A_MOSI       BIT_05        // 5  = VGA_CTRL_A MOSI
#define VGA_CTRL_A_SCLK       BIT_04        // 4  = VGA_CTRL_A SCLK
#define VGA_CTRL_A_CS_N       BIT_03        // 3  = VGA_CTRL_A CS_N
#define VGA_CTRL_B_MOSI       BIT_02        // 2  = VGA_CTRL_B MOSI
#define VGA_CTRL_B_SCLK       BIT_01        // 1  = VGA_CTRL_B SCLK
#define VGA_CTRL_B_CS_N       BIT_00        // 0  = VGA_CTRL_B CS_N
#define DAC_MOD_PIN           (0x1e0000)
#define CHANNEL_A             (0x010000)    // code uses both this version and VGA_ versions
#define CHANNEL_B             (0x000000)
#define VGA_CHANNEL_A         (CHANNEL_A)
#define VGA_CHANNEL_B         (CHANNEL_B)
#define ADC_COUNTER_BIT       BIT_20
#define RESET_ADC_COUNTER     BIT_19
#endif
