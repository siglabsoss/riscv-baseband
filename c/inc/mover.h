#ifndef __MOVER_H__
#define __MOVER_H__

#include "table.h"
#include "xbaseband.h"
#include "vmem.h"

typedef struct {
    int src_addr;
    int src_add;
    int dst_addr;
    int dst_add;
} Schedule;

typedef struct {
    unsigned int src_addr[16];
    unsigned int src_add[16];
    unsigned int dst_addr[16];
    unsigned int dst_add[16];
} VmemSchedule;

void mover_load_offset_input(const VmemSchedule* const schedule, const unsigned int input_offset_row);

void mover_load_offset_output(const VmemSchedule* const schedule, const unsigned int output_offset);

void mover_load_vmem(const VmemSchedule* const schedule);

void mover_schedule(const Schedule* const schedule, const unsigned int scratch_addr);

void mover_roll(const unsigned int lines);

void mover_unroll(const unsigned int lines);

unsigned int mover_debug_load_qpsk(const unsigned int values[16]);

void mover_load_vmem_row_single(const VmemSchedule* const schedule, const unsigned int input_row);
void mover_load_vmem_offset_input_single(const VmemSchedule* const schedule, const unsigned int input_offset_row);

void mover_copy(const unsigned int input_data, const unsigned int output_data, const unsigned int size);

void mover_roll2(const VmemSchedule* const schedule, const unsigned int schedules);
void mover_roll3(const VmemSchedule* const schedule, const unsigned int schedules);


typedef struct {
    unsigned b00:1;
    unsigned b01:1;
    unsigned b02:1;
    unsigned b03:1;
    unsigned b04:1;
    unsigned b05:1;
    unsigned b06:1;
    unsigned b07:1;
    unsigned b08:1;
    unsigned b09:1;
    unsigned b10:1;
    unsigned b11:1;
    unsigned b12:1;
    unsigned b13:1;
    unsigned b14:1;
    unsigned b15:1;
} __attribute__((packed)) bitfield16_t;


#endif /* __MOVER_H__ */