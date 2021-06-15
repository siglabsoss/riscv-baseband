// Xbaseband macro instructions

#ifndef __XBASEBAND_H__
#define __XBASEBAND_H__

#include "sig_utils.h"





#define VLEN (16)
#define KLEN (32)
#define NREGS (16)
#define MVL (32)
#define NSLICES (16)

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

#define OPCODE_RS2_SHIFT (20)
#define OPCODE_RS2_MASK (0x1F)

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


#define V0 0
#define V1 1
#define V2 2
#define V3 3
#define V4 4
#define V5 5
#define V6 6
#define V7 7


#define V8 8
#define V9 9
#define V10 10
#define V11 11
#define V12 12
#define V13 13
#define V14 14
#define V15 15


// static const int log2slices = 5;
// static const int slices = 32;
// static const int permShift = 12;

















/*
========================
Generating for VNOP - KNOP
========================
*/

#define VNOP_KNOP   asm   (".word((0x0b))")


























/*
========================
Generating for VNOP - SK1
========================
*/

#define VNOP_SK1(s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | (0x0b))")




























/*
========================
Generating for VNOP - SK2
========================
*/

#define VNOP_SK2(s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | (0x0b))")




























/*
========================
Generating for VNOP - SK13
========================
*/

#define VNOP_SK13(s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | (0x0b))")




























/*
========================
Generating for VNOP - SK15
========================
*/

#define VNOP_SK15(s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | (0x0b))")




























/*
========================
Generating for VNOP - LK8
========================
*/

#define VNOP_LK8(s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | (0x0b))")




























/*
========================
Generating for VNOP - LK9
========================
*/

#define VNOP_LK9(s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | (0x0b))")




























/*
========================
Generating for VNOP - LK10
========================
*/

#define VNOP_LK10(s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | (0x0b))")




























/*
========================
Generating for VNOP - LK11
========================
*/

#define VNOP_LK11(s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | (0x0b))")




























/*
========================
Generating for VNOP - LK13
========================
*/

#define VNOP_LK13(s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | (0x0b))")




























/*
========================
Generating for VNOP - LK14
========================
*/

#define VNOP_LK14(s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | (0x0b))")




























/*
========================
Generating for VNOP - LK15
========================
*/

#define VNOP_LK15(s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | (0x0b))")



























/*
========================
Generating for ADD - KNOP
========================
*/

#define _GET_OVERRIDE_ADD_KNOP(_1, _2, _3, _4, NAME, ...) NAME
      
#define ADD_KNOP(...) _GET_OVERRIDE_ADD_KNOP(__VA_ARGS__, ADD_KNOP_p, ADD_KNOP_np)(__VA_ARGS__)

      
#define ADD_KNOP_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ADD_KNOP_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")


























/*
========================
Generating for ADD - SK1
========================
*/
#define _GET_OVERRIDE_ADD_SK1(_1, _2, _3, _4, NAME, ...) NAME
      
#define ADD_SK1(...) _GET_OVERRIDE_ADD_SK1(__VA_ARGS__, ADD_SK1_p, ADD_SK1_np)(__VA_ARGS__)
      
#define ADD_SK1_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ADD_SK1_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ADD - SK2
========================
*/
#define _GET_OVERRIDE_ADD_SK2(_1, _2, _3, _4, NAME, ...) NAME
      
#define ADD_SK2(...) _GET_OVERRIDE_ADD_SK2(__VA_ARGS__, ADD_SK2_p, ADD_SK2_np)(__VA_ARGS__)
      
#define ADD_SK2_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ADD_SK2_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ADD - SK13
========================
*/
#define _GET_OVERRIDE_ADD_SK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define ADD_SK13(...) _GET_OVERRIDE_ADD_SK13(__VA_ARGS__, ADD_SK13_p, ADD_SK13_np)(__VA_ARGS__)
      
#define ADD_SK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ADD_SK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ADD - SK15
========================
*/
#define _GET_OVERRIDE_ADD_SK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define ADD_SK15(...) _GET_OVERRIDE_ADD_SK15(__VA_ARGS__, ADD_SK15_p, ADD_SK15_np)(__VA_ARGS__)
      
#define ADD_SK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ADD_SK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ADD - LK8
========================
*/
#define _GET_OVERRIDE_ADD_LK8(_1, _2, _3, _4, NAME, ...) NAME
      
#define ADD_LK8(...) _GET_OVERRIDE_ADD_LK8(__VA_ARGS__, ADD_LK8_p, ADD_LK8_np)(__VA_ARGS__)
      
#define ADD_LK8_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ADD_LK8_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ADD - LK9
========================
*/
#define _GET_OVERRIDE_ADD_LK9(_1, _2, _3, _4, NAME, ...) NAME
      
#define ADD_LK9(...) _GET_OVERRIDE_ADD_LK9(__VA_ARGS__, ADD_LK9_p, ADD_LK9_np)(__VA_ARGS__)
      
#define ADD_LK9_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ADD_LK9_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ADD - LK10
========================
*/
#define _GET_OVERRIDE_ADD_LK10(_1, _2, _3, _4, NAME, ...) NAME
      
#define ADD_LK10(...) _GET_OVERRIDE_ADD_LK10(__VA_ARGS__, ADD_LK10_p, ADD_LK10_np)(__VA_ARGS__)
      
#define ADD_LK10_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ADD_LK10_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ADD - LK11
========================
*/
#define _GET_OVERRIDE_ADD_LK11(_1, _2, _3, _4, NAME, ...) NAME
      
#define ADD_LK11(...) _GET_OVERRIDE_ADD_LK11(__VA_ARGS__, ADD_LK11_p, ADD_LK11_np)(__VA_ARGS__)
      
#define ADD_LK11_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ADD_LK11_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ADD - LK13
========================
*/
#define _GET_OVERRIDE_ADD_LK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define ADD_LK13(...) _GET_OVERRIDE_ADD_LK13(__VA_ARGS__, ADD_LK13_p, ADD_LK13_np)(__VA_ARGS__)
      
#define ADD_LK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ADD_LK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ADD - LK14
========================
*/
#define _GET_OVERRIDE_ADD_LK14(_1, _2, _3, _4, NAME, ...) NAME
      
#define ADD_LK14(...) _GET_OVERRIDE_ADD_LK14(__VA_ARGS__, ADD_LK14_p, ADD_LK14_np)(__VA_ARGS__)
      
