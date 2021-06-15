#ifndef __FEEDBACK_BUS_H__
#define __FEEDBACK_BUS_H__


#include <stdint.h>
#include <stdbool.h>
#include "feedback_bus_types.h"
#include "schedule.h"


#ifndef NSLICES
#define NSLICES (16)
#endif


// bitfields for peers
// first bit is always "self" (aka the attached higgs)
// so this word has 31 addressable peers, not 32
#define FEEDBACK_PEER_SELF (0x1<<0)
#define FEEDBACK_PEER_0  (0x1<<1)
#define FEEDBACK_PEER_1  (0x1<<2)
#define FEEDBACK_PEER_2  (0x1<<3)
#define FEEDBACK_PEER_3  (0x1<<4)
#define FEEDBACK_PEER_4  (0x1<<5)
#define FEEDBACK_PEER_5  (0x1<<6)
#define FEEDBACK_PEER_6  (0x1<<7)
#define FEEDBACK_PEER_7  (0x1<<8)
#define FEEDBACK_PEER_8  (0x1<<9)
#define FEEDBACK_PEER_9  (0x1<<10)
#define FEEDBACK_PEER_10  (0x1<<11)
#define FEEDBACK_PEER_11  (0x1<<12)
#define FEEDBACK_PEER_12  (0x1<<13)
#define FEEDBACK_PEER_13  (0x1<<14)
#define FEEDBACK_PEER_14  (0x1<<15)
#define FEEDBACK_PEER_15  (0x1<<16)
#define FEEDBACK_PEER_16  (0x1<<17)
#define FEEDBACK_PEER_17  (0x1<<18)
#define FEEDBACK_PEER_18  (0x1<<19)
#define FEEDBACK_PEER_19  (0x1<<20)
#define FEEDBACK_PEER_20  (0x1<<21)
#define FEEDBACK_PEER_21  (0x1<<22)
#define FEEDBACK_PEER_22  (0x1<<23)
#define FEEDBACK_PEER_23  (0x1<<24)
#define FEEDBACK_PEER_24  (0x1<<25)
#define FEEDBACK_PEER_25  (0x1<<26)
#define FEEDBACK_PEER_26  (0x1<<27)
#define FEEDBACK_PEER_27  (0x1<<28)
#define FEEDBACK_PEER_28  (0x1<<29)

// fixme, add peers 31-61

// all peers, but not us
#define FEEDBACK_PEER_ALL (FEEDBACK_PEER_0 | FEEDBACK_PEER_1 | FEEDBACK_PEER_2 | FEEDBACK_PEER_3 | FEEDBACK_PEER_4 | FEEDBACK_PEER_5 | FEEDBACK_PEER_6 | FEEDBACK_PEER_7 | FEEDBACK_PEER_8 | FEEDBACK_PEER_9 | FEEDBACK_PEER_10| FEEDBACK_PEER_11| FEEDBACK_PEER_12| FEEDBACK_PEER_13| FEEDBACK_PEER_14| FEEDBACK_PEER_15| FEEDBACK_PEER_16| FEEDBACK_PEER_17| FEEDBACK_PEER_18| FEEDBACK_PEER_19| FEEDBACK_PEER_20| FEEDBACK_PEER_21| FEEDBACK_PEER_22| FEEDBACK_PEER_23| FEEDBACK_PEER_24| FEEDBACK_PEER_25| FEEDBACK_PEER_26| FEEDBACK_PEER_27| FEEDBACK_PEER_28)

// part of dst 2, these flags grow from MSB
#define FEEDBACK_DST_PC      (0x1<<30)
#define FEEDBACK_DST_HIGGS   (0x1<<31)




#define FEEDBACK_HEADER_WORDS (16)
#define FEEDBACK_BODY_WORDS   (1024)  // worst case
#define FEEDBACK_MAX_LENGTH   (FEEDBACK_BODY_WORDS+FEEDBACK_HEADER_WORDS) // longest length possible for a single message
// just a guess, this is not a hard number,
// just a heuristic to detect bad headers.  if you are hitting this feel free to change
// 20000 words results in size 0x271000
#define FEEDBACK_MAPMOV_MAX_LENGTH (0x9c40000)

// how manu words deep into the stack can we find the type member"
#define FEEDBACK_WORD_OFFSET (0)
#define FEEDBACK_VECTOR_VTYPE_OFFSET (4)


#define FRAME_PRIMITIVE_WORDS (4)
#define FRAME_PRIMITIVE \
    unsigned int type; \
    unsigned int length; /* in words, length of entire frame*/ \
                         /* if less than 16, interpreted as min*/ \
                         /* of 16,  but small value may hold other info */ \
                                                                            \
    unsigned int destination0; /* 32 bit bit vector of destination addresses*/ \
    unsigned int destination1; /* 32 bit vector of destination flags */


