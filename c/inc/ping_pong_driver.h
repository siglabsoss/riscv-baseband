#ifndef __PING_PONG_DRIVER_H__
#define __PING_PONG_DRIVER_H__

#include "dma.h"
#include "vmem.h"
#include "csr_control.h"
#include "config_word_cmul_eq_0f.h"
#include "config_word_conj_eq_0f.h"
#include <stdint.h>
#include <stdbool.h>
#include "vector_multiply.h"
#include "circular_buffer_pow2.h"


#ifndef PING_PONG_BUFFER_SIZE

#ifndef PING_PONG_BUFFER_SIZE_IN
#define PING_PONG_BUFFER_SIZE_IN  (1024)
#endif

#ifndef PING_PONG_BUFFER_SIZE_OUT
#define PING_PONG_BUFFER_SIZE_OUT (1024)
#endif

#else
#define PING_PONG_BUFFER_SIZE_IN  (PING_PONG_BUFFER_SIZE)
#define PING_PONG_BUFFER_SIZE_OUT (PING_PONG_BUFFER_SIZE)
#endif

#ifdef PING_PONG_DISABLE_OUTPUT
#undef PING_PONG_BUFFER_SIZE_OUT
#endif

// PING_PONG_MODIFY_OUTPUT


#ifdef PING_PONG_FOUR_PONG
#define PONG_LEVEL (4)
#else
#define PONG_LEVEL (2)
#endif


#define PING_PONG_CIRCULAR_BUFFER_SIZE (PONG_LEVEL)
#define PING_PONG_INPUT_BUFFER_COUNT (PONG_LEVEL)
#define PING_PONG_TRANSFORM_BUFFER_COUNT (PONG_LEVEL)
#define PING_PONG_MAX_INPUT_OCCUPANCY (PONG_LEVEL)
#define PING_PONG_MAX_OUTPUT_OCCUPANCY (PONG_LEVEL)


VMEM_SECTION unsigned int input_dma_buf[PING_PONG_BUFFER_SIZE_IN*PING_PONG_INPUT_BUFFER_COUNT];

#ifndef PING_PONG_DISABLE_OUTPUT
VMEM_SECTION unsigned int transform_dma_buf[PING_PONG_BUFFER_SIZE_OUT*PING_PONG_TRANSFORM_BUFFER_COUNT];
#endif


unsigned int input_dma_buf_addr[PING_PONG_INPUT_BUFFER_COUNT];
unsigned int* input_dma_buf_cpu[PING_PONG_INPUT_BUFFER_COUNT];

#ifndef PING_PONG_DISABLE_OUTPUT
unsigned int transform_buf_addr[PING_PONG_TRANSFORM_BUFFER_COUNT];
unsigned int* transform_buf_cpu[PING_PONG_TRANSFORM_BUFFER_COUNT];
#endif

//
circular_buf_pow2_t __input_dma_schedule =
CIRBUF_POW2_STATIC_CONSTRUCTOR(__input_dma_schedule, PING_PONG_CIRCULAR_BUFFER_SIZE);
circular_buf_pow2_t* input_dma_schedule = &__input_dma_schedule;
//
circular_buf_pow2_t __transform_schedule =
CIRBUF_POW2_STATIC_CONSTRUCTOR(__transform_schedule, PING_PONG_CIRCULAR_BUFFER_SIZE);
circular_buf_pow2_t* transform_schedule = &__transform_schedule;
//
circular_buf_pow2_t __available_input_dma =
CIRBUF_POW2_STATIC_CONSTRUCTOR(__available_input_dma, PING_PONG_CIRCULAR_BUFFER_SIZE);
circular_buf_pow2_t* available_input_dma = &__available_input_dma;

#ifndef PING_PONG_DISABLE_OUTPUT
circular_buf_pow2_t __output_dma_schedule =
CIRBUF_POW2_STATIC_CONSTRUCTOR(__output_dma_schedule, PING_PONG_CIRCULAR_BUFFER_SIZE);
circular_buf_pow2_t* output_dma_schedule = &__output_dma_schedule;
#endif
//
circular_buf_pow2_t __available_transform_dma =
CIRBUF_POW2_STATIC_CONSTRUCTOR(__available_transform_dma, PING_PONG_CIRCULAR_BUFFER_SIZE);
circular_buf_pow2_t* available_transform_dma = &__available_transform_dma;

#ifndef PING_PONG_DISABLE_OUTPUT
circular_buf_pow2_t __output_schedule =
CIRBUF_POW2_STATIC_CONSTRUCTOR(__output_schedule, PING_PONG_CIRCULAR_BUFFER_SIZE);
circular_buf_pow2_t* output_schedule = &__output_schedule;
#endif

