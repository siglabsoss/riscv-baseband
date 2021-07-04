#include "slice.hpp"
#include "slice_container.hpp"

#include <iostream>
#include <assert.h>
#include <functional>


static uint32_t vexregs[VEX_REGS];
// SliceFunctionalModel *slice;
SliceContainerModel *parent;

using namespace std;

void input(uint32_t op)
{
  uint32_t rs1 = ((op >> OPCODE_RS1_SHIFT)&OPCODE_RS1_MASK);
  uint32_t import_reg = vexregs[rs1];

  // cout << "rs1: " << rs1 << " = " << HEX_STRING(import_reg) << endl;



  parent->input(op, import_reg);

  // uint32_t op_sv = (9 << OPCODE_OP_SHIFT) | (1 << OPCODE_S1_SHIFT) | (2 << OPCODE_S2_SHIFT) ;
}


int main (void)
{

  parent = new SliceContainerModel();
  parent->reset();
  
  

  for(auto i = 0; i < VEX_REGS; i++)
  {
    vexregs[i] = 0;
  }

  


  // some pre-made regs in vex
  vexregs[0] = 0x0; // this is wired to zero inside riscv
  vexregs[1] = 0x1;
  vexregs[2] = 0x2;
  vexregs[3] = 0x3;
  vexregs[4] = 0x4;
  vexregs[5] = 0x5;
  vexregs[7] = 0xdeadbeef;
  vexregs[8] = 0xcafebabe;
  vexregs[9] = 0xfffffffe; // all bits set bit 0
  vexregs[10] = 0x0; // changing, do not rely
  vexregs[11] = 0x0; // changing, do not rely

  // cout << "right idx " << parent->get_right_index(2) << endl;
  // cout << "right idx " << parent->get_right_index(30) << endl;
  // cout << "right idx " << parent->get_right_index(31) << endl;
  // cout << "right idx " << parent->get_right_index(0) << endl;
  // cout << "right idx " << parent->get_right_index(1) << endl;

  // cout << "left idx " << parent->get_left_index(2) << endl;
  // cout << "left idx " << parent->get_left_index(30) << endl;
  // cout << "left idx " << parent->get_left_index(31) << endl;
  // cout << "left idx " << parent->get_left_index(0) << endl;
  // cout << "left idx " << parent->get_left_index(1) << endl;


  uint32_t pred_load;
  uint32_t pred_move;
  
  for(auto i = 0; i < NSLICES; i++)
  {
    // cout << "iiiii " << i << " iiiii" << endl;
    // use processor reg 10 for a value
    vexregs[10] = i;

    // slices[*]->vregs[0] = i
    pred_load = (MV_X_V << OPCODE_OP_SHIFT) | (10 << OPCODE_RS1_SHIFT) | (0 << OPCODE_DS_SHIFT) ;
    input(pred_load);

    // use processor reg 11 for a predicate
    vexregs[11] = ~(1 << i);

    // cout << "feeding: 0x" << HEX_STRING(vexregs[11]) << endl;

    // set vregs[1] = vregs[0] but only enabled for one slice
    pred_move = (MV << OPCODE_OP_SHIFT)   |   (0 << OPCODE_S2_SHIFT)  | ( 1 << OPCODE_DS_SHIFT) | (11 << OPCODE_RS1_SHIFT);
    input(pred_move);
  }

  for(auto i = 0; i < NSLICES; i++)
  {
    assert( parent->slices[i]->vregs[1] == i && "individual load failed");
  }

  cout << "---------------- at this point each slice has it's own index in r1 ----------------" << endl;



  // -------------------------- test roll left --------------------------  
  // uint32_t load_rol;
  // // uint32_t load_rol = (MV_X_V << OPCODE_OP_SHIFT) | (4 << OPCODE_RS1_SHIFT) | (7 << OPCODE_DS_SHIFT) ;
  // // input(load_rol);

  // load_rol = (MV_X_V << OPCODE_OP_SHIFT) | (7 << OPCODE_RS1_SHIFT) | (8 << OPCODE_DS_SHIFT);
  // input(load_rol);


  // shift left
  uint32_t rol_op0 = (ROL << OPCODE_OP_SHIFT)  | (1 << OPCODE_S2_SHIFT) | (2 << OPCODE_DS_SHIFT) | (0 << OPCODE_RS1_SHIFT);
  input(rol_op0);

  for(auto i = 0; i < NSLICES; i++)
  {
    // cout << "slice " << i << ": " << parent->slices[i]->vregs[2] << endl;

    auto check = i - 1;

    if(i == 0){
      check = 31;
    }

    assert( parent->slices[i]->vregs[2] == check && "ROL got wrong number");
  }

  // shift left again, this time the result is in 3
  uint32_t rol_op1 = (ROL << OPCODE_OP_SHIFT)  | (2 << OPCODE_S2_SHIFT) | (3 << OPCODE_DS_SHIFT) | (0 << OPCODE_RS1_SHIFT);
  input(rol_op1);

  // shift right for the first time, the result in 4
  uint32_t ror_op = (ROR << OPCODE_OP_SHIFT)  | (3 << OPCODE_S2_SHIFT) | (4 << OPCODE_DS_SHIFT) | (0 << OPCODE_RS1_SHIFT);
  input(ror_op);

  // copy paste the same loop check afrom above, but checking 4 this time
  for(auto i = 0; i < NSLICES; i++)
  {
    auto check = i - 1;
    if(i == 0){
      check = 31;
    }
    assert( parent->slices[i]->vregs[4] == check && "ROR got wrong number");
  }





  // input(rol_op);
  // input(rol_op);
  // input(rol_op);
  // input(rol_op);
  // slice->print_all_regs();

  // // slice->print_regs();

  // assert( slice->vregs[8] == 0xeadbeefd && "didn't roll left ");



  // cout << endl << endl;
  // cout << "-----------------------all regs for step " << endl;
  // for(auto j = 0; j < NSLICES; j++)
  // {
  //   cout << "-----------------------   slice: " << j << endl;
  //   parent->slices[j]->print_regs();
  // }
  // cout << endl;

#ifdef asddlfkj

  // s1 is reg
  // s2 is mem addr


  // int32_t new_load = (LK15 << OPCODE_K_SHIFT) | (NOP << OPCODE_OP_SHIFT) | (7 << OPCODE_RS1_SHIFT) | (0 << OPCODE_DS_SHIFT) ;

  // slice->parse_op(new_load);

  // slice->print_all_regs();

  // input(new_load);

  // -------------------------- test import --------------------------
  
  uint32_t load_in7 = (MV_X_V << OPCODE_OP_SHIFT) | (7 << OPCODE_RS1_SHIFT) | (0 << OPCODE_DS_SHIFT) ;
  input(load_in7);

  // slice->print_all_regs();
  // slice->print_mem(0,100);
  for(auto i = 0; i < NSLICES; i++ ) {
    assert( parent->slices[i]->vregs[i] == 0xdeadbeef && "Import op didn't work");
  }
  

  uint32_t load_in2 = (MV_X_V << OPCODE_OP_SHIFT) | (8 << OPCODE_RS1_SHIFT) | (0 << OPCODE_DS_SHIFT) ;
  input(load_in2);

  // slice->print_regs();
  assert( slice->vregs[0] == 0xcafebabe && "2nd import didn't work");

  uint32_t load_zero = (MV_X_V << OPCODE_OP_SHIFT) | (0 << OPCODE_RS1_SHIFT) | (0 << OPCODE_DS_SHIFT) ;
  input(load_zero);  

  // slice->print_regs();
  assert( slice->vregs[0] == 0x0 && "didn't re-zero");


  // -------------------------- test STore --------------------------

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


  assert( slice->mem[3] == 0xdeadbeef && "store opcode didn't work" );



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

  assert( slice->vregs[4] == 0xdeadbeef && "opcode load didn't work");



  // -------------------------- test move -------------------------

  uint32_t move_load;

  // vregs[1] = vex[7]
  move_load = (MV_X_V << OPCODE_OP_SHIFT) | (7 << OPCODE_RS1_SHIFT) | (1 << OPCODE_DS_SHIFT) ;
  input(move_load);

  move_load = (MV_X_V << OPCODE_OP_SHIFT) | (8 << OPCODE_RS1_SHIFT) | (2 << OPCODE_DS_SHIFT) ;
  input(move_load);

  assert( slice->vregs[1] == 0xdeadbeef && "opcode load didn't work");
  assert( slice->vregs[2] == 0xcafebabe && "opcode load didn't work");

  
  // move pointer reg 2 into pointer reg 15
  uint32_t test_move = (MV << OPCODE_OP_SHIFT)   |   (2 << OPCODE_S2_SHIFT)   | ( 1 << OPCODE_DS_SHIFT);
  input(test_move);

  assert( slice->vregs[1] == 0xcafebabe && "register move didn't work");

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


  // // -------------------------- test roll left --------------------------  
  // uint32_t load_rol;
  // // uint32_t load_rol = (MV_X_V << OPCODE_OP_SHIFT) | (4 << OPCODE_RS1_SHIFT) | (7 << OPCODE_DS_SHIFT) ;
  // // input(load_rol);

  // load_rol = (MV_X_V << OPCODE_OP_SHIFT) | (7 << OPCODE_RS1_SHIFT) | (8 << OPCODE_DS_SHIFT);
  // input(load_rol);



  // uint32_t rol_op = (ROL << OPCODE_OP_SHIFT)  | (8 << OPCODE_S2_SHIFT) | (8 << OPCODE_DS_SHIFT);

  // input(rol_op);
  // input(rol_op);
  // input(rol_op);
  // input(rol_op);
  // slice->print_all_regs();

  // // slice->print_regs();

  // assert( slice->vregs[8] == 0xeadbeefd && "didn't roll left ");


  // // -------------------------- test roll right --------------------------  
  // uint32_t load_ror;
  // // uint32_t load_ror = (MV_X_V << OPCODE_OP_SHIFT) | (1 << OPCODE_RS1_SHIFT) | (7 << OPCODE_DS_SHIFT) ;
  // // input(load_ror);

  // load_ror = (MV_X_V << OPCODE_OP_SHIFT) | (7 << OPCODE_RS1_SHIFT) | (8 << OPCODE_DS_SHIFT);
  // input(load_ror);

  // load_ror = (MV_X_V << OPCODE_OP_SHIFT) | (0 << OPCODE_RS1_SHIFT) | (9 << OPCODE_DS_SHIFT);
  // input(load_ror);

  // slice->print_all_regs();

  // uint32_t ror_op = (ROR << OPCODE_OP_SHIFT) | (8 << OPCODE_S2_SHIFT) | (9 << OPCODE_DS_SHIFT);
  // input(ror_op);

  // assert( slice->vregs[9] == 0xef56df77 && "didn't roll right" );

  // slice->print_all_regs();




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


#endif

  return 0;
}
