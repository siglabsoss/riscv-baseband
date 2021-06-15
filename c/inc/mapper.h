#ifndef __MAPPER_H__
#define __MAPPER_H__
#include "apb_bus.h"
#include "table.h"
#include "xbaseband.h"

Table mapper_qpsk_table(unsigned int t_addr);

Table mapper_qpsk_table_gain(unsigned int t_addr, short gain);

Table mapper_bpsk_table(unsigned int t_addr);

Table mapper_debug_qpsk_table(unsigned int t_addr);


void mapper_load_qpsk(Table * table, unsigned int dest_raddr, unsigned int src_addr);

void mapper_rload_bpsk(Table * table, unsigned int dest_raddr, unsigned int src_addr);

void mapper_lload_bpsk(Table * table, unsigned int dest_raddr, unsigned int src_addr);


#endif /* __MAPPER_H__ */