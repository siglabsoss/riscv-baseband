#include "mapmov.h"
#include "ringbus.h"

///////////////////////////////////////////
///
/// Shared Functions
///



#ifndef VERILATE_TESTBENCH

///////////////////////////////////////////
///
/// Vex functions
///

static unsigned int __mapmov_active;
static unsigned int __mapmov_start;
static unsigned int __mapmov_end;
static unsigned int __mapmov_mode;



/// Partial Stuff
///
static void (*partial_callback)(void) = 0;
static unsigned int times_partial_called = 0;

/// This allows us to to chunked / partial updates to these registers
// static unsigned int partial_active = 0;

static void start_partial(void (*cb)(void)) {
    partial_callback = cb;
    times_partial_called = 0;
}

static void finish_partial(void) {
    partial_callback = 0;
    SET_REG(x3, 0x6ffff);
}






// // forward declare this
// void ring_block_send_eth(unsigned int data);
// forward declare this
void queue_dma_out_blocking(unsigned int data);

// other CSR_WRITE are a macro, this is actually a function
// but it mapps to a macro

void CSR_WRITE_MAPMOV_ACTIVE(const unsigned int index, const unsigned int value) {
    switch(index) {
        case 0:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+ 0, value);
            break;
        case 1:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+ 1, value);
            break;
        case 2:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+ 2, value);
            break;
        case 3:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+ 3, value);
            break;
        case 4:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+ 4, value);
            break;
        case 5:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+ 5, value);
            break;
        case 6:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+ 6, value);
            break;
        case 7:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+ 7, value);
            break;
        case 8:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+ 8, value);
            break;
        case 9:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+ 9, value);
            break;
        case 10:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+10, value);
            break;
        case 11:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+11, value);
            break;
        case 12:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+12, value);
            break;
        case 13:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+13, value);
            break;
        case 14:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+14, value);
            break;
        case 15:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+15, value);
            break;
        case 16:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+16, value);
            break;
        case 17:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+17, value);
            break;
        case 18:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+18, value);
            break;
        case 19:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+19, value);
            break;
        case 20:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+20, value);
            break;
        case 21:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+21, value);
            break;
        case 22:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+22, value);
            break;
        case 23:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+23, value);
            break;
        case 24:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+24, value);
            break;
        case 25:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+25, value);
            break;
        case 26:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+26, value);
            break;
        case 27:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+27, value);
            break;
        case 28:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+28, value);
            break;
        case 29:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+29, value);
            break;
        case 30:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+30, value);
            break;
        case 31:
            CSR_WRITE(MAPMOV_MOVER_ACTIVE+31, value);
            break;
        default:
            // major issue
            break;
        }
}



/*
// Original version of this function, took a very long time to execute
void mapmov_mode_128_monolithic() {
    const unsigned int pilot = 0x00002000;

    CSR_WRITE(MAPMOV_TRIM_START, 0);
    CSR_WRITE(MAPMOV_TRIM_END, 1023);

    unsigned int did_activate = 0;

    for(unsigned int i = 0; i < 32; i++) {
        unsigned bit_mask = 0;
        for(unsigned int j = 0; j < 32; j++) {
            unsigned int sc = (i*32) + j;
            SET_REG(x3, sc);  // remove to save 2 us over span of loop

            bit_mask = bit_mask >> 1;

            // if odd
            if( (sc & 0x1) == 1 ) {
                if( sc < 129 || sc > 896) {
                    bit_mask |= (0x1<<31);
                    did_activate++;
                }
            }
        }

        if( i == 0 ) {
            bit_mask &= ~0x1;
        }

        // a fn() not a macro
        CSR_WRITE_MAPMOV_ACTIVE(i, bit_mask);
    }

    for(unsigned int sc = 0; sc < 1024; sc++) {
        CSR_WRITE(MAPMOV_PILOT_RAM_ADDR, sc);

        if(
            ( sc <= 128 || sc >= 896 )
          )
            {
                CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, pilot);
            } else {
                CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, 0x0);
            }

        CSR_WRITE_ZERO(MAPMOV_PILOT_RAM_WE);
    }

    mapmov_latch_settings(did_activate, 0, 1023);
}
*/

