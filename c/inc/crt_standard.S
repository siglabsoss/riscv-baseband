# we made our own .init.text seciton and made sure it goes first in the ld file
.section .init.text
 
.global _start
_start:
.=0x0
j __init


.=0x20
mret


__init:

// put the start in a5
__determine_start_bss:
lui  a5,       %hi(__bss_vma_start)       // load msg(hi)
addi a5, a5,   %lo(__bss_vma_start)       // load msg(lo)

// put the end in a4
__determine_end_bss:
lui  a4,       %hi(__bss_vma_end)
addi a4, a4,   %lo(__bss_vma_end)

// If there are no BSS variables, skip initialization
beq a4, a5,  __clear_register

__fill_zero_loop:
sw zero, 0(a5)
addi a5, a5, 4

bne a5, a4, __fill_zero_loop  // if start is not the same as end, jump back to the loop

__reset_interrupt_reg:
li t0, 0
csrw mie, t0
li t0, 0
csrw mip, t0
li t0, 0
csrw mstatus, t0


__clear_register:
addi x1, zero, 0
addi x2, zero, 0
addi x3, zero, 0
addi x4, zero, 0
addi x5, zero, 0
addi x6, zero, 0
addi x7, zero, 0
addi x8, zero, 0
addi x9, zero, 0
addi x10, zero, 0
addi x11, zero, 0
addi x12, zero, 0
addi x13, zero, 0
addi x14, zero, 0
addi x15, zero, 0
addi x16, zero, 0
addi x17, zero, 0
addi x18, zero, 0
addi x19, zero, 0
addi x20, zero, 0
addi x21, zero, 0
addi x22, zero, 0
addi x23, zero, 0
addi x24, zero, 0
addi x25, zero, 0
addi x26, zero, 0
addi x27, zero, 0
addi x28, zero, 0
addi x29, zero, 0
addi x30, zero, 0
addi x31, zero, 0




__set_stack_pointer:
lui sp,      %hi(__sp_start)
addi sp, sp, %lo(__sp_start)

jal ra, main

.global __halt_main
__halt_main:
j __halt_main


// pad the end of this file with 4 literal zeros:
// this prevents gcc from packing a function immediately after __halt_main.
// some testbenches look at `iBus_cmd_payload_pc` which may be 1 or 2 ahead of
// PC, in order to determine if cpu has exited main().  This padding prevents
// false detections of a finished cpu
.word(0)
.word(0)
.word(0)
.word(0)