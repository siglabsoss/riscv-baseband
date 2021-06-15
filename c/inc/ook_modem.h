#ifndef __OOK_MODEM_H__
#define __OOK_MODEM_H__

#include <stdlib.h> // for abs()
#include <stdint.h>
#include <stdbool.h>
#include "fixed_iir.h"
#include "ook_types.h"
#include "random.h"



// in bits
#define OOK_HASH_LENGTH (8)

// in bits
#define OOK_FIXED_LENGTH (32 + 16 + OOK_HASH_LENGTH)
// in words, must be previous over 32
#define OOK_STORAGE (2)

#define OOK_HEADER_LENGTH (6)

// in bits, total length of ook message
#define OOK_TOTAL_LENGTH (OOK_FIXED_LENGTH + OOK_HEADER_LENGTH)

// in bits / frames
// assuming one bit per frame, how many delta frames did it take between
// transmission and detection.  used for adjusting counter offsets
#define OOK_DELTA_FRAMES (OOK_TOTAL_LENGTH-1)


// states for the FSM
#define OOK_STATE_IDLE (0)
#define OOK_PARTIAL_HEADER (1)
#define OOK_CONSIDER_HEADER (2)
#define OOK_UPDATE_FILTERS (3)
#define OOK_PARSE_BODY (4)
#define OOK_CHECK_HASH (5)

typedef struct OOKMessage {
    uint32_t data[OOK_STORAGE];
    uint32_t count;
    uint32_t symbol;
} OOKMessage;

typedef struct OOKDemod {
    uint32_t raw   [OOK_HEADER_LENGTH];
    bool     header[OOK_HEADER_LENGTH];
    uint32_t state;
    uint32_t h_count;
    int64_t  off_filter_state;
    int64_t  on_filter_state;
    int64_t  on_filter_state_saved;
    uint32_t filter_gain_off;
    uint32_t filter_gain_on;
} OOKDemod;

bool ook_sync[OOK_HEADER_LENGTH] = {true, false, false, true, true, false};

OOKMessage driver_packet; // single instance of message the driver uses

typedef void (*ook_got_message_t)(const OOKMessage* const);

ook_got_message_t ook_dispatch = 0; // pointer to user's callback


void ook_register_callback(ook_got_message_t ptr) {
    ook_dispatch = ptr;
}


void ook_prep_inbound(OOKMessage* const m) {
    for(int i = 0; i < OOK_STORAGE; i++) {
        m->data[i] = 0;
    }
    m->count = 0;
}

void ook_prep_outbound(OOKMessage* const m) {
    m->symbol = 0x00002001;
    ook_prep_inbound(m);
}

void ook_prep_outbound_gain(OOKMessage* const m, uint32_t g) {
    m->symbol = g;
    ook_prep_inbound(m);
}


void ook_prep_demod(OOKDemod* const d) {
    d->state = 0;
    for(int i = 0; i < OOK_HEADER_LENGTH; i++) {
        d->raw[i] = 0;
        d->header[i] = 0;
    }
    d->filter_gain_off = 65536 * (0.05f);       // Default of soft filter
    d->filter_gain_on  = 65536 * (0.11f);       // Default of soft filter

    d->off_filter_state = 0x40*0x40;
    d->on_filter_state  = 0x3c4*0x3c4;
    // d->on_filter_state  = 0x5b1*0x5b1;

    d->state = OOK_STATE_IDLE;
    d->h_count = 0;
    // d->b_count = 0;
}

/// converts a word to a bit using a location
bool load_bit(const uint32_t* const data, const uint32_t offset) {
    uint32_t word     = offset / 32;
    uint32_t bitshift = offset % 32;
    uint32_t load = (data[word] >> bitshift) & 0x1;
    return load;
}


// returns the hash of a message
// the hash is shifted to the correct location as it would be in the final message
uint32_t ook_get_hash(const OOKMessage* const m) {
    unsigned int copy[OOK_STORAGE];

    copy[0] = m->data[0];
    copy[1] = m->data[1] & 0xffff;

    uint32_t hash = xorshift32(0xfeadbeef, copy, 2);
    return (hash & 0xff) << 16;
}

// loads hash and zeros upper half of second word
void ook_load_hash(OOKMessage* const m) {
    uint32_t hash = ook_get_hash(m);
    m->data[1] = (m->data[1] & 0xffff) | hash;
    // _printf("h: %x\n", hash);
    // _printf("l: %x\n", m->data[1]);
}

/// returns true for hash ok
/// returns false for bad hash
bool ook_check_hash(const OOKMessage* const m) {
    uint32_t ota_hash = m->data[1] & 0xff0000;
    uint32_t expected_hash = ook_get_hash(m);
    return ota_hash == expected_hash;
}

