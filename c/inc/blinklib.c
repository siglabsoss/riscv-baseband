#include "blinklib.h"
#include "csr_control.h"
// #include "ringbus2_pre.h"
// #include "ringbus2_post.h"

// All timers are in counts
// led on timer
static unsigned int blinklib_on_time;
// led off time
static unsigned int blinklib_off_time;
// time between error codes
static unsigned int blinklib_wait_1;
// time between last error code
static unsigned int blinklib_wait_2;
// storage for status codes
static unsigned int blinklib_codes[BLINKLIB_MAX_BLINK_CODES];
// how many non zero status codes are active
static unsigned int blinklib_active_codes;
// how many blinks have we sent
static unsigned int blinklib_lit_count;
// is the LED currently on (assuming nobody else is controlling it)
static unsigned int blinklib_is_on;
// timer value of next event
static unsigned int blinklib_next_event;
// times we've shown the current status code
static unsigned int blinklib_track_times_shown;

#define LEDON()  CSR_SET_BITS(GPIO_WRITE, LED_GPIO_BIT)
#define LEDOFF() CSR_CLEAR_BITS(GPIO_WRITE, LED_GPIO_BIT)

// default "constructor" with default times
// timer values are against CSR timer
void setup_blinklib(void)
{
    setup_blinklib_timers(
        700,
        400,
        0, // unused 
        1500
        );

    setup_blinklib_timers(
        20000000,
        35000000,
        0, // unused 
        125000000
        );
}
void setup_blinklib_timers(
    const unsigned int on_time,
    const unsigned int off_time,
    const unsigned int wait_1,
    const unsigned int wait_2)
{
    blinklib_on_time = on_time;
    blinklib_off_time = off_time;
    blinklib_wait_1 = wait_1;
    blinklib_wait_2 = wait_2;

    // setup gpio
    CSR_SET_BITS(GPIO_WRITE_EN, LED_GPIO_BIT);

    blinklib_status(0);
}

// void debug_blinklib(void) {
//     static debug_calls = 0;
//     unsigned int now;

//     if( debug_calls > 1000 ) {
//         CSR_READ(TIMER_VALUE, now);
//         ring_block_send_eth(0);
//         ring_block_send_eth(now);
//         ring_block_send_eth(blinklib_next_event);
//         debug_calls = 0;
//     }

//     debug_calls++;
// }

inline unsigned int blinklib_subtract_timers(unsigned int a, unsigned int b) {
  if (a < b) {
      // time rollover(overflow)
      return (0xFFFFFFFF - b) + 1 + a;
    } else {
      return a - b;
    }
}

// the structure is this:
// each time we pet, we do nothing until the next even time
// once it is equal or past to the next event time, we update the LED, and 
// then calculate the next event time
// this allows us to quickly exit the fn after 2 compares for the majority
// of calls, and only do more work if we are on an LED edge
void pet_blinklib(void)
{
    unsigned int now;
    if( blinklib_active_codes == 0 ) {
        return;
    }
    // debug_blinklib();
    CSR_READ(TIMER_VALUE, now);

    // unsigned int is_on = blinklib_is_on;//!(blinklib_is_on&0x1);

    // using a subtract routine due to rollover, this is the same as:
    //   if( now < blinklib_next_event ) 
    if( blinklib_subtract_timers(blinklib_next_event+1000000,now) > 1000000 ) {
        return;
    }

    // AT this point, we are making a change to led state

    // if led is on, we turn off, and wait for off time
    if( blinklib_is_on ) {
        LEDOFF();
        // SET_REG(x3, 0xf0);

        // if lit_count is equal to our error code
        // w// how many blinks have we sente wait for longer, and reset lit_count
        if( blinklib_lit_count == blinklib_codes[0] ) {
            // we've just finished a full blink pattern
            // we now keep off for extra time to separate blinks
            blinklib_next_event += blinklib_wait_2;
            blinklib_lit_count = 0;
        } else {
            blinklib_next_event += blinklib_off_time; // keep off for normal period
            // blinklib_lit_count++;
        }

        blinklib_is_on = 0;

    } else {
        // if led is off, we turn on, and wait for on time
        LEDON();
        // SET_REG(x3, 0xf1);
        if( blinklib_lit_count == 0 ) {
            blinklib_track_times_shown++; // if we are here with 
        }
        blinklib_next_event += blinklib_on_time; // keep on for normal period
        blinklib_lit_count++;
        blinklib_is_on = 1;
    }

    // SET_REG(x4, blinklib_next_event);

}

// how many times has the most recent code
// repeated (a value of 0 means we are still doing the first)
// the logic behind blinklib_track_times_shown means it will actually be +1 the
// expected value
unsigned int blinklib_times_shown(void) {
    if( blinklib_track_times_shown == 0 )
        return 0;

    return blinklib_track_times_shown-1;
}

// call this with status 0 to disable all blinks
void blinklib_status(const unsigned int status) {
    unsigned int now;
    if( status != 0 ) {
        blinklib_active_codes = 1;
        blinklib_is_on = 0;
        LEDOFF();
        
        CSR_READ(TIMER_VALUE, now);
        blinklib_next_event = now + blinklib_wait_2;
    } else {
        blinklib_active_codes = 0;
        LEDOFF();
    }
    blinklib_codes[0] = status;
    // how many blinks have we sentblinklib_is_on = 0; // always reset no matter what
    blinklib_lit_count = 0;
    blinklib_track_times_shown = 0;
}

void blinklib_delta_status(const unsigned int status) {
    if( status != blinklib_codes[0] ) {
        blinklib_status(status);
    }
}