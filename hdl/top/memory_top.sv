module top #(
    parameter AWIDTH = 13,
    parameter DEPTH  = (1 << AWIDTH)
) (
    input           timerInterrupt,
    input           externalInterrupt,

    input           debug_bus_cmd_valid,
    output          debug_bus_cmd_ready,
    input           debug_bus_cmd_payload_wr,
    input  [7:0]    debug_bus_cmd_payload_address,
    input  [31:0]   debug_bus_cmd_payload_data,
    output [31:0]   debug_bus_rsp_data,
    output          debug_resetOut,

    output          xbaseband_cmd_valid,
    input           xbaseband_cmd_ready,
    output [31:0]   xbaseband_cmd_payload_instruction,
    output [31:0]   xbaseband_cmd_payload_rs1,

    input           clk,
    input           reset,
    input           debugReset
);

logic           iBus_cmd_valid;
logic           iBus_cmd_ready;
logic   [31:0]  iBus_cmd_payload_pc;
logic           iBus_rsp_ready;
logic           iBus_rsp_error;
logic   [31:0]  iBus_rsp_inst;

assign iBus_rsp_error = 1'b0;

logic           dBus_cmd_valid;
logic           dBus_cmd_ready;
logic           dBus_cmd_payload_wr;
logic   [31:0]  dBus_cmd_payload_address;
logic   [31:0]  dBus_cmd_payload_data;
logic   [1:0]   dBus_cmd_payload_size;
logic           dBus_rsp_ready;
logic           dBus_rsp_error;
logic   [31:0]  dBus_rsp_data;

assign dBus_rsp_error = 1'b0;

VexRiscv VexRiscv (
    .timerInterrupt                 (timerInterrupt),
    .externalInterrupt              (externalInterrupt),

    .debug_bus_cmd_valid            (debug_bus_cmd_valid),
    .debug_bus_cmd_ready            (debug_bus_cmd_ready),
    .debug_bus_cmd_payload_wr       (debug_bus_cmd_payload_wr),
    .debug_bus_cmd_payload_address  (debug_bus_cmd_payload_address),
    .debug_bus_cmd_payload_data     (debug_bus_cmd_payload_data),
    .debug_bus_rsp_data             (debug_bus_rsp_data),
    .debug_resetOut                 (debug_resetOut),

    .iBus_cmd_valid                 (iBus_cmd_valid),
    .iBus_cmd_ready                 (iBus_cmd_ready),
    .iBus_cmd_payload_pc            (iBus_cmd_payload_pc),

    .iBus_rsp_ready                 (iBus_rsp_ready),
    .iBus_rsp_inst                  (iBus_rsp_inst),
    .iBus_rsp_error                 (iBus_rsp_error),

    .dBus_cmd_valid                 (dBus_cmd_valid),
    .dBus_cmd_ready                 (dBus_cmd_ready),
    .dBus_cmd_payload_wr            (dBus_cmd_payload_wr),
    .dBus_cmd_payload_address       (dBus_cmd_payload_address),
    .dBus_cmd_payload_data          (dBus_cmd_payload_data),
    .dBus_cmd_payload_size          (dBus_cmd_payload_size),

    .dBus_rsp_ready                 (dBus_rsp_ready),
    .dBus_rsp_data                  (dBus_rsp_data),
    .dBus_rsp_error                 (dBus_rsp_error),

    .xbaseband_cmd_valid                (xbaseband_cmd_valid),
    .xbaseband_cmd_ready                (xbaseband_cmd_ready),
    .xbaseband_cmd_payload_instruction  (xbaseband_cmd_payload_instruction),
    .xbaseband_cmd_payload_rs1          (xbaseband_cmd_payload_rs1),

    .clk                            (clk),
    .reset                          (reset),
    .debugReset                     (debugReset)
);

generic_dpram  #(
    .AWIDTH     (AWIDTH),
    .DEPTH      (DEPTH)
) mem (
    .clk        (clk),

    .t0_valid   (iBus_cmd_valid),
    .t0_ready   (iBus_cmd_ready),
    .t0_we      (1'b0),
    .t0_size    (2'b0),
    .t0_addr    (iBus_cmd_payload_pc),
    .t0_data    (32'b0),

    .i0_valid   (iBus_rsp_ready),
    .i0_ready   (1'b1),
    .i0_data    (iBus_rsp_inst),

    .t1_valid   (dBus_cmd_valid),
    .t1_ready   (dBus_cmd_ready),
    .t1_we      (dBus_cmd_payload_wr),
    .t1_size    (dBus_cmd_payload_size),
    .t1_addr    (dBus_cmd_payload_address),
    .t1_data    (dBus_cmd_payload_data),

    .i1_valid   (dBus_rsp_ready),
    .i1_ready   (1'b1),
    .i1_data    (dBus_rsp_data)
);

endmodule
