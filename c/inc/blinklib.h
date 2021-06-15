#ifndef __BLINKLIB_H__
#define __BLINKLIB_H__

#define BLINKLIB_MAX_BLINK_CODES (4)

void setup_blinklib(void);
void setup_blinklib_timers(const unsigned int on_time, const unsigned int off_time, const unsigned int wait_1, const unsigned int wait_2);
void pet_blinklib(void);
void blinklib_status(const unsigned int status);
void blinklib_delta_status(const unsigned int status);
unsigned int blinklib_times_shown(void);

// looks like this was built to support 4 blink codes, however was later simplified
// to only 1

#endif