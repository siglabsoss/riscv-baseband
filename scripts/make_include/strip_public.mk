##################
#
#  strips the public out of hdl/generated/VexRiscv.v
# 

STRIP_SOURCE:=$(RISCV_BASEBAND_REPO)/hdl/generated/VexRiscvUntouched.v
STRIP_DEST:=$(RISCV_BASEBAND_REPO)/hdl/generated/VexRiscv.v

######
#
# we use | for this regex so that / works normally
# note we have to escape ? as \?
#                        * as \*
#  
strip: $(STRIP_SOURCE)
	@echo ""
	sed 's| \?/\* \?verilator public \?\*/ \?||g' < $(STRIP_SOURCE) > $(STRIP_DEST)
	@echo ""
	@echo "Removed /* verilator public */"
	@echo "from: $(STRIP_SOURCE)"
	@echo "  to: $(STRIP_DEST)"
	@echo ""

