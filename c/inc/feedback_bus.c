#include "feedback_bus.h"
#include "ringbus.h"

//////////////////////////////////////////
//
// Shared Functions
//



// pass a cpu_pointer to a FILLED type which was declared
// in vmem
// OR in different destinations for 2nd argument
// we don't support ringbus to the PC through this method
void init_feedback_ringbus(
    feedback_frame_ringbus_filled_t *v,
    const unsigned int destinations) {
    v->type = FEEDBACK_TYPE_RINGBUS;
    v->destination0 = destinations;
    v->destination1 = FEEDBACK_DST_HIGGS;
}

void set_feedback_ringbus_size(
    feedback_frame_ringbus_filled_t *f,
    const unsigned int ring_count) {
    // length is never treated as less than 16, however we set it less
    // to signify the last valid word of packed_ring[]
    f->length = FRAME_PRIMITIVE_WORDS+(ring_count*2);
}

void fill_feedback_ringbus_1(
    feedback_frame_ringbus_filled_t *f,
    const unsigned int enum0,
    const unsigned int data0
    ) {
    f->packed_ring[0] = enum0;
    f->packed_ring[1] = data0;

    set_feedback_ringbus_size(f, 1);
}

void fill_feedback_ringbus_2(
    feedback_frame_ringbus_filled_t *f,
    const unsigned int enum0,
    const unsigned int data0,
    const unsigned int enum1,
    const unsigned int data1
    ) {
    f->packed_ring[0] = enum0;
    f->packed_ring[1] = data0;
    f->packed_ring[2] = enum1;
    f->packed_ring[3] = data1;

    set_feedback_ringbus_size(f, 2);
}

void fill_feedback_ringbus_3(
    feedback_frame_ringbus_filled_t *f,
    const unsigned int enum0,
    const unsigned int data0,
    const unsigned int enum1,
    const unsigned int data1,
    const unsigned int enum2,
    const unsigned int data2
    ) {
    f->packed_ring[0] = enum0;
    f->packed_ring[1] = data0;
    f->packed_ring[2] = enum1;
    f->packed_ring[3] = data1;
    f->packed_ring[4] = enum2;
    f->packed_ring[5] = data2;

    set_feedback_ringbus_size(f, 3);
}


// set deliver_higgs to true if the message should end up on higgs
// set to false for it to arrive to the PC
void init_feedback_stream(
    feedback_frame_stream_filled_t *v,
    const unsigned int destinations,
    const bool deliver_higgs,
    const bool deliver_pc,
    const unsigned int stype) {
    v->type = FEEDBACK_TYPE_STREAM;
    v->stype = stype;
    v->destination0 = destinations;

    v->destination1 = 0;
    if( deliver_higgs ) {
        v->destination1 = FEEDBACK_DST_HIGGS;
    }
    if( deliver_pc ) {
        v->destination1 = FEEDBACK_DST_PC;
    }
}

void set_feedback_stream_length(
    feedback_frame_stream_filled_t *v,
    const unsigned int length) {

    v->length = FEEDBACK_HEADER_WORDS + length;
}



void init_feedback_vector(
    feedback_frame_vector_filled_t *v,
    const unsigned int destinations,
    const bool deliver_higgs,
    const bool deliver_pc,
    const unsigned int vtype) {
    v->type = FEEDBACK_TYPE_VECTOR;
    v->vtype = vtype;
    v->destination0 = destinations;

    v->destination1 = 0;
    if( deliver_higgs ) {
        v->destination1 = FEEDBACK_DST_HIGGS;
    }
    if( deliver_pc ) {
        v->destination1 = FEEDBACK_DST_PC;
    }
}

void set_feedback_vector_length(
    feedback_frame_vector_filled_t *v,
    const unsigned int length) {

    v->length = FEEDBACK_HEADER_WORDS + length;
}





// returns true if the feedback type is valid
bool feedback_type_valid(const feedback_frame_t *v) {
    switch(v->type) {
        case FEEDBACK_TYPE_STREAM:
        case FEEDBACK_TYPE_VECTOR:
        case FEEDBACK_TYPE_RINGBUS:
        case FEEDBACK_TYPE_FLUSH:
            return true;
            break;
        default:
            return false;
            break;
    }
}

