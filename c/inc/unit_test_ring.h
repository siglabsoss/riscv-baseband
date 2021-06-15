#ifndef __UNIT_TEST_RING_H__
#define __UNIT_TEST_RING_H__

#include "random.h"


#define UNIT_SRC_SHIFT (0)
#define UNIT_SRC_MASK (0x1F)

#define UNIT_DST_SHIFT (5)
#define UNIT_DST_MASK (0x1F)

#define UNIT_FIELD1_SHIFT (10)
#define UNIT_FIELD1_MASK (0x1F)

#define UNIT_FIELD2_SHIFT (15)
#define UNIT_FIELD2_MASK (0x1F)

#define UNIT_FIELD3_SHIFT (20)
#define UNIT_FIELD3_MASK (0x1F)

#define UNIT_FIELD4_SHIFT (25)
#define UNIT_FIELD4_MASK (0x1F)

#define SEED_PULL_MASK (0x2f)

// this is the split out fields for a ringbus message
typedef struct {
  unsigned int src;
  unsigned int dst;
  unsigned int f1;
  unsigned int f2;
  unsigned int f3;
  unsigned int f4;
} ring_unit_t;

#define RING_UNIT_COUNTERS_MAX (2)

// this structure is tracked by this FPGA during operations
typedef struct {
  unsigned int counters[RING_UNIT_COUNTERS_MAX];
  unsigned int illegal;
  unsigned int queue0;  // how many time to repeat queue
  unsigned int queue1;  // who to send it to
  unsigned int queue2;  // enum value which looks up exact value to be sent
  unsigned int seed;    // random seed, optional to set, 0 to disable
  unsigned int delay_countdown;
} ring_unit_counters_t;

ring_unit_t ring_t_decode(unsigned int opcode) {
  ring_unit_t res;

  res.src = ((opcode >> UNIT_SRC_SHIFT)&UNIT_SRC_MASK);
  res.dst = ((opcode >> UNIT_DST_SHIFT)&UNIT_DST_MASK);
  res.f1 = ((opcode >> UNIT_FIELD1_SHIFT)&UNIT_FIELD1_MASK);
  res.f2 = ((opcode >> UNIT_FIELD2_SHIFT)&UNIT_FIELD2_MASK);
  res.f3 = ((opcode >> UNIT_FIELD3_SHIFT)&UNIT_FIELD3_MASK);
  res.f4 = ((opcode >> UNIT_FIELD4_SHIFT)&UNIT_FIELD4_MASK);

  return res;
}

unsigned int ring_t_encode(unsigned int src, unsigned int dst, unsigned f1, unsigned f2, unsigned f3, unsigned f4 ) {
  unsigned int res;

res =
    (src&UNIT_SRC_MASK) << UNIT_SRC_SHIFT |
    (dst&UNIT_DST_MASK) << UNIT_DST_SHIFT |
    (f1&UNIT_FIELD1_MASK) << UNIT_FIELD1_SHIFT |
    (f2&UNIT_FIELD2_MASK) << UNIT_FIELD2_SHIFT |
    (f3&UNIT_FIELD3_MASK) << UNIT_FIELD3_SHIFT |
    (f4&UNIT_FIELD4_MASK) << UNIT_FIELD4_SHIFT;

    return res;
}

// shorter version of above
unsigned int ring_t_enc(unsigned f1, unsigned f2, unsigned f3, unsigned f4 ) {
  return ring_t_encode(0,0,f1,f2,f3,f4); 
}



unsigned int bump_c0(void) { return ring_t_enc(1,1,0,0); }
unsigned int bump_c1(void) { return ring_t_enc(1,1,1,0); }
unsigned int gen_type_2(unsigned int target) { return ring_t_enc(3,2,target,0); }
unsigned int gen_set_seed(unsigned int seed) {

  // assumes that all fields are 5 bits
  unsigned int f2 = seed & 0x1f;
  unsigned int f3 = (seed>>5) & 0x1f;
  unsigned int f4 = (seed>>10) & 0x1f;
  return ring_t_enc(5,f2,f3,f4);
}









