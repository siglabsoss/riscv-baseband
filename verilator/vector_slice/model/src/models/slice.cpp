#include "slice_container.hpp"
#include "slice.hpp"

#include <iostream>
#include <assert.h>


using namespace std;

// used for this file only
#define VERBOSE(x) if(this->verbose){x;}


    // ADD
    // SUB
    // AND
    // OR
    // XOR
    // MV
    // ROL
    // ROR
    // LV
    // SV
    // NOP

SliceFunctionalModel::SliceFunctionalModel(int index) : slice_index(index), verbose(true), parent(0)
{
  kregs_display[0] = 0;
  kregs_display[1] = 1;
  kregs_display[2] = 1;
  kregs_display[3] = 0;
  kregs_display[4] = 0;
  kregs_display[5] = 0;
  kregs_display[6] = 0;
  kregs_display[7] = 1;
  kregs_display[8] = 1;
  kregs_display[9] = 1;
  kregs_display[10] = 1;
  kregs_display[11] = 0;
  kregs_display[12] = 0;
  kregs_display[13] = 0;
  kregs_display[14] = 1;
  kregs_display[15] = 1;

  op_can_predicate[0] = 0;
  op_can_predicate[1] = 1; // add
  op_can_predicate[2] = 1;
  op_can_predicate[3] = 1;
  op_can_predicate[4] = 1;
  op_can_predicate[5] = 1;
  op_can_predicate[6] = 1; // mv
  op_can_predicate[7] = 0;
  op_can_predicate[8] = 1; // rol
  op_can_predicate[9] = 1; // ror
  op_can_predicate[10] = 0; // mv.x.v
  op_can_predicate[11] = 1; // mv.k15.v
  op_can_predicate[12] = 0;
  op_can_predicate[13] = 0;
  op_can_predicate[14] = 0;
  op_can_predicate[15] = 0; // mv.v.k15


  // emulate odd sized registers by masking with this value
  // We represent everything with 32 bits.  If VLEN is smaller
  // or changes, this mask allows us to represent that behaviour correctly
  vregs_mask = BIT_MASK32(0,VLEN-1);

}

void SliceFunctionalModel::reset()
{

  for(auto i = 0; i < NREGS; i++)
  {
    vregs[i] = 0;
  }

  for(auto i = 0; i < N_K_REGS; i++)
  {
    kregs[i] = 0;
  }

  
}

void SliceFunctionalModel::execute_k_op(uint32_t import)
{
  switch(kop) {
    case SK1:
      // datapath i0
      mem[vregs[s1]] = kregs[1];
    break;
    case SK2:
      // datapath i1
      mem[vregs[s1]] = kregs[2];
    break;
    case SK15:
      // vector register store helper
      mem[vregs[s1]] = kregs[15];
    break;
    case LK8:
      // datapath t0
      kregs[8] = mem[mem_bank_address];
    break;
    case LK9:
      // datapath t1
      kregs[9] = mem[mem_bank_address];
    break;
    case LK10:
      // datapath t2
      kregs[10] = mem[mem_bank_address];
    break;
    case LK11:
      // datapath t3
      kregs[11] = mem[mem_bank_address];
    break;
    case LK14:
      // datapath configuration
      kregs[14] = mem[mem_bank_address];
    break;
    case LK15:
      // vector register load helper
      // cout << "s1 " << s1 << endl;
      // cout << "vregs " << mem_bank_address << endl;

      kregs[15] = mem[mem_bank_address];
    break;
    default:
    case KNOP:
    break;
  }
}

// mask for vregs only, kregs are planned to be 32 bit for awhile

uint32_t SliceFunctionalModel::mask(uint32_t value)
{
  return vregs_mask & value;
}