// To generate this
// Copy the first loop in the function mapmov_mode_128_monolithic above
// print the value of bit_mask
// print the value of did_activate
static const unsigned int precalc_active_128 = 128;
static const unsigned int precalc_bitmask[32] = {
0xaaaaaaaa,
0xaaaaaaaa,
0xaaaaaaaa,
0xaaaaaaaa,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0xaaaaaaaa,
0xaaaaaaaa,
0xaaaaaaaa,
0xaaaaaaaa};

void partial_mapmov_mode_128(void) {

    static unsigned i;
    // static int j;
    static unsigned int sc;

    const unsigned int pilot = 0x00002000;

    // SET_REG(x3, 0xffa00000);
    // SET_REG(x3, times_partial_called);

    static int state = 0;

    // local, non static variable
    int next_state = state;

    /// times_partial_called is controlled outside this function
    /// we only check if this is 0, and then use our own state variable for further progress
    /// tracking
    if(times_partial_called == 0) {
        i = 0;
        // j = 0;
        sc = 0;

        state = 0;  // state is 0
        next_state = 0;

        CSR_WRITE(MAPMOV_TRIM_START, 0);
        CSR_WRITE(MAPMOV_TRIM_END, 1023);
    }

    if( state == 0 ) {
        const unsigned mask_chunk = 17;
        const unsigned this_end = i + mask_chunk;
        for(/*empty*/; i < 32 && i < this_end; i++) {
            // this used to be a loop, see comment above
            unsigned bit_mask = precalc_bitmask[i];
            // a fn() not a macro
            CSR_WRITE_MAPMOV_ACTIVE(i, bit_mask);
        }
        if( i == 32 ) {
            next_state = state+1;
        }
    }

    if( state == 1 ) {
        // 64 ok
        const unsigned sc_chunk = 20; // can be un-even divide into 1024
        const unsigned this_end = sc + sc_chunk;

        for(/*empty*/; sc < 1024 && sc < this_end; sc++) {
            CSR_WRITE(MAPMOV_PILOT_RAM_ADDR, sc);

            if(
                ( sc <= 128 || sc >= 896 )
              )
                {
                    CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, pilot);
                } else {
                    CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, 0x0);
                }

            CSR_WRITE_ZERO(MAPMOV_PILOT_RAM_WE);
        }
        // loop will increment and exit, leaving sc at 1024, this means we are done
        if( sc == 1024 ) {
            next_state = state+1;
        }
    }

    if( state == 2 ) {
        mapmov_latch_settings(precalc_active_128, 0, 1023);
        finish_partial();
    }



    state = next_state;
}

void mapmov_mode_128(void) {
    SET_REG(x3, 0x7ffff);
    start_partial(&partial_mapmov_mode_128);
}


void mapmov_mode_320(void) {
    const unsigned int pilot = 0x00002000;

    const unsigned int low_bound = 320;
    const unsigned int high_bound = 1024-320;

    const unsigned int low_bound_pilot = 323;
    const unsigned int high_bound_pilot = 701;


    CSR_WRITE(MAPMOV_TRIM_START, 0);
    CSR_WRITE(MAPMOV_TRIM_END, 1023);

    unsigned int did_activate = 0;

    for(unsigned int i = 0; i < 32; i++) {
        unsigned bit_mask = 0;
        for(unsigned int j = 0; j < 32; j++) {
            const unsigned int sc = (i*32) + j;
            SET_REG(x3, sc);  // remove to save 2 us over span of loop

            bit_mask = bit_mask >> 1;

            // if odd
            if( (sc & 0x1) == 1 ) {
                if( sc < (low_bound+1) || sc > (high_bound)) {
                    bit_mask |= (0x1<<31);
                    did_activate++;
                }
            }
        }

        if( i == 0 ) {
            bit_mask &= ~0x1;
        }

        // a fn() not a macro
        CSR_WRITE_MAPMOV_ACTIVE(i, bit_mask);
    }


    // manually do zero
    CSR_WRITE(MAPMOV_PILOT_RAM_ADDR, 0);
    CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, 0x0);
    CSR_WRITE_ZERO(MAPMOV_PILOT_RAM_WE);

    // skip zero
    for(unsigned int sc = 1; sc < 1024; sc++) {
        CSR_WRITE(MAPMOV_PILOT_RAM_ADDR, sc);

        if(
            ( (sc & 0x1) == 0 && (sc <= low_bound_pilot || sc >= high_bound_pilot) )
          )
            {
                CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, pilot);
            } else {
                CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, 0x0);
            }

        CSR_WRITE_ZERO(MAPMOV_PILOT_RAM_WE);
    }

    mapmov_latch_settings(did_activate, 0, 1023);
}


