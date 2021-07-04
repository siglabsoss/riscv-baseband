lappend system "clk"
lappend system "reset"

set num_added [ gtkwave::addSignalsFromList $system ]

gtkwave::/Edit/Insert_Comment "--- iBus ---"

lappend iBus "VexRiscv.iBus_cmd_valid"
lappend iBus "VexRiscv.iBus_cmd_ready"
lappend iBus "VexRiscv.iBus_cmd_payload_pc"
lappend iBus "VexRiscv.iBus_rsp_ready"
lappend iBus "VexRiscv.iBus_rsp_error"
lappend iBus "VexRiscv.iBus_rsp_inst"

set num_added [ gtkwave::addSignalsFromList $iBus ]

gtkwave::/Edit/Insert_Comment "--- dBus ---"

lappend dBus "VexRiscv.dBus_cmd_valid"
lappend dBus "VexRiscv.dBus_cmd_ready"
lappend dBus "VexRiscv.dBus_cmd_payload_wr"
lappend dBus "VexRiscv.dBus_cmd_payload_address"
lappend dBus "VexRiscv.dBus_cmd_payload_data"
lappend dBus "VexRiscv.dBus_cmd_payload_size"
lappend dBus "VexRiscv.dBus_rsp_ready"
lappend dBus "VexRiscv.dBus_rsp_error"
lappend dBus "VexRiscv.dBus_rsp_data"

set num_added [ gtkwave::addSignalsFromList $dBus ]

gtkwave::/Edit/Insert_Comment "--- writeback ---"

lappend writeback "VexRiscv.writeBack_PC"

set num_added [ gtkwave::addSignalsFromList $writeback ]



# gtkwave::/Edit/Insert_Comment "--- Regs ---"
# lappend regs VexRiscv.RegFilePlugin_regFile(0)
# lappend regs VexRiscv.CsrPlugin_exception
# set num_added [ gtkwave::addSignalsFromList $regs ]




gtkwave::setZoomFactor -2
