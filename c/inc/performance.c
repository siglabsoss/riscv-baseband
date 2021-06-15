#include "performance.h"
#include "csr_control.h"
#include "circular_buffer_pow2.h"
#include "ringbus.h"
#include "ringbus2_pre.h"

///
/// Choose a ringbus command to reply under
///


#if   OUR_RING_ENUM == RING_ENUM_ETH
#define PERF_REPORTS_AS PERF_ETH_PCCMD

//////////////////#elif OUR_RING_ENUM == RING_ENUM_CS20
/////////////////#define PERF_REPORTS_AS PERF_20_PCCMD

#elif OUR_RING_ENUM == RING_ENUM_CS01
#define PERF_REPORTS_AS PERF_01_PCCMD

#elif OUR_RING_ENUM == RING_ENUM_CS11
#define PERF_REPORTS_AS PERF_11_PCCMD

#elif OUR_RING_ENUM == RING_ENUM_CS21
#define PERF_REPORTS_AS PERF_21_PCCMD

#elif OUR_RING_ENUM == RING_ENUM_CS31
#define PERF_REPORTS_AS PERF_31_PCCMD

#elif OUR_RING_ENUM == RING_ENUM_CS02
#define PERF_REPORTS_AS PERF_02_PCCMD

#elif OUR_RING_ENUM == RING_ENUM_CS12
#define PERF_REPORTS_AS PERF_12_PCCMD

#elif OUR_RING_ENUM == RING_ENUM_CS22
#define PERF_REPORTS_AS PERF_22_PCCMD

#elif OUR_RING_ENUM == RING_ENUM_CS32
#define PERF_REPORTS_AS PERF_32_PCCMD

#elif OUR_RING_ENUM == RING_ENUM_CS20
#define PERF_REPORTS_AS PERF_20_PCCMD

// #elif OUR_RING_ENUM == RING_ENUM_CS23
// #define PERF_REPORTS_AS PERF_23_PCCMD

// #elif OUR_RING_ENUM == RING_ENUM_CS33
// #define PERF_REPORTS_AS PERF_33_PCCMD

#elif OUR_RING_ENUM == RING_ENUM_AS_PC
// use a BAD value, why did we get here??? what does it all mean?
#define PERF_REPORTS_AS RING_ENUM_ETH
#warning performance.c does not understand when RING_ENUM_ETH is PC

#else 
// this could also use a #error however...
#warning performance.c could not understand value of OUR_RING_ENUM
#endif






// typedef struct circular_buf_pow2_t circular_buf_pow2_t;

// per second
#define CLOCK_HZ 125000000
#define OFDM_PER_SECOND 24414
#define CLOCK_BUDGET_PER_1 5120

#define PERF_FIFO_0_SIZE 16
#define PERF_FIFO_1_SIZE 16
#define PERF_FIFO_2_SIZE 16
#define PERF_FIFO_3_SIZE 128

circular_buf_pow2_t perf_fifo = CIRBUF_POW2_STATIC_CONSTRUCTOR(perf_fifo, PERF_FIFO_3_SIZE);
// static unsigned int idle_timer_last;
static unsigned int idle_timer_now;
static unsigned int idle_storage_0;
// static means only this .c file can use them, this is a must for libraries
// static unsigned int perf_storage_0[PERF_FIFO_0_SIZE];
// static unsigned int perf_storage_1[PERF_FIFO_1_SIZE];
// static unsigned int perf_storage_2[PERF_FIFO_2_SIZE];
// static unsigned int perf_check_short = 4;
// static unsigned int perf_check_long = OFDM_PER_SECOND;
static unsigned int perf_ok_run = 0;
static unsigned int perf_active = 0;
static unsigned int perf_request_dump = 0;
static unsigned int perf_is_dump = 0;
static unsigned int perf_on_first = 0;
static unsigned int perf_first_storage = 0;
static unsigned int perf_second_storage = 0;
static unsigned int perf_work_count = 0;
// how many periods before we snap a timer
static unsigned int perf_accumulation_period = 0;

// forward declare
void ring_block_send_eth(unsigned int data);

static void _reset_perf(void) {
    perf_ok_run = 1;
    circular_buf2_reset(&perf_fifo);
    perf_request_dump = 0;
    perf_is_dump = 0;
    perf_on_first = 1;
    perf_work_count = 0;
}