void mapmov_mode_640_lin(void) {
    const unsigned int pilot = 0x00002000;

    CSR_WRITE(MAPMOV_TRIM_START, 0);
    CSR_WRITE(MAPMOV_TRIM_END, 1023);

    unsigned int did_activate = 0;

    for(unsigned int i = 0; i < 32; i++) {
        unsigned bit_mask = 0;
        for(unsigned int j = 0; j < 32; j++) {
            const unsigned int sc = (i*32) + j;

            bit_mask = bit_mask >> 1;

            if( (sc >= (16+1) && sc < (16+320+1)) || (sc >= (1024-16-320+1) && sc < (1024-16+1) ) ) {
                bit_mask |= (0x1<<31);
                did_activate++;
                SET_REG(x3, sc);
            }
        }

        if( i == 0 ) {
            bit_mask &= ~0x1;
        }

        // a fn() not a macro
        CSR_WRITE_MAPMOV_ACTIVE(i, bit_mask);
    }


    // manually do zero
    CSR_WRITE(MAPMOV_PILOT_RAM_ADDR, 0);
    CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, 0x0);
    CSR_WRITE_ZERO(MAPMOV_PILOT_RAM_WE);

    // skip zero
    for(unsigned int sc = 1; sc < 1024; sc++) {
        CSR_WRITE(MAPMOV_PILOT_RAM_ADDR, sc);

        if(
            (sc < (16+320+1)) || (sc >= (1024-16-320+1))
          )
            {
                CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, pilot);
            } else {
                CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, 0x0);
            }

        CSR_WRITE_ZERO(MAPMOV_PILOT_RAM_WE);
    }

    mapmov_latch_settings(did_activate, 0, 1023);
}


void mapmov_mode_512_lin(void) {
    const unsigned int pilot = 0x00002000;

    CSR_WRITE(MAPMOV_TRIM_START, 0);
    CSR_WRITE(MAPMOV_TRIM_END, 1023);

    unsigned int did_activate = 0;

    for(unsigned int i = 0; i < 32; i++) {
        unsigned bit_mask = 0;
        for(unsigned int j = 0; j < 32; j++) {
            const unsigned int sc = (i*32) + j;

            bit_mask = bit_mask >> 1;

            if( (sc >= (1) && sc < (320+1)) || (sc >= (1024-320+1) && sc < (1024-128+1) ) ) {
                bit_mask |= (0x1<<31);
                did_activate++;
                SET_REG(x3, sc);
            }
        }

        if( i == 0 ) {
            bit_mask &= ~0x1;
        }

        // a fn() not a macro
        CSR_WRITE_MAPMOV_ACTIVE(i, bit_mask);
    }


    // manually do zero
    CSR_WRITE(MAPMOV_PILOT_RAM_ADDR, 0);
    CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, 0x0);
    CSR_WRITE_ZERO(MAPMOV_PILOT_RAM_WE);

    // skip zero
    for(unsigned int sc = 1; sc < 1024; sc++) {
        CSR_WRITE(MAPMOV_PILOT_RAM_ADDR, sc);

        if(
            (sc >= (1024-320+1))
          )
            {
                CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, pilot);
            } else {
                CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, 0x0);
            }

        CSR_WRITE_ZERO(MAPMOV_PILOT_RAM_WE);
    }

    mapmov_latch_settings(did_activate, 0, 1023);
}