/////////////////////
//
//  Make a new struct with:
//
//      typedef struct {
//
//  Choose first-most member variables with one of
//
//      FRAME_PRIMITIVE
//
//      } feedback_frame_YOURTYPE_t;
//
//  Copy and paste to make a second version with _filled_
//  calculate how many bytes are left to round out to 16
//
//      unsigned int filler[NSLICES-FRAME_PRIMITIVE_DST_WORDS - N ]
//  
//   where FRAME_PRIMITIVE_DST_WORDS matches what you chose above
//   and N is a literal which is the number of bytes you added
//
//  Note: the reason we have the filled types, is so that
//  riscv can allocate vmem using filled types to ensure the header is always
//  16 long.  The non filled types can be used by parsers and others to avoid
//  carrying around the extra bytes on the tail

typedef struct {
    FRAME_PRIMITIVE
} feedback_frame_t;

// typedef struct {
//     FRAME_PRIMITIVE
//     unsigned int filler[NSLICES-FRAME_PRIMITIVE_WORDS];
// } feedback_frame_filled_t;

// how many zeros does the filler[] member have?
#define FEEDBACK_VECTOR_ZERO_COUNT (NSLICES-FRAME_PRIMITIVE_WORDS-5)
// literal zeros with commas, used inside {} as an initializer list
#define FEEDBACK_VECTOR_ZERO_LIST  0,0,0,0,0,0,0


typedef struct {
    FRAME_PRIMITIVE
    unsigned int vtype; // vector type, can be arbitrary
    unsigned int seq;   // sequence number
    unsigned int seq2;
} feedback_frame_vector_t;

typedef struct {
    FRAME_PRIMITIVE
    unsigned int vtype; // vector type, can be arbitrary, this is like a sub address.  the destination decides which PC/grav this ends up on, but this can decide which FPGA it goes to
    unsigned int seq;
    unsigned int seq2;
    unsigned int input_packet_size;
    unsigned int constellation;
    unsigned int filler[FEEDBACK_VECTOR_ZERO_COUNT];
} feedback_frame_vector_filled_t;


#define FEEDBACK_STREAM_ZERO_COUNT (NSLICES-FRAME_PRIMITIVE_WORDS-2)
#define FEEDBACK_STREAM_ZERO_LIST  0,0,0,0,0,0,0,0,0,0

// streaming data
// it's assumed that the streaming data starts at the next 16
// Warning, if you edit this, and it is different than vector_t, 
typedef struct {
    FRAME_PRIMITIVE
    unsigned int stype; // stream type, probably will ignore for now
    unsigned int seq;   // sequence number
    // fixme: add modulation index and or subcarrer index
} feedback_frame_stream_t;

typedef struct {
    FRAME_PRIMITIVE
    unsigned int stype; // stream type, probably will ignore for now
    unsigned int seq;
    unsigned int filler[FEEDBACK_STREAM_ZERO_COUNT];
} feedback_frame_stream_filled_t;





// supports sending up to 6 ringbus messages at once
#define FEEDBACK_RINGBUS_PACKED (6)
typedef struct {
    FRAME_PRIMITIVE
    unsigned int packed_ring[(FEEDBACK_RINGBUS_PACKED*2)];
} feedback_frame_ringbus_t;

typedef struct {
    FRAME_PRIMITIVE
    unsigned int packed_ring[(FEEDBACK_RINGBUS_PACKED*2)];
    unsigned int filler[NSLICES-FRAME_PRIMITIVE_WORDS-(FEEDBACK_RINGBUS_PACKED*2)]; // size 16 -3 -12 = 1
} feedback_frame_ringbus_filled_t;








//////////////////////////////////////////
//
// Shared Functions
//

void init_feedback_ringbus(feedback_frame_ringbus_filled_t *v, const unsigned int destinations);
void set_feedback_ringbus_size( feedback_frame_ringbus_filled_t *f, const unsigned int ring_count);
void fill_feedback_ringbus_1( feedback_frame_ringbus_filled_t *f, const unsigned int enum0, const unsigned int data0 );
void fill_feedback_ringbus_2( feedback_frame_ringbus_filled_t *f, const unsigned int enum0, const unsigned int data0, const unsigned int enum1, const unsigned int data1 );
void fill_feedback_ringbus_3( feedback_frame_ringbus_filled_t *f, const unsigned int enum0, const unsigned int data0, const unsigned int enum1, const unsigned int data1, const unsigned int enum2, const unsigned int data2 );
bool feedback_type_valid(const feedback_frame_t *v);


void init_feedback_stream(feedback_frame_stream_filled_t *v, const unsigned int destinations, const bool deliver_higgs, const bool deliver_pc, const unsigned int stype);
void set_feedback_stream_length(feedback_frame_stream_filled_t *v, const unsigned int length);