// how many bytes should we consume wrt this vector
// this is meant to be run by the pc while consuming a stream
// passing an invalid type will
// passing a feedback_frame that was type zero, will return 1 !!
// this is because the consumer should advance 1 word
// pass a *error which will be set if something looks wrong with the length
// the returned length will probably be invalid in the case that error is set
uint32_t feedback_word_length(const feedback_frame_t *v, bool *error) {
    *error = false;
    switch(v->type) {
        case FEEDBACK_TYPE_STREAM:
        case FEEDBACK_TYPE_VECTOR:
            if(v->length < FEEDBACK_HEADER_WORDS) {
                *error = true;
                return 1;
            }
            if(v->length > FEEDBACK_MAX_LENGTH) {
                *error = true;
                return 1;
            }
            return v->length;
            break;

        case FEEDBACK_TYPE_RINGBUS:
            if(v->length > FEEDBACK_HEADER_WORDS) {
                *error = true;
                return 1;
            }
            if(v->length < FRAME_PRIMITIVE_WORDS) {
                *error = true; // a length of 0,1,2,3 are illegal
                // techincally a rb could be empty but why?
                return 1;
            }
            // smaller values are OK and used to parse last useful byte of struct
            return FEEDBACK_HEADER_WORDS; // length for ringbus is ALWAYS 16
            break;
        case FEEDBACK_TYPE_FLUSH:
            // in the case of a flush, we return 1 to force caller
            // to check every byte 1 at a time
            return 1;
            break;
        default:
            // unknown type
            *error = true;
            return 1;

            break;
    }
}

/*
 * Convert a peer id, to a mask
 * WARNING this only supports the lower 31 peers, needs upgrade
 */
uint32_t feedback_peer_to_mask(const uint32_t peer_id) {
    return (0x1<<(peer_id+1));
}

#ifndef VERILATE_TESTBENCH

//////////////////////////////////////////
//
// Vex functions
//


#else

#include "cpp_utils.hpp"
#include <assert.h>

#include <iostream>     // std::cout, std::ios
#include <sstream> 
#include <cmath>

#include "ringbus.h"
#include "ringbus2_pre.h"
#include "tb_ringbus.hpp"

//////////////////////////////////////////
//
// TestBench / S-Modem functions
//


void print_feedback_ringbus(const feedback_frame_ringbus_t *v) {
    std::cout << "Type: Ringbus" << std::endl;
    unsigned num_ring = v->length - FRAME_PRIMITIVE_WORDS;
    std::cout << "Length: " << v->length << " (literal), ringbus packets: " << num_ring/2 << std::endl;

    if(num_ring > FEEDBACK_RINGBUS_PACKED) {
        std::cout << "ERROR: invalid length, too large" << std::endl;
        num_ring = 0; // this prevents infinite loop below
    }

    if((num_ring & 0x1) == 1) {
        std::cout << "ERROR: length cannot be odd for ringbus type" << std::endl;
    }

    for(unsigned int i = 0; i < num_ring; i+=2) {
        std::cout << "  Rb #" << i/2 << " enum:   " << lookup_ringbus_enum(v->packed_ring[i], true) << " (" << v->packed_ring[i] << ")" << std::endl;
        std::cout << "  Rb #" << i/2 << " data: 0x" << HEX32_STRING(v->packed_ring[i+1]) << std::endl;
    }
}


void print_feedback_stream(const feedback_frame_stream_t *v) {
    std::cout << "Type: Stream" << std::endl;
    std::cout << "Stream Tag: " << v->stype << std::endl;
    unsigned num_words = v->length - FEEDBACK_HEADER_WORDS;
    // std::cout << "Length: " << v->length << " " << std::endl;
    std::cout << "Length: " << num_words << " (words)" << std::endl;

    // pointer arithmetic
    const unsigned int* data = ((const unsigned int *)v)+FEEDBACK_HEADER_WORDS;

    if(num_words > FEEDBACK_BODY_WORDS) {
        std::cout << "ERROR: invalid length, too large" << std::endl;
    }

    if(num_words == 0) {
        std::cout << "WARNING: Zero length stream header" << std::endl;
    }

    std::cout << "Values: [";

    // how many words to preview for this type
    const unsigned int max_preview = 4;

    for(unsigned int i = 0; i < max_preview && i < num_words; i++) {
        std::cout << "0x" << HEX32_STRING(data[i]) << ", ";
    }

    std::cout << "... ]" << std::endl;;
}



