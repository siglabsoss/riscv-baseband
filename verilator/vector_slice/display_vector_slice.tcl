lappend system "clk"
lappend system "srst"




set num_added [ gtkwave::addSignalsFromList $system ]

gtkwave::/Edit/Insert_Comment "--- opcode ---"

lappend bundle0 "vector_slice.s_src1"
lappend bundle0 "vector_slice.s_kscratch"
lappend bundle0 "vector_slice.s_src2"
lappend bundle0 "vector_slice.s_xsrc"
lappend bundle0 "vector_slice.s_funct"
lappend bundle0 "vector_slice.s_dest"
lappend bundle0 "vector_slice.s_xrs"

set num_added [ gtkwave::addSignalsFromList $bundle0 ]

gtkwave::/Edit/Insert_Comment "--- V-Regs ---"

# so, it seems like we MUST use absolute paths with array types
# however for non array types we can ommit the TOP

lappend bundle1 "TOP.vector_slice.vreg(0)"
lappend bundle1 "TOP.vector_slice.vreg(1)"
lappend bundle1 "TOP.vector_slice.vreg(2)"
lappend bundle1 "TOP.vector_slice.vreg(3)"
lappend bundle1 "TOP.vector_slice.vreg(4)"
lappend bundle1 "TOP.vector_slice.vreg(5)"
lappend bundle1 "TOP.vector_slice.vreg(6)"
lappend bundle1 "TOP.vector_slice.vreg(7)"


set num_added [ gtkwave::addSignalsFromList $bundle1 ]




gtkwave::/Edit/Insert_Comment "--- K-Regs ---"

lappend bundle2 "vector_slice.k15_reg"

set num_added [ gtkwave::addSignalsFromList $bundle2 ]


# gtkwave::/Edit/Insert_Comment "--- writeback ---"

# lappend writeback "VexRiscv.writeBack_PC"

# set num_added [ gtkwave::addSignalsFromList $writeback ]



# gtkwave::/Edit/Insert_Comment "--- Regs ---"
# lappend regs VexRiscv.RegFilePlugin_regFile(0)
# lappend regs VexRiscv.CsrPlugin_exception
# set num_added [ gtkwave::addSignalsFromList $regs ]




gtkwave::setZoomFactor -4