void init_feedback_vector(feedback_frame_vector_filled_t *v, const unsigned int destinations, const bool deliver_higgs, const bool deliver_pc, const unsigned int vtype);
void set_feedback_vector_length(feedback_frame_vector_filled_t *v, const unsigned int length);
uint32_t feedback_peer_to_mask(const uint32_t peer_id);

#ifndef VERILATE_TESTBENCH


//////////////////////////////////////////
//
// Vex functions
//


#else

#include <string.h>
#include <iostream>
#include <vector>

//////////////////////////////////////////
//
// TestBench / S-Modem functions
//

typedef uint32_t (*fb_hash_t)(const std::vector<uint32_t>&);

// hacked forwared declare (This is in higgs_helper.hpp)
std::string lookup_ringbus_enum( unsigned int v, bool upper);

void print_feedback_ringbus(const feedback_frame_ringbus_t *v);
void print_feedback_generic(const feedback_frame_t *v);

void set_mapmov_epoc_timeslot(std::vector<uint32_t>& rhs, const epoc_timeslot_t& a );
void set_mapmov_epoc_timeslot(std::vector<uint32_t>& rhs, const uint32_t epoc, const uint32_t timeslot );
void set_mapmov_epoc_frames(std::vector<uint32_t>& rhs, const uint32_t epoc, const uint32_t timeslot );
void set_mapmov_lifetime_32(std::vector<uint32_t>& rhs, const uint32_t lifetime_32);

void feedback_update_length_field(std::vector<uint32_t>& rhs);

double feedback_bits_per_constellation(uint32_t constellation);
std::vector<uint32_t> feedback_vector_packet_mapmov( uint32_t vtype, std::vector<uint32_t> data, uint32_t custom_size, uint32_t d0 = 0, uint32_t d1 = 0);
std::vector<uint32_t> feedback_vector_mapmov_scheduled( const uint32_t vtype, const std::vector<uint32_t>& data, const uint32_t custom_size, const uint32_t d0, const uint32_t d1, const uint32_t timeslot, const uint32_t epoc, const uint32_t constellation = FEEDBACK_MAPMOV_QPSK );
std::vector<uint32_t> feedback_vector_mapmov_scheduled_sized( const uint32_t vtype, const std::vector<uint32_t>& data, const uint32_t enabled_subcarriers, const uint32_t d0, const uint32_t d1, const uint32_t timeslot, const uint32_t epoc, const uint32_t constellation = FEEDBACK_MAPMOV_QPSK );
std::vector<uint32_t> feedback_vector_mapmov_scheduled_sized_frames( const uint32_t vtype, const std::vector<uint32_t>& data, const uint32_t enabled_subcarriers, const uint32_t d0, const uint32_t d1, const uint32_t frame, const uint32_t epoc, const uint32_t constellation = FEEDBACK_MAPMOV_QPSK );
std::vector<uint32_t> feedback_vector_packet( const uint32_t vtype, const std::vector<uint32_t> data, const uint32_t d0 = 0, const uint32_t d1 = 0 );
std::vector<uint32_t> feedback_stream_packet( const uint32_t stype, const std::vector<uint32_t> data );
std::vector<uint32_t> feedback_unjam_packet();
std::vector<uint32_t> feedback_ringbus_packet(
    const uint32_t enum0,
    const uint32_t data0,
    const uint32_t enum1 = 0,
    const uint32_t data1 = 0,
    const uint32_t enum2 = 0,
    const uint32_t data2 = 0
    );
void printFillLevelReply(const uint32_t word, const int target);

std::string getErrorStringFeedbackBusParse(const uint32_t word, uint32_t* critical_error = 0);
uint32_t getErrorFeedbackBusParseCritical(const uint32_t word);
std::string getErrorStringTestStack(const uint32_t word);

std::vector<uint32_t> feedback_flush_packet(const uint32_t zeros, const uint32_t other = 3);

std::vector<uint32_t> feedback_frame_vec_to_vector(const feedback_frame_vector_t* const vec);

#define SUGGESTED_FEEDBACKBUS_FLUSH_TAIL() feedback_ringbus_packet(RING_ENUM_CS10, DO_NOTHING_CMD)

std::vector<uint32_t> get_check_awake_packet(const unsigned size = 1);

uint32_t feedback_hash(const feedback_frame_t *v, fb_hash_t cb );

uint32_t feedback_word_length(const feedback_frame_t *v, bool* const error, const uint32_t enabled_subcarriers = 0, const uint32_t constellation = 0, bool* const was_ud = 0);

uint32_t feedback_mapmov_reverse_size(
    const uint32_t custom_size,
    const uint32_t enabled_subcarriers,
    const uint32_t constellation);

#endif
#endif