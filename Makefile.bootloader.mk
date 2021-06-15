                    
# all must be set before include
Q_ENGINE_REPO=../q-engine
IP_LIBRARY_REPO=../ip-library
RISCV_BASEBAND_REPO=.
include $(Q_ENGINE_REPO)/scripts/make_include/verilog_paths.mk

# path should be relative to where this makefile is (repo root)
VER_CPP_INCLUDE_PATH=verilator/inc

VER_INCLUDE_DIRS=-I./hdl  -I.

VER_TOP=--top-module $(Q_ENGINE_VERILATOR_TOP) +define+VERILATE


# use sources for Q-Engine / VexRiscv
VER_SOURCES= $(Q_ENGINE_ALL_VERILOG)


THIS_FILE=Makefile.bootloader.mk
CPP_TB_FILES= verilator/tb_bootloader.cpp
C_PROJECT_NAME=bootloader_example


# this path is relative to where this makefile is because it gets expanded here and
# passed to verilator
CPP_TB_FILES+= $(wildcard $(VER_CPP_INCLUDE_PATH)/*.cpp)



C_SRC = ./c/$(C_PROJECT_NAME)/src
VER_FLAGS = -Wno-PINMISSING --trace  
VER_FLAGS += +define+SCALAR_ENGINE_PUBLIC_MEMORY=1 +define+VERILATOR_PUBLIC=1
VER_BINARY = Vq_engine




IBUS=SIMPLE
DBUS=SIMPLE
TRACE=YES
TRACE_ACCESS?=no
TRACE_START=0
ISA_TEST?=yes
MUL?=no
DIV?=yes
CSR?=yes
MMU?=no
DEBUG_PLUGIN?=no
DEBUG_PLUGIN_EXTERNAL?=no
CUSTOM_SIMD_ADD?=no
REDO?=1
REF=no
TRACE_WITH_TIME=no
REF_TIME=no
THREAD_COUNT=1

ADDCFLAGS += -CFLAGS -DIBUS_${IBUS}
ADDCFLAGS += -CFLAGS -DDBUS_${DBUS}
ADDCFLAGS += -CFLAGS -DREDO=${REDO}
ADDCFLAGS += -CFLAGS -pthread

# path is relative to obj_dir
ADDCFLAGS += -CFLAGS -I../c/inc
ADDCFLAGS += -CFLAGS -I../$(VER_CPP_INCLUDE_PATH)

ADDCFLAGS += -CFLAGS -DTHREAD_COUNT=${THREAD_COUNT}


ifeq ($(TRACE),yes)
	VERILATOR_ARGS += --trace
	ADDCFLAGS += -CFLAGS -DTRACE
endif

ifeq ($(CUSTOM_SIMD_ADD),yes)
	ADDCFLAGS += -CFLAGS -DCUSTOM_SIMD_ADD
endif

ifeq ($(TRACE_WITH_TIME),yes)
	ADDCFLAGS += -CFLAGS -DTRACE_WITH_TIME
endif

ifeq ($(REF_TIME),yes)
	ADDCFLAGS += -CFLAGS -DREF_TIME
endif

ifeq ($(TRACE_ACCESS),yes)
	ADDCFLAGS += -CFLAGS -DTRACE_ACCESS
endif

ifneq ($(DEBUG_PLUGIN),no)
	ADDCFLAGS += -CFLAGS -DDEBUG_PLUGIN
	ADDCFLAGS += -CFLAGS -DDEBUG_PLUGIN_${DEBUG_PLUGIN}
endif

ifeq ($(DEBUG_PLUGIN_EXTERNAL),yes)
	ADDCFLAGS += -CFLAGS -DDEBUG_PLUGIN_EXTERNAL
endif

ifeq ($(REF),yes)
	ADDCFLAGS += -CFLAGS -DREF
endif

ADDCFLAGS += -CFLAGS -DTRACE_START=${TRACE_START}
ifeq ($(FREERTOS),yes)
	ADDCFLAGS += -CFLAGS -DFREERTOS
endif

all: mif_style


mif_style: 
	$(MAKE) -f $(THIS_FILE) cleanall 
	$(MAKE) -f $(THIS_FILE) compile_hex compile_mif verilate
	$(MAKE) -f $(THIS_FILE) run TRACE=yes
	@echo "now do:"
	@echo "   make show"
	@echo ""

ben:
	echo $(THIS_FILE)


compile_hex: c/$(C_PROJECT_NAME)/build/atomic.hex

c/$(C_PROJECT_NAME)/build/atomic.hex: $(C_SRC)/main.c
	$(MAKE) -C c/$(C_PROJECT_NAME)


# warning I couldn't figure out how to make this check the date of all 4 files at once
compile_mif: scalar0.mif

scalar0.mif: c/$(C_PROJECT_NAME)/build/atomic.hex
	python scripts/hex2mif.py -i c/$(C_PROJECT_NAME)/build/atomic.hex -o0 scalar0.mif -o1 scalar1.mif -o2 scalar2.mif -o3 scalar3.mif

run_only:
	./obj_dir/$(VER_BINARY)

run: compile
	./obj_dir/$(VER_BINARY)

verilate:
	verilator $(VER_TOP) $(VER_FLAGS) $(VER_INCLUDE_DIRS) -cc  $(VER_SOURCES)  -O3 -CFLAGS -std=c++11 -LDFLAGS -pthread  ${ADDCFLAGS} --gdbbt ${VERILATOR_ARGS} -Wno-UNOPTFLAT -Wno-WIDTH --x-assign unique --exe $(CPP_TB_FILES)


compile: verilate
	make  -j  -C obj_dir/ -f $(VER_BINARY).mk $(VER_BINARY)

clean:
	rm -rf obj_dir
	rm -rf c/$(C_PROJECT_NAME)/build/*

cleanall: clean clean_mif

clean_mif:
	rm -rf scalar0.mif scalar1.mif scalar2.mif scalar3.mif

show:
	gtkwave ./testFirst.vcd -S verilator/riscv_regs_dma.tcl &