void print_feedback_vector(const feedback_frame_vector_t *v) {
    std::cout << "Type: Vector" << std::endl;
    std::cout << "Vector Tag: " << v->vtype << std::endl;
    unsigned num_words = v->length - FEEDBACK_HEADER_WORDS;
    // std::cout << "Length: " << v->length << " " << std::endl;
    std::cout << "Length: " << num_words << " (words)" << std::endl;

    // pointer arithmetic
    const unsigned int* data = ((const unsigned int *)v)+FEEDBACK_HEADER_WORDS;

    if(num_words > FEEDBACK_BODY_WORDS) {
        std::cout << "ERROR: invalid length, too large" << std::endl;
    }

    if(num_words == 0) {
        std::cout << "WARNING: Zero length stream header" << std::endl;
    }

    std::cout << "Values: [";

    // how many words to preview for this type
    const unsigned int max_preview = 16;

    for(unsigned int i = 0; i < max_preview && i < num_words; i++) {
        std::cout << "0x" << HEX32_STRING(data[i]) << ", ";
    }

    std::cout << "... ]" << std::endl;;
}




void print_feedback_generic(const feedback_frame_t *v) {
    switch(v->type) {
        case FEEDBACK_TYPE_STREAM:
            print_feedback_stream((const feedback_frame_stream_t*)v);
            break;
        case FEEDBACK_TYPE_VECTOR:
            print_feedback_vector((const feedback_frame_vector_t*)v);
            break;
        case FEEDBACK_TYPE_RINGBUS:
            print_feedback_ringbus((const feedback_frame_ringbus_t*)v);
            break;
        case FEEDBACK_TYPE_FLUSH:
            // std::cout << "fixme(flush)";
            // no print
            break;
        default:
            std::cout << " Can't print unknown type " << v->type << std::endl;
            break;
    }
}

uint32_t feedback_hash(const feedback_frame_t *v, fb_hash_t cb) {

    unsigned num_words = std::max( v->length, (unsigned)FEEDBACK_HEADER_WORDS );

    if( num_words >= 1024*512 ) {
        std::cout << "Warning: feedback_hash() got very large " << num_words << " length\n";
        num_words = 1024;
    }

    const uint32_t* data = ((const uint32_t*)v);

    std::vector<uint32_t> a;
    a.assign(data, data+num_words);

    return cb(a);
}

// pass custom_size, we assume you know what you're doing
std::vector<uint32_t> feedback_vector_packet_mapmov(
    uint32_t vtype, // type or tag
    std::vector<uint32_t> data, 
    uint32_t custom_size,
    uint32_t d0, uint32_t d1 ) {

    if( data.size() > FEEDBACK_BODY_WORDS ) {
        // std::cout << "Data size was: " << data.size() << std::endl;
        // assert(0 && "data must be less than or equal to limit");
    }

    // size_t sz = sizeof(feedback_frame_ringbus_filled_t);
    
    uint32_t destination0 = d0; // unused for now
    uint32_t destination1 = d1;

    feedback_frame_vector_filled_t on_stack = {
        FEEDBACK_TYPE_VECTOR,
        custom_size,
        destination0,
        destination1,
        vtype,
        0, // seq
        0, // seq2
        0,
        0,
        {FEEDBACK_VECTOR_ZERO_LIST}};

    std::vector<uint32_t> out;

    uint32_t* memory_pointer = (uint32_t*)(&on_stack);
    for(uint32_t i = 0; i < sizeof(on_stack)/4; i++)
    {
        out.push_back(memory_pointer[i]);
        // cout << "pushing " << HEX32_STRING(memory_pointer[i]) << endl;
    }

    // push on payload
    uint32_t words_size = data.size();
    for(uint32_t i = 0; i < words_size; i++)
    {
        out.push_back(data[i]);
        // cout << "pushing " << HEX32_STRING(data[i]) << endl;
    }


    return out;
}

void set_mapmov_epoc_timeslot(std::vector<uint32_t>& rhs, const uint32_t epoc, const uint32_t timeslot ) {
    rhs[5] = (timeslot*SCHEDULE_LENGTH);
    rhs[6] = epoc;
}

