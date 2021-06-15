
Q_ENGINE_REPO=../q-engine


VER_INCLUDE_DIRS=-I./hdl  -I.

VER_TOP=--top-module riscv_baseband +define+VERILATE

# VER_SOURCES= ./hdl/generated/VexRiscv.v
VER_SOURCES= ./hdl/generated/VexRiscv.v ./hdl/top/riscv_qengine_top.sv \
$(Q_ENGINE_REPO)/hdl/dpram.sv \
$(Q_ENGINE_REPO)/hdl/scalar_memory.sv \
$(Q_ENGINE_REPO)/hdl/apb_decode.sv \
$(Q_ENGINE_REPO)/hdl/dma/dma_in.sv \
$(Q_ENGINE_REPO)/hdl/dma/dma_in_peripheral.sv \
$(Q_ENGINE_REPO)/hdl/dma/dma_out.sv \
$(Q_ENGINE_REPO)/hdl/dma/dma_out_peripheral.sv \
$(Q_ENGINE_REPO)/hdl/elastic_dpram.sv \
$(Q_ENGINE_REPO)/hdl/arbiter.sv \
$(Q_ENGINE_REPO)/hdl/q_engine.sv

VER_FLAGS = -Wno-PINMISSING --trace  

VER_BINARY = Vriscv_baseband

THIS_FILE=Makefile.xbb.mk

CPP_PROJECT_NAME=first_try


CPP_TB_NAME = verilator/tb_capture_xbb.cpp




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
	$(MAKE) cleanall 
	$(MAKE) compile_hex compile_mif verilate
	$(MAKE) run TRACE=yes
	@echo "now do:"
	@echo "   make show"
	@echo ""



compile_hex: cpp/$(CPP_PROJECT_NAME)/build/atomic.hex

cpp/$(CPP_PROJECT_NAME)/build/atomic.hex: cpp/$(CPP_PROJECT_NAME)/src/crt.S cpp/$(CPP_PROJECT_NAME)/src/main.c
	$(MAKE) -C cpp/$(CPP_PROJECT_NAME)


# warning I couldn't figure out how to make this check the date of all 4 files at once
compile_mif: scalar0.mif

scalar0.mif: cpp/$(CPP_PROJECT_NAME)/build/atomic.hex
	python scripts/hex2mif.py -i cpp/$(CPP_PROJECT_NAME)/build/atomic.hex -o0 scalar0.mif -o1 scalar1.mif -o2 scalar2.mif -o3 scalar3.mif

run: compile
	./obj_dir/$(VER_BINARY)

verilate:
	verilator $(VER_TOP) $(VER_FLAGS) $(VER_INCLUDE_DIRS) -cc  $(VER_SOURCES)  -O3 -CFLAGS -std=c++11 -LDFLAGS -pthread  ${ADDCFLAGS} --gdbbt ${VERILATOR_ARGS} -Wno-UNOPTFLAT -Wno-WIDTH --x-assign unique --exe $(CPP_TB_NAME)


compile: verilate
	make  -j  -C obj_dir/ -f Vriscv_baseband.mk Vriscv_baseband

clean:
	rm -rf obj_dir

cleanall: clean clean_mif
	$(MAKE) -C cpp/$(CPP_PROJECT_NAME) clean

clean_mif:
	rm -rf scalar0.mif scalar1.mif scalar2.mif scalar3.mif

show:
	gtkwave ./testFirst.vcd -S verilator/gtkwave.tcl &