void ring_unit_counters_t_init(ring_unit_counters_t *c) 
{
  for(unsigned int i = 0; i < RING_UNIT_COUNTERS_MAX; i++) {
    c->counters[i] = 0;
  }
  c->illegal = 0;

  c->queue0 = 0;
  c->queue1 = 0;
  c->queue2 = 0;

  c->seed = 0;
  c->delay_countdown = 0;
}






unsigned int ring_unit_lookup_addr(unsigned int enumm) {
  switch(enumm) {
    case RING_ENUM_PC:
      return RING_ADDR_PC;
    case RING_ENUM_ETH:
      return RING_ADDR_ETH;
    case RING_ENUM_CS20:
      return RING_ADDR_CS20;
    case RING_ENUM_CS01:
      return RING_ADDR_CS01;
    case RING_ENUM_CS11:
      return RING_ADDR_CS11;
    case RING_ENUM_CS21:
      return RING_ADDR_CS21;
    case RING_ENUM_CS31:
      return RING_ADDR_CS31;
    case RING_ENUM_CS02:
      return RING_ADDR_CS02;
    case RING_ENUM_CS12:
      return RING_ADDR_CS12;
    case RING_ENUM_CS22:
      return RING_ADDR_CS22;
    case RING_ENUM_CS32:
      return RING_ADDR_CS32;
    default:
      return 0xffffffff;
  }
}
#ifndef VERILATE_TESTBENCH

void ring_unit_send_to_enum(unsigned int dst, unsigned int data) {
  unsigned int ttl = ring_unit_lookup_addr(dst);

  unsigned int occupancy;

  if(ttl != 0xffffffff) {
    // these nop are handled by previous calls
    // these only protect against back-to-back calling of this fn
    // asm("nop");
    // asm("nop");
    // asm("nop");
    while(1)
    {
     CSR_READ(RINGBUS_SCHEDULE_OCCUPANCY, occupancy);
     if(occupancy < RINGBUS_SCHEDULE_DEPTH)
     {
      break;
     }
    }

    CSR_WRITE(RINGBUS_WRITE_ADDR, ttl);
    CSR_WRITE(RINGBUS_WRITE_DATA, data);
    CSR_WRITE_ZERO(RINGBUS_WRITE_EN);
  }
}

void handle_counters_op(ring_unit_counters_t *counters, ring_unit_t *parsed) {
  // register volatile unsigned int check_dma asm("x3");

  // check_dma = 0x40000000 | parsed->f2;
  // check_dma = 0x40000000 | parsed->f3;
  // check_dma = 0x40000000 | parsed->f4;

  if(parsed->f3 >= RING_UNIT_COUNTERS_MAX) {
    counters->illegal++;
    return;
  }

  switch(parsed->f2) {
    case 1:
      // check_dma = 0x44000000 | counters->counters[parsed->f3];
      counters->counters[parsed->f3]++;
      break;
    case 2:
      counters->counters[parsed->f3]--;
      break;
    case 3:
      counters->counters[parsed->f3] += parsed->f4;
      break;

    default:
    case 0:
      counters->illegal++;
      break;
  }
}

void handle_set_seed_op(ring_unit_counters_t *counters, ring_unit_t *parsed) {
  counters->seed = parsed->f2 | (parsed->f3<<5) | (parsed->f4<<10);
  // ring_unit_send_to_enum(RING_ENUM_PC, counters->seed); // debug
  // apply seed
  simple_random_seed(counters->seed);
}

