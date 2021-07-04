
#ifndef __SLICE_HPP__
#define __SLICE_HPP__

#include <stdint.h>
#include "slice_constants.hpp"
// #include "slice_container.hpp"


class SliceContainerModel;

// #include "slice_container.hpp"


typedef enum op_meaning
{
  NOP = 0,
  ADD,
  SUB,
  AND,
  OR,
  XOR,
  MV,
  ROL = 8,
  ROR,
  MV_X_V,
  MV_K15_V,
  MV_V_K15 = 15
} opcode_t;


typedef enum k_op_meaning
{
  KNOP = 0,
  SK1,
  SK2,
  SK15 = 7,
  LK8,
  LK9,
  LK10,
  LK11,
  LK14 = 14,
  LK15
} k_opcode_t;

// typedef enum memory_access_meaning
// {
//   WORD = 0,
//   LOW_HALF_WORD,
//   HIGH_HALF_WORD,
//   BYTE_0,
//   BYTE_1,
//   BYTE_2,
//   BYTE_3,
//   BLACK_HOLE
// } mem_access_t;




class SliceFunctionalModel
{
public:
  SliceFunctionalModel(int index = 0);

  void input(uint32_t opcode, uint32_t import);

  void reset();

  SliceContainerModel *parent; // pointer to parent sli

  uint32_t slice_index; // what index in the slice array are we

  uint32_t vregs[NREGS];
  bool op_can_predicate[N_VECTOR_OPS]; // true if the opcide is disabled by predicate

  uint32_t vregs_mask; // emulate odd sized registers by masking with this value

  uint32_t mem[MEM_SIZE];
  uint32_t kregs[N_K_REGS];

  bool kregs_display[N_K_REGS]; // which kregs should we display with print_k_regs()
  bool verbose;

  // all regs 32 bit for ease
  uint32_t s1;
  k_opcode_t kop;
  uint32_t s2;
  uint32_t rs1;
  opcode_t op;
  uint32_t ds;

  // memory is alwasy accessed from s1
  // we actually split s1 out into these sub fields
  uint32_t mem_bank_address;
  uint32_t mem_permutation;
  // uint32_t mem_g;
  // mem_access_t mem_access;



  // false if opcode is disabled, 
  // true if opcide is enabled
  // this will ops be true if vregs_can_predicate[op] is false
  bool predicate;

  void parse_op(uint32_t opcode);

  void set_predicate(uint32_t import);

  void parse_memory_fields(uint32_t s1);
  void util_parse_memory_fields(uint32_t s1, uint32_t &mem_bank_address, uint32_t &mem_permutation);

  void execute_op(uint32_t import);

  void execute_k_op(uint32_t import);

  void print_all_regs(void);
  void print_regs(void);
  void print_k_regs(void);
  void print_mem(uint32_t start = 0, uint32_t end = 0);

  uint32_t mask(uint32_t value);

  // from most recent op


};

#endif