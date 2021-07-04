#ifndef VEX_HPP
#define VEX_HPP

#include <iostream>

#include "Vvector_slice.h"
#include "Vvector_slice_vector_slice.h"
#include <stdint.h>

#include "model/src/models/slice_constants.hpp"
#include "model/src/models/slice.hpp"

#if VM_TRACE
# include <verilated_vcd_c.h>
#endif

class Vex : public Vvector_slice {
private:

	int main_time;

	void clearer();

	void setter(uint64_t combined);

	uint16_t vregs[NREGS];
	uint16_t k15;

	VerilatedVcdC *tfp;

	void tick(int val = 1);

public:

	Vex();

	void initialize(VerilatedVcdC *tfp);

	void reset(int t = 1);

	void set_time(int t);

	void set_left(int t);

	void set_right(int t);

	uint16_t get_vexreg(int i);

	bool get_ready();

	void mv(uint16_t xrs1_import, int dest, int src_2);

	void mv_x_v(uint16_t xrs1_import, int dest);

	void mv_V_K15(int src_2);

	void mv_k15_V(uint16_t xrs1_import, int dest);

	void rol(uint16_t xrs1_import, int dest);

	void ror(uint16_t xrs1_import, int dest);

	void vadd(uint16_t xrs1_import, int dest, int src_1, int src_2);

	void vsub(uint16_t xrs1_import, int dest, int src_1, int src_2);

	void vor(uint16_t xrs1_import, int dest, int src_1, int src_2);

	void vxor(uint16_t xrs1_import, int dest, int src_1, int src_2);

	void vand(uint16_t xrs1_import, int dest, int src_1, int src_2);

	void posedge(int val);

	bool verify();

	bool test();

	void print_all_regs(void);

	void print_regs(void);

	void print_k_regs(void);

	void reset_regs_sequence();

};

#endif