void _perf_ringbus_callback(unsigned int data) {
    unsigned int dmode = (data >> 16) & 0xff;
    unsigned int data_16 = data & 0xffff;
    switch(dmode) {
        case 1:
            if( perf_request_dump == 0 ) {
                perf_request_dump = 1;
                // marks beginning of report to pc
                ring_block_send_eth(PERF_REPORTS_AS | 0x000000);
                ring_block_send_eth(PERF_REPORTS_AS | perf_accumulation_period);
            }
        break;
        case 2:
            _reset_perf();
        break;
        case 3:
            // call this before reset to get a new period
            _perf_set_acumulation_period(data_16);
        default:
        break;
    }
}

void __attribute__((deprecated)) _setup_perf(void) {
    CIRBUF_POW2_RUNTIME_INITIALIZE(perf_fifo);

    // circular_buf2_get(&perf_fifo, &data);
    // circular_buf2_put(dma_schedule_in, 2);
    perf_ok_run = 1;

    // for(unsigned int i = 0; i < PERF_FIFO_0_SIZE; i++) {
    //     perf_storage_0[i] = 0;
    //     perf_storage_1[i] = 0;
    //     perf_storage_2[i] = 0;
    // }
    idle_storage_0 = 0;

    perf_on_first = 1;

    perf_active = 3;
    perf_work_count = 0;

    // default
    // does not get changed at reset
    _perf_set_acumulation_period(4);
    
    ring_register_callback(&_perf_ringbus_callback, PERF_CMD);

    // CSR_READ(TIMER_VALUE, idle_timer_last);
}


inline unsigned int _perf_subtract_timers(unsigned int a, unsigned int b) {
  if (a < b) {
      // time rollover(overflow)
      return (0xFFFFFFFF - b) + 1 + a;
    } else {
      return a - b;
    }
}

void _perf_set_acumulation_period(unsigned int p) {
    perf_accumulation_period = p;
}



void __attribute__((deprecated)) _perf_work(void) {
    if(!perf_ok_run) return;

    perf_work_count++;
    
    if(perf_on_first) {
        CSR_READ(TIMER_VALUE, perf_first_storage);
        perf_on_first = 0;
        return;
    } else {
        if(perf_work_count == perf_accumulation_period) {
            CSR_READ(TIMER_VALUE, perf_second_storage);
        }
    }

}

void _perf_mark(unsigned int i) {
    (void)i;
    if(!perf_ok_run) return;
}

static void _perf_slow_dump(void) {
    unsigned int empty = circular_buf2_empty(&perf_fifo);
    if(!empty) {

        unsigned int occupancy;
        unsigned int data_out;
        CSR_READ(RINGBUS_SCHEDULE_OCCUPANCY, occupancy);
        
        if(occupancy == 0) {
            circular_buf2_get(&perf_fifo, &data_out);

            unsigned int data_final = PERF_REPORTS_AS | (data_out & 0xffffff);

            ring_block_send_eth(data_final);
            // CSR_WRITE(RINGBUS_WRITE_ADDR, RING_ADDR_PC);
            // CSR_WRITE(RINGBUS_WRITE_DATA, data_out);
            // CSR_WRITE(RINGBUS_WRITE_EN, 0);
        }

    } else {
        perf_is_dump = 0;
        perf_ok_run = 1;
    }
}

// this must be the first thing the run loop does
void _perf_top_idle_loop(void) {

    CSR_READ(TIMER_VALUE, idle_timer_now);

    // unsigned int delta = _perf_subtract_timers(idle_timer_now, idle_timer_last);

    idle_storage_0++;

    if(perf_work_count < perf_accumulation_period) return;

    if(perf_request_dump != 0) {
        perf_request_dump = 0;
        perf_is_dump = 1;
        perf_ok_run = 0;
    }

    if( perf_is_dump ) {
        _perf_slow_dump();
        return;
    }



    circular_buf2_put(&perf_fifo, idle_storage_0);

    // if == then it's ok
    // if greater, that means we did 2 work calls before we got a call here
    // if( perf_work_count >= perf_accumulation_period) {
    circular_buf2_put(&perf_fifo, perf_second_storage - perf_first_storage);
    // }

    // reset for next
    perf_first_storage = 0;
    perf_second_storage = 0;
    perf_on_first = 1;
    perf_work_count = 0;


    // for(unsigned int i = 0; i < perf_active; i++) {
    //     circular_buf2_put(&perf_fifo, perf_storage_0[i] - perf_storage_1[i]);
    //     perf_storage_1[i] = perf_storage_0[i];
    // }

    idle_storage_0 = 0;
    // idle_timer_last = idle_timer_now;
}

// ignores results until the next top of loop
void _perf_invalidate(void) {
    if(!perf_ok_run) return;

}


