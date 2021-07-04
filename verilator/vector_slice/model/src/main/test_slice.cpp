#include "slice.hpp"

#include <iostream>
#include <assert.h>
#include <functional>


static uint32_t vexregs[VEX_REGS];
SliceFunctionalModel *slice;

using namespace std;

void input(uint32_t op)
{
  uint32_t rs1 = ((op >> OPCODE_RS1_SHIFT)&OPCODE_RS1_MASK);
  uint32_t import_reg = vexregs[rs1];

  cout << "rs1: " << rs1 << " = " << HEX_STRING(import_reg) << endl;



  slice->input(op, import_reg);

  // uint32_t op_sv = (9 << OPCODE_OP_SHIFT) | (1 << OPCODE_S1_SHIFT) | (2 << OPCODE_S2_SHIFT) ;
}


int main (void)
{

  slice = new SliceFunctionalModel();
  slice->reset();
  
  // reset riscv
  for(auto i = 0; i < VEX_REGS; i++)
  {
    vexregs[i] = 0;
  }

  

  // some pre-made regs in vex
  vexregs[0] = 0x0;
  vexregs[1] = 0x1;
  vexregs[2] = 0x2;
  vexregs[3] = 0x3;
  vexregs[4] = 0x4;
  vexregs[5] = 0x5;
  vexregs[7] = 0xdeadbeef;
  vexregs[8] = 0xcafebabe;
  vexregs[9] = 0xfffffffe; // all bits set bit 0
  vexregs[12] = -2; // all bits set bit 0
  vexregs[13] = 3; // all bits set bit 0
  vexregs[14] = 0xf801; // all bits set bit 0
  vexregs[15] = 0x0fff; // all bits set bit 0


  // cout << "0x" << HEX_STRING( BIT_MASK32(0,31) ) << endl;



  // s1 is reg
  // s2 is mem addr


  // int32_t new_load = (LK15 << OPCODE_K_SHIFT) | (NOP << OPCODE_OP_SHIFT) | (7 << OPCODE_RS1_SHIFT) | (0 << OPCODE_DS_SHIFT) ;

  // slice->parse_op(new_load);

  // slice->print_all_regs();

  // input(new_load);

  cout << "-------------------------- test import --------------------------" << endl;
  
  uint32_t load_in7 = (MV_X_V << OPCODE_OP_SHIFT) | (7 << OPCODE_RS1_SHIFT) | (0 << OPCODE_DS_SHIFT) ;
  input(load_in7);

  // slice->print_all_regs();
  // slice->print_mem(0,100);
  assert( slice->vregs[0] == 0xbeef && "Import op didn't work");
  

  uint32_t load_in2 = (MV_X_V << OPCODE_OP_SHIFT) | (8 << OPCODE_RS1_SHIFT) | (0 << OPCODE_DS_SHIFT) ;
  input(load_in2);

  // slice->print_regs();
  assert( slice->vregs[0] == 0xbabe && "2nd import didn't work");

  uint32_t load_zero = (MV_X_V << OPCODE_OP_SHIFT) | (0 << OPCODE_RS1_SHIFT) | (0 << OPCODE_DS_SHIFT) ;
  input(load_zero);  

  // slice->print_regs();
  assert( slice->vregs[0] == 0x0 && "didn't re-zero");


  cout << "-------------------------- test Store --------------------------" << endl;

  uint32_t st_load;

  // deadbeef to vregs[1]
  st_load  = (MV_X_V << OPCODE_OP_SHIFT) | (7 << OPCODE_RS1_SHIFT) | (1 << OPCODE_DS_SHIFT);
  input(st_load);

  // 3 to vregs[2]
  st_load  = (MV_X_V << OPCODE_OP_SHIFT) | (3 << OPCODE_RS1_SHIFT) | (2 << OPCODE_DS_SHIFT);
  input(st_load);

  assert( slice->mem[3] == 0 && "mem didn't start out at zero" );

  // vregs[1] stored to pointer vregs[2]
  // in two parts

  // part 1:
  //   k15 = vregs[1]
  int32_t new_store_h1 = (MV_V_K15 << OPCODE_OP_SHIFT) | (1 << OPCODE_S2_SHIFT);
  input(new_store_h1);

  // part 2:
  //   mem[vregs[2]] = k15
  int32_t new_store_h2 = (SK15 << OPCODE_K_SHIFT) | (2 << OPCODE_S1_SHIFT);
  input(new_store_h2);

  slice->print_all_regs();
  slice->print_mem(0,200);


  assert( slice->mem[3] == 0xbeef && "store opcode didn't work" );



  // -------------------------- test Load --------------------------

  cout << "-------------------------- test Load --------------------------" << endl;
  // 
  // slice->print_regs();

  // pointer reg 2 in memory loaded into reg 4, in 2 parts

  // k[15] = mem[regs[s1]]
  int32_t new_load_h1 = (LK15 << OPCODE_K_SHIFT) | (NOP << OPCODE_OP_SHIFT) | (2 << OPCODE_S1_SHIFT);
  input(new_load_h1);

  slice->print_all_regs();

  // regs[ds] = k[15]
  int32_t new_load_h2 = (MV_K15_V << OPCODE_OP_SHIFT) | (4 << OPCODE_DS_SHIFT);
  input(new_load_h2);


  slice->print_all_regs();

  assert( slice->vregs[4] == 0xbeef && "opcode load didn't work");

  // hand of god way to set 32 bits of memory
  slice->mem[3] = 0x1234feef;

  int32_t new_load_special = (LK15 << OPCODE_K_SHIFT) | (NOP << OPCODE_OP_SHIFT) | (2 << OPCODE_S1_SHIFT);
  input(new_load_special);

  assert( slice->kregs[15] == 0x1234feef && "32 bit mem load didn't work");



  cout << "-------------------------- test move -------------------------" << endl;

  uint32_t move_load;

  // vregs[1] = vex[7]
  move_load = (MV_X_V << OPCODE_OP_SHIFT) | (7 << OPCODE_RS1_SHIFT) | (1 << OPCODE_DS_SHIFT) ;
  input(move_load);

  move_load = (MV_X_V << OPCODE_OP_SHIFT) | (8 << OPCODE_RS1_SHIFT) | (2 << OPCODE_DS_SHIFT) ;
  input(move_load);

  assert( slice->vregs[1] == 0xbeef && "opcode load didn't work");
  assert( slice->vregs[2] == 0xbabe && "opcode load didn't work");

  
  // move pointer reg 2 into pointer reg 15
  uint32_t test_move = (MV << OPCODE_OP_SHIFT)   |   (2 << OPCODE_S2_SHIFT)   | ( 1 << OPCODE_DS_SHIFT);
  input(test_move);

  assert( slice->vregs[1] == 0xbabe && "register move didn't work");

  cout << "-------------------------- test add --------------------------" << endl;


  uint32_t load_in1 = (MV_X_V << OPCODE_OP_SHIFT) | (1 << OPCODE_RS1_SHIFT) | (1 << OPCODE_DS_SHIFT) ;
  input(load_in1);
  assert( slice->vregs[1] == 0x1 && "didn't import to 1");



  // vregs[5] = vregs[1] + vregs[5]
  uint32_t test_add = (ADD << OPCODE_OP_SHIFT) | (1 << OPCODE_S1_SHIFT) | (5 << OPCODE_S2_SHIFT) | (5 << OPCODE_DS_SHIFT) ;
  input(test_add);
  slice->print_regs();
  assert( slice->vregs[5] == 0x1 && "didn't add 1+0");

  uint32_t test_add2 = (ADD << OPCODE_OP_SHIFT) | (1 << OPCODE_S1_SHIFT) | (1 << OPCODE_S2_SHIFT) | (5 << OPCODE_DS_SHIFT) ;
  input(test_add2);
  slice->print_regs();
  assert( slice->vregs[5] == 0x2 && "didn't add 1+1");
  
  uint32_t test_add3 = (ADD << OPCODE_OP_SHIFT) | (5 << OPCODE_S1_SHIFT) | (5 << OPCODE_S2_SHIFT) | (5 << OPCODE_DS_SHIFT) ;
  input(test_add3);
  slice->print_regs();
  assert( slice->vregs[5] == 0x4 && "didn't add 2+2");



  cout << "-------------------------- test sub --------------------------" << endl;

  uint32_t load_in3 = (MV_X_V << OPCODE_OP_SHIFT) | (3 << OPCODE_RS1_SHIFT) | (6 << OPCODE_DS_SHIFT) ;
  input(load_in3);
  slice->print_regs();

  uint32_t test_sub = (SUB << OPCODE_OP_SHIFT) | (6 << OPCODE_S1_SHIFT) | (1 << OPCODE_S2_SHIFT) | (6 << OPCODE_DS_SHIFT) ;
  input(test_sub);
  slice->print_regs();
  assert( slice->vregs[6] == 0x2 && "didn't sub 3-1");


  cout << "-------------------------- test add predicate --------------------------" << endl;
  // https://stackoverflow.com/questions/4324763/can-we-have-functions-inside-functions
  std::function<void()> setup_add_predicate = [&](){

    load_in1 = (MV_X_V << OPCODE_OP_SHIFT) | (1 << OPCODE_RS1_SHIFT) | (1 << OPCODE_DS_SHIFT) ;
    input(load_in1);
    load_in1 = (MV_X_V << OPCODE_OP_SHIFT) | (4 << OPCODE_RS1_SHIFT) | (4 << OPCODE_DS_SHIFT) ;
    input(load_in1);
    load_in1 = (MV_X_V << OPCODE_OP_SHIFT) | (5 << OPCODE_RS1_SHIFT) | (5 << OPCODE_DS_SHIFT) ;
    input(load_in1);
    assert( slice->vregs[1] == 0x1 && "didn't import");
    assert( slice->vregs[4] == 0x4 && "didn't import");
    assert( slice->vregs[5] == 0x5 && "didn't import");
  };

  setup_add_predicate();


  // vregs[5] = vregs[1] + vregs[5]
  uint32_t pred_test_add = (ADD << OPCODE_OP_SHIFT) | (4 << OPCODE_S1_SHIFT) | (5 << OPCODE_S2_SHIFT) | (1 << OPCODE_DS_SHIFT) ;
  input(pred_test_add);
  slice->print_regs();
  assert( slice->vregs[1] == 0x9 && "didn't add 1+0");


  setup_add_predicate();
  // should disable
  pred_test_add = (ADD << OPCODE_OP_SHIFT) | (4 << OPCODE_S1_SHIFT) | (5 << OPCODE_S2_SHIFT) | (1 << OPCODE_DS_SHIFT) | (1 << OPCODE_RS1_SHIFT) ;
  input(pred_test_add);
  slice->print_regs();
  assert( slice->vregs[1] == 0x1 && "added when PREDICATE is disabled");


  setup_add_predicate();
  // should disable
  pred_test_add = (ADD << OPCODE_OP_SHIFT) | (4 << OPCODE_S1_SHIFT) | (5 << OPCODE_S2_SHIFT) | (1 << OPCODE_DS_SHIFT) | (2 << OPCODE_RS1_SHIFT) ;
  input(pred_test_add);
  slice->print_regs();
  assert( slice->vregs[1] == 0x9 && "didn't add with neighbor predicate (1)");


  setup_add_predicate();
  // should disable
  pred_test_add = (ADD << OPCODE_OP_SHIFT) | (4 << OPCODE_S1_SHIFT) | (5 << OPCODE_S2_SHIFT) | (1 << OPCODE_DS_SHIFT) | (9 << OPCODE_RS1_SHIFT) ;
  input(pred_test_add);
  slice->print_regs();
  assert( slice->vregs[1] == 0x9 && "didn't add with neighbor predicate (2)");


  cout << "-------------------------- test mem parse --------------------------" << endl;

  uint32_t split_add_load = (MV_X_V << OPCODE_OP_SHIFT) | (9 << OPCODE_RS1_SHIFT) | (0 << OPCODE_DS_SHIFT) ;
  input(split_add_load);

  int32_t split_k15 = (LK15 << OPCODE_K_SHIFT) | (NOP << OPCODE_OP_SHIFT) | (0 << OPCODE_S1_SHIFT);
  input(split_k15);

  assert( slice->mem_bank_address == 0x7fe && "Slice not parsing memory address correctly");
  assert( slice->mem_permutation == 0x1f && "Slice not parsing memory mem_permutation correctly");

  cout << HEX_STRING(slice->mem_bank_address) << " " << HEX_STRING(slice->mem_permutation) << endl;
  // cout << slice->mem_bank_address << " " << slice->mem_permutation << endl;


  cout << "-------------------------- test split add --------------------------" << endl;
  split_add_load = (MV_X_V << OPCODE_OP_SHIFT) | (0 << OPCODE_RS1_SHIFT) | (0 << OPCODE_DS_SHIFT) ;
  input(split_add_load);

  split_add_load = (MV_X_V << OPCODE_OP_SHIFT) | (14 << OPCODE_RS1_SHIFT) | (1 << OPCODE_DS_SHIFT) ;
  input(split_add_load);
  slice->print_regs();

  // 0xf801 should subtract 1 from permutation, and add 1 to bank address
  
  uint32_t split_add0 = (ADD << OPCODE_OP_SHIFT) | (0 << OPCODE_S1_SHIFT) | (1 << OPCODE_S2_SHIFT) | (0 << OPCODE_DS_SHIFT);

  input(split_add0);
  input(split_add0);
  // slice->print_regs();

  uint32_t r_addr, r_perm;
  slice->util_parse_memory_fields(slice->vregs[0], r_addr, r_perm);
  cout << "Res: 0x" << HEX_STRING(slice->vregs[0]) << " 0x" << HEX_STRING(r_addr) << ", 0x" << HEX_STRING(r_perm) << endl;

  // after we run it twice, we would expect -2 in permutation and 2 in bank
  // turns out this test doesn't differentiate between normal add and splut add, check next test for that
  assert( slice->vregs[0] == 0xF002 && "didn't add correctly");


  cout << "-------------------------- test split add (2) --------------------------" << endl;

  split_add_load = (MV_X_V << OPCODE_OP_SHIFT) | (15 << OPCODE_RS1_SHIFT) | (0 << OPCODE_DS_SHIFT) ;
  input(split_add_load);

  split_add_load = (MV_X_V << OPCODE_OP_SHIFT) | (15 << OPCODE_RS1_SHIFT) | (1 << OPCODE_DS_SHIFT) ;
  input(split_add_load);
  slice->print_regs();

  split_add0 = (ADD << OPCODE_OP_SHIFT) | (2 << OPCODE_DS_SHIFT) | (0 << OPCODE_S1_SHIFT) | (1 << OPCODE_S2_SHIFT);
  input(split_add0);


  slice->util_parse_memory_fields(slice->vregs[2], r_addr, r_perm);
  cout << "Res: 0x" << HEX_STRING(slice->vregs[2]) << " 0x" << HEX_STRING(r_addr) << ", 0x" << HEX_STRING(r_perm) << endl;

  assert( r_addr == 0x7FE && "split add not working correctly");
  assert( r_perm == 0x2   && "split add not working correctly (2)");

  return 0;
}