void SliceFunctionalModel::execute_op(uint32_t import)
{
  uint32_t t1,t2,t3,t4;

  uint32_t s1_perm, s1_addr, s2_perm, s2_addr, t_addr, t_perm;
  SliceFunctionalModel *left, *right;

  // cout << "input import: 0x" << HEX_STRING(import) << endl;

  if(predicate) {

    switch(op){
      case ADD:
        util_parse_memory_fields(vregs[s1], s1_addr, s1_perm);
        util_parse_memory_fields(vregs[s2], s2_addr, s2_perm);

        // cout << "S1: 0x" << HEX_STRING(vregs[s1]) << " 0x" << HEX_STRING(s1_addr) << ", 0x" << HEX_STRING(s1_perm) << endl;
        // cout << "S2: 0x" << HEX_STRING(vregs[s2]) << " 0x" << HEX_STRING(s2_addr) << ", 0x" << HEX_STRING(s2_perm) << endl;

        t_addr = (s1_addr + s2_addr) & MEMORY_ADDR_MASK;
        t_perm = (s1_perm + s2_perm) & MEMORY_PERMUTATION_MASK;

        vregs[ds] = mask((t_perm<<MEMORY_PERMUTATION_SHIFT) | (t_addr << MEMORY_ADDR_SHIFT));
      break;

      case SUB:
        util_parse_memory_fields(vregs[s1], s1_addr, s1_perm);
        util_parse_memory_fields(vregs[s2], s2_addr, s2_perm);

        t_addr = (s1_addr - s2_addr) & MEMORY_ADDR_MASK;
        t_perm = (s1_perm - s2_perm) & MEMORY_PERMUTATION_MASK;

        vregs[ds] = mask((t_perm<<MEMORY_PERMUTATION_SHIFT) | (t_addr << MEMORY_ADDR_SHIFT));
      break;

      case AND:
        vregs[ds] = mask(vregs[s1] & vregs[s2]);
      break;

      case OR:
        vregs[ds] = mask(vregs[s1] | vregs[s2]);
      break;
   
      case XOR:
        vregs[ds] = mask(vregs[s1] ^ vregs[s2]);
      break;
   
      case MV:
        vregs[ds] = mask(vregs[s2]);
      break;

      case ROL:
        assert(parent);
        left = parent->get_left(slice_index);
        vregs[ds] = mask(left->vregs[s2]);
      break;

      case ROR:
        assert(parent);
        right = parent->get_right(slice_index);
        vregs[ds] = mask(right->vregs[s2]);
      break;

      case MV_V_K15:
        kregs[15] = mask(vregs[s2]);
        break;
      case MV_K15_V:
        vregs[ds] = mask(kregs[15]);
        break;

      case MV_X_V:
        vregs[ds] = mask(import);
      break;
      default:
      case NOP:
      break;
    } // switch(op)
  } // if predicate
} // execute_op


// op must be set in order for this to run
void SliceFunctionalModel::set_predicate(uint32_t import)
{
  // bool predicate  ->

  // false if opcode is disabled, 
  // true if opcide is enabled
  // this will always be true if op_can_predicate[op] is false

  predicate = true;

  // does this opcode support predicate?
  bool can_predicate = op_can_predicate[op];

  VERBOSE(cout << "checked " << op << " with " << can_predicate << endl);

  if(can_predicate)
  {
    // if the predicate bit on import for our slice index is 0, we are enabled
    predicate = ! BIT_SHIFT_MASK(import,slice_index);

    VERBOSE(
    if(predicate){
      cout << "Predicate is enabling this instruciton" << endl;
    } else {
      cout << "Predicate is disabling this instruciton" << endl;
    }
    );

  }
  else
  {
    VERBOSE(cout << "Predicate CHECKING is not done for this instruciton" << endl);
  }

}

void SliceFunctionalModel::input(uint32_t opcode, uint32_t import)
{
  // parse opcode, sets s1,s2,op ...
  parse_op(opcode);

  // relies on op
  set_predicate(import);

  // using value of s1, parse out memory access fields
  parse_memory_fields(vregs[s1]);

  // the order of execution should NEVER matter here
  execute_op(import);
  execute_k_op(import);
}