void handle_generate_op(ring_unit_counters_t *counters, ring_unit_t *parsed) {
  // register volatile unsigned int check_dma asm("x3");

  // check_dma = 0x50000000 | parsed->f2;
  // check_dma = 0x50000000 | parsed->f3;
  // check_dma = 0x50000000 | parsed->f4;

  if( counters->queue0 != 0 ) {
    counters->illegal++; // can't start a queue when we already have one
  }

  // unsigned int op;

  switch(parsed->f2) {
    case 1:
      counters->queue0 = 5;
      counters->queue1 = 0;
#define QUEUE_TYPE_1 ring_t_enc(2,0,8,0)
      counters->queue2 = 1;
      break;
    case 2:
      // set queue0 which will be read later in ring_unit_empty_queue
      counters->queue0 = 15;
      counters->queue1 = parsed->f3;
#define QUEUE_TYPE_2 ring_t_enc(1,1,0,0)
      counters->queue2 = 2;
      // ring_unit_send_to_enum(RING_ENUM_PC, counters->seed); // debug
      // counters->seed = 123;
      if( counters->seed != 0 ) {
        counters->delay_countdown = simple_random() & SEED_PULL_MASK;
        // ring_unit_send_to_enum(RING_ENUM_PC, counters->delay_countdown); // debug
      }

      break;
    // case 3:
    //   counters->counters[parsed->f3] += parsed->f4;
    //   break;

    default:
    case 0:
      counters->illegal++;
      break;
  }
}

void handle_dump(ring_unit_counters_t *counters) {
  ring_unit_send_to_enum(RING_ENUM_PC, OUR_RING_ENUM);
  for(unsigned int i = 0; i < RING_UNIT_COUNTERS_MAX; i++) {
    ring_unit_send_to_enum(RING_ENUM_PC, counters->counters[i]);
    asm("nop");
    asm("nop");
    asm("nop");
  }
  
  ring_unit_send_to_enum(RING_ENUM_PC, counters->illegal);
  asm("nop");
  asm("nop");
  asm("nop");
  ring_unit_send_to_enum(RING_ENUM_PC, counters->queue0);
  asm("nop");
  asm("nop");
  asm("nop");
  ring_unit_send_to_enum(RING_ENUM_PC, counters->queue1);
  asm("nop");
  asm("nop");
  asm("nop");
  ring_unit_send_to_enum(RING_ENUM_PC, counters->queue2);
  asm("nop");
  asm("nop");
  asm("nop");


}

void handle_single_ring_in(ring_unit_counters_t *counters) {
  // register volatile unsigned int check_dma asm("x3");
  CSR_WRITE(RINGBUS_INTERRUPT_CLEAR, 0);
  int a;
  CSR_READ(RINGBUS_READ_DATA, a);


  ring_unit_t parsed = ring_t_decode(a);
  // ring_unit_t parsed;

  // check_dma = 0x30000000 | parsed.f1;
    

  switch(parsed.f1) {
    case 0:
      break; // nop
    case 1:
      handle_counters_op(counters, &parsed);
      break;
    case 2:
      ring_unit_send_to_enum(parsed.f2, parsed.f3);
      break;
    case 3:
      handle_generate_op(counters, &parsed);
      break;
    case 4:
      handle_dump(counters);
      break;
    case 5:
      handle_set_seed_op(counters, &parsed);
      break;
    default:
      counters->illegal++;
      break;
  }

  // foomax(parsed);

  // parsed = retfn();
}


void ring_unit_empty_queue(ring_unit_counters_t *counters) {
  // register volatile unsigned int check_dma asm("x3");
  unsigned int occupancy;

  if(counters->queue0) {


      // if we have a seed, we exit immediatly to create a random jitter
      if(counters->seed != 0) {
        if(counters->delay_countdown > 0) {
          counters->delay_countdown--;
          return;
        } else {

          // ring_unit_send_to_enum(RING_ENUM_PC, 0xb);
          // grab a new seed and run
          counters->delay_countdown = simple_random() & SEED_PULL_MASK;
        }
      }


      CSR_READ(RINGBUS_SCHEDULE_OCCUPANCY, occupancy);
      if(occupancy < RINGBUS_SCHEDULE_DEPTH) {

        unsigned int message = 0;

        if(counters->queue2 == 1) {
          message = QUEUE_TYPE_1;
        }
        if(counters->queue2 == 2) {
          message = QUEUE_TYPE_2;
        }


        ring_unit_send_to_enum(counters->queue1,message);
        counters->queue0--;
        // check_dma = 0x60000000 | counters->queue0;
      }
    }

  if(counters->queue0 == 0) {
    counters->queue0 = 0;
    counters->queue1 = 0;
    counters->queue2 = 0;
  }
}