#define ADD_LK14_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ADD_LK14_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ADD - LK15
========================
*/
#define _GET_OVERRIDE_ADD_LK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define ADD_LK15(...) _GET_OVERRIDE_ADD_LK15(__VA_ARGS__, ADD_LK15_p, ADD_LK15_np)(__VA_ARGS__)
      
#define ADD_LK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ADD_LK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (1  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")


































/*
========================
Generating for SUB - KNOP
========================
*/

#define _GET_OVERRIDE_SUB_KNOP(_1, _2, _3, _4, NAME, ...) NAME
      
#define SUB_KNOP(...) _GET_OVERRIDE_SUB_KNOP(__VA_ARGS__, SUB_KNOP_p, SUB_KNOP_np)(__VA_ARGS__)

      
#define SUB_KNOP_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define SUB_KNOP_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")


























/*
========================
Generating for SUB - SK1
========================
*/
#define _GET_OVERRIDE_SUB_SK1(_1, _2, _3, _4, NAME, ...) NAME
      
#define SUB_SK1(...) _GET_OVERRIDE_SUB_SK1(__VA_ARGS__, SUB_SK1_p, SUB_SK1_np)(__VA_ARGS__)
      
#define SUB_SK1_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define SUB_SK1_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for SUB - SK2
========================
*/
#define _GET_OVERRIDE_SUB_SK2(_1, _2, _3, _4, NAME, ...) NAME
      
#define SUB_SK2(...) _GET_OVERRIDE_SUB_SK2(__VA_ARGS__, SUB_SK2_p, SUB_SK2_np)(__VA_ARGS__)
      
#define SUB_SK2_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define SUB_SK2_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for SUB - SK13
========================
*/
#define _GET_OVERRIDE_SUB_SK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define SUB_SK13(...) _GET_OVERRIDE_SUB_SK13(__VA_ARGS__, SUB_SK13_p, SUB_SK13_np)(__VA_ARGS__)
      
#define SUB_SK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define SUB_SK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for SUB - SK15
========================
*/
#define _GET_OVERRIDE_SUB_SK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define SUB_SK15(...) _GET_OVERRIDE_SUB_SK15(__VA_ARGS__, SUB_SK15_p, SUB_SK15_np)(__VA_ARGS__)
      
#define SUB_SK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define SUB_SK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for SUB - LK8
========================
*/
#define _GET_OVERRIDE_SUB_LK8(_1, _2, _3, _4, NAME, ...) NAME
      
#define SUB_LK8(...) _GET_OVERRIDE_SUB_LK8(__VA_ARGS__, SUB_LK8_p, SUB_LK8_np)(__VA_ARGS__)
      
#define SUB_LK8_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define SUB_LK8_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for SUB - LK9
========================
*/
#define _GET_OVERRIDE_SUB_LK9(_1, _2, _3, _4, NAME, ...) NAME
      
#define SUB_LK9(...) _GET_OVERRIDE_SUB_LK9(__VA_ARGS__, SUB_LK9_p, SUB_LK9_np)(__VA_ARGS__)
      
#define SUB_LK9_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define SUB_LK9_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for SUB - LK10
========================
*/
#define _GET_OVERRIDE_SUB_LK10(_1, _2, _3, _4, NAME, ...) NAME
      
#define SUB_LK10(...) _GET_OVERRIDE_SUB_LK10(__VA_ARGS__, SUB_LK10_p, SUB_LK10_np)(__VA_ARGS__)
      
#define SUB_LK10_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define SUB_LK10_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for SUB - LK11
========================
*/
#define _GET_OVERRIDE_SUB_LK11(_1, _2, _3, _4, NAME, ...) NAME
      
#define SUB_LK11(...) _GET_OVERRIDE_SUB_LK11(__VA_ARGS__, SUB_LK11_p, SUB_LK11_np)(__VA_ARGS__)
      
#define SUB_LK11_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define SUB_LK11_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for SUB - LK13
========================
*/
#define _GET_OVERRIDE_SUB_LK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define SUB_LK13(...) _GET_OVERRIDE_SUB_LK13(__VA_ARGS__, SUB_LK13_p, SUB_LK13_np)(__VA_ARGS__)
      
#define SUB_LK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define SUB_LK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for SUB - LK14
========================
*/
#define _GET_OVERRIDE_SUB_LK14(_1, _2, _3, _4, NAME, ...) NAME
      
#define SUB_LK14(...) _GET_OVERRIDE_SUB_LK14(__VA_ARGS__, SUB_LK14_p, SUB_LK14_np)(__VA_ARGS__)
      
#define SUB_LK14_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define SUB_LK14_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for SUB - LK15
========================
*/
#define _GET_OVERRIDE_SUB_LK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define SUB_LK15(...) _GET_OVERRIDE_SUB_LK15(__VA_ARGS__, SUB_LK15_p, SUB_LK15_np)(__VA_ARGS__)
      
#define SUB_LK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define SUB_LK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (2  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")


































/*
========================
Generating for AND - KNOP
========================
*/

#define _GET_OVERRIDE_AND_KNOP(_1, _2, _3, _4, NAME, ...) NAME
      
#define AND_KNOP(...) _GET_OVERRIDE_AND_KNOP(__VA_ARGS__, AND_KNOP_p, AND_KNOP_np)(__VA_ARGS__)

      
#define AND_KNOP_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define AND_KNOP_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")


























/*
========================
Generating for AND - SK1
========================
*/
#define _GET_OVERRIDE_AND_SK1(_1, _2, _3, _4, NAME, ...) NAME
      
#define AND_SK1(...) _GET_OVERRIDE_AND_SK1(__VA_ARGS__, AND_SK1_p, AND_SK1_np)(__VA_ARGS__)
      
#define AND_SK1_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define AND_SK1_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for AND - SK2
========================
*/
#define _GET_OVERRIDE_AND_SK2(_1, _2, _3, _4, NAME, ...) NAME
      
#define AND_SK2(...) _GET_OVERRIDE_AND_SK2(__VA_ARGS__, AND_SK2_p, AND_SK2_np)(__VA_ARGS__)
      
#define AND_SK2_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define AND_SK2_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for AND - SK13
========================
*/
#define _GET_OVERRIDE_AND_SK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define AND_SK13(...) _GET_OVERRIDE_AND_SK13(__VA_ARGS__, AND_SK13_p, AND_SK13_np)(__VA_ARGS__)
      
#define AND_SK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define AND_SK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for AND - SK15
========================
*/
#define _GET_OVERRIDE_AND_SK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define AND_SK15(...) _GET_OVERRIDE_AND_SK15(__VA_ARGS__, AND_SK15_p, AND_SK15_np)(__VA_ARGS__)
      
