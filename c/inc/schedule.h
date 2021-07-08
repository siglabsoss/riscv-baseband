#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#define SCHEDULE_SLOTS (50)
#define SCHEDULE_LENGTH (512)
#define SCHEDULE_LENGTH_BITS (9)
#define SCHEDULE_FRAMES ((SCHEDULE_SLOTS)*(SCHEDULE_LENGTH))


#include <stdint.h>

typedef struct schedule_t {
    uint32_t s[SCHEDULE_SLOTS];
    uint32_t id; // our id
    uint32_t id_mask; // our id as a mask
    // uint32_t offset; // offset to a counter
    uint32_t epoc_time; // not an offset, actual epoc seconds, this gets changed inside get_timeslot2
} schedule_t;

typedef struct epoc_frame_t {
    uint32_t epoc;
    uint32_t frame;
} epoc_frame_t;

typedef struct epoc_timeslot_t {
    uint32_t epoc;
    uint32_t timeslot;
} epoc_timeslot_t;

void default_schedule(schedule_t *o);
void schedule_all_on(schedule_t *o);

void set_id(schedule_t *o, const uint32_t id);

void schedule_get_timeslot2(
    schedule_t* const o,
    const uint32_t counter,
    uint32_t* const progress,
    uint32_t* const accumulated_progress, 
    uint32_t* const timeslot, 
    uint32_t* const epoc, 
    uint32_t* const can_tx);

epoc_timeslot_t schedule_frame_to_timeslot(const epoc_frame_t y);


#ifndef VERILATE_TESTBENCH

//////////////////////////////////////////
//
// Vex functions
//


#else

// #include "cpp_utils.hpp"
// #include <assert.h>

//////////////////////////////////////////
//
// TestBench / S-Modem functions
//
void print_epoc_frame_t(const epoc_frame_t& f);

epoc_frame_t adjust_frames_to_schedule(const epoc_frame_t& old, const int64_t frames);
epoc_frame_t add_frames_to_schedule(const epoc_frame_t& old, const uint32_t frames);
long unsigned schedule_to_pure_frames(const epoc_frame_t& a);
epoc_frame_t pure_frames_to_epoc_frame(const long unsigned frames);
long schedule_delta_frames(const epoc_frame_t& a, const epoc_frame_t& b);


#endif

#endif