typedef unsigned (*ping_pong_cb_t)(const unsigned int, const unsigned int* const, unsigned int* const);
typedef void (*ping_pong_event_t)(void);
typedef void (*ping_pong_adjust_output_cb_t)(unsigned* const addr, unsigned* const length);


ping_pong_cb_t transform_function = 0;
ping_pong_event_t entered_pause_function = 0;
#ifdef PING_PONG_MODIFY_OUTPUT
ping_pong_adjust_output_cb_t modify_output_function = 0;
#endif


#define PP_NORMAL (0)
#define PP_REQUEST_PAUSE (1)
#define PP_PAUSED (2)

unsigned ping_pong_state = PP_NORMAL;

/**
 *
 */
void ping_pong_set_callback(const ping_pong_cb_t transform_callback);

void ping_pong_set_pause_callback(const ping_pong_event_t cb);

#ifdef PING_PONG_MODIFY_OUTPUT
void ping_pong_set_modify_output_callback(const ping_pong_adjust_output_cb_t cb);
#endif

/**
 *
 */
void setup_ping_pong(void);

/**
 *
 */
void execute_ping_pong(void);

/**
 * Enable two input DMA simultaneously and store DMA addresses in array
 */
void init_input_dma(void);

/**
 *
 */
void init_transform_buf(void);

/**
 *
 */
void init_circular_buf(void);

/**
 *
 */
void _update_transform_schedule(const unsigned int occupancy);

/**
 *
 */
void _schedule_input_dma(const unsigned int occupancy);

/**
 *
 */
void input_dma_process(void);

/**
 *
 */
void transform_process(void);
void transform_process_no_output(void);

/**
 *
 */
void _schedule_output_dma(const unsigned int out_occupancy);

/**
 *
 */
void _update_available_transform(const unsigned int out_occupancy);

/**
 *
 */
void output_dma_process(void);

void ping_pong_set_callback(const ping_pong_cb_t transform_callback) {
    transform_function = transform_callback;
}

void ping_pong_set_pause_callback(const ping_pong_event_t cb) {
    entered_pause_function = cb;
}

#ifdef PING_PONG_MODIFY_OUTPUT
void ping_pong_set_modify_output_callback(const ping_pong_adjust_output_cb_t cb) {
    modify_output_function = cb;
}
#endif

void setup_ping_pong(void) {
    // STALL(50);
    // _printf("Boot\n");
    init_circular_buf();
    init_input_dma();
    init_transform_buf();
}

unsigned int pp_ta;
unsigned int pp_tb;

void execute_ping_pong(void) {
    input_dma_process();
#ifndef PING_PONG_DISABLE_OUTPUT
    transform_process();
    output_dma_process();
#else
    transform_process_no_output();
#endif
}

void init_input_dma(void) {
    int error;
    (void)error;
    unsigned int buffer_addr;
    for(int i = 0; i < PING_PONG_INPUT_BUFFER_COUNT; i++) {
        buffer_addr = VMEM_DMA_ADDRESS(input_dma_buf)+(PING_PONG_BUFFER_SIZE_IN*i);
        input_dma_buf_addr[i] = buffer_addr;
        input_dma_buf_cpu[i] = REVERSE_VMEM_DMA_ADDRESS(buffer_addr);
        dma_in_set(buffer_addr, PING_PONG_BUFFER_SIZE_IN);
        error = circular_buf2_put(input_dma_schedule, i);
    }
}

void init_transform_buf(void) {
#ifndef PING_PONG_DISABLE_OUTPUT
    int error;
    (void)error;
    unsigned int buffer_addr;
    for(int i = 0; i < PING_PONG_TRANSFORM_BUFFER_COUNT; i++) {
        buffer_addr = VMEM_DMA_ADDRESS(transform_dma_buf)+(PING_PONG_BUFFER_SIZE_OUT*i);
        transform_buf_addr[i] = buffer_addr;
        transform_buf_cpu[i] = REVERSE_VMEM_DMA_ADDRESS(buffer_addr);
        error = circular_buf2_put(available_transform_dma, i);
    }
#endif
}

void init_circular_buf(void) {
    CIRBUF_POW2_RUNTIME_INITIALIZE(__input_dma_schedule);
    CIRBUF_POW2_RUNTIME_INITIALIZE(__transform_schedule);
    CIRBUF_POW2_RUNTIME_INITIALIZE(__available_input_dma);
    CIRBUF_POW2_RUNTIME_INITIALIZE(__available_transform_dma);
#ifndef PING_PONG_DISABLE_OUTPUT
    CIRBUF_POW2_RUNTIME_INITIALIZE(__output_dma_schedule);
    CIRBUF_POW2_RUNTIME_INITIALIZE(__output_schedule);
#endif
}