/// strips hash from message
void ook_strip_hash(OOKMessage* const m) {
    m->data[1] = (m->data[1] & 0xffff);
}

void ook_modulate_next(OOKMessage* const m, uint32_t* output, bool* const done) {

    if( unlikely(m->count == 0) ) {
        ook_load_hash(m);
    }

    bool bit;
    if( m->count < OOK_HEADER_LENGTH ) {
        bit = ook_sync[m->count];
    } else {
        bit = load_bit(m->data, m->count - OOK_HEADER_LENGTH );
    }


    if( bit ) {
        *output = m->symbol;
    } else {
        *output = 0;
    }
    m->count++;

    if( m->count == OOK_TOTAL_LENGTH ) {
        *done = true;
    } else {
        *done = false;
    }
}

/// converts a location and bit into a word
/// data must be zerod out before using this as we only write one bits and skip writing zero
/// bits
void unload_bit(uint32_t* const data, const bool bit, const uint32_t offset) {
    if( unlikely(!bit) ) {
        return;
    }
    uint32_t word     = offset / 32;
    uint32_t bitshift = offset % 32;
    data[word] |= 0x1 << bitshift;
}

/// converts a location and bit into a word
/// only used for 1 bit, do not call for 0 bit
// void __attribute__((always_inline)) unload_one_bit(uint32_t* const data, const uint32_t offset) {
//     uint32_t word     = offset / 32;
//     uint32_t bitshift = offset % 32;
//     data[word] |= 0x1 << bitshift;
// }

uint32_t ook_mag2(const uint32_t channel_data) {
    int32_t re,im;

    re =  (int16_t)(channel_data & 0xffff);
    im =  (int16_t)((channel_data>>16) & 0xffff);

    const uint32_t mag_squared = (re*re)+(im*im);
    return mag_squared;
}

/// returns a bit from a word based on current state of filters
/// we classify based on minimum distance
/// the problem with this is that we are comparing distance of the mag squared value
/// this means that if our thresh are
///   12000^2        144000000
///   22000^2        676000000
///
/// Ideally we would want a value of 17001 to be detected as one and 16999 to be detected as zero
///   
///   16999^2        288966001
///   17001^2        289034001
/// But using our method they are both classified as zero due to the square bias
/// we could probably help fix this with a crude lookup table
bool ook_classify_bit(const OOKDemod* const modem, uint32_t mag) {
    uint32_t d_low  = abs(mag - modem->off_filter_state);
    uint32_t d_high = abs(mag - modem->on_filter_state);

    if( d_low < d_high ) {
        return false;
    } else {
        return true;
    }
}


void ook_save_one_filter(OOKDemod* const modem) {
    modem->on_filter_state_saved = modem->on_filter_state;
}

