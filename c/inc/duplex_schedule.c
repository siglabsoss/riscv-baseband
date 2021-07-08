#include "duplex_schedule.h"
#include "sig_utils.h"

#ifdef VERILATE_TESTBENCH
#define __RISCV_INLINE
#else
#define __RISCV_INLINE __attribute__((always_inline))
#endif




// row offsets, start and end for each part of the partial pilots
// format is [start, length]
const unsigned duplex_partial_pilot[20] = {
0 , 4,
4 , 4,
8 , 4,
12, 4,
16, 4,

44, 4,
48, 4,
52, 4,
56, 4,
60, 4
};

const unsigned duplex_partial_pilot_rx[20] = {
961, 63,
897, 64,
833, 64,
769, 64,
705, 64,

257, 64,
193, 64,
129, 64,
65 , 64,
1  , 64
};




// cs11 uses this to determine which phase of feedback we are getting
int32_t duplex_ul_feedback_phase(const uint32_t i) {
    switch(i) {
        case DUPLEX_ULFB_START:
        case DUPLEX_ULFB_START+1:
        case DUPLEX_ULFB_START+2:
        case DUPLEX_ULFB_START+3:
            return i-DUPLEX_ULFB_START;
            break;
        default:
            return -1;
            break;
    }
}

// cs11 uses this to determine which phase of P
int32_t duplex_ul_pilot_phase(const uint32_t i) {
    switch(i) {
        case DUPLEX_B0:
        case DUPLEX_B0+1:
            return i-DUPLEX_B0;
            break;
        default:
            return -1;
            break;
    }
}

// cs11 uses this to determine which phase of p
int32_t duplex_dl_pilot_phase(const uint32_t i) {
    switch(i) {
        case 0:
        case 1:
        case 2:
        case 3:
            return i;
            break;
        default:
            return -1;
            break;
    }
}

// cs31 uses this to determine which phase of i
int32_t duplex_dl_beam_pilot_phase(const uint32_t i) {
    switch(i) {
        case 0:
        case 1:
        case 2:
        case 3:
            return i;
            break;
        default:
            return -1;
            break;
    }
}



// cs11 uses this to determine which phase of p
// only responds for our slot
int32_t duplex_dp_pilot_phase_individual(const duplex_timeslot_t* const dts, const uint32_t i) {
    if( dts->role == DUPLEX_ROLE_TX_0 && (i == 0) ) {
        return 0;
    }
    if( dts->role == DUPLEX_ROLE_TX_1 && (i == 1) ) {
        return 1;
    }
    if( dts->role == DUPLEX_ROLE_TX_2 && (i == 2) ) {
        return 2;
    }
    if( dts->role == DUPLEX_ROLE_TX_3 && (i == 3) ) {
        return 3;
    }
    return -1;
}



// which transmitter is sending downlink "p" frame?
// -1 means no transmitter is sending "p"
int32_t duplex_dl_pilot_transmitter(const uint32_t i) {
    switch(i) {
        case 0:
        case 1:
        case 2:
        case 3:
            return i;
            break;
        default:
            return -1;
            break;
    }
}


// #define DUPLEX_PRINT

#ifdef DUPLEX_PRINT
#include <stdio.h>
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"