#ifndef PING_PONG_DISABLE_RUN_TILL_LAST
bool _handle_recover_last(const unsigned int occupancy, const unsigned int status) {
    (void)occupancy;
    if( status & 0x1 ) {
        unsigned int expected_input_occupancy;
        expected_input_occupancy = circular_buf2_occupancy(input_dma_schedule);
        int error;
        (void)error;
        unsigned int corrupt0 = 0;
        error = circular_buf2_peek(input_dma_schedule, &corrupt0);
#ifdef PING_PONG_ENABLE_PRINT
        _printf("%s%d %d\n", "in scheduled: ", expected_input_occupancy, corrupt0);
#endif
        // unsigned int* cpu_in0 = REVERSE_VMEM_DMA_ADDRESS(input_dma_buf_addr[0]);
        // unsigned int* cpu_in1 = REVERSE_VMEM_DMA_ADDRESS(input_dma_buf_addr[1]);
        // _printf("%d\n%d\n%d\n%d\n\n", cpu_in0[0],cpu_in0[1],cpu_in0[2],cpu_in0[3]);
        // _printf("%d\n%d\n%d\n%d\n", cpu_in1[0],cpu_in1[1],cpu_in1[2],cpu_in1[3]);
        SET_REG(x3, 0xf0000000);
        SET_REG(x3, corrupt0);
        SET_REG(x3, 0x0);

        dma_run_till_last();

        // _puts("after run till last");

        unsigned runs = 0;
        unsigned int occupancy2;
        while(1) {
            CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, occupancy2);
            if( occupancy2 == 0) {
                break;
            }
            SET_REG(x3, runs);
            runs++;
        }

        for( unsigned i = 0; i < expected_input_occupancy; i++) {
            circular_buf2_peek_n(input_dma_schedule, &corrupt0, i);
            dma_in_set(input_dma_buf_addr[corrupt0], PING_PONG_BUFFER_SIZE_IN);
        }
        return true;
    }
    return false;
}
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"

void __attribute__((always_inline)) _update_transform_schedule(const unsigned int occupancy) {
    const int expected_input_occupancy = circular_buf2_occupancy(input_dma_schedule);
    const int occupancy_diff = expected_input_occupancy - (int)occupancy;

    if (occupancy_diff > 0) {
        int error;
        unsigned int completed_input_dma;
        for (int i = 0; i < occupancy_diff; i++) {
            error = circular_buf2_get(input_dma_schedule, &completed_input_dma);
            if (error != -1) {
                circular_buf2_put(transform_schedule, completed_input_dma);
            } else {
                break;
            }
        }
    }
}

void __attribute__((always_inline)) _schedule_input_dma(const unsigned int occupancy) {
    if (
           (occupancy < (PING_PONG_MAX_INPUT_OCCUPANCY))
        && (ping_pong_state == PP_NORMAL)
        ) {
        int error;
        unsigned int available_dma;

        error = circular_buf2_get(available_input_dma, &available_dma);
        if (error != -1) {
            dma_in_set(input_dma_buf_addr[available_dma], PING_PONG_BUFFER_SIZE_IN);
            error = circular_buf2_put(input_dma_schedule, available_dma);
#ifdef PING_PONG_ENABLE_PRINT
            _printf("%s%d\n", "    DMA     ", available_dma);
#endif
        }
    }

    if(ping_pong_state == PP_REQUEST_PAUSE) {
        const unsigned occ = circular_buf2_occupancy(available_input_dma);

        if( occ == PING_PONG_INPUT_BUFFER_COUNT ) {
            ping_pong_state = PP_PAUSED;
            if( entered_pause_function != 0 ) {
                entered_pause_function();
            }
        }
    }
}

void __attribute__((always_inline)) input_dma_process(void) {
    unsigned int occupancy;
    CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, occupancy);
    
#ifndef PING_PONG_DISABLE_RUN_TILL_LAST
    unsigned int status;
    CSR_READ(DMA_0_STATUS, status);
    bool recovered = _handle_recover_last(occupancy, status);
    if( recovered ) {
        CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, occupancy);
    }
#endif

    _update_transform_schedule(occupancy);
    _schedule_input_dma(occupancy);
}

#ifndef PING_PONG_DISABLE_OUTPUT
static void __attribute__((always_inline)) _update_output_schedule(const unsigned int available_dma) {
    int error;
    (void)error;

    error = circular_buf2_put(output_schedule, available_dma);
}
#endif

static void __attribute__((always_inline)) _update_available_input_dma(const unsigned int available_dma) {
    int error;
    (void)error;

    error = circular_buf2_put(available_input_dma, available_dma);
}