#define AND_SK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define AND_SK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for AND - LK8
========================
*/
#define _GET_OVERRIDE_AND_LK8(_1, _2, _3, _4, NAME, ...) NAME
      
#define AND_LK8(...) _GET_OVERRIDE_AND_LK8(__VA_ARGS__, AND_LK8_p, AND_LK8_np)(__VA_ARGS__)
      
#define AND_LK8_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define AND_LK8_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for AND - LK9
========================
*/
#define _GET_OVERRIDE_AND_LK9(_1, _2, _3, _4, NAME, ...) NAME
      
#define AND_LK9(...) _GET_OVERRIDE_AND_LK9(__VA_ARGS__, AND_LK9_p, AND_LK9_np)(__VA_ARGS__)
      
#define AND_LK9_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define AND_LK9_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for AND - LK10
========================
*/
#define _GET_OVERRIDE_AND_LK10(_1, _2, _3, _4, NAME, ...) NAME
      
#define AND_LK10(...) _GET_OVERRIDE_AND_LK10(__VA_ARGS__, AND_LK10_p, AND_LK10_np)(__VA_ARGS__)
      
#define AND_LK10_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define AND_LK10_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for AND - LK11
========================
*/
#define _GET_OVERRIDE_AND_LK11(_1, _2, _3, _4, NAME, ...) NAME
      
#define AND_LK11(...) _GET_OVERRIDE_AND_LK11(__VA_ARGS__, AND_LK11_p, AND_LK11_np)(__VA_ARGS__)
      
#define AND_LK11_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define AND_LK11_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for AND - LK13
========================
*/
#define _GET_OVERRIDE_AND_LK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define AND_LK13(...) _GET_OVERRIDE_AND_LK13(__VA_ARGS__, AND_LK13_p, AND_LK13_np)(__VA_ARGS__)
      
#define AND_LK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define AND_LK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for AND - LK14
========================
*/
#define _GET_OVERRIDE_AND_LK14(_1, _2, _3, _4, NAME, ...) NAME
      
#define AND_LK14(...) _GET_OVERRIDE_AND_LK14(__VA_ARGS__, AND_LK14_p, AND_LK14_np)(__VA_ARGS__)
      
#define AND_LK14_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define AND_LK14_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for AND - LK15
========================
*/
#define _GET_OVERRIDE_AND_LK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define AND_LK15(...) _GET_OVERRIDE_AND_LK15(__VA_ARGS__, AND_LK15_p, AND_LK15_np)(__VA_ARGS__)
      
#define AND_LK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define AND_LK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (3  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")


































/*
========================
Generating for OR - KNOP
========================
*/

#define _GET_OVERRIDE_OR_KNOP(_1, _2, _3, _4, NAME, ...) NAME
      
#define OR_KNOP(...) _GET_OVERRIDE_OR_KNOP(__VA_ARGS__, OR_KNOP_p, OR_KNOP_np)(__VA_ARGS__)

      
#define OR_KNOP_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define OR_KNOP_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")


























/*
========================
Generating for OR - SK1
========================
*/
#define _GET_OVERRIDE_OR_SK1(_1, _2, _3, _4, NAME, ...) NAME
      
#define OR_SK1(...) _GET_OVERRIDE_OR_SK1(__VA_ARGS__, OR_SK1_p, OR_SK1_np)(__VA_ARGS__)
      
#define OR_SK1_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define OR_SK1_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for OR - SK2
========================
*/
#define _GET_OVERRIDE_OR_SK2(_1, _2, _3, _4, NAME, ...) NAME
      
#define OR_SK2(...) _GET_OVERRIDE_OR_SK2(__VA_ARGS__, OR_SK2_p, OR_SK2_np)(__VA_ARGS__)
      
#define OR_SK2_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define OR_SK2_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for OR - SK13
========================
*/
#define _GET_OVERRIDE_OR_SK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define OR_SK13(...) _GET_OVERRIDE_OR_SK13(__VA_ARGS__, OR_SK13_p, OR_SK13_np)(__VA_ARGS__)
      
#define OR_SK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define OR_SK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for OR - SK15
========================
*/
#define _GET_OVERRIDE_OR_SK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define OR_SK15(...) _GET_OVERRIDE_OR_SK15(__VA_ARGS__, OR_SK15_p, OR_SK15_np)(__VA_ARGS__)
      
#define OR_SK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define OR_SK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for OR - LK8
========================
*/
#define _GET_OVERRIDE_OR_LK8(_1, _2, _3, _4, NAME, ...) NAME
      
#define OR_LK8(...) _GET_OVERRIDE_OR_LK8(__VA_ARGS__, OR_LK8_p, OR_LK8_np)(__VA_ARGS__)
      
#define OR_LK8_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define OR_LK8_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for OR - LK9
========================
*/
#define _GET_OVERRIDE_OR_LK9(_1, _2, _3, _4, NAME, ...) NAME
      
#define OR_LK9(...) _GET_OVERRIDE_OR_LK9(__VA_ARGS__, OR_LK9_p, OR_LK9_np)(__VA_ARGS__)
      
#define OR_LK9_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define OR_LK9_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for OR - LK10
========================
*/
#define _GET_OVERRIDE_OR_LK10(_1, _2, _3, _4, NAME, ...) NAME
      
#define OR_LK10(...) _GET_OVERRIDE_OR_LK10(__VA_ARGS__, OR_LK10_p, OR_LK10_np)(__VA_ARGS__)
      
#define OR_LK10_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define OR_LK10_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for OR - LK11
========================
*/
#define _GET_OVERRIDE_OR_LK11(_1, _2, _3, _4, NAME, ...) NAME
      
#define OR_LK11(...) _GET_OVERRIDE_OR_LK11(__VA_ARGS__, OR_LK11_p, OR_LK11_np)(__VA_ARGS__)
      
#define OR_LK11_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define OR_LK11_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for OR - LK13
========================
*/
#define _GET_OVERRIDE_OR_LK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define OR_LK13(...) _GET_OVERRIDE_OR_LK13(__VA_ARGS__, OR_LK13_p, OR_LK13_np)(__VA_ARGS__)
      
#define OR_LK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define OR_LK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for OR - LK14
========================
*/
#define _GET_OVERRIDE_OR_LK14(_1, _2, _3, _4, NAME, ...) NAME
      
#define OR_LK14(...) _GET_OVERRIDE_OR_LK14(__VA_ARGS__, OR_LK14_p, OR_LK14_np)(__VA_ARGS__)
      
