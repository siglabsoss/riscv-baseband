#include "schedule.h"
#include "feedback_bus.h" // for feedback_peer_to_mask()

#ifndef VERILATE_TESTBENCH

#include "csr_control.h"

#else

#include <iostream>

#endif


void default_schedule(schedule_t *o) {

    set_id(o, 1);
    for(uint32_t i = 0; i < SCHEDULE_SLOTS; i++) {
        if(i < 5) {
            o->s[i] = o->id_mask; // us
        } else {
            o->s[i] = 0; // nobody
        }
        // o->s[i] = 0; // nobody
    }
}

void schedule_all_on(schedule_t *o) {

    set_id(o, 1);
    for(uint32_t i = 0; i < SCHEDULE_SLOTS; i++) {
        // if(i < 5) {
            o->s[i] = o->id_mask; // us
        // } else {
        //     o->s[i] = 0; // nobody
        // }
        // o->s[i] = 0; // nobody
    }
}



// sets id and mask
void set_id(schedule_t *o, const uint32_t id) {
    o->id = id;
    o->id_mask = feedback_peer_to_mask(id);
    // SET_REG(x4, 0x1234);
    // SET_REG(x4, feedback_peer_to_mask(id));
    // SET_REG(x4, o->id_mask);
}

void schedule_get_timeslot2(
    schedule_t* const o,
    const uint32_t counter,
    uint32_t* const progress,
    uint32_t* const accumulated_progress,
    uint32_t* const timeslot,
    uint32_t* const epoc,
    uint32_t* const can_tx ) {
    const uint32_t now = counter; // + o->offset;

    // expensive, how to avoid?
    const uint32_t sample = now % SCHEDULE_FRAMES;

    // which sample did the current schedule start at?
    const uint32_t counter_schedule_start = counter - sample;
    // SET_REG(x3, sample);

    *timeslot = sample >> SCHEDULE_LENGTH_BITS; // same as divide by SCHEDULE_LENGTH

    // what sample did the timeslot start on
    const uint32_t start = (*timeslot * SCHEDULE_LENGTH) + counter_schedule_start;

    *progress = counter - start;

    // bump at 0/0 that way we can always return the value that is in the struct
    if(
        *timeslot == 0
        && *progress == 0 ) {
        o->epoc_time++;
    }

    *epoc = o->epoc_time;

    if(o->s[*timeslot] & o->id_mask) {
        *can_tx = 1;
    } else {
        *can_tx = 0;
    }

    *accumulated_progress = sample;
}

epoc_timeslot_t schedule_frame_to_timeslot(const epoc_frame_t y) {
    epoc_timeslot_t x;

    x.epoc = y.epoc;
    x.timeslot = y.frame / SCHEDULE_LENGTH;
    return x;
}



#ifndef VERILATE_TESTBENCH

//////////////////////////////////////////
//
// Vex functions
//


#else

//////////////////////////////////////////
//
// TestBench / S-Modem functions
//

void print_epoc_frame_t(const epoc_frame_t& f) {
    std::cout << "Frame Type:\n";
    std::cout << "      epoc: " << f.epoc << "\n";
    std::cout << "     frame: " << f.frame << "\n";

    // std::cout << " Frame :" << f.
}

// accepts positive or negative values
// even more lazy code
// epoc_frame_t adjust_frames_to_schedule(epoc_frame_t& old, int32_t frames) {
    
//     epoc_frame_t ret = old;

//     // lazy
//     while( frames < 0 ) {
//         frames += SCHEDULE_FRAMES;
//         ret.epoc--;
//     }



//     return add_frames_to_schedule(ret, frames);
// }

epoc_frame_t adjust_frames_to_schedule(const epoc_frame_t& old, const int64_t frames) {
    
    epoc_frame_t ret = old;

    if(frames == 0) {
        return ret;
    }

    const int sign = (frames < 0) ? -1 : 1;

    if( sign == 1 ) {
        for(int64_t i = 0; i < frames; i++) {

            if(ret.frame == (SCHEDULE_FRAMES-1) ) {
                ret.epoc += 1;
                ret.frame = 0;
            } else {
                ret.frame++;
            }

        }
    }

    if( sign == -1 ) {
        for(int64_t i = 0; i > frames; i--) {

            if(ret.frame == 0) {
                ret.epoc += 1;
                ret.frame += SCHEDULE_FRAMES;
            } 

            ret.frame--;
        }
    }

    


    // lazy
    // while( frames < 0 ) {
    //     frames += SCHEDULE_FRAMES;
    //     ret.epoc--;
    // }


    return ret;
    // return add_frames_to_schedule(ret, frames);
}

// returns a - b
long schedule_delta_frames(const epoc_frame_t& a, const epoc_frame_t& b) {
    // long unsigned 
    return (long)schedule_to_pure_frames(a) - (long)schedule_to_pure_frames(b);
}

long unsigned schedule_to_pure_frames(const epoc_frame_t& a) {
    // long unsigned ret = 0;

    return ((long unsigned)a.epoc * (long unsigned)SCHEDULE_FRAMES) + (long unsigned)a.frame;
}

epoc_frame_t pure_frames_to_epoc_frame(const long unsigned frames) {
    epoc_frame_t ret;

    const long unsigned r0 = frames / (long unsigned)SCHEDULE_FRAMES;
    const long unsigned r1 = frames % (long unsigned)SCHEDULE_FRAMES;

    ret.epoc = r0;
    ret.frame = r1;

    return ret;
}

// only accepts positive values
epoc_frame_t add_frames_to_schedule(const epoc_frame_t& old, const uint32_t frames) {
    return adjust_frames_to_schedule(old, (int32_t)frames);
}



#endif