// returns true if did expensive run
///
/// @param dts pointer to duplex struct
/// @param lifetime
///
/// This calculates a modulous.  since this is very expensive to do on riscv
/// we cache the results.  we expect that this function will get called with 
/// lifetime incrementing by 1 each call.  The mod goes into lt_phase
///
/// we check the lt_target_valid. if false we are forced to do the expensive mod
/// Once we run it, we calculate lt_target as well, which is the next value of lifetime
/// which will result in an increment to lt_phase, and a re-calculation of lt_target
///
__RISCV_INLINE bool duplex_calculate_phase(duplex_timeslot_t* const dts, const uint32_t lifetime) {

    if( unlikely(lifetime == 0) ) {
        dts->lt_target_valid = false;
    }

    // we think we have a valid cached value for the expensive mod
    if( likely(dts->lt_target_valid) ) {

#ifdef DUPLEX_PRINT
        printf("valid ");
        printf("%x %x %x %x ",
                        lifetime,
                        dts->lt_target,
                        (lifetime - dts->lt_target),
                        (dts->lt_target - lifetime)
        );
#endif
        if( unlikely((dts->lifetime_p+1) != lifetime) ) {
            dts->lt_target_valid = false;
        } else if( unlikely(lifetime == dts->lt_target) ) {
        // if we are matching the cached value
            // printf(" match ");
            // bump the cache
            dts->lt_target += DUPLEX_FRAMES;
            // bump the phase
            dts->lt_phase++;
            
            // handle phase wrap
            if( unlikely(dts->lt_phase == dts->lt_period) ) {
                dts->lt_phase = 0;
            } else if ( unlikely(dts->lt_phase >= dts->lt_period) ) {
                // should be impossible, something is wrong
                dts->lt_target_valid = false;
            }
        }
    }
    
    // we need to do an expensive mod
    if( unlikely(!dts->lt_target_valid) ) {
        
        // frames over 128
        uint32_t life_over_128 = (lifetime / DUPLEX_FRAMES);
        
        // this number mod 5 is our phase
        // this is the expensive part
        dts->lt_phase = life_over_128 % dts->lt_period;
        
        // cache the target as the result of the mod
        dts->lt_target = (life_over_128 + 1) * DUPLEX_FRAMES;
        
        dts->lt_target_valid = true;

#ifdef DUPLEX_PRINT
        printf("recalc %x %x %x %x\n", lifetime, life_over_128, dts->lt_phase, dts->lt_target);
#endif

        dts->lifetime_p = lifetime;
        return true;
    }

    dts->lifetime_p = lifetime;
    return false;
}
#pragma GCC diagnostic pop

uint32_t get_duplex_mode(duplex_timeslot_t* const dts, const uint32_t i, const uint32_t lifetime) {

    duplex_calculate_phase(dts, lifetime);

    if( dts->role == DUPLEX_ROLE_RX ) {
        if( i >= DUPLEX_B0 && i < (DUPLEX_B0+2) ) {
            return DUPLEX_SEND_UL_PILOT;
        }
        if(  i == (DUPLEX_B0+2) ) {
            return DUPLEX_SEND_UL_FINESYNC;
        }
        
        if ( i >= (DUPLEX_ULFB_START) && i < (DUPLEX_ULFB_START+1) ) {
            return DUPLEX_SEND_UL_FEEDBACK_0;
        }
        if ( i >= (DUPLEX_ULFB_START+1) && i < (DUPLEX_ULFB_START+2) ) {
            return DUPLEX_SEND_UL_FEEDBACK_1;
        }
        if ( i >= (DUPLEX_ULFB_START+2) && i < (DUPLEX_ULFB_START+3) ) {
            return DUPLEX_SEND_UL_FEEDBACK_2;
        }
        if ( i >= (DUPLEX_ULFB_START+3) && i < (DUPLEX_ULFB_START+4) ) {
            return DUPLEX_SEND_UL_FEEDBACK_3;
        }
        
        if( i >= (DUPLEX_B0+2) && i < DUPLEX_B1 ) {
            return DUPLEX_SEND_UL_DATA;
        }
        
        return DUPLEX_SEND_ZERO;
    }
    
    if( i < DUPLEX_B0 ) {
        if( dts->role == DUPLEX_ROLE_TX_0 && (i == 0) ) {
            return DUPLEX_SEND_DL_PILOT_0;
        }
        if( dts->role == DUPLEX_ROLE_TX_1 && (i == 1) ) {
            return DUPLEX_SEND_DL_PILOT_1;
        }
        if( dts->role == DUPLEX_ROLE_TX_2 && (i == 2) ) {
            return DUPLEX_SEND_DL_PILOT_2;
        }
        if( dts->role == DUPLEX_ROLE_TX_3 && (i == 3) ) {
            return DUPLEX_SEND_DL_PILOT_3;
        }

        return DUPLEX_SEND_ZERO;
    } else {
        if( (i >= DUPLEX_B1) && (i < (DUPLEX_B1+2))) {
            return DUPLEX_SEND_DL_BEAM_PILOT;
        }

        if( i >= DUPLEX_B1 ) {
            return DUPLEX_SEND_DL_DATA;
        }

    }
    
    return DUPLEX_SEND_ZERO;
}