#define OR_LK14_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define OR_LK14_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for OR - LK15
========================
*/
#define _GET_OVERRIDE_OR_LK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define OR_LK15(...) _GET_OVERRIDE_OR_LK15(__VA_ARGS__, OR_LK15_p, OR_LK15_np)(__VA_ARGS__)
      
#define OR_LK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define OR_LK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (4  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")


































/*
========================
Generating for XOR - KNOP
========================
*/

#define _GET_OVERRIDE_XOR_KNOP(_1, _2, _3, _4, NAME, ...) NAME
      
#define XOR_KNOP(...) _GET_OVERRIDE_XOR_KNOP(__VA_ARGS__, XOR_KNOP_p, XOR_KNOP_np)(__VA_ARGS__)

      
#define XOR_KNOP_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define XOR_KNOP_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")


























/*
========================
Generating for XOR - SK1
========================
*/
#define _GET_OVERRIDE_XOR_SK1(_1, _2, _3, _4, NAME, ...) NAME
      
#define XOR_SK1(...) _GET_OVERRIDE_XOR_SK1(__VA_ARGS__, XOR_SK1_p, XOR_SK1_np)(__VA_ARGS__)
      
#define XOR_SK1_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define XOR_SK1_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for XOR - SK2
========================
*/
#define _GET_OVERRIDE_XOR_SK2(_1, _2, _3, _4, NAME, ...) NAME
      
#define XOR_SK2(...) _GET_OVERRIDE_XOR_SK2(__VA_ARGS__, XOR_SK2_p, XOR_SK2_np)(__VA_ARGS__)
      
#define XOR_SK2_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define XOR_SK2_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for XOR - SK13
========================
*/
#define _GET_OVERRIDE_XOR_SK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define XOR_SK13(...) _GET_OVERRIDE_XOR_SK13(__VA_ARGS__, XOR_SK13_p, XOR_SK13_np)(__VA_ARGS__)
      
#define XOR_SK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define XOR_SK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for XOR - SK15
========================
*/
#define _GET_OVERRIDE_XOR_SK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define XOR_SK15(...) _GET_OVERRIDE_XOR_SK15(__VA_ARGS__, XOR_SK15_p, XOR_SK15_np)(__VA_ARGS__)
      
#define XOR_SK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define XOR_SK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for XOR - LK8
========================
*/
#define _GET_OVERRIDE_XOR_LK8(_1, _2, _3, _4, NAME, ...) NAME
      
#define XOR_LK8(...) _GET_OVERRIDE_XOR_LK8(__VA_ARGS__, XOR_LK8_p, XOR_LK8_np)(__VA_ARGS__)
      
#define XOR_LK8_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define XOR_LK8_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for XOR - LK9
========================
*/
#define _GET_OVERRIDE_XOR_LK9(_1, _2, _3, _4, NAME, ...) NAME
      
#define XOR_LK9(...) _GET_OVERRIDE_XOR_LK9(__VA_ARGS__, XOR_LK9_p, XOR_LK9_np)(__VA_ARGS__)
      
#define XOR_LK9_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define XOR_LK9_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for XOR - LK10
========================
*/
#define _GET_OVERRIDE_XOR_LK10(_1, _2, _3, _4, NAME, ...) NAME
      
#define XOR_LK10(...) _GET_OVERRIDE_XOR_LK10(__VA_ARGS__, XOR_LK10_p, XOR_LK10_np)(__VA_ARGS__)
      
#define XOR_LK10_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define XOR_LK10_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for XOR - LK11
========================
*/
#define _GET_OVERRIDE_XOR_LK11(_1, _2, _3, _4, NAME, ...) NAME
      
#define XOR_LK11(...) _GET_OVERRIDE_XOR_LK11(__VA_ARGS__, XOR_LK11_p, XOR_LK11_np)(__VA_ARGS__)
      
#define XOR_LK11_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define XOR_LK11_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for XOR - LK13
========================
*/
#define _GET_OVERRIDE_XOR_LK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define XOR_LK13(...) _GET_OVERRIDE_XOR_LK13(__VA_ARGS__, XOR_LK13_p, XOR_LK13_np)(__VA_ARGS__)
      
#define XOR_LK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define XOR_LK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for XOR - LK14
========================
*/
#define _GET_OVERRIDE_XOR_LK14(_1, _2, _3, _4, NAME, ...) NAME
      
#define XOR_LK14(...) _GET_OVERRIDE_XOR_LK14(__VA_ARGS__, XOR_LK14_p, XOR_LK14_np)(__VA_ARGS__)
      
#define XOR_LK14_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define XOR_LK14_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for XOR - LK15
========================
*/
#define _GET_OVERRIDE_XOR_LK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define XOR_LK15(...) _GET_OVERRIDE_XOR_LK15(__VA_ARGS__, XOR_LK15_p, XOR_LK15_np)(__VA_ARGS__)
      
#define XOR_LK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define XOR_LK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (5  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")





































/*
========================
Generating for MV - KNOP
========================
*/

#define _GET_OVERRIDE_MV_KNOP(_1, _2, _3, NAME, ...) NAME
      
#define MV_KNOP(...) _GET_OVERRIDE_MV_KNOP(__VA_ARGS__, MV_KNOP_p, MV_KNOP_np)(__VA_ARGS__)


#define MV_KNOP_p(ds, s2, rs1)   asm   (".word(((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MV_KNOP_np(ds, s2)   asm   (".word(((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")























/*
========================
Generating for MV - SK1
========================
*/
#define _GET_OVERRIDE_MV_SK1(_1, _2, _3, _4, NAME, ...) NAME
      
#define MV_SK1(...) _GET_OVERRIDE_MV_SK1(__VA_ARGS__, MV_SK1_p, MV_SK1_np)(__VA_ARGS__)
      
#define MV_SK1_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MV_SK1_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MV - SK2
========================
*/
#define _GET_OVERRIDE_MV_SK2(_1, _2, _3, _4, NAME, ...) NAME
      
#define MV_SK2(...) _GET_OVERRIDE_MV_SK2(__VA_ARGS__, MV_SK2_p, MV_SK2_np)(__VA_ARGS__)
      
#define MV_SK2_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MV_SK2_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MV - SK13
========================
*/
#define _GET_OVERRIDE_MV_SK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define MV_SK13(...) _GET_OVERRIDE_MV_SK13(__VA_ARGS__, MV_SK13_p, MV_SK13_np)(__VA_ARGS__)
      
