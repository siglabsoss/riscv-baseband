#ifndef __SLICE_CONSTANTS_HPP__
#define __SLICE_CONSTANTS_HPP__

#define VLEN (16)
#define KLEN (32)
#define NREGS (8)
#define MVL (32)
#define NSLICES (32)

// how many addresses of a 32-bit memory is there
#define MEM_SIZE (2048)

// how many vex-riscv registers are there?
#define VEX_REGS (32)
#define N_K_REGS (16)

#define N_VECTOR_OPS (16)
//
#define OPCODE_NOP       (0x0)
#define OPCODE_ADD       (0x1)
#define OPCODE_SUB       (0x2)
#define OPCODE_AND       (0x3)
#define OPCODE_OR        (0x4)
#define OPCODE_XOR       (0x5)
#define OPCODE_MV        (0x6)
#define OPCODE_ROL       (0x8)
#define OPCODE_ROR       (0x9)
#define OPCODE_MV_X_V    (0xA) //Move EXT to VREG
#define OPCODE_MV_K15_V  (0xB) //Move K15 scratch to VREG
#define OPCODE_MV_V_K15   (0xF)  //Move VREG to scratch K7




// These define the locaiton and width of opcode bitfields


#define OPCODE_DS_SHIFT (7)
#define OPCODE_DS_MASK (0xF)

#define OPCODE_OP_SHIFT (7+4)
#define OPCODE_OP_MASK (0xF)

#define OPCODE_RS1_SHIFT (7+4+4)
#define OPCODE_RS1_MASK (0x1F)

#define OPCODE_S2_SHIFT (7+4+4+5)
#define OPCODE_S2_MASK (0xF)

#define OPCODE_K_SHIFT (7+4+4+5+4)
#define OPCODE_K_MASK (0xF)

#define OPCODE_S1_SHIFT (7+4+4+5+4+4)
#define OPCODE_S1_MASK (0xF)


// bank address
#define MEMORY_ADDR_SHIFT (0)
#define MEMORY_ADDR_MASK  (0x7FF)

#define MEMORY_PERMUTATION_SHIFT (11)
#define MEMORY_PERMUTATION_MASK  (0x1F)


//#define MEMORY_G_SHIFT ()




// string util

#define HEX_STRING(n) std::hex << (n) << std::dec

// bit util

#define BIT_SHIFT_MASK(val, shift) (((val) >> (shift))&0x1)

// 32bit or less bitmask
// This will set bit a through bit b (inclusive), as long as 0 <= a <= 31 and 0 <= b <= 31.
#define BIT_MASK32(a, b) (((uint32_t) -1 >> (31 - (b))) & ~((1U << (a)) - 1))


#endif