void ring_unit_test_as(unsigned int me) {
  (void)me;
  // register volatile unsigned int check_dma asm("x3");
  // check_dma = 0xff000000 | me;

  ring_unit_counters_t counters;
  ring_unit_counters_t_init(&counters);

  unsigned int occupancy;
    

  // int h1;
  while(1) {
    // CSR_READ(mip, h1);

    CSR_READ(RINGBUS_READ_OCCUPANCY, occupancy);
    if(occupancy) {
      // check_dma = 0x20000000;
      handle_single_ring_in(&counters);
    }

    // check_dma = 0x0f0f0f0f;

    ring_unit_empty_queue(&counters);

    // check_dma = 0x0f0f0f0f;
  }


}

#else

std::string get_enum_string(uint32_t enumm) {
  if( enumm == RING_ENUM_ETH)  return std::string(_STR(RING_ENUM_ETH));
  if( enumm == RING_ENUM_PC)   return std::string(_STR(RING_ENUM_PC));
  if( enumm == RING_ENUM_CS20) return std::string(_STR(RING_ENUM_CS20));
  if( enumm == RING_ENUM_CS01) return std::string(_STR(RING_ENUM_CS01));
  if( enumm == RING_ENUM_CS11) return std::string(_STR(RING_ENUM_CS11));
  if( enumm == RING_ENUM_CS21) return std::string(_STR(RING_ENUM_CS21));
  if( enumm == RING_ENUM_CS31) return std::string(_STR(RING_ENUM_CS31));
  if( enumm == RING_ENUM_CS02) return std::string(_STR(RING_ENUM_CS02));
  if( enumm == RING_ENUM_CS12) return std::string(_STR(RING_ENUM_CS12));
  if( enumm == RING_ENUM_CS22) return std::string(_STR(RING_ENUM_CS22));
  if( enumm == RING_ENUM_CS32) return std::string(_STR(RING_ENUM_CS32));
  return "";
}

void print_ring_unit_t(ring_unit_t x) {
  using namespace std;
  cout << "ring_unit_t:" << endl;
  cout << "  src " << x.src  << endl;
  cout << "  dst " << x.dst << endl;
  cout << "  f1 " << x.f1 << endl;
  cout << "  f2 " << x.f2 << endl;
  cout << "  f3 " << x.f3 << endl;
  cout << "  f4 " << x.f4 << endl;
}

void print_ring_unit_counters_t(uint32_t enumm, ring_unit_counters_t x) {
  using namespace std;
  cout << "ring_unit_counters_t (" << get_enum_string(enumm) << "):" << endl;
  cout << "  c[0]    " << x.counters[0]  << endl;
  cout << "  c[1]    " << x.counters[1]  << endl;
  cout << "  illegal " << x.illegal  << endl;
  cout << "  queue0 " << x.queue0  << endl;
  cout << "  queue1 0x" << HEX_STRING(x.queue1)  << endl;
  cout << "  queue2 " << x.queue2  << endl;
  // cout << "  dst " << x.dst << endl;
  // cout << "  f1 " << x.f1 << endl;
  // cout << "  f2 " << x.f2 << endl;
  // cout << "  f3 " << x.f3 << endl;
  // cout << "  f4 " << x.f4 << endl;
}


// return 0 means ok
int vector_to_ring_unit_counters(std::vector<uint32_t> din, uint32_t *enumm, ring_unit_counters_t* ret)
{
  using namespace std;
  // vector should have 1 extra uint32_t which is the enumm of the reporting
  // vector should have 2 more extra which are late additions

  unsigned int got_len = din.size();
  unsigned int expected_len = (sizeof(ring_unit_counters_t)/4) + 1 - 2;

  if( expected_len != got_len ) {
    cout << "Expected " << expected_len << " rb packets, got " << got_len << endl;
    return 1;
  }

  uint32_t* p = (uint32_t*)ret;

  *enumm = din[0];

  for(auto it = din.begin()+1; it != din.end(); it++) {
    *p = *it;
    p++;
  }

  return 0;

}


#endif // VERILATE_TESTBENCH




#endif