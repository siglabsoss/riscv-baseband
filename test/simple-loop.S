.section .text

.global _start
_start:

#define custom_0_type_insn(_src1, _scratch, _src2, _rs1, _op, _dst, _opc) \
.word (((_src1) << 28) | ((_scratch) << 24) | ((_src2) << 20) | ((_rs1) << 15) | ((_op) << 11) | ((_dst) << 7) | ((_opc) << 0))

#define XB(_src1, _scratch, _src2, _rs1, _op, _dst) \
custom_0_type_insn(_src1, _scratch, _src2, _rs1, _op, _dst, 0b0001011)

#define VA(_index) _index
#define VB(_index) _index
#define VC(_index) _index
#define K(_index) _index
#define X(_index) _index
#define A(_index) (_index + 10)
#define DROP_DROP() 0
#define DROP_ADD() 1

# reset vector at 0x0
.=0x0

li a4, 10
_loop:
addi a4,a4,-1
XB(VA(2), K(1), VB(1), A(4), DROP_DROP(), VC(1))
bnez a4,_loop

_end:
j _end
