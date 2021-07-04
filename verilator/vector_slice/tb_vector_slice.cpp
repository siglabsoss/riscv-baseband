// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed into the Public Domain, for any use,
// without warranty, 2017 by Wilson Snyder.
//======================================================================

// Include common routines
#include <verilated.h>

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

#include <sys/stat.h>  // mkdir

// Include model header, generated from Verilating "top.v"
#include "Vvector_slice.h"
#include "Vvector_slice_vector_slice.h"
#include "Vex.hpp"

#define VM_TRACE 1

// If "verilator --trace" is used, include the tracing class
#if VM_TRACE
# include <verilated_vcd_c.h>
#endif

// Current simulation time (64-bit unsigned)
vluint64_t main_time = 0;
// Called by $time in Verilog
double sc_time_stamp () {
    return main_time; // Note does conversion to real, to match SystemC
}


int main(int argc, char** argv, char** env) {
    // This is a more complicated example, please also see the simpler examples/hello_world_c.

    // Prevent unused variable warnings
    if (0 && argc && argv && env) {}
    // Pass arguments so Verilated code can see them, e.g. $value$plusargs
//    Verilated::commandArgs(argc, argv);

    // Set debug level, 0 is off, 9 is highest presently used
    Verilated::debug(0);

    // Randomization reset policy
    Verilated::randReset(2);

//    // Construct the Verilated model, from Vtop.h generated from Verilating "top.v"
//    Vvector_slice* top = new Vvector_slice; // Or use a const unique_ptr, or the VL_UNIQUE_PTR wrapper

      Vex* top = new Vex;

#if VM_TRACE
    // If verilator was invoked with --trace argument,
    // and if at run time passed the +trace argument, turn on tracing
    VerilatedVcdC* tfp = NULL;
//    const char* flag = Verilated::commandArgsPlusMatch("trace");
    if (1) {
        Verilated::traceEverOn(true);  // Verilator must compute traced signals
        VL_PRINTF("Enabling waves into logs/vlt_dump.vcd...\n");
        tfp = new VerilatedVcdC;
        top->trace(tfp, 99);  // Trace 99 levels of hierarchy
        mkdir("logs", 0777);
        tfp->open("logs/vlt_dump.vcd");  // Open the dump file
    }
#endif

    // Set some inputs
    top->initialize(tfp);

    top->set_left(0xad00);
    top->set_right(0xc0de);
    top->reset(5);
    top->posedge(5);

    top->reset_regs_sequence();

    for(int i; i < NREGS; i++) {
        assert(top->vector_slice->vreg[i] == 0 && "reset_regs_sequence() not working");
    }

    // top->print_regs();
    top->mv_x_v(0xF, 0x0);
    assert(top->vector_slice->vreg[0] == 0xf && "mv_x_v didn't work");


	top->mv_x_v(0x1312, 0x1);
	top->mv_x_v(0x1, 0x2);
	top->rol(0x1, 0x3);
	top->ror(0x1, 0x4);
	top->vadd(0x1, 0x5, 0x1, 0x2);
	top->mv_V_K15(0x5);

    top->print_all_regs();

	top->mv_k15_V(0x1,0x6);
	top->mv(0x1,0x7, 0x3);
	top->verify();
	top->vand(0x1, 0x1, 0x3, 0x0);
	top->vor(0x1, 0x2, 0x1, 0x2);
	top->vsub(0x1, 0x3, 0x5, 0x7);
	top->vxor(0x1, 0x4, 0x2, 0x3);
	top->posedge(5);
	top->verify();


	// Read outputs
//	VL_PRINTF ("[%" VL_PRI64 "d] clk=%x srst=%x iquad=%" VL_PRI64 "x"
//			   " -> oquad=%" VL_PRI64"x owide=%x_%08x_%08x\n",
//			   main_time, top->clk, top->srst);


    // Final model cleanup
    top->final();

    // Close trace if opened
#if VM_TRACE
    if (tfp) { tfp->close(); }
#endif

    //  Coverage analysis (since test passed)
#if VM_COVERAGE
    mkdir("logs", 0777);
    VerilatedCov::write("logs/coverage.dat");
#endif

    // Destroy model
    delete top; top = NULL;

    // Fin
    exit(0);
}