void set_mapmov_epoc_frames(std::vector<uint32_t>& rhs, const uint32_t epoc, const uint32_t timeslot ) {
    rhs[5] = timeslot;
    rhs[6] = epoc;
}

// pass custom_size, we assume you know what you're doing
// I dislike the order of the function arguments
std::vector<uint32_t> feedback_vector_mapmov_scheduled(
    const uint32_t vtype, // type or tag
    const std::vector<uint32_t>& data, 
    const uint32_t custom_size,
    const uint32_t d0, const uint32_t d1,
    const uint32_t timeslot, const uint32_t epoc,
    const uint32_t constellation ) {

    // if( data.size() > FEEDBACK_BODY_WORDS ) {
    // std::cout << "Data size was: " << data.size() << std::endl;
    // }

    // size_t sz = sizeof(feedback_frame_ringbus_filled_t);
    
    uint32_t destination0 = d0; // unused for now
    uint32_t destination1 = d1;

    feedback_frame_vector_filled_t on_stack = {
        FEEDBACK_TYPE_VECTOR,
        custom_size,
        destination0,
        destination1,
        vtype,
        timeslot, // seq
        epoc, // seq2
        (uint32_t)data.size(),
        constellation,
        {FEEDBACK_VECTOR_ZERO_LIST}};

    std::vector<uint32_t> out;

    // speed up pushbacks
    out.reserve((sizeof(on_stack)/4) + data.size());

    uint32_t* memory_pointer = (uint32_t*)(&on_stack);
    for(uint32_t i = 0; i < sizeof(on_stack)/4; i++)
    {
        out.push_back(memory_pointer[i]);
        // cout << "pushing " << HEX32_STRING(memory_pointer[i]) << endl;
    }

    // push on payload
    uint32_t words_size = data.size();
    for(uint32_t i = 0; i < words_size; i++)
    {
        out.push_back(data[i]);
        // cout << "pushing " << HEX32_STRING(data[i]) << endl;
    }


    return out;
}

double feedback_bits_per_constellation(uint32_t constellation) {
    double bits_per_subcarrier = 0;
    switch(constellation) {
        default:
        case FEEDBACK_MAPMOV_QPSK:
            bits_per_subcarrier = 2;
            break;
        case FEEDBACK_MAPMOV_QAM8:
            bits_per_subcarrier = 3;
            break;
        case FEEDBACK_MAPMOV_QAM16:
            bits_per_subcarrier = 4;
            break;
        case FEEDBACK_MAPMOV_QAM32:
            bits_per_subcarrier = 5;
            break;
        case FEEDBACK_MAPMOV_QAM64:
            bits_per_subcarrier = 6;
            break;
        case FEEDBACK_MAPMOV_QAM128:
            bits_per_subcarrier = 7;
            break;
    }
    return bits_per_subcarrier;
}

/// timeslot version
/// This is the original version of this function
/// we keep this around but internally multiply by 512
/// to convert timeslots to frames
std::vector<uint32_t> feedback_vector_mapmov_scheduled_sized(
    const uint32_t vtype, // type or tag
    const std::vector<uint32_t>& data, 
    const uint32_t enabled_subcarriers,
    const uint32_t d0, const uint32_t d1,
    const uint32_t timeslot, const uint32_t epoc,
    const uint32_t constellation ) {

    return feedback_vector_mapmov_scheduled_sized_frames(
        vtype
        ,data
        ,enabled_subcarriers
        ,d0
        ,d1
        , (timeslot * SCHEDULE_LENGTH)
        ,epoc
        ,constellation
        );
}

/// frame version
/// This is actually the original function
/// however when we call it externally, we will pass a [0-25k] number
/// instead of [0-49]
std::vector<uint32_t> feedback_vector_mapmov_scheduled_sized_frames(
    const uint32_t vtype, // type or tag
    const std::vector<uint32_t>& data, 
    const uint32_t enabled_subcarriers,
    const uint32_t d0, const uint32_t d1,
    const uint32_t frame, const uint32_t epoc,
    const uint32_t constellation ) {

    const int header = FEEDBACK_HEADER_WORDS;
    const double bits_per_subcarrier = feedback_bits_per_constellation(constellation);
    
    const uint32_t custom_size = header +
        std::ceil(((double)data.size()*32.0/bits_per_subcarrier) / (double)enabled_subcarriers)*1024;


    return feedback_vector_mapmov_scheduled(
        vtype,
        data,
        custom_size,
        d0,
        d1,
        frame,
        epoc,
        constellation
        );
}