#ifndef PING_PONG_DISABLE_OUTPUT
void __attribute__((always_inline)) transform_process(void) {
    // int dma_error;
    int error;
    (void)error;
    // int transform_error;
    unsigned int available_dma;
    unsigned int available_transform;
    if (
           circular_buf2_peek(transform_schedule, &available_dma) != -1
        && circular_buf2_peek(available_transform_dma, &available_transform) != -1 ) {
        circular_buf2_drop(transform_schedule);
        circular_buf2_drop(available_transform_dma);
        if (available_dma == available_transform) {
            unsigned int* cpu_in = input_dma_buf_cpu[available_dma];
            unsigned int* cpu_out = transform_buf_cpu[available_dma];
            unsigned user_ret = transform_function(available_dma,
                                                   cpu_in,
                                                   cpu_out
                                                   );
            (void)user_ret;
            _update_output_schedule(available_dma);
            _update_available_input_dma(available_dma);
#ifdef PING_PONG_ENABLE_PRINT
            _printf("%s%d\n", "    TFM     ", available_dma);
#endif
        }
    }
}

#else

void __attribute__((always_inline)) transform_process_no_output(void) {
    // int dma_error;
    int error;
    (void)error;
    // int transform_error;
    unsigned int available_dma;
    // unsigned int available_transform;
    if (
           circular_buf2_peek(transform_schedule, &available_dma) != -1
        ) {
        circular_buf2_drop(transform_schedule);
        if (1) {
            unsigned int* cpu_in = input_dma_buf_cpu[available_dma];
            unsigned user_ret = transform_function(available_dma,
                                                   cpu_in,
                                                   0
                                                   );
            (void)user_ret;
            _update_available_input_dma(available_dma);
#ifdef PING_PONG_ENABLE_PRINT
            _printf("%s%d\n", "    TFM     ", available_dma);
#endif
        }
    }
}

#endif

#ifndef PING_PONG_DISABLE_OUTPUT
void __attribute__((always_inline)) _schedule_output_dma(const unsigned int out_occupancy) {
    if (out_occupancy < (PING_PONG_MAX_OUTPUT_OCCUPANCY)) {
        int error;
        unsigned int available_dma;
        error = circular_buf2_get(output_schedule, &available_dma);

        if (error != -1) {
            unsigned output_dma_address = transform_buf_addr[available_dma];
            unsigned output_dma_size = PING_PONG_BUFFER_SIZE_OUT;
            #ifdef PING_PONG_MODIFY_OUTPUT
            modify_output_function(&output_dma_address, &output_dma_size);
            #endif
#ifdef PING_PONG_USE_LAST_OUTPUT
            dma_block_send_finalized(output_dma_address, output_dma_size, 1);
#else
            dma_block_send(output_dma_address, output_dma_size);
#endif
            error = circular_buf2_put(output_dma_schedule, available_dma);
#ifdef PING_PONG_ENABLE_PRINT
            _printf("%s%d\n", "    ODMA    ", available_dma);
#endif
        }
    }
}
#endif

#ifndef PING_PONG_DISABLE_OUTPUT
void __attribute__((always_inline)) _update_available_transform(const unsigned int out_occupancy) {
    const int expected_output_occupancy = circular_buf2_occupancy(output_dma_schedule);
    const int occupancy_diff = expected_output_occupancy - (int)out_occupancy;

    if (occupancy_diff > 0) {
#ifdef PING_PONG_ENABLE_PRINT
    _printf("%s%d %s%d %s%d \n", "    ODMA -- ", out_occupancy,
            " ", expected_output_occupancy, " ", occupancy_diff);
#endif

        int error;
        unsigned int completed_output_dma;
        for (int i = 0; i < occupancy_diff; i++) {
            error = circular_buf2_get(output_dma_schedule,
                                      &completed_output_dma);
            if (error != -1) {
                circular_buf2_put(available_transform_dma,
                                  completed_output_dma); 
            } else {
                break;
            }
        }
    }
}
#endif


#pragma GCC diagnostic pop

#ifndef PING_PONG_DISABLE_OUTPUT
void output_dma_process(void) {
    unsigned int out_occupancy;
    CSR_READ(DMA_1_SCHEDULE_OCCUPANCY, out_occupancy);
    _schedule_output_dma(out_occupancy);
    CSR_READ(DMA_1_SCHEDULE_OCCUPANCY, out_occupancy);
    _update_available_transform(out_occupancy);
}
#endif

void ping_pong_request_pause(void) {
    ping_pong_state = PP_REQUEST_PAUSE;
}

void ping_pong_request_resume(void) {
    ping_pong_state = PP_NORMAL;
}


#endif

