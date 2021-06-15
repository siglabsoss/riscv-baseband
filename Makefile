
# all must be set before include
Q_ENGINE_REPO=../q-engine
IP_LIBRARY_REPO=../ip-library
RISCV_BASEBAND_REPO=.
DATAPATH_REPO=../datapath
include $(Q_ENGINE_REPO)/scripts/make_include/verilog_paths.mk
include $(RISCV_BASEBAND_REPO)/scripts/make_include/strip_public.mk

# path should be relative to where this makefile is (repo root)
VER_CPP_INCLUDE_PATH=verilator/inc

VER_INCLUDE_DIRS=-I./hdl  -I.

VER_TOP=--top-module $(Q_ENGINE_VERILATOR_TOP) +define+VERILATE


# use sources for Q-Engine / VexRiscv
VER_SOURCES= $(Q_ENGINE_ALL_VERILOG)


THIS_FILE=Makefile
CPP_TB_FILES=verilator/tb_riscv_dma.cpp
C_PROJECT_NAME=first_try
C_SRC = ./c/$(C_PROJECT_NAME)/src
VER_FLAGS = -Wno-PINMISSING --trace  

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


compile_hex: c/$(C_PROJECT_NAME)/build/atomic.hex

c/$(C_PROJECT_NAME)/build/atomic.hex: $(C_SRC)/main.c
	$(MAKE) -C c/$(C_PROJECT_NAME)


# warning I couldn't figure out how to make this check the date of all 4 files at once
compile_mif: scalar0.mif

scalar0.mif: c/$(C_PROJECT_NAME)/build/atomic.hex
	python scripts/hex2mif.py -i c/$(C_PROJECT_NAME)/build/atomic.hex -o0 scalar0.mif -o1 scalar1.mif -o2 scalar2.mif -o3 scalar3.mif

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
	$(MAKE) -C c/$(C_PROJECT_NAME) clean

clean_mif:
	rm -rf scalar0.mif scalar1.mif scalar2.mif scalar3.mif

show:
	gtkwave ./testFirst.vcd -S verilator/riscv_regs_dma.tcl &





################## Sub Makes ##################
#
#  We seem to be making our own custom makefiles, so this way we can just
#  keep them all in the same dir with different names, and then call them

torture:
	make -f Makefile.torture.mk all_test


bootloader:
	make -f Makefile.bootloader.mk

genriscv:
	cp scala/DemapperCsrPlugin.scala VexRiscv/src/main/scala/vexriscv/plugin/
	cp scala/DEngineCsrPlugin.scala VexRiscv/src/main/scala/vexriscv/plugin/
	cp scala/CsrPlugin.scala VexRiscv/src/main/scala/vexriscv/plugin/
	cp scala/GenericOutCsrPlugin.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/SatDetectCsrPlugin.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/ControlStatusCsrPlugin.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/MapperMoverCsrPlugin.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/InterruptCsrPlugin.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/TimerCsrPlugin.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/DmaCsrPlugin.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/GpioCsrPlugin.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/MuraxUtiles.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/RingBusCsrPlugin.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/NCOCsrPlugin.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/Xbaseband.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/XbbVectorCordic.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/XbbRiscv.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/Briey.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/Murax.scala VexRiscv/src/main/scala/vexriscv/demo/
	cp scala/Services.scala VexRiscv/src/main/scala/vexriscv/
	cp scala/XbbRiscvUtiles.scala VexRiscv/src/main/scala/vexriscv/demo/
	cd VexRiscv  &&	sbt "run-main vexriscv.demo.XbbRiscv"
	cp VexRiscv/XbbRiscv.v hdl/generated/
	cd VexRiscv  &&	sbt "run-main vexriscv.demo.XbbRiscvWithRam"
	rm -f hdl/generated/VexRiscv.v
	sed -i 's| \?/\* \?verilator public \?\*/ \?||g' hdl/generated/XbbRiscv.v
	#sed -i 's|wire \[31:0\] writeBack_PC;|wire \[31:0\] writeBack_PC;\n  define CUSTOM_VERILATOR_PUBLIC_32(sig) function[31:0] get_`sig``; /verilator public/   begin   get_``sig`` = sig;   end endfunction  \n   ifdef VERILATE_DEF \n    CUSTOM_VERILATOR_PUBLIC_32(writeBack_PC)  \n `endif \n  |g'   hdl/generated/XbbRiscv.v
	cat hdl/generated/XbbRiscv.v | sed 's/\(ram \[.*\);/\1 \/\* synthesis syn_ramstyle = "registers" \*\/;/' > hdl/generated/XbbRiscvNoEBR.v