#define MV_SK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MV_SK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MV - SK15
========================
*/
#define _GET_OVERRIDE_MV_SK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define MV_SK15(...) _GET_OVERRIDE_MV_SK15(__VA_ARGS__, MV_SK15_p, MV_SK15_np)(__VA_ARGS__)
      
#define MV_SK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MV_SK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MV - LK8
========================
*/
#define _GET_OVERRIDE_MV_LK8(_1, _2, _3, _4, NAME, ...) NAME
      
#define MV_LK8(...) _GET_OVERRIDE_MV_LK8(__VA_ARGS__, MV_LK8_p, MV_LK8_np)(__VA_ARGS__)
      
#define MV_LK8_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MV_LK8_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MV - LK9
========================
*/
#define _GET_OVERRIDE_MV_LK9(_1, _2, _3, _4, NAME, ...) NAME
      
#define MV_LK9(...) _GET_OVERRIDE_MV_LK9(__VA_ARGS__, MV_LK9_p, MV_LK9_np)(__VA_ARGS__)
      
#define MV_LK9_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MV_LK9_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MV - LK10
========================
*/
#define _GET_OVERRIDE_MV_LK10(_1, _2, _3, _4, NAME, ...) NAME
      
#define MV_LK10(...) _GET_OVERRIDE_MV_LK10(__VA_ARGS__, MV_LK10_p, MV_LK10_np)(__VA_ARGS__)
      
#define MV_LK10_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MV_LK10_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MV - LK11
========================
*/
#define _GET_OVERRIDE_MV_LK11(_1, _2, _3, _4, NAME, ...) NAME
      
#define MV_LK11(...) _GET_OVERRIDE_MV_LK11(__VA_ARGS__, MV_LK11_p, MV_LK11_np)(__VA_ARGS__)
      
#define MV_LK11_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MV_LK11_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MV - LK13
========================
*/
#define _GET_OVERRIDE_MV_LK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define MV_LK13(...) _GET_OVERRIDE_MV_LK13(__VA_ARGS__, MV_LK13_p, MV_LK13_np)(__VA_ARGS__)
      
#define MV_LK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MV_LK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MV - LK14
========================
*/
#define _GET_OVERRIDE_MV_LK14(_1, _2, _3, _4, NAME, ...) NAME
      
#define MV_LK14(...) _GET_OVERRIDE_MV_LK14(__VA_ARGS__, MV_LK14_p, MV_LK14_np)(__VA_ARGS__)
      
#define MV_LK14_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MV_LK14_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MV - LK15
========================
*/
#define _GET_OVERRIDE_MV_LK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define MV_LK15(...) _GET_OVERRIDE_MV_LK15(__VA_ARGS__, MV_LK15_p, MV_LK15_np)(__VA_ARGS__)
      
#define MV_LK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MV_LK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (6  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")





































/*
========================
Generating for ROL - KNOP
========================
*/

#define _GET_OVERRIDE_ROL_KNOP(_1, _2, _3, NAME, ...) NAME
      
#define ROL_KNOP(...) _GET_OVERRIDE_ROL_KNOP(__VA_ARGS__, ROL_KNOP_p, ROL_KNOP_np)(__VA_ARGS__)


#define ROL_KNOP_p(ds, s2, rs1)   asm   (".word(((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROL_KNOP_np(ds, s2)   asm   (".word(((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")























/*
========================
Generating for ROL - SK1
========================
*/
#define _GET_OVERRIDE_ROL_SK1(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROL_SK1(...) _GET_OVERRIDE_ROL_SK1(__VA_ARGS__, ROL_SK1_p, ROL_SK1_np)(__VA_ARGS__)
      
#define ROL_SK1_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROL_SK1_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROL - SK2
========================
*/
#define _GET_OVERRIDE_ROL_SK2(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROL_SK2(...) _GET_OVERRIDE_ROL_SK2(__VA_ARGS__, ROL_SK2_p, ROL_SK2_np)(__VA_ARGS__)
      
#define ROL_SK2_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROL_SK2_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROL - SK13
========================
*/
#define _GET_OVERRIDE_ROL_SK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROL_SK13(...) _GET_OVERRIDE_ROL_SK13(__VA_ARGS__, ROL_SK13_p, ROL_SK13_np)(__VA_ARGS__)
      
#define ROL_SK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROL_SK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROL - SK15
========================
*/
#define _GET_OVERRIDE_ROL_SK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROL_SK15(...) _GET_OVERRIDE_ROL_SK15(__VA_ARGS__, ROL_SK15_p, ROL_SK15_np)(__VA_ARGS__)
      
#define ROL_SK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROL_SK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROL - LK8
========================
*/
#define _GET_OVERRIDE_ROL_LK8(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROL_LK8(...) _GET_OVERRIDE_ROL_LK8(__VA_ARGS__, ROL_LK8_p, ROL_LK8_np)(__VA_ARGS__)
      
#define ROL_LK8_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROL_LK8_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROL - LK9
========================
*/
#define _GET_OVERRIDE_ROL_LK9(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROL_LK9(...) _GET_OVERRIDE_ROL_LK9(__VA_ARGS__, ROL_LK9_p, ROL_LK9_np)(__VA_ARGS__)
      
#define ROL_LK9_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROL_LK9_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROL - LK10
========================
*/
#define _GET_OVERRIDE_ROL_LK10(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROL_LK10(...) _GET_OVERRIDE_ROL_LK10(__VA_ARGS__, ROL_LK10_p, ROL_LK10_np)(__VA_ARGS__)
      
#define ROL_LK10_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROL_LK10_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROL - LK11
========================
*/
#define _GET_OVERRIDE_ROL_LK11(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROL_LK11(...) _GET_OVERRIDE_ROL_LK11(__VA_ARGS__, ROL_LK11_p, ROL_LK11_np)(__VA_ARGS__)
      
#define ROL_LK11_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROL_LK11_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROL - LK13
========================
*/
#define _GET_OVERRIDE_ROL_LK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROL_LK13(...) _GET_OVERRIDE_ROL_LK13(__VA_ARGS__, ROL_LK13_p, ROL_LK13_np)(__VA_ARGS__)
      
#define ROL_LK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROL_LK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROL - LK14
========================
*/
#define _GET_OVERRIDE_ROL_LK14(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROL_LK14(...) _GET_OVERRIDE_ROL_LK14(__VA_ARGS__, ROL_LK14_p, ROL_LK14_np)(__VA_ARGS__)
      
