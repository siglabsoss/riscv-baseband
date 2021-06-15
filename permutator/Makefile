all: build verilate compile run show

clean:
	rm hdl/*
	rm -rf obj_dir

build:
	./bin/templer.js --source templates/ --output templates.js && ./bin/gen.js

verilate:
	verilator \
	--trace \
	-cc \
	-O3 \
	--top-module permutator \
	--exe hdl/tb.cpp \
	hdl/*.v

compile: verilate
	make -j -C obj_dir/ -f Vpermutator.mk Vpermutator

run:
	./obj_dir/Vpermutator

show:
	gtkwave ./permutator.vcd -S hdl/top-wave.tcl &