// rx chain uses this to determine if we should directly forward the data through
bool duplex_should_forward_eq_data(
    const duplex_timeslot_t* const dts,
    const uint32_t i,
    const uint32_t cooked_data_type ) {

    // we are the receiver
    // the transmitter is sending pilots to us in the first 2 slots
    if(    (cooked_data_type == 2)
        && (dts->role == DUPLEX_ROLE_RX)
        && (i < 4)
        ) {
        return true;
    }

    // we are the transmitter
    // the receiver is sending us corrections
    if( (cooked_data_type == 2) ) {
        if( (dts->role == DUPLEX_ROLE_TX_0 ) && (i == (DUPLEX_ULFB_START+0) ) ) {
            return true;
        }
        if( (dts->role == DUPLEX_ROLE_TX_1 ) && (i == (DUPLEX_ULFB_START+1) ) ) {
            return true;
        }
        if( (dts->role == DUPLEX_ROLE_TX_2 ) && (i == (DUPLEX_ULFB_START+2) ) ) {
            return true;
        }
        if( (dts->role == DUPLEX_ROLE_TX_3 ) && (i == (DUPLEX_ULFB_START+3) ) ) {
            return true;
        }
    }


    return false;
}

// rx chain uses this to determine if we should directly forward the data through
bool duplex_do_not_rotate(
    const duplex_timeslot_t* const dts,
    const uint32_t i,
    const uint32_t cooked_data_type,
    const uint32_t extra) {

    (void)dts;

    // we are the receiver
    // the transmitter is sending pilots to us in the first 2 slots
    if(    (cooked_data_type == 2)
        //&& (dts->role == DUPLEX_ROLE_RX)
        && ((i < 4 || i >= DUPLEX_B1 ) || ( extra && ( i >= (DUPLEX_ULFB_START) && i <= (DUPLEX_ULFB_END) )) )
        ) {
        return true;
    }

    // we are the transmitter
    // the receiver is sending us corrections
    // if(    (cooked_data_type == 2)
    //     && (dts->role != DUPLEX_ROLE_RX)
    //     && (i == DUPLEX_ULFB_START || i == DUPLEX_ULFB_END)
    //     ) {
    //     return true;
    // }


    return false;
}

// does not need a duplex_timeslot_t
// pass progress and tag
// returns true if the progress is in the tag region
bool duplex_tag_section(
    const uint32_t i,
    const uint32_t tag) {
        switch(tag) {
            case 1:
                if(i == 0) {
                    return true;
                }
                break;
            case 2:
                if(i == 1) {
                    return true;
                }
                break;
            case 3:
                if(i == 2) {
                    return true;
                }
                break;
            case 4:
                if(i == 3) {
                    return true;
                }
                break;
            case 5:
                if(i < DUPLEX_B0) {
                    return true;
                }
                break;
            case 6:
                if ( i == (DUPLEX_B0) ) {
                    return true;
                }
                break;
            case 7:
                if ( i == (DUPLEX_B0+1) ) {
                    return true;
                }
                break;
            case 8:
                if ( i == (DUPLEX_B0+2) ) {
                    return true;
                }
                break;
            case 9:
                if(i >= DUPLEX_B0 && i < (DUPLEX_B0+2)) {
                    return true;
                }
                break;
            case 10:
                if(i >= DUPLEX_B0 && i < (DUPLEX_B0+3)) {
                    return true;
                }
                break;
            case 11:
                if ( i == (DUPLEX_ULFB_START) ) {
                    return true;
                }
                break;
            case 12:
                if ( i == (DUPLEX_ULFB_START+1) ) {
                    return true;
                }
                break;
            case 13:
                if ( i == (DUPLEX_ULFB_START+2) ) {
                    return true;
                }
                break;
            case 14:
                if ( i == (DUPLEX_ULFB_START+3) ) {
                    return true;
                }
                break;
            case 15:
                if ( i >= (DUPLEX_ULFB_START) && i < (DUPLEX_ULFB_END) ) {
                    return true;
                }
                break;
            case 16:
                if ( i >= DUPLEX_B0 && i < (DUPLEX_B1) ) {
                    return true;
                }
                break;
            case 17:
                if( (i >= DUPLEX_B1) && (i < (DUPLEX_B1+2))) {
                    return true;
                }
                break;
            case 18:
                if ( i >= (DUPLEX_B1) ) {
                    return true;
                }
                break;
            case 19:
                if((i < 1) || (i >= (DUPLEX_ULFB_START) && i < (DUPLEX_ULFB_END))) {
                    return true;
                }
                break;
            case 20:
                if((i >= (DUPLEX_ULFB_START) && i < (DUPLEX_ULFB_END)) || ((i >= DUPLEX_B1) && (i < (DUPLEX_B1+2)))) {
                    return true;
                }
                break;
            case 21:
                if((i < 1) || (i >= (DUPLEX_ULFB_START) && i < (DUPLEX_ULFB_END)) || ((i >= DUPLEX_B1) && (i < (DUPLEX_B1+2)))) {
                    return true;
                }
                break;
            case 22:
                if((i < 1) || ((i >= DUPLEX_B1) && (i < (DUPLEX_B1+2)))) {
                    return true;
                }
                break;
            case 23:
                if(( i >= DUPLEX_B0 && i < (DUPLEX_B0+2)) || ( (i >= DUPLEX_B1) && (i < (DUPLEX_B1+2))) ) {
                    return true;
                }
                break;
            case 24:
                if ( i == 0 || i == (DUPLEX_B0) ) {
                    return true;
                }
                break;
            case 25:
                if ( i == 1 || i == (DUPLEX_B0) ) {
                    return true;
                }
                break;
            case 26:
                if ( i == 2 || i == (DUPLEX_B0) ) {
                    return true;
                }
                break;
            case 27:
                if ( i == 3 || i == (DUPLEX_B0) ) {
                    return true;
                }
                break;
            case 28:
                if ( (i >= 0 && i < 4) || (i == (DUPLEX_B0) || i == (DUPLEX_B0+1)) ) {
                    return true;
                }
                break;
            default:
                return false;
                break;
        }
        return false;
}