#define ROL_LK14_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROL_LK14_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROL - LK15
========================
*/
#define _GET_OVERRIDE_ROL_LK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROL_LK15(...) _GET_OVERRIDE_ROL_LK15(__VA_ARGS__, ROL_LK15_p, ROL_LK15_np)(__VA_ARGS__)
      
#define ROL_LK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROL_LK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (8  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")





































/*
========================
Generating for ROR - KNOP
========================
*/

#define _GET_OVERRIDE_ROR_KNOP(_1, _2, _3, NAME, ...) NAME
      
#define ROR_KNOP(...) _GET_OVERRIDE_ROR_KNOP(__VA_ARGS__, ROR_KNOP_p, ROR_KNOP_np)(__VA_ARGS__)


#define ROR_KNOP_p(ds, s2, rs1)   asm   (".word(((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROR_KNOP_np(ds, s2)   asm   (".word(((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")























/*
========================
Generating for ROR - SK1
========================
*/
#define _GET_OVERRIDE_ROR_SK1(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROR_SK1(...) _GET_OVERRIDE_ROR_SK1(__VA_ARGS__, ROR_SK1_p, ROR_SK1_np)(__VA_ARGS__)
      
#define ROR_SK1_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROR_SK1_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROR - SK2
========================
*/
#define _GET_OVERRIDE_ROR_SK2(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROR_SK2(...) _GET_OVERRIDE_ROR_SK2(__VA_ARGS__, ROR_SK2_p, ROR_SK2_np)(__VA_ARGS__)
      
#define ROR_SK2_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROR_SK2_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROR - SK13
========================
*/
#define _GET_OVERRIDE_ROR_SK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROR_SK13(...) _GET_OVERRIDE_ROR_SK13(__VA_ARGS__, ROR_SK13_p, ROR_SK13_np)(__VA_ARGS__)
      
#define ROR_SK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROR_SK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROR - SK15
========================
*/
#define _GET_OVERRIDE_ROR_SK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROR_SK15(...) _GET_OVERRIDE_ROR_SK15(__VA_ARGS__, ROR_SK15_p, ROR_SK15_np)(__VA_ARGS__)
      
#define ROR_SK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROR_SK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROR - LK8
========================
*/
#define _GET_OVERRIDE_ROR_LK8(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROR_LK8(...) _GET_OVERRIDE_ROR_LK8(__VA_ARGS__, ROR_LK8_p, ROR_LK8_np)(__VA_ARGS__)
      
#define ROR_LK8_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROR_LK8_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROR - LK9
========================
*/
#define _GET_OVERRIDE_ROR_LK9(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROR_LK9(...) _GET_OVERRIDE_ROR_LK9(__VA_ARGS__, ROR_LK9_p, ROR_LK9_np)(__VA_ARGS__)
      
#define ROR_LK9_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROR_LK9_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROR - LK10
========================
*/
#define _GET_OVERRIDE_ROR_LK10(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROR_LK10(...) _GET_OVERRIDE_ROR_LK10(__VA_ARGS__, ROR_LK10_p, ROR_LK10_np)(__VA_ARGS__)
      
#define ROR_LK10_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROR_LK10_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROR - LK11
========================
*/
#define _GET_OVERRIDE_ROR_LK11(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROR_LK11(...) _GET_OVERRIDE_ROR_LK11(__VA_ARGS__, ROR_LK11_p, ROR_LK11_np)(__VA_ARGS__)
      
#define ROR_LK11_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROR_LK11_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROR - LK13
========================
*/
#define _GET_OVERRIDE_ROR_LK13(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROR_LK13(...) _GET_OVERRIDE_ROR_LK13(__VA_ARGS__, ROR_LK13_p, ROR_LK13_np)(__VA_ARGS__)
      
#define ROR_LK13_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROR_LK13_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROR - LK14
========================
*/
#define _GET_OVERRIDE_ROR_LK14(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROR_LK14(...) _GET_OVERRIDE_ROR_LK14(__VA_ARGS__, ROR_LK14_p, ROR_LK14_np)(__VA_ARGS__)
      
#define ROR_LK14_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROR_LK14_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for ROR - LK15
========================
*/
#define _GET_OVERRIDE_ROR_LK15(_1, _2, _3, _4, NAME, ...) NAME
      
#define ROR_LK15(...) _GET_OVERRIDE_ROR_LK15(__VA_ARGS__, ROR_LK15_p, ROR_LK15_np)(__VA_ARGS__)
      
#define ROR_LK15_p(ds, s1, s2, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define ROR_LK15_np(ds, s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (9  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")





















































/*
========================
Generating for MVXV - KNOP
========================
*/

#define _GET_OVERRIDE_MVXV_KNOP(_1, _2, NAME, ...) NAME
      
#define MVXV_KNOP(...) _GET_OVERRIDE_MVXV_KNOP(__VA_ARGS__, MVXV_KNOP_p, MVXV_KNOP_np)(__VA_ARGS__)


#define MVXV_KNOP_p(ds, rs1)   asm   (".word((((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVXV_KNOP_np(ds)   asm   (".word((10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")


























/*
========================
Generating for MVXV - SK1
========================
*/

#define _GET_OVERRIDE_MVXV_SK1(_1, _2, _3, NAME, ...) NAME
      
#define MVXV_SK1(...) _GET_OVERRIDE_MVXV_SK1(__VA_ARGS__, MVXV_SK1_p, MVXV_SK1_np)(__VA_ARGS__)


#define MVXV_SK1_p(ds, rs1, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVXV_SK1_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVXV - SK2
========================
*/

#define _GET_OVERRIDE_MVXV_SK2(_1, _2, _3, NAME, ...) NAME
      
#define MVXV_SK2(...) _GET_OVERRIDE_MVXV_SK2(__VA_ARGS__, MVXV_SK2_p, MVXV_SK2_np)(__VA_ARGS__)


#define MVXV_SK2_p(ds, rs1, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVXV_SK2_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVXV - SK13
========================
*/

#define _GET_OVERRIDE_MVXV_SK13(_1, _2, _3, NAME, ...) NAME
      
#define MVXV_SK13(...) _GET_OVERRIDE_MVXV_SK13(__VA_ARGS__, MVXV_SK13_p, MVXV_SK13_np)(__VA_ARGS__)


#define MVXV_SK13_p(ds, rs1, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVXV_SK13_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVXV - SK15
========================
*/

#define _GET_OVERRIDE_MVXV_SK15(_1, _2, _3, NAME, ...) NAME
      
