######################################################################
#
# DESCRIPTION: Verilator Example: Small Makefile
#
# This calls the object directory makefile.  That allows the objects to
# be placed in the "current directory" which simplifies the Makefile.
#
# Copyright 2003-2018 by Wilson Snyder. This program is free software; you can
# redistribute it and/or modify it under the terms of either the GNU
# Lesser General Public License Version 3 or the Perl Artistic License
# Version 2.0.
#
######################################################################
# Check for sanity to avoid later confusion

ifneq ($(words $(CURDIR)),1)
 $(error Unsupported: GNU Make cannot build in directories containing spaces, build elsewhere: '$(CURDIR)')
endif

######################################################################
# Set up variables

# If $VERILATOR_ROOT isn't in the environment, we assume it is part of a
# package inatall, and verilator is in your path. Otherwise find the
# binary relative to $VERILATOR_ROOT (such as when inside the git sources).
ifeq ($(VERILATOR_ROOT),)
VERILATOR = verilator
VERILATOR_COVERAGE = verilator_coverage
else
export VERILATOR_ROOT
VERILATOR = $(VERILATOR_ROOT)/bin/verilator
VERILATOR_COVERAGE = $(VERILATOR_ROOT)/bin/verilator_coverage
endif

VERILATOR_FLAGS =
# Generate C++ in executable form
VERILATOR_FLAGS += -cc --exe
# Generate makefile dependencies (not shown as complicates the Makefile)
#VERILATOR_FLAGS += -MMD
# Optimize
VERILATOR_FLAGS += -O2 -x-assign 0
# Warn abount lint issues; may not want this on less solid designs
VERILATOR_FLAGS += -Wall -Wno-WIDTH -Wno-UNDRIVEN -Wno-PINCONNECTEMPTY -Wno-PINMISSING -Wno-ASSIGNDLY -Wno-DECLFILENAME -Wno-UNUSED -Wno-UNOPTFLAT
# Make waveforms
VERILATOR_FLAGS += --trace
# Check SystemVerilog assertions
VERILATOR_FLAGS += --assert
# Generate coverage analysis
# VERILATOR_FLAGS += --coverage
# Run Verilator in debug mode
#VERILATOR_FLAGS += --debug
# Add this trace to get a backtrace in gdb
#VERILATOR_FLAGS += --gdbbt

######################################################################
default: run

.PHONY : clean run all wave show mwave show-config maintainer-copy

all: run 

run:
	
	@echo
	@echo "-- VERILATE ----------------"
	
	$(VERILATOR) $(VERILATOR_FLAGS) \
	tb_vector_slice.cpp	\
	--top-module vector_slice +define+VERILATE \
	-I../../hdl/vectorslice/ \
	./Vex.cpp \
	../../hdl/vectorslice/vector_slice.sv
	
	@echo
	@echo "-- COMPILE -----------------"	
	$(MAKE) -j 4 -C obj_dir -f ../Makefile_obj
	
	@echo
	@echo "-- RUN ---------------------"
	@mkdir -p logs
	obj_dir/Vvector_slice +trace=1

	# @echo
	# @echo "-- COVERAGE ----------------"
	# $(VERILATOR_COVERAGE) --annotate logs/annotated logs/coverage.dat


show: wave

wave:
	@echo "Bringing up logs/vlt_dump.vcd in gtkwave"
	gtkwave logs/vlt_dump.vcd -S display_vector_slice.tcl &

mwave:
	@echo "Converting vcd to wlf"
	vcd2wlf logs/vlt_dump.vcd logs/vlt_dump.wlf
	vsim -gui -wlf logs/vlt_dump.wlf
	


######################################################################
# Other targets

show-config:
	$(VERILATOR) -V

maintainer-copy::
clean mostlyclean distclean maintainer-clean::
	-rm -rf obj_dir logs *.log *.dmp *.vpd coverage.dat core