std::vector<uint32_t> feedback_vector_packet(
    const uint32_t vtype, // type or tag
    const std::vector<uint32_t> data, const uint32_t d0, const uint32_t d1 ) {

    uint32_t payload_sz = data.size();

    // size_t sz = sizeof(feedback_frame_ringbus_filled_t);
    
    uint32_t destination0 = d0; // unused for now
    uint32_t destination1 = d1;

    feedback_frame_vector_filled_t on_stack = {
        FEEDBACK_TYPE_VECTOR,
        FEEDBACK_HEADER_WORDS + payload_sz,
        destination0,
        destination1,
        vtype,
        0, // seq
        0, // seq2
        0,
        0,
        {FEEDBACK_VECTOR_ZERO_LIST}};

    std::vector<uint32_t> out;

    uint32_t* memory_pointer = (uint32_t*)(&on_stack);
    for(uint32_t i = 0; i < sizeof(on_stack)/4; i++)
    {
        out.push_back(memory_pointer[i]);
        // cout << "pushing " << HEX32_STRING(memory_pointer[i]) << endl;
    }

    // push on payload
    for(uint32_t i = 0; i < payload_sz; i++)
    {
        out.push_back(data[i]);
        // cout << "pushing " << HEX32_STRING(data[i]) << endl;
    }


    return out;
}

// this code is used in may tests.  I think that passing size of 0
// is illegal
std::vector<uint32_t> get_check_awake_packet(const unsigned size) {
    // dumb is here because we require size 1 due to a bug
    // default function argument is 1
    std::vector<uint32_t> dumb;
    dumb.resize(size);
    return feedback_vector_packet(
                FEEDBACK_VEC_STATUS_REPLY,
                dumb,
                FEEDBACK_PEER_8, FEEDBACK_DST_HIGGS);
}

std::vector<uint32_t> feedback_stream_packet(
    const uint32_t stype, // always pass zero for now
    const std::vector<uint32_t> data ) {

    if( data.size() > FEEDBACK_BODY_WORDS ) {
        assert(0 && "data must be less than or equal to limit");
    }

    uint32_t payload_sz = data.size();

    // size_t sz = sizeof(feedback_frame_ringbus_filled_t);
    
    uint32_t destination0 = 0; // unused for now
    uint32_t destination1 = 0;

    feedback_frame_stream_filled_t on_stack = {
        FEEDBACK_TYPE_STREAM,
        FEEDBACK_HEADER_WORDS + payload_sz,
        destination0,
        destination1,
        stype,
        0, // seq
        {FEEDBACK_STREAM_ZERO_LIST}};

    std::vector<uint32_t> out;

    uint32_t* memory_pointer = (uint32_t*)(&on_stack);
    for(uint32_t i = 0; i < sizeof(on_stack)/4; i++)
    {
        out.push_back(memory_pointer[i]);
        // cout << "pushing " << HEX32_STRING(memory_pointer[i]) << endl;
    }

    // push on payload
    for(uint32_t i = 0; i < payload_sz; i++)
    {
        out.push_back(data[i]);
        // cout << "pushing " << HEX32_STRING(data[i]) << endl;
    }


    return out;
}





// fixme add up to 5
std::vector<uint32_t> feedback_ringbus_packet(
    const uint32_t enum0,
    const uint32_t data0,
    const uint32_t enum1,
    const uint32_t data1,
    const uint32_t enum2,
    const uint32_t data2
    ) {

    uint32_t ringbus_packed = 3;
    if( enum2 == 0 && data2 == 0 ) {
        ringbus_packed--;
        if( enum1 == 0 && data1 == 0) {
            ringbus_packed--;
        }
    }


    // size_t sz = sizeof(feedback_frame_ringbus_filled_t);
    

    uint32_t destination0 = 0; // unused for now
    uint32_t destination1 = 0;

    feedback_frame_ringbus_filled_t on_stack = {
        FEEDBACK_TYPE_RINGBUS,
        FRAME_PRIMITIVE_WORDS+(ringbus_packed*2),
        destination0,
        destination1,
        {enum0,
        data0,
        enum1,
        data1,
        enum2,
        data2},
        {}
        };

    std::vector<uint32_t> out;

    uint32_t* memory_pointer = (uint32_t*)(&on_stack);
    for(uint32_t i = 0; i < sizeof(on_stack)/4; i++)
    {
        out.push_back(memory_pointer[i]);
        // cout << "pushing " << HEX32_STRING(memory_pointer[i]) << endl;
    }

    return out;
}