#define MVXV_SK15(...) _GET_OVERRIDE_MVXV_SK15(__VA_ARGS__, MVXV_SK15_p, MVXV_SK15_np)(__VA_ARGS__)


#define MVXV_SK15_p(ds, rs1, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVXV_SK15_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVXV - LK8
========================
*/

#define _GET_OVERRIDE_MVXV_LK8(_1, _2, _3, NAME, ...) NAME
      
#define MVXV_LK8(...) _GET_OVERRIDE_MVXV_LK8(__VA_ARGS__, MVXV_LK8_p, MVXV_LK8_np)(__VA_ARGS__)


#define MVXV_LK8_p(ds, rs1, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVXV_LK8_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVXV - LK9
========================
*/

#define _GET_OVERRIDE_MVXV_LK9(_1, _2, _3, NAME, ...) NAME
      
#define MVXV_LK9(...) _GET_OVERRIDE_MVXV_LK9(__VA_ARGS__, MVXV_LK9_p, MVXV_LK9_np)(__VA_ARGS__)


#define MVXV_LK9_p(ds, rs1, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVXV_LK9_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVXV - LK10
========================
*/

#define _GET_OVERRIDE_MVXV_LK10(_1, _2, _3, NAME, ...) NAME
      
#define MVXV_LK10(...) _GET_OVERRIDE_MVXV_LK10(__VA_ARGS__, MVXV_LK10_p, MVXV_LK10_np)(__VA_ARGS__)


#define MVXV_LK10_p(ds, rs1, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVXV_LK10_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVXV - LK11
========================
*/

#define _GET_OVERRIDE_MVXV_LK11(_1, _2, _3, NAME, ...) NAME
      
#define MVXV_LK11(...) _GET_OVERRIDE_MVXV_LK11(__VA_ARGS__, MVXV_LK11_p, MVXV_LK11_np)(__VA_ARGS__)


#define MVXV_LK11_p(ds, rs1, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVXV_LK11_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVXV - LK13
========================
*/

#define _GET_OVERRIDE_MVXV_LK13(_1, _2, _3, NAME, ...) NAME
      
#define MVXV_LK13(...) _GET_OVERRIDE_MVXV_LK13(__VA_ARGS__, MVXV_LK13_p, MVXV_LK13_np)(__VA_ARGS__)


#define MVXV_LK13_p(ds, rs1, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVXV_LK13_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVXV - LK14
========================
*/

#define _GET_OVERRIDE_MVXV_LK14(_1, _2, _3, NAME, ...) NAME
      
#define MVXV_LK14(...) _GET_OVERRIDE_MVXV_LK14(__VA_ARGS__, MVXV_LK14_p, MVXV_LK14_np)(__VA_ARGS__)


#define MVXV_LK14_p(ds, rs1, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVXV_LK14_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVXV - LK15
========================
*/

#define _GET_OVERRIDE_MVXV_LK15(_1, _2, _3, NAME, ...) NAME
      
#define MVXV_LK15(...) _GET_OVERRIDE_MVXV_LK15(__VA_ARGS__, MVXV_LK15_p, MVXV_LK15_np)(__VA_ARGS__)


#define MVXV_LK15_p(ds, rs1, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVXV_LK15_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | (10  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")


























/*
========================
Generating for MVK15V - KNOP
========================
*/

#define _GET_OVERRIDE_MVK15V_KNOP(_1, _2, NAME, ...) NAME
      
#define MVK15V_KNOP(...) _GET_OVERRIDE_MVK15V_KNOP(__VA_ARGS__, MVK15V_KNOP_p, MVK15V_KNOP_np)(__VA_ARGS__)


#define MVK15V_KNOP_p(ds, rs1)   asm   (".word((((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVK15V_KNOP_np(ds)   asm   (".word((11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")


























/*
========================
Generating for MVK15V - SK1
========================
*/

#define _GET_OVERRIDE_MVK15V_SK1(_1, _2, _3, NAME, ...) NAME
      
#define MVK15V_SK1(...) _GET_OVERRIDE_MVK15V_SK1(__VA_ARGS__, MVK15V_SK1_p, MVK15V_SK1_np)(__VA_ARGS__)


#define MVK15V_SK1_p(ds, s1, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVK15V_SK1_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVK15V - SK2
========================
*/

#define _GET_OVERRIDE_MVK15V_SK2(_1, _2, _3, NAME, ...) NAME
      
#define MVK15V_SK2(...) _GET_OVERRIDE_MVK15V_SK2(__VA_ARGS__, MVK15V_SK2_p, MVK15V_SK2_np)(__VA_ARGS__)


#define MVK15V_SK2_p(ds, s1, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVK15V_SK2_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVK15V - SK13
========================
*/

#define _GET_OVERRIDE_MVK15V_SK13(_1, _2, _3, NAME, ...) NAME
      
#define MVK15V_SK13(...) _GET_OVERRIDE_MVK15V_SK13(__VA_ARGS__, MVK15V_SK13_p, MVK15V_SK13_np)(__VA_ARGS__)


#define MVK15V_SK13_p(ds, s1, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVK15V_SK13_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVK15V - SK15
========================
*/

#define _GET_OVERRIDE_MVK15V_SK15(_1, _2, _3, NAME, ...) NAME
      
#define MVK15V_SK15(...) _GET_OVERRIDE_MVK15V_SK15(__VA_ARGS__, MVK15V_SK15_p, MVK15V_SK15_np)(__VA_ARGS__)


#define MVK15V_SK15_p(ds, s1, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVK15V_SK15_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVK15V - LK8
========================
*/

#define _GET_OVERRIDE_MVK15V_LK8(_1, _2, _3, NAME, ...) NAME
      
#define MVK15V_LK8(...) _GET_OVERRIDE_MVK15V_LK8(__VA_ARGS__, MVK15V_LK8_p, MVK15V_LK8_np)(__VA_ARGS__)


#define MVK15V_LK8_p(ds, s1, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVK15V_LK8_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVK15V - LK9
========================
*/

#define _GET_OVERRIDE_MVK15V_LK9(_1, _2, _3, NAME, ...) NAME
      
#define MVK15V_LK9(...) _GET_OVERRIDE_MVK15V_LK9(__VA_ARGS__, MVK15V_LK9_p, MVK15V_LK9_np)(__VA_ARGS__)


#define MVK15V_LK9_p(ds, s1, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVK15V_LK9_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVK15V - LK10
========================
*/

#define _GET_OVERRIDE_MVK15V_LK10(_1, _2, _3, NAME, ...) NAME
      