// normally called with s1, has side effects on class
void SliceFunctionalModel::parse_memory_fields(uint32_t val)
{
  cout << "Parse memory: 0x" << HEX_STRING(val) << endl;
  // uint32_t _mem_access;
  mem_bank_address = ((val >> MEMORY_ADDR_SHIFT)&MEMORY_ADDR_MASK);
  mem_permutation =  ((val >> MEMORY_PERMUTATION_SHIFT)&MEMORY_PERMUTATION_MASK);
  // mem_g =            ((val >> MEMORY_G_SHIFT)&MEMORY_G_MASK);
  // _mem_access =       ((val >> MEMORY_ACCESS_SHIFT)&MEMORY_ACCESS_MASK);
  // mem_access = (mem_access_t) _mem_access;

  if( verbose ) {
    cout << "mem_bank         " << HEX_STRING(mem_bank_address) << endl;
    cout << "mem_permutation  " << HEX_STRING(mem_permutation) << endl;
    // cout << "mem_g            " << HEX_STRING(mem_g) << endl;
    // cout << "mem_access       " << HEX_STRING(_mem_access) << endl;
    cout << endl;
  }
}

void SliceFunctionalModel::util_parse_memory_fields(uint32_t val, uint32_t &mem_bank_address, uint32_t &mem_permutation)
{
  mem_bank_address = ((val >> MEMORY_ADDR_SHIFT)&MEMORY_ADDR_MASK);
  mem_permutation =  ((val >> MEMORY_PERMUTATION_SHIFT)&MEMORY_PERMUTATION_MASK);
}


// slice->parse_op(0x780); // ds only
// slice->parse_op(0x7800); // op only
// slice->parse_op(0xF8000); // rs1 only
// slice->parse_op(0xF00000); // s2 only
// slice->parse_op(0xF000000); // k only
// slice->parse_op(0xF0000000); // s1 only
void SliceFunctionalModel::parse_op(uint32_t opcode)
{
  VERBOSE(cout << "Looking at 0x" << HEX_STRING(opcode) << endl;);

  uint32_t _op;
  uint32_t _k;

  ds = ((opcode >> OPCODE_DS_SHIFT)&OPCODE_DS_MASK);
  _op = ((opcode >> OPCODE_OP_SHIFT)&OPCODE_OP_MASK);
  rs1 = ((opcode >> OPCODE_RS1_SHIFT)&OPCODE_RS1_MASK);
  s2 = ((opcode >> OPCODE_S2_SHIFT)&OPCODE_S2_MASK);
  _k = ((opcode >> OPCODE_K_SHIFT)&OPCODE_K_MASK);
  s1 = ((opcode >> OPCODE_S1_SHIFT)&OPCODE_S1_MASK);

  op = (opcode_t) _op;
  kop = (k_opcode_t) _k;
  


  if(verbose) {
    cout << "s1  0x" << HEX_STRING( s1 ) << endl;
    cout << "k   0x" << HEX_STRING( kop ) << endl;
    cout << "s2  0x" << HEX_STRING( s2 ) << endl;
    cout << "rs1 0x" << HEX_STRING( rs1 ) << endl;
    cout << "op  0x" << HEX_STRING( op ) << endl;
    cout << "ds  0x" << HEX_STRING( ds ) << endl;
    cout << endl;
  }

  assert( ds <= NREGS && "illegal value for ds" );
  assert( s1 <= NREGS && "illegal value for s1" );
  assert( s2 <= NREGS && "illegal value for s2" );
}

void SliceFunctionalModel::print_all_regs(void)
{
  print_regs();
  print_k_regs();
}

void SliceFunctionalModel::print_regs(void)
{
  cout << "Vregs: " << endl;
  for(auto i = 0; i < NREGS; i++)
  {
    cout << " " << i << ": " << HEX_STRING(vregs[i]) << endl;
  }
}

void SliceFunctionalModel::print_k_regs(void)
{
  cout << "Kregs: " << endl;
  for(auto i = 0; i < N_K_REGS; i++) {
    if (kregs_display[i]) {
      cout << " " << i << ": " << HEX_STRING(kregs[i]) << endl;
    }
  }
}


void SliceFunctionalModel::print_mem(uint32_t start, uint32_t end)
{

  auto j = 0;
  auto col = 16;
  for(auto i = start; i < end; i++)
  {
    cout << HEX_STRING( mem[i] ) << ", ";

    if(++j % col == 0)
    {
      cout << endl;
    }


  }

  cout << endl;

}



// //      |S1||K ||S2||RS1||OP||DS|
// key = M"-------------------------0001011",