void init_duplex(duplex_timeslot_t* const dts, const uint32_t role) {
    dts->role = role;
    dts->lt_phase = 0;
    dts->lt_target = 0;
    dts->lt_target_valid = false;
    dts->lifetime_p = 0;

    if( role == DUPLEX_ROLE_RX ) {
        dts->lt_period = 10;
    } else {
        dts->lt_period = 10;
    }
}

void update_duplex_role(duplex_timeslot_t* const dts) {
    uint32_t role_copy = dts->role;

    init_duplex(dts, role_copy);
}


/*
returns index for:

fft1024_cfg_t active_plan; // also known as default plan   // idx 0
fft1024_cfg_t fft_plan_dl_pilot;                           // idx 1
fft1024_cfg_t fft_plan_ul_pilot;                           // idx 2
fft1024_cfg_t fft_plan_ul_feedback;                        // idx 3
fft1024_cfg_t fft_plan_dl_beam_pilot;                      // idx 4
fft1024_cfg_t fft_plan_dl_beam_data;                       // idx 5

*/
uint32_t duplex_fft_set_for_mode(const duplex_timeslot_t* const role, const uint32_t mode) {
    (void)role;
    // if(dts->role) {

    // }
    switch(mode) {
        default:
        case DUPLEX_SEND_ZERO:
        case DUPLEX_SEND_UL_FINESYNC:
        case DUPLEX_SEND_UL_DATA:
            return 0;
            break;
        case DUPLEX_SEND_DL_PILOT_0: //    p
        case DUPLEX_SEND_DL_PILOT_1:
        case DUPLEX_SEND_DL_PILOT_2:
        case DUPLEX_SEND_DL_PILOT_3:
            return 1; 
            break;
        case DUPLEX_SEND_UL_PILOT:   //    P
            return 2; 
            break;
        case DUPLEX_SEND_UL_FEEDBACK_0: // F
        case DUPLEX_SEND_UL_FEEDBACK_1:
        case DUPLEX_SEND_UL_FEEDBACK_2:
        case DUPLEX_SEND_UL_FEEDBACK_3:
            return 3;
            break;
        case DUPLEX_SEND_DL_BEAM_PILOT: // i
            return 4;
            break;
        case DUPLEX_SEND_DL_DATA:       // d
            return 5;
            break;
    }
}