#define MVK15V_LK10(...) _GET_OVERRIDE_MVK15V_LK10(__VA_ARGS__, MVK15V_LK10_p, MVK15V_LK10_np)(__VA_ARGS__)


#define MVK15V_LK10_p(ds, s1, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVK15V_LK10_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVK15V - LK11
========================
*/

#define _GET_OVERRIDE_MVK15V_LK11(_1, _2, _3, NAME, ...) NAME
      
#define MVK15V_LK11(...) _GET_OVERRIDE_MVK15V_LK11(__VA_ARGS__, MVK15V_LK11_p, MVK15V_LK11_np)(__VA_ARGS__)


#define MVK15V_LK11_p(ds, s1, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVK15V_LK11_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVK15V - LK13
========================
*/

#define _GET_OVERRIDE_MVK15V_LK13(_1, _2, _3, NAME, ...) NAME
      
#define MVK15V_LK13(...) _GET_OVERRIDE_MVK15V_LK13(__VA_ARGS__, MVK15V_LK13_p, MVK15V_LK13_np)(__VA_ARGS__)


#define MVK15V_LK13_p(ds, s1, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVK15V_LK13_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVK15V - LK14
========================
*/

#define _GET_OVERRIDE_MVK15V_LK14(_1, _2, _3, NAME, ...) NAME
      
#define MVK15V_LK14(...) _GET_OVERRIDE_MVK15V_LK14(__VA_ARGS__, MVK15V_LK14_p, MVK15V_LK14_np)(__VA_ARGS__)


#define MVK15V_LK14_p(ds, s1, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVK15V_LK14_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")




























/*
========================
Generating for MVK15V - LK15
========================
*/

#define _GET_OVERRIDE_MVK15V_LK15(_1, _2, _3, NAME, ...) NAME
      
#define MVK15V_LK15(...) _GET_OVERRIDE_MVK15V_LK15(__VA_ARGS__, MVK15V_LK15_p, MVK15V_LK15_np)(__VA_ARGS__)


#define MVK15V_LK15_p(ds, s1, rs1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | (((((\"%0\"==\"t0\") &5) |((\"%0\"==\"t1\") &6) |((\"%0\"==\"t2\") &7) |((\"%0\"==\"s0\") &8) |((\"%0\"==\"s1\") &9) |((\"%0\"==\"a0\") &10)|((\"%0\"==\"a1\") &11)|((\"%0\"==\"a2\") &12)|((\"%0\"==\"a3\") &13)|((\"%0\"==\"a4\") &14)|((\"%0\"==\"a5\") &15)|((\"%0\"==\"a6\") &16)|((\"%0\"==\"a7\") &17)|((\"%0\"==\"s2\") &18)|((\"%0\"==\"s3\") &19)|((\"%0\"==\"s4\") &20)|((\"%0\"==\"s5\") &21)|((\"%0\"==\"s6\") &22)|((\"%0\"==\"s7\") &23)|((\"%0\"==\"s8\") &24)|((\"%0\"==\"s9\") &25)|((\"%0\"==\"s10\")&26)|((\"%0\"==\"s11\")&27)|((\"%0\"==\"t3\") &28)|((\"%0\"==\"t4\") &29)|((\"%0\"==\"t5\") &30)|((\"%0\"==\"t6\") &31))) << " _XSTR(OPCODE_RS1_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))" : : "r" (rs1))

#define MVK15V_LK15_np(ds, s1)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | (11  <<" _XSTR(OPCODE_OP_SHIFT) ") | ((" _XSTR(ds) ") <<" _XSTR(OPCODE_DS_SHIFT) ") | (0x0b))")






































/*
========================
Generating for MVVK15 - KNOP
========================
*/

#define MVVK15_KNOP(s2)   asm   (".word(((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (15  <<" _XSTR(OPCODE_OP_SHIFT) ") | (0x0b))")


























/*
========================
Generating for MVVK15 - SK1
========================
*/

#define MVVK15_SK1(s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (1<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (15  <<" _XSTR(OPCODE_OP_SHIFT) ") | | (0x0b))")




























/*
========================
Generating for MVVK15 - SK2
========================
*/

#define MVVK15_SK2(s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (2<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (15  <<" _XSTR(OPCODE_OP_SHIFT) ") | | (0x0b))")




























/*
========================
Generating for MVVK15 - SK13
========================
*/

#define MVVK15_SK13(s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (5<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (15  <<" _XSTR(OPCODE_OP_SHIFT) ") | | (0x0b))")




























/*
========================
Generating for MVVK15 - SK15
========================
*/

#define MVVK15_SK15(s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (7<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (15  <<" _XSTR(OPCODE_OP_SHIFT) ") | | (0x0b))")




























/*
========================
Generating for MVVK15 - LK8
========================
*/

#define MVVK15_LK8(s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (8<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (15  <<" _XSTR(OPCODE_OP_SHIFT) ") | | (0x0b))")




























/*
========================
Generating for MVVK15 - LK9
========================
*/

#define MVVK15_LK9(s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (9<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (15  <<" _XSTR(OPCODE_OP_SHIFT) ") | | (0x0b))")




























/*
========================
Generating for MVVK15 - LK10
========================
*/

#define MVVK15_LK10(s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (10<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (15  <<" _XSTR(OPCODE_OP_SHIFT) ") | | (0x0b))")




























/*
========================
Generating for MVVK15 - LK11
========================
*/

#define MVVK15_LK11(s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (11<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (15  <<" _XSTR(OPCODE_OP_SHIFT) ") | | (0x0b))")




























/*
========================
Generating for MVVK15 - LK13
========================
*/

#define MVVK15_LK13(s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (13<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (15  <<" _XSTR(OPCODE_OP_SHIFT) ") | | (0x0b))")




























/*
========================
Generating for MVVK15 - LK14
========================
*/

#define MVVK15_LK14(s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (14<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (15  <<" _XSTR(OPCODE_OP_SHIFT) ") | | (0x0b))")




























/*
========================
Generating for MVVK15 - LK15
========================
*/

#define MVVK15_LK15(s1, s2)   asm   (".word(((" _XSTR(s1) ") << " _XSTR(OPCODE_S1_SHIFT) ") | (15<<" _XSTR(OPCODE_K_SHIFT) ") | ((" _XSTR(s2) ") <<" _XSTR(OPCODE_S2_SHIFT) ") | (15  <<" _XSTR(OPCODE_OP_SHIFT) ") | | (0x0b))")














#endif /* XBASEBAND_H */
