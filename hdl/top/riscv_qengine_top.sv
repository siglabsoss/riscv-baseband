module riscv_baseband 
		#(
		 parameter V_MEM_DEPTH = 2048, // FIXME: this is ignored
         parameter SCALAR_MEM_0 = "scalar0.mif",
         parameter SCALAR_MEM_1 = "scalar1.mif",
         parameter SCALAR_MEM_2 = "scalar2.mif",
         parameter SCALAR_MEM_3 = "scalar3.mif")
		(
		input 	       timerInterrupt,
		input 	       debug_bus_cmd_valid,
		output 	       debug_bus_cmd_ready,
		input 	       debug_bus_cmd_payload_wr,
		input [7:0] 	       debug_bus_cmd_payload_address,
		input [31:0]        debug_bus_cmd_payload_data,
		output [31:0]       debug_bus_rsp_data,
		output 	       debug_resetOut,

		output 	       xbaseband_cmd_valid,
		input 	       xbaseband_cmd_ready,
		output [31:0]       xbaseband_cmd_payload_instruction,
		output [31:0]       xbaseband_cmd_payload_rs1,

		input 	       clk,
		input 	       reset,
		input 	       debugReset,

		input wire [31:0]   t0_data,
		input wire 	       t0_valid,
		output wire 	       t0_ready,


		output logic [31:0] i0_data,
		output logic        i0_valid,
		input logic 	       i0_ready,

		inout wire [0:0] 	       gpio,
		input 	       i_ringbus,
		output 	       o_ringbus
		);

	//   logic 	       i_ringbus,o_ringbus;
	//   assign i_ringbus=o_ringbus;
   
   
	logic 	       iBus_cmd_valid;
	logic 	       iBus_cmd_ready;
	logic [31:0]        iBus_cmd_payload_pc;
	logic 	       iBus_rsp_ready;
	logic 	       iBus_rsp_error;
	logic [31:0]        iBus_rsp_inst;

	//   assign iBus_rsp_error = 1'b0;

	logic 	       dBus_cmd_valid;
	logic 	       dBus_cmd_ready;
	logic 	       dBus_cmd_payload_wr;
	logic [31:0]        dBus_cmd_payload_address;
	logic [31:0]        dBus_cmd_payload_data;
	logic [1:0] 	       dBus_cmd_payload_size;
	logic 	       dBus_rsp_ready;
	logic 	       dBus_rsp_error;
	logic [31:0]        dBus_rsp_data;


	logic 	       proc_interrupt;

	//   assign dBus_rsp_error = 1'b0;

	logic 	       dma_0_config_valid;
	logic 	       dma_0_config_ready;
	logic [31:0]        dma_0_config_payload_startAddr;
	logic [31:0]        dma_0_config_payload_length;
	logic [31:0]        dma_0_config_payload_timerInit;
	logic 	       dma_0_busy;
	logic 	       dma_0_interrupt;
	logic 	       dma_0_interrupt_clear;

	logic 	       dma_1_config_valid;
	logic 	       dma_1_config_ready;
	logic [31:0]        dma_1_config_payload_startAddr;
	logic [31:0]        dma_1_config_payload_length;
	logic [31:0]        dma_1_config_payload_timerInit;
	logic 	       dma_1_busy;
	logic 	       dma_1_interrupt;
	logic 	       dma_1_interrupt_clear;

	logic [31:0]        interrupt_mask;
	logic 	       interrupt_clear;
	logic [31:0]        interrupt_interruptVector;
	logic [31:0]        interrupt_serviceInterrupt;

	logic 	       ringbus_interrupt_clear;
	logic [31:0]        ringbus_write_data;
	logic [31:0]        ringbus_write_addr;
	logic 	       ringbus_write_done;
	logic 	       ringbus_write_en;
	logic [31:0]        ringbus_read_data;
	logic 	       ringbus_interrupt;

	logic [0:0] 	       gpio_read;
	logic [0:0] 	       gpio_write;
	logic [0:0] 	       gpio_writeEnable;
   
	logic [31:0]        timerCsr_gtimer;

	assign gpio_read=gpio;
	assign gpio=gpio_writeEnable?gpio_write:'z;
   
	VexRiscv VexRiscv 
		(
			.timerInterrupt                 (timerInterrupt),
			.externalInterrupt              ({3'b0,ringbus_interrupt,dma_1_interrupt,dma_0_interrupt}),

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
			.debugReset                     (debugReset),
      
			.dma_0_config_payload_startAddr(dma_0_config_payload_startAddr),
			.dma_0_config_payload_length(dma_0_config_payload_length),
			.dma_0_config_payload_timerInit(dma_0_config_payload_timerInit),
			.dma_0_config_valid(dma_0_config_valid),
			.dma_0_config_ready(dma_0_config_ready),
			.dma_0_busy(dma_0_busy),
			.dma_0_interrupt_clear(dma_0_interrupt_clear),

			.dma_1_config_payload_startAddr(dma_1_config_payload_startAddr),
			.dma_1_config_payload_length(dma_1_config_payload_length),
			.dma_1_config_payload_timerInit(dma_1_config_payload_timerInit),
			.dma_1_config_valid(dma_1_config_valid),
			.dma_1_config_ready(dma_1_config_ready),
			.dma_1_busy(dma_1_busy),
			.dma_1_interrupt_clear(dma_1_interrupt_clear),

			.interrupt_mask(interrupt_mask),
			.interrupt_clear(interrupt_clear),
			.interrupt_interruptVector(interrupt_interruptVector),
			.interrupt_serviceInterrupt(interrupt_serviceInterrupt),

			.timerCsr_gtimer(timerCsr_gtimer),

			.ringbus_interrupt_clear(ringbus_interrupt_clear),
			.ringbus_config_payload_write_data(ringbus_write_data),
			.ringbus_config_payload_write_addr(ringbus_write_addr),
			.ringbus_write_done(ringbus_write_done),
			.ringbus_config_valid(ringbus_write_en),
			.ringbus_read_data(ringbus_read_data),

			.gpio_read(gpio_read),
			.gpio_write(gpio_write),
			.gpio_writeEnable(gpio_writeEnable)
		);



	q_engine #(
		.V_MEM_DEPTH (V_MEM_DEPTH),
	   .SCALAR_MEM_0(SCALAR_MEM_0),
       .SCALAR_MEM_1 (SCALAR_MEM_1),
       .SCALAR_MEM_2 (SCALAR_MEM_2),
       .SCALAR_MEM_3 (SCALAR_MEM_3)
		) q_engine
		(
			.clk        (clk),
			.srst       (reset),

			.iBus_cmd_valid       (iBus_cmd_valid),
			.iBus_cmd_ready       (iBus_cmd_ready),
			.iBus_cmd_payload_pc       (iBus_cmd_payload_pc),
			.iBus_rsp_ready       (iBus_rsp_ready),
			.iBus_rsp_inst       (iBus_rsp_inst),
			.iBus_rsp_error       (iBus_rsp_error),
			.dBus_cmd_valid       (dBus_cmd_valid),
			.dBus_cmd_ready       (dBus_cmd_ready),
			.dBus_cmd_payload_wr       (dBus_cmd_payload_wr),
			.dBus_cmd_payload_address       (dBus_cmd_payload_address),
			.dBus_cmd_payload_data       (dBus_cmd_payload_data),
			.dBus_cmd_payload_size       (dBus_cmd_payload_size),
			.dBus_rsp_ready       (dBus_rsp_ready),
			.dBus_rsp_data       (dBus_rsp_data),
			.dBus_rsp_error       (dBus_rsp_error),

			.t0_data       (t0_data),
			.t0_valid      (t0_valid),
			.t0_ready      (t0_ready),

			.i0_data        (i0_data),
			.i0_valid       (i0_valid),
			.i0_ready       (i0_ready),

			.dma_0_config_payload_startAddr(dma_0_config_payload_startAddr),
			.dma_0_config_payload_length(dma_0_config_payload_length),
			.dma_0_config_payload_timerInit(dma_0_config_payload_timerInit),
			.dma_0_config_valid(dma_0_config_valid),
			.dma_0_config_ready(dma_0_config_ready),
			.dma_0_busy(dma_0_busy),
			.dma_0_interrupt(dma_0_interrupt),
			.dma_0_interrupt_clear(dma_0_interrupt_clear),

			.dma_1_config_payload_startAddr(dma_1_config_payload_startAddr),
			.dma_1_config_payload_length(dma_1_config_payload_length),
			.dma_1_config_payload_timerInit(dma_1_config_payload_timerInit),
			.dma_1_config_valid(dma_1_config_valid),
			.dma_1_config_ready(dma_1_config_ready),
			.dma_1_busy(dma_1_busy),
			.dma_1_interrupt(dma_1_interrupt),
			.dma_1_interrupt_clear(dma_1_interrupt_clear),

			.interrupt_mask(interrupt_mask),
			.interrupt_clear(interrupt_clear),
			.interrupt_interruptVector(interrupt_interruptVector),
			.interrupt_serviceInterrupt(interrupt_serviceInterrupt),

			.timerCsr_gtimer(timerCsr_gtimer),

			.ringbus_interrupt_clear(ringbus_interrupt_clear),
			.ringbus_write_data(ringbus_write_data),
			.ringbus_write_addr(ringbus_write_addr),
			.ringbus_write_done(ringbus_write_done),
			.ringbus_write_en(ringbus_write_en),
			.ringbus_read_data(ringbus_read_data),
			.ringbus_interrupt(ringbus_interrupt),
      
			.proc_interrupt (proc_interrupt),

			.i_ringbus(i_ringbus),
			.o_ringbus(o_ringbus)
		);

endmodule

