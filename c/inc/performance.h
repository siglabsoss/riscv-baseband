#ifndef __PERFORMANCE_H__
#define __PERFORMANCE_H__

void _setup_perf(void);

void _perf_mark(unsigned int i);

// this must be the first thing the run loop does
void _perf_top_idle_loop(void);

// ignores results until the next top of loop
void _perf_invalidate(void);

void _perf_work(void);

// defaults to 4
// how many "works" to average over
void _perf_set_acumulation_period(unsigned int p);

#endif