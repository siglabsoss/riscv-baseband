#ifndef __RINGBUS2_POST_H__
#define __RINGBUS2_POST_H__

/// This file includes function definitions which usually is a nono
/// This was done for historical reasons before OUR_RING_ENUM was added at the compiler
/// argument level
/// 


#ifndef __RINGBUS2_PRE_H__
#error "you must include ringbus2_pre.h before including rinbus2_post.h"
#endif

#ifndef OUR_RING_ENUM
#error "You must define OUR_RING_ENUM before including this file"
#endif


#define RING_ADDR_PC   (((RING_ENUM_PC   - OUR_RING_ENUM - 1) + (RING_BUS_LENGTH*2)) % RING_BUS_LENGTH)
#define RING_ADDR_ETH  (((RING_ENUM_ETH  - OUR_RING_ENUM - 1) + (RING_BUS_LENGTH*2)) % RING_BUS_LENGTH)
#define RING_ADDR_CS20 (((RING_ENUM_CS20 - OUR_RING_ENUM - 1) + (RING_BUS_LENGTH*2)) % RING_BUS_LENGTH)
#define RING_ADDR_CS01 (((RING_ENUM_CS01 - OUR_RING_ENUM - 1) + (RING_BUS_LENGTH*2)) % RING_BUS_LENGTH)
#define RING_ADDR_CS11 (((RING_ENUM_CS11 - OUR_RING_ENUM - 1) + (RING_BUS_LENGTH*2)) % RING_BUS_LENGTH)
#define RING_ADDR_CS21 (((RING_ENUM_CS21 - OUR_RING_ENUM - 1) + (RING_BUS_LENGTH*2)) % RING_BUS_LENGTH)
#define RING_ADDR_CS31 (((RING_ENUM_CS31 - OUR_RING_ENUM - 1) + (RING_BUS_LENGTH*2)) % RING_BUS_LENGTH)
#define RING_ADDR_CS02 (((RING_ENUM_CS02 - OUR_RING_ENUM - 1) + (RING_BUS_LENGTH*2)) % RING_BUS_LENGTH)
#define RING_ADDR_CS12 (((RING_ENUM_CS12 - OUR_RING_ENUM - 1) + (RING_BUS_LENGTH*2)) % RING_BUS_LENGTH)
#define RING_ADDR_CS22 (((RING_ENUM_CS22 - OUR_RING_ENUM - 1) + (RING_BUS_LENGTH*2)) % RING_BUS_LENGTH)
#define RING_ADDR_CS32 (((RING_ENUM_CS32 - OUR_RING_ENUM - 1) + (RING_BUS_LENGTH*2)) % RING_BUS_LENGTH)




#define G2_RING_ADDR_PC   (((G2_RING_ENUM_PC   - OUR_RING_ENUM - 1) + (G2_RING_BUS_LENGTH*2)) % G2_RING_BUS_LENGTH)
#define G2_RING_ADDR_ETH  (((G2_RING_ENUM_ETH  - OUR_RING_ENUM - 1) + (G2_RING_BUS_LENGTH*2)) % G2_RING_BUS_LENGTH)
#define G2_RING_ADDR_CS20 (((G2_RING_ENUM_CS20 - OUR_RING_ENUM - 1) + (G2_RING_BUS_LENGTH*2)) % G2_RING_BUS_LENGTH)
#define G2_RING_ADDR_CS10 (((G2_RING_ENUM_CS10 - OUR_RING_ENUM - 1) + (G2_RING_BUS_LENGTH*2)) % G2_RING_BUS_LENGTH)
#define G2_RING_ADDR_CS00 (((G2_RING_ENUM_CS00 - OUR_RING_ENUM - 1) + (G2_RING_BUS_LENGTH*2)) % G2_RING_BUS_LENGTH)
#define G2_RING_ADDR_CS01 (((G2_RING_ENUM_CS01 - OUR_RING_ENUM - 1) + (G2_RING_BUS_LENGTH*2)) % G2_RING_BUS_LENGTH)
#define G2_RING_ADDR_CS11 (((G2_RING_ENUM_CS11 - OUR_RING_ENUM - 1) + (G2_RING_BUS_LENGTH*2)) % G2_RING_BUS_LENGTH)
#define G2_RING_ADDR_CS21 (((G2_RING_ENUM_CS21 - OUR_RING_ENUM - 1) + (G2_RING_BUS_LENGTH*2)) % G2_RING_BUS_LENGTH)
#define G2_RING_ADDR_CS31 (((G2_RING_ENUM_CS31 - OUR_RING_ENUM - 1) + (G2_RING_BUS_LENGTH*2)) % G2_RING_BUS_LENGTH)
#define G2_RING_ADDR_CS30 (((G2_RING_ENUM_CS30 - OUR_RING_ENUM - 1) + (G2_RING_BUS_LENGTH*2)) % G2_RING_BUS_LENGTH)





#ifndef VERILATE_TESTBENCH

#ifndef EXCLUDE_RINGBUS2_FUNCTIONS

// returns ttl that you can pass directly to your ringbus output
// make sure to pass an ENUM and not an ADDR
unsigned int ring_enum_to_addr(unsigned int partner_enum) {
    switch(partner_enum) {
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
            return 0; // not found means we just give a 0 for minimum damage
    }
}

#endif

#include "csr_control.h"

#if OUR_RING_ENUM != RING_ENUM_ETH

#ifndef EXCLUDE_RINGBUS2_FUNCTIONS

// will send a single ringbus message to eth, and block
// until it's done. warning calling this a lot will slow down your code
// even though this says eth, it will send a ringbus to the PC
void ring_block_send_eth(unsigned int data)
{
  unsigned int occupancy;

  while(1)
  {
   CSR_READ(RINGBUS_SCHEDULE_OCCUPANCY, occupancy);
   if(occupancy < RINGBUS_SCHEDULE_DEPTH)
   {
    break;
   }
  }

  CSR_WRITE(RINGBUS_WRITE_ADDR, RING_ADDR_PC);
  CSR_WRITE(RINGBUS_WRITE_DATA, data);
  CSR_WRITE_ZERO(RINGBUS_WRITE_EN);
}


// sends 2 messages, an upper/lower combination
// this is a "standard" way of sending a uint32_t to
// a specific ringbus target
void ring_block_send_eth_u32(const unsigned int rb_type, const unsigned int data) {
    ring_block_send_eth( rb_type | 0x00000 | (data & 0x0000ffff)  );
    ring_block_send_eth( rb_type | 0x10000 | (data>>16 & 0x0000ffff)  );
}

#endif



#else

/// ring_block_send_eth is not defined
/// this should throw a warning due to wrong number of arguments
// void ring_block_send_eth() {

// }

#endif


#endif



#endif

#ifdef RINGBUS2_FUNCTIONS_FOWARD_DECLARE
void ring_block_send_eth(unsigned int data);
unsigned int ring_enum_to_addr(unsigned int partner_enum);
void ring_block_send_eth_u32(const unsigned int rb_type, const unsigned int data);
#endif

#include "ringbus3.h"