std::vector<uint32_t> feedback_flush_packet(
    const uint32_t zeros,
    const uint32_t other
    ) {

    std::vector<uint32_t> out;

    for(uint32_t i = 0; i < zeros; i++)
    {
        out.push_back(0);
    }

    return out;
}


std::vector<uint32_t> feedback_unjam_packet() {

    std::vector<uint32_t> out;

    out.push_back(FEEDBACK_TYPE_UNJAM);
    out.push_back(FEEDBACK_HEADER_WORDS*2);

    while(out.size() < FEEDBACK_HEADER_WORDS*2) {
        out.push_back(0);
    }

    return out;
}












#define _SCHEDULE_SLOTS (50)
#define _SCHEDULE_LENGTH (512)
#define _SCHEDULE_LENGTH_BITS (9)
#define _SCHEDULE_FRAMES ((_SCHEDULE_SLOTS)*(_SCHEDULE_LENGTH))

void printFillLevelReply(const uint32_t word, const int target) {
    uint32_t dmode =      (word & 0x00ff0000) >> 16;
    int32_t frame_delta =  word & 0x0000ffff;

    // do this to sign extend
    frame_delta <<= 16;
    frame_delta >>= 16;

    int epoc_delta = (int8_t)dmode;


    while(0 < epoc_delta) {
        frame_delta += _SCHEDULE_FRAMES;
        epoc_delta--;
    }

    std::cout << "epoc_delta represented as frames " << frame_delta << std::endl;

    // int target = 0; // this could be put somewhere else

    if( abs(frame_delta) > (_SCHEDULE_FRAMES*2) ) {
        std::cout << "epoc delta is WAY out of estimate" << std::endl;
    }

    
    // int target_error = frame_delta - target;
    int target_error = target - frame_delta;

    std::cout << "   target_error " << target_error << std::endl;

    if( abs(target_error) < 200 ) {
        std::cout << "   Skipping doesn't need update" << std::endl;
        return;
    }

    // if( allow_epoc_adjust ) {

    //     epoc_estimated = adjust_frames_to_schedule(epoc_estimated, target_error);
    // }
}
#undef _SCHEDULE_SLOTS
#undef _SCHEDULE_LENGTH
#undef _SCHEDULE_LENGTH_BITS
#undef _SCHEDULE_FRAMES


// std::string getErrorStringPadding() {

// }