/*

// load into https://coliru.stacked-crooked.com/

#include <iostream>

using namespace std;

char get_char_for_duplex_mode(const uint32_t dmode) {
    switch(dmode) {
        case DUPLEX_SEND_ZERO:
            return '_';
        case DUPLEX_SEND_DL_PILOT_0:
            return 'p';
        case DUPLEX_SEND_DL_PILOT_1:
            return 'p'+1;
        case DUPLEX_SEND_DL_PILOT_2:
            return 'p'+2;
        case DUPLEX_SEND_DL_PILOT_3:
            return 'p'+3;
        case DUPLEX_SEND_DL_DATA:
            return 'd';
        case DUPLEX_SEND_UL_PILOT:
            return 'P';
        case DUPLEX_SEND_UL_FINESYNC:
            return 'S';
        case DUPLEX_SEND_UL_DATA:
            return 'D';
        case DUPLEX_SEND_UL_FEEDBACK_0:
            return 'F';
        case DUPLEX_SEND_UL_FEEDBACK_1:
            return 'F'+1;
        case DUPLEX_SEND_UL_FEEDBACK_2:
            return 'F'+2;
        case DUPLEX_SEND_UL_FEEDBACK_3:
            return 'F'+3;
        case DUPLEX_SEND_DL_BEAM_PILOT:
            return 'i';
        default:
            return '?';
    }
}

void print_r(duplex_timeslot_t* const r) {
    for( int i = 0; i < DUPLEX_FRAMES; i++ ) {
        uint32_t dmode = get_duplex_mode(r, i, i);
        char cc = get_char_for_duplex_mode(dmode);
        cout << cc << "";
    }
    cout << "\n";
}


void print_duplex_helper(duplex_timeslot_t* r, std::string name, bool include_dnr = false) {
    
    // for( int i = 0; i < DUPLEX_FRAMES; i++ ) {
    //     int32_t v = duplex_ul_feedback_phase(i);
    //     cout << v+1;
    // }
    // cout << "  " << name << " feedback_phase" << "\n";
    
    for( int i = 0; i < DUPLEX_FRAMES; i++ ) {
        int32_t v = duplex_should_forward_eq_data(r, i, 2);
        cout << v;
    }
    cout << "  " << name << " should_forward" << "\n";
    
    if(include_dnr) {
        for( int i = 0; i < DUPLEX_FRAMES; i++ ) {
            int32_t v = duplex_do_not_rotate(r, i, 2, 0);
            cout << v;
        }
        cout << "  " << name << " do_not_rotate" << "\n";
    }
    if(1) {    
        for( int i = 0; i < DUPLEX_FRAMES; i++ ) {
            int32_t v = duplex_dl_pilot_phase(i);
            cout << v+1;
        }
        cout << "  " << name << " duplex_dl_pilot_phase" << "\n";
    }
    if(1) {
        for( int i = 0; i < DUPLEX_FRAMES; i++ ) {
            int32_t v = duplex_dl_beam_pilot_phase(i);
            cout << v+1;
        }
        cout << "  " << name << " duplex_dl_beam_pilot_phase" << "\n";
    }
    cout << "\n";
}

void print_duplex_tag(const unsigned tagslimit) {
    
    for(uint32_t tag = 1; tag < tagslimit; tag++) {
        
        for( int i = 0; i < DUPLEX_FRAMES; i++ ) {
            int32_t v = duplex_tag_section(i, tag);
            cout << (v ? '1' : ' ');
        }
        cout << "  :" << tag <<  "\n";
    }
}


int main() {
    cout << "\n";
    
    duplex_timeslot_t r0;
    init_duplex(&r0, DUPLEX_ROLE_RX);
    
    duplex_timeslot_t t0;
    init_duplex(&t0, DUPLEX_ROLE_TX_0);
    
    duplex_timeslot_t t1;
    init_duplex(&t1, DUPLEX_ROLE_TX_1);
    
    duplex_timeslot_t t2;
    init_duplex(&t2, DUPLEX_ROLE_TX_2);
    
    duplex_timeslot_t t3;
    init_duplex(&t3, DUPLEX_ROLE_TX_3);
    
    //char c = 'a';
    for( int i = 0; i < DUPLEX_FRAMES; i++ ) {
        if( i % 10 == 0) {
            cout << (i / 10) % 10;
        } else {
            cout << " ";
        }
    }
    cout << "\n";
    for( int i = 0; i < DUPLEX_FRAMES; i++ ) {
        cout << i % 10;
    }
    cout << "\n\n";
    
    print_r(&r0);
    print_r(&t0);
    print_r(&t1);
    print_r(&t2);
    print_r(&t3);
    cout << "\n";
    
    print_duplex_helper(&r0, "r0", true);
    print_duplex_helper(&t0, "t0");
    print_duplex_helper(&t1, "t1");
    print_duplex_helper(&t2, "t2");
    print_duplex_helper(&t3, "t3");
    
    cout << "\n";
    
    print_duplex_tag(30);

}



*/