void ook_restore_one_filter(OOKDemod* const modem) {
    modem->on_filter_state = modem->on_filter_state_saved;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"

void __attribute__((always_inline)) ook_update_zero_filter(OOKDemod* const modem, const uint32_t mag) {
    i32_fixed_iir_16(&modem->off_filter_state, (int32_t)mag, modem->filter_gain_off);
}

void __attribute__((always_inline)) ook_update_one_filter(OOKDemod* const modem, const uint32_t mag) {
    i32_fixed_iir_16(&modem->on_filter_state, (int32_t)mag, modem->filter_gain_on);
}

void __attribute__((always_inline)) ook_enforce_filter_gap(OOKDemod* const modem, const uint32_t mag) {
    if( modem->off_filter_state >= modem->on_filter_state ) {

        uint32_t mag_plus = mag + 150;

        modem->on_filter_state = mag_plus*mag_plus;

#ifdef OOK_USE_DEBUG
        _printf("mag value %x triggered gap update\n", mag);
#endif
    }
}

#pragma GCC diagnostic pop

#define OOK_ONE  (1<<16)
#define OOK_ZERO (0)

/// Demodulates ook messages one subcarrier at a time
/// calls callback when successful message is sent
/// The demod object has a state variable which we use here
/// The state machine OR's the current demodulated bit onto the state
/// as to encode each state twice (current state with a zero and current state with a one)
void ook_demodulate(OOKDemod* const modem, uint32_t word) {

    uint32_t mag = ook_mag2(word);

    bool bit = ook_classify_bit(modem, mag);

    // SET_REG(x3, 0xffffffff);
    // SET_REG(x3, 0x0);
    // SET_REG(x3, modem->off_filter_state);
    // SET_REG(x3, 0x0);
    // SET_REG(x3, modem->off_filter_state);

#ifdef OOK_USE_DEBUG
    // _printf("----\n");

    // _printf("w: %x    %x\n", mag, modem->off_filter_state);
    _printf("m: %x    %x\n", word, mag);
    // _printf("w: %x\n", word);

    STALL(30);

    uint32_t a = modem->off_filter_state&0xffffffff;

    _printf("  %c    off:  %x\n", bit?'h':' ', a);
    STALL(10);
    a = modem->on_filter_state&0xffffffff;
    _printf("        on:  %x\n", a);
#endif

    bool match = true; // used inside fsm

    bool re_fsm;
    do {
        re_fsm = false; // should we re-renter the fsm?

        // create a combination of the current state and the current bit
        const uint32_t hybrid_state = modem->state | (((uint32_t)bit) << 16);

        switch(hybrid_state) {
            case OOK_STATE_IDLE | OOK_ZERO:
                ook_update_zero_filter(modem, mag);
                // ook_enforce_filter_gap(modem, mag);
                break;
            case OOK_STATE_IDLE | OOK_ONE:
                modem->raw   [0] = mag;
                modem->header[0] = bit;

                modem->h_count = 1;
                modem->state = OOK_PARTIAL_HEADER;
                break;

            case OOK_PARTIAL_HEADER | OOK_ZERO:
            case OOK_PARTIAL_HEADER | OOK_ONE:
                modem->raw   [modem->h_count] = mag;
                modem->header[modem->h_count] = bit;
                
                modem->h_count++;

                if( unlikely(modem->h_count >= OOK_HEADER_LENGTH) ) {
                    modem->state = OOK_CONSIDER_HEADER;
                    re_fsm = true;
                }

                break;

            case OOK_CONSIDER_HEADER | OOK_ZERO:
            case OOK_CONSIDER_HEADER | OOK_ONE:
#ifdef OOK_USE_DEBUG
                _printf("header\n");
#endif
                for(int i = 0; i < OOK_HEADER_LENGTH; i++) {
                    if( modem->header[i] != ook_sync[i] ) {
                        match = false;
                        break;
                    }
                }
                if( match ) {
#ifdef OOK_USE_DEBUG
                    _printf("match\n");
#endif
                    modem->state = OOK_UPDATE_FILTERS;
                    re_fsm = true;
                } else {
#ifdef OOK_USE_DEBUG
                    _printf("no match\n");
#endif
                    modem->state = OOK_STATE_IDLE;
                }
                break;

            case OOK_UPDATE_FILTERS | OOK_ZERO:
            case OOK_UPDATE_FILTERS | OOK_ONE:
                ook_save_one_filter(modem);
                for(int i = 0; i < OOK_HEADER_LENGTH; i++) {
                    if( ook_sync[i] ) {
                        ook_update_one_filter(modem, modem->raw[i]);
                    }
                }
                modem->state = OOK_PARSE_BODY;
                ook_prep_inbound(&driver_packet); // resets count to 0
                break;

            case OOK_PARSE_BODY | OOK_ONE:
                unload_bit(driver_packet.data, bit, driver_packet.count);
                __attribute__ ((fallthrough));
            case OOK_PARSE_BODY | OOK_ZERO:
                // _printf("p                     %d %d\n", driver_packet.count, (int)bit);
                driver_packet.count++;
                if( unlikely(driver_packet.count >= OOK_FIXED_LENGTH) ) {
                    modem->state = OOK_CHECK_HASH;
                    re_fsm = true;
                    // modem->state = OOK_STATE_IDLE;
                }
                break;

            case OOK_CHECK_HASH | OOK_ZERO:
            case OOK_CHECK_HASH | OOK_ONE:

                if( ook_check_hash(&driver_packet) ) {
#ifdef OOK_USE_DEBUG
                    _puts("hash ok");
#endif
                    ook_strip_hash(&driver_packet);
                    if( ook_dispatch ) {
                        ook_dispatch(&driver_packet);
                        // _printf("go\n");
                    } else {
                        // _printf("no go\n");
                    }

                } else {
                    // in the event that the hash failed
                    // we would like to "undo" any learning the filter has done from this packet
                    // the only filter that updates during the body of the packet is the ones filter
                    // so we restore the state
                    ook_restore_one_filter(modem);
#ifdef OOK_USE_DEBUG
                    _puts("hash failed");
#endif
                }
                modem->state = OOK_STATE_IDLE;

                break;


            default:
#ifdef OOK_USE_DEBUG
                _printf("illegal state %x\n", hybrid_state);
#endif
                modem->state = OOK_STATE_IDLE;
                break;
        }
    } while( re_fsm );


}

#undef OOK_ONE
#undef OOK_ZERO 


#endif