std::string getErrorStringFeedbackBusParse(const uint32_t word, uint32_t* critical_error) {
    
    uint32_t funny_dmode =      (word & 0xffff00) >> 8;

    // mask we feed into the switch statement
    uint32_t switch_on = (word & 0xff0000ff);


    std::ostringstream os;

    os << "--------------------------------------------" << std::endl;

    os << " - ";

    uint32_t local_crit = 0;

    switch(switch_on) {
        case (TX_USERDATA_ERROR | 2):
            os << " Requested packet was in the past";
            break;
        case (TX_USERDATA_ERROR | 7):
            os << " Epoc was correct, but timeslot was in the past";
            break;
        case (TX_USERDATA_ERROR | 4):
            os << " Schedule timing was ok, but can_tx is false";
            break;
        case (TX_USERDATA_ERROR | 5):
            /// due to changing over to frame based scheduling
            /// cs11 can never send this error message now
            os << " fail, we got the packet in the right epoc second, but timeslot was too late; even if timeslot was correct, progress was not zero, so still fail";
            break;
        case (TX_USERDATA_ERROR | 6):
            os << " Packet came on time, but underflowed during transmission. We underflowed after sending: " << funny_dmode;
            break;
        case (TX_USERDATA_ERROR | 8):
            os << " user_data_callback() got called but cs20 cirbuf was full";
            break;
        case (TX_USERDATA_ERROR | 0xa):
            os << " Flushing with Zeros encountered";
            local_crit = 1;
            break;
        case (TX_USERDATA_ERROR | 0xb):
            os << " Flushing with Zeros finished after " << funny_dmode << " zeros";
            local_crit = 2;
            break;
        case (TX_USERDATA_ERROR | 0xc):
            os << " Ringbus fifo overflowed and dropped " << funny_dmode << " messages";
            break;
        case (TX_USERDATA_ERROR | 0xe): {
                std::string what;
                if( funny_dmode == 1) {
                    what = "too small";
                } else if( funny_dmode == 2 ) {
                    what = "too large, user data";
                } else if (funny_dmode == 3 ) {
                    what = "too large, vec or stream";
                } else {
                    what = "?????";
                }
                os << " Size error: length field " << what << " ";
                local_crit = 3;
            }
            break;
        case (TX_USERDATA_ERROR | 0x0f):
            os << " Illegal type upper 0x" << HEX32_STRING(funny_dmode<<16);
            break;
        case (TX_USERDATA_ERROR | 0x10):
            os << " Illegal type lower 0x" << HEX32_STRING(funny_dmode);
            local_crit = 3;
            break;
        case (TX_USERDATA_ERROR | 0x11):
            os << " CS20 did not handle Vector type upper 0x" << HEX32_STRING(funny_dmode<<16) << "";
            break;
        case (TX_USERDATA_ERROR | 0x12):
            os << " CS20 did not handle Vector type lower 0x" << HEX32_STRING(funny_dmode) << "";
            local_crit = 3;
            break;
        case (TX_USERDATA_ERROR | 0x13):
            os << " CS20 did not handle Stream type upper 0x" << HEX32_STRING(funny_dmode<<16) << "";
            break;
        case (TX_USERDATA_ERROR | 0x14):
            os << " CS20 did not handle Stream type lower 0x" << HEX32_STRING(funny_dmode) << "";
            local_crit = 3;
            break;
        case (TX_USERDATA_ERROR | 0x15):
            os << " CS20 fb_ring_queue->occupancy is illegal large 0x" << HEX32_STRING(funny_dmode<<16) << "";
            break;
        case (TX_USERDATA_ERROR | 0x16):
            os << " Readback upper 0x" << HEX32_STRING(funny_dmode<<16) << "";
            break;
        case (TX_USERDATA_ERROR | 0x17):
            os << " Readback lower 0x" << HEX32_STRING(funny_dmode) << "";
            break;

        default:
            os << "getErrorStringFeedbackBusParse() does not understand " << HEX32_STRING(word) << std::endl;
            break;
    }

    if( critical_error ) {
        *critical_error = local_crit;
    }


    os << std::endl << "--------------------------------------------" << std::endl;

    // os << "- ";
    // os << "dec: " << 15 << " hex: " << std::hex << 15 << std::endl;
    return  os.str();
}

// goes with functions from stack_test.c
// putting in this c file to make makefiles easier
std::string getErrorStringTestStack(const uint32_t word) {
    uint32_t dmode =      (word & 0xffff);
    uint32_t upper_dmode =      (word & 0xf00000) >> 20;

    // mask we feed into the switch statement
    // uint32_t switch_on = (word & 0xff0000ff);

    std::string fpga = "?";

    switch(upper_dmode) {
        case RING_ENUM_CS20:
            fpga = "cs20";
            break;
        default:
            break;
    }


    std::ostringstream os;

    os << "--------------------------------------------" << std::endl;

    os << " - ";

    os << " " + fpga + " Stack was as low as " << dmode*4 << " bytes";

    os << std::endl << "--------------------------------------------" << std::endl;
    return os.str();
}

/// takes a feedback_frame_vector_t pointer.  This pointer only points to 7 words
/// We convert this to a feedback_frame_vector_filled_t which points to 16 words
/// then this is converted to a vector and returned
/// WARNING: this class assumes that pointer points to 16 valid words!!
std::vector<uint32_t> feedback_frame_vec_to_vector(const feedback_frame_vector_t* const vec) {
    const uint32_t* aswords = reinterpret_cast<const uint32_t*>(vec);

    std::vector<uint32_t> words;

    words.assign(aswords, aswords + FEEDBACK_HEADER_WORDS);

    return words;
}

void feedback_update_length_field(std::vector<uint32_t>& rhs) {
    rhs[1] = rhs.size();
}



#endif