void mapmov_mode_64_lin(void) {
    // const unsigned int pilot = 0x00002000;

    CSR_WRITE(MAPMOV_TRIM_START, 0);
    CSR_WRITE(MAPMOV_TRIM_END, 1023);

    unsigned int did_activate = 0;

    for(unsigned int i = 0; i < 32; i++) {
        unsigned bit_mask = 0;
        for(unsigned int j = 0; j < 32; j++) {
            const unsigned int sc = (i*32) + j;

            bit_mask = bit_mask >> 1;

            if( (sc >= (16) && sc < (80)) ) {
                bit_mask |= (0x1<<31);
                did_activate++;
                SET_REG(x3, sc);
            }
        }

        if( i == 0 ) {
            bit_mask &= ~0x1;
        }

        // a fn() not a macro
        CSR_WRITE_MAPMOV_ACTIVE(i, bit_mask);
    }


    // manually do zero
    CSR_WRITE(MAPMOV_PILOT_RAM_ADDR, 0);
    CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, 0x0);
    CSR_WRITE_ZERO(MAPMOV_PILOT_RAM_WE);

    // skip zero
    for(unsigned int sc = 1; sc < 1024; sc++) {
        CSR_WRITE(MAPMOV_PILOT_RAM_ADDR, sc);
        CSR_WRITE_ZERO(MAPMOV_PILOT_RAM_WDATA);
        CSR_WRITE_ZERO(MAPMOV_PILOT_RAM_WE);
    }

    mapmov_latch_settings(did_activate, 0, 1023);
}



void mampmov_mode_debug(void) {
    CSR_WRITE(MAPMOV_TRIM_START, 0);
    CSR_WRITE(MAPMOV_TRIM_END, 1023);

    unsigned int bit_mask = 0;
    for(unsigned int i = 0; i < 32; i++) {
        if( i == 0 ) {
            bit_mask = 0xffffffff;
        } else {
            bit_mask = 0;
        }
        CSR_WRITE_MAPMOV_ACTIVE(i, bit_mask);
    }

    for(unsigned int sc = 0; sc < 1024; sc++) {
        CSR_WRITE(MAPMOV_PILOT_RAM_ADDR, sc);
        CSR_WRITE(MAPMOV_PILOT_RAM_WDATA, sc);
        CSR_WRITE_ZERO(MAPMOV_PILOT_RAM_WE);
    }

    mapmov_latch_settings(32, 0, 1023);
}

void mapmov_latch_settings(const unsigned int active,
                           const unsigned int start,
                           const unsigned int end) {
    __mapmov_active = active;
    __mapmov_start = start;
    __mapmov_end = end;
}

void mapmov_report_settings(void) {
    // unsigned int dmode;
    // dmode = ( (2)<<16 );

    unsigned int rb;

    rb = ( (1)<<16 ) | __mapmov_active | MAPMOV_MODE_REPORT;
    queue_dma_out_blocking(rb);

    rb = ( (2)<<16 ) | __mapmov_start | MAPMOV_MODE_REPORT;
    queue_dma_out_blocking(rb);

    rb = ( (3)<<16 ) | __mapmov_end | MAPMOV_MODE_REPORT;
    queue_dma_out_blocking(rb);

    rb = ( (4)<<16 ) | __mapmov_mode | MAPMOV_MODE_REPORT;
    queue_dma_out_blocking(rb);

}


///
/// we can add more modes and refer to them by index
/// make sure that each mode ends by calling mapmov_latch_settings()
void mapmov_choose_mode(const unsigned int mode, const unsigned int reset_module) {
    SET_REG(x3, 0x3ffff);
    if( reset_module ) {
        CSR_WRITE_ZERO(MAPMOV_RESET);
    }
    SET_REG(x3, 0x4ffff);
    unsigned int mode_found = 1;
    switch(mode) {
        case MAPMOV_SUBCARRIER_128:
            mapmov_mode_128();
            break;
        case MAPMOV_MODE_DEBUG:
            mampmov_mode_debug();
            break;
        case MAPMOV_SUBCARRIER_320:
            mapmov_mode_320();
            break;
        case MAPMOV_SUBCARRIER_640_LIN:
            mapmov_mode_640_lin();
            break;
        case MAPMOV_SUBCARRIER_512_LIN:
            mapmov_mode_512_lin();
            break;
        case MAPMOV_SUBCARRIER_64_LIN:
            mapmov_mode_64_lin();
            break;
        default:
            mode_found = 0;
            break;
    }

    if(mode_found) {
        __mapmov_mode = mode;
    } else {
        __mapmov_mode = 0xffffff; // 24 bits
    }
    SET_REG(x3, 0x5ffff);

    // mapmov_report_settings();
}

void mapmov_pet_partial(void) {
    if( partial_callback != 0) {
        partial_callback();
        times_partial_called++;
    }
}


#else

///////////////////////////////////////////
///
/// TestBench / S-Modem functions
///

#endif