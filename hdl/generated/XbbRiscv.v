// Generator : SpinalHDL v1.1.5    git head : 0310b2489a097f2b9de5535e02192d9ddd2764ae
// Date      : 26/08/2019, 14:05:29
// Component : XbbRiscv


`define Src2CtrlEnum_binary_sequancial_type [1:0]
`define Src2CtrlEnum_binary_sequancial_RS 2'b00
`define Src2CtrlEnum_binary_sequancial_IMI 2'b01
`define Src2CtrlEnum_binary_sequancial_IMS 2'b10
`define Src2CtrlEnum_binary_sequancial_PC 2'b11

`define execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_type [2:0]
`define execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_boot 3'b000
`define execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateInit 3'b001
`define execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateCompute 3'b010
`define execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateSaturate 3'b011
`define execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateNormalize 3'b100
`define execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateOutput 3'b101

`define BranchCtrlEnum_binary_sequancial_type [1:0]
`define BranchCtrlEnum_binary_sequancial_INC 2'b00
`define BranchCtrlEnum_binary_sequancial_B 2'b01
`define BranchCtrlEnum_binary_sequancial_JAL 2'b10
`define BranchCtrlEnum_binary_sequancial_JALR 2'b11

`define UartCtrlTxState_binary_sequancial_type [2:0]
`define UartCtrlTxState_binary_sequancial_IDLE 3'b000
`define UartCtrlTxState_binary_sequancial_START 3'b001
`define UartCtrlTxState_binary_sequancial_DATA 3'b010
`define UartCtrlTxState_binary_sequancial_PARITY 3'b011
`define UartCtrlTxState_binary_sequancial_STOP 3'b100

`define UartStopType_binary_sequancial_type [0:0]
`define UartStopType_binary_sequancial_ONE 1'b0
`define UartStopType_binary_sequancial_TWO 1'b1

`define JtagState_binary_sequancial_type [3:0]
`define JtagState_binary_sequancial_RESET 4'b0000
`define JtagState_binary_sequancial_IDLE 4'b0001
`define JtagState_binary_sequancial_IR_SELECT 4'b0010
`define JtagState_binary_sequancial_IR_CAPTURE 4'b0011
`define JtagState_binary_sequancial_IR_SHIFT 4'b0100
`define JtagState_binary_sequancial_IR_EXIT1 4'b0101
`define JtagState_binary_sequancial_IR_PAUSE 4'b0110
`define JtagState_binary_sequancial_IR_EXIT2 4'b0111
`define JtagState_binary_sequancial_IR_UPDATE 4'b1000
`define JtagState_binary_sequancial_DR_SELECT 4'b1001
`define JtagState_binary_sequancial_DR_CAPTURE 4'b1010
`define JtagState_binary_sequancial_DR_SHIFT 4'b1011
`define JtagState_binary_sequancial_DR_EXIT1 4'b1100
`define JtagState_binary_sequancial_DR_PAUSE 4'b1101
`define JtagState_binary_sequancial_DR_EXIT2 4'b1110
`define JtagState_binary_sequancial_DR_UPDATE 4'b1111

`define UartCtrlRxState_binary_sequancial_type [2:0]
`define UartCtrlRxState_binary_sequancial_IDLE 3'b000
`define UartCtrlRxState_binary_sequancial_START 3'b001
`define UartCtrlRxState_binary_sequancial_DATA 3'b010
`define UartCtrlRxState_binary_sequancial_PARITY 3'b011
`define UartCtrlRxState_binary_sequancial_STOP 3'b100

`define Src1CtrlEnum_binary_sequancial_type [1:0]
`define Src1CtrlEnum_binary_sequancial_RS 2'b00
`define Src1CtrlEnum_binary_sequancial_IMU 2'b01
`define Src1CtrlEnum_binary_sequancial_FOUR 2'b10

`define AluBitwiseCtrlEnum_binary_sequancial_type [1:0]
`define AluBitwiseCtrlEnum_binary_sequancial_XOR_1 2'b00
`define AluBitwiseCtrlEnum_binary_sequancial_OR_1 2'b01
`define AluBitwiseCtrlEnum_binary_sequancial_AND_1 2'b10
`define AluBitwiseCtrlEnum_binary_sequancial_SRC1 2'b11

`define UartParityType_binary_sequancial_type [1:0]
`define UartParityType_binary_sequancial_NONE 2'b00
`define UartParityType_binary_sequancial_EVEN 2'b01
`define UartParityType_binary_sequancial_ODD 2'b10

`define EnvCtrlEnum_binary_sequancial_type [1:0]
`define EnvCtrlEnum_binary_sequancial_NONE 2'b00
`define EnvCtrlEnum_binary_sequancial_EBREAK 2'b01
`define EnvCtrlEnum_binary_sequancial_MRET 2'b10

`define AluCtrlEnum_binary_sequancial_type [1:0]
`define AluCtrlEnum_binary_sequancial_ADD_SUB 2'b00
`define AluCtrlEnum_binary_sequancial_SLT_SLTU 2'b01
`define AluCtrlEnum_binary_sequancial_BITWISE 2'b10

`define ShiftCtrlEnum_binary_sequancial_type [1:0]
`define ShiftCtrlEnum_binary_sequancial_DISABLE_1 2'b00
`define ShiftCtrlEnum_binary_sequancial_SLL_1 2'b01
`define ShiftCtrlEnum_binary_sequancial_SRL_1 2'b10
`define ShiftCtrlEnum_binary_sequancial_SRA_1 2'b11

module BufferCC (
      input   io_initial,
      input   io_dataIn,
      output  io_dataOut,
      input   io_mainClk,
      input   resetCtrl_systemReset);
  reg  buffers_0;
  reg  buffers_1;
  assign io_dataOut = buffers_1;
  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      buffers_0 <= io_initial;
      buffers_1 <= io_initial;
    end else begin
      buffers_0 <= io_dataIn;
      buffers_1 <= buffers_0;
    end
  end

endmodule

module BufferCC_1 (
      input   io_dataIn,
      output  io_dataOut,
      input   io_mainClk,
      input   resetCtrl_mainClkReset);
  reg  buffers_0;
  reg  buffers_1;
  assign io_dataOut = buffers_1;
  always @ (posedge io_mainClk) begin
    buffers_0 <= io_dataIn;
    buffers_1 <= buffers_0;
  end

endmodule

module UartCtrlTx (
      input  [2:0] io_configFrame_dataLength,
      input  `UartStopType_binary_sequancial_type io_configFrame_stop,
      input  `UartParityType_binary_sequancial_type io_configFrame_parity,
      input   io_samplingTick,
      input   io_write_valid,
      output reg  io_write_ready,
      input  [7:0] io_write_payload,
      output  io_txd,
      input   io_mainClk,
      input   resetCtrl_systemReset);
  wire  _zz_2;
  wire [0:0] _zz_3;
  wire [2:0] _zz_4;
  wire [0:0] _zz_5;
  wire [2:0] _zz_6;
  reg  clockDivider_counter_willIncrement;
  wire  clockDivider_counter_willClear;
  reg [2:0] clockDivider_counter_valueNext;
  reg [2:0] clockDivider_counter_value;
  wire  clockDivider_counter_willOverflowIfInc;
  wire  clockDivider_tick;
  reg [2:0] tickCounter_value;
  reg `UartCtrlTxState_binary_sequancial_type stateMachine_state;
  reg  stateMachine_parity;
  reg  stateMachine_txd;
  reg  _zz_1;
  assign _zz_2 = (tickCounter_value == io_configFrame_dataLength);
  assign _zz_3 = clockDivider_counter_willIncrement;
  assign _zz_4 = {2'd0, _zz_3};
  assign _zz_5 = ((io_configFrame_stop == `UartStopType_binary_sequancial_ONE) ? (1'b0) : (1'b1));
  assign _zz_6 = {2'd0, _zz_5};
  always @ (*) begin
    clockDivider_counter_willIncrement = 1'b0;
    if(io_samplingTick)begin
      clockDivider_counter_willIncrement = 1'b1;
    end
  end

  assign clockDivider_counter_willClear = 1'b0;
  assign clockDivider_counter_willOverflowIfInc = (clockDivider_counter_value == (3'b100));
  assign clockDivider_tick = (clockDivider_counter_willOverflowIfInc && clockDivider_counter_willIncrement);
  always @ (*) begin
    if(clockDivider_tick)begin
      clockDivider_counter_valueNext = (3'b000);
    end else begin
      clockDivider_counter_valueNext = (clockDivider_counter_value + _zz_4);
    end
    if(clockDivider_counter_willClear)begin
      clockDivider_counter_valueNext = (3'b000);
    end
  end

  always @ (*) begin
    stateMachine_txd = 1'b1;
    io_write_ready = 1'b0;
    case(stateMachine_state)
      `UartCtrlTxState_binary_sequancial_IDLE : begin
      end
      `UartCtrlTxState_binary_sequancial_START : begin
        stateMachine_txd = 1'b0;
      end
      `UartCtrlTxState_binary_sequancial_DATA : begin
        stateMachine_txd = io_write_payload[tickCounter_value];
        if(clockDivider_tick)begin
          if(_zz_2)begin
            io_write_ready = 1'b1;
          end
        end
      end
      `UartCtrlTxState_binary_sequancial_PARITY : begin
        stateMachine_txd = stateMachine_parity;
      end
      default : begin
      end
    endcase
  end

  assign io_txd = _zz_1;
  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      clockDivider_counter_value <= (3'b000);
      stateMachine_state <= `UartCtrlTxState_binary_sequancial_IDLE;
      _zz_1 <= 1'b1;
    end else begin
      clockDivider_counter_value <= clockDivider_counter_valueNext;
      case(stateMachine_state)
        `UartCtrlTxState_binary_sequancial_IDLE : begin
          if((io_write_valid && clockDivider_tick))begin
            stateMachine_state <= `UartCtrlTxState_binary_sequancial_START;
          end
        end
        `UartCtrlTxState_binary_sequancial_START : begin
          if(clockDivider_tick)begin
            stateMachine_state <= `UartCtrlTxState_binary_sequancial_DATA;
          end
        end
        `UartCtrlTxState_binary_sequancial_DATA : begin
          if(clockDivider_tick)begin
            if(_zz_2)begin
              if((io_configFrame_parity == `UartParityType_binary_sequancial_NONE))begin
                stateMachine_state <= `UartCtrlTxState_binary_sequancial_STOP;
              end else begin
                stateMachine_state <= `UartCtrlTxState_binary_sequancial_PARITY;
              end
            end
          end
        end
        `UartCtrlTxState_binary_sequancial_PARITY : begin
          if(clockDivider_tick)begin
            stateMachine_state <= `UartCtrlTxState_binary_sequancial_STOP;
          end
        end
        default : begin
          if(clockDivider_tick)begin
            if((tickCounter_value == _zz_6))begin
              stateMachine_state <= (io_write_valid ? `UartCtrlTxState_binary_sequancial_START : `UartCtrlTxState_binary_sequancial_IDLE);
            end
          end
        end
      endcase
      _zz_1 <= stateMachine_txd;
    end
  end

  always @ (posedge io_mainClk) begin
    if(clockDivider_tick)begin
      tickCounter_value <= (tickCounter_value + (3'b001));
    end
    if(clockDivider_tick)begin
      stateMachine_parity <= (stateMachine_parity ^ stateMachine_txd);
    end
    case(stateMachine_state)
      `UartCtrlTxState_binary_sequancial_IDLE : begin
      end
      `UartCtrlTxState_binary_sequancial_START : begin
        if(clockDivider_tick)begin
          stateMachine_parity <= (io_configFrame_parity == `UartParityType_binary_sequancial_ODD);
          tickCounter_value <= (3'b000);
        end
      end
      `UartCtrlTxState_binary_sequancial_DATA : begin
        if(clockDivider_tick)begin
          if(_zz_2)begin
            tickCounter_value <= (3'b000);
          end
        end
      end
      `UartCtrlTxState_binary_sequancial_PARITY : begin
        if(clockDivider_tick)begin
          tickCounter_value <= (3'b000);
        end
      end
      default : begin
      end
    endcase
  end

endmodule

module UartCtrlRx (
      input  [2:0] io_configFrame_dataLength,
      input  `UartStopType_binary_sequancial_type io_configFrame_stop,
      input  `UartParityType_binary_sequancial_type io_configFrame_parity,
      input   io_samplingTick,
      output  io_read_valid,
      output [7:0] io_read_payload,
      input   io_rxd,
      input   io_mainClk,
      input   resetCtrl_systemReset);
  wire  _zz_2;
  wire  _zz_3;
  wire  _zz_4;
  wire  _zz_5;
  wire  _zz_6;
  wire [0:0] _zz_7;
  wire [2:0] _zz_8;
  wire  sampler_syncroniser;
  wire  _zz_1;
  wire  sampler_samples_0;
  reg  sampler_samples_1;
  reg  sampler_samples_2;
  reg  sampler_value;
  reg  sampler_tick;
  reg [2:0] bitTimer_counter;
  reg  bitTimer_tick;
  reg [2:0] bitCounter_value;
  reg `UartCtrlRxState_binary_sequancial_type stateMachine_state;
  reg  stateMachine_parity;
  reg [7:0] stateMachine_shifter;
  reg  stateMachine_validReg;
  assign _zz_4 = (sampler_tick && (! sampler_value));
  assign _zz_5 = (bitCounter_value == io_configFrame_dataLength);
  assign _zz_6 = (bitTimer_counter == (3'b000));
  assign _zz_7 = ((io_configFrame_stop == `UartStopType_binary_sequancial_ONE) ? (1'b0) : (1'b1));
  assign _zz_8 = {2'd0, _zz_7};
  BufferCC bufferCC_3 ( 
    .io_initial(_zz_2),
    .io_dataIn(io_rxd),
    .io_dataOut(_zz_3),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  assign _zz_2 = 1'b0;
  assign sampler_syncroniser = _zz_3;
  assign _zz_1 = 1'b1;
  assign sampler_samples_0 = sampler_syncroniser;
  always @ (*) begin
    bitTimer_tick = 1'b0;
    if(sampler_tick)begin
      if(_zz_6)begin
        bitTimer_tick = 1'b1;
      end
    end
  end

  assign io_read_valid = stateMachine_validReg;
  assign io_read_payload = stateMachine_shifter;
  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      sampler_samples_1 <= _zz_1;
      sampler_samples_2 <= _zz_1;
      sampler_value <= 1'b1;
      sampler_tick <= 1'b0;
      stateMachine_state <= `UartCtrlRxState_binary_sequancial_IDLE;
      stateMachine_validReg <= 1'b0;
    end else begin
      if(io_samplingTick)begin
        sampler_samples_1 <= sampler_samples_0;
      end
      if(io_samplingTick)begin
        sampler_samples_2 <= sampler_samples_1;
      end
      sampler_value <= (((1'b0 || ((1'b1 && sampler_samples_0) && sampler_samples_1)) || ((1'b1 && sampler_samples_0) && sampler_samples_2)) || ((1'b1 && sampler_samples_1) && sampler_samples_2));
      sampler_tick <= io_samplingTick;
      stateMachine_validReg <= 1'b0;
      case(stateMachine_state)
        `UartCtrlRxState_binary_sequancial_IDLE : begin
          if(_zz_4)begin
            stateMachine_state <= `UartCtrlRxState_binary_sequancial_START;
          end
        end
        `UartCtrlRxState_binary_sequancial_START : begin
          if(bitTimer_tick)begin
            stateMachine_state <= `UartCtrlRxState_binary_sequancial_DATA;
            if((sampler_value == 1'b1))begin
              stateMachine_state <= `UartCtrlRxState_binary_sequancial_IDLE;
            end
          end
        end
        `UartCtrlRxState_binary_sequancial_DATA : begin
          if(bitTimer_tick)begin
            if(_zz_5)begin
              if((io_configFrame_parity == `UartParityType_binary_sequancial_NONE))begin
                stateMachine_state <= `UartCtrlRxState_binary_sequancial_STOP;
                stateMachine_validReg <= 1'b1;
              end else begin
                stateMachine_state <= `UartCtrlRxState_binary_sequancial_PARITY;
              end
            end
          end
        end
        `UartCtrlRxState_binary_sequancial_PARITY : begin
          if(bitTimer_tick)begin
            if((stateMachine_parity == sampler_value))begin
              stateMachine_state <= `UartCtrlRxState_binary_sequancial_STOP;
              stateMachine_validReg <= 1'b1;
            end else begin
              stateMachine_state <= `UartCtrlRxState_binary_sequancial_IDLE;
            end
          end
        end
        default : begin
          if(bitTimer_tick)begin
            if((! sampler_value))begin
              stateMachine_state <= `UartCtrlRxState_binary_sequancial_IDLE;
            end else begin
              if((bitCounter_value == _zz_8))begin
                stateMachine_state <= `UartCtrlRxState_binary_sequancial_IDLE;
              end
            end
          end
        end
      endcase
    end
  end

  always @ (posedge io_mainClk) begin
    if(sampler_tick)begin
      bitTimer_counter <= (bitTimer_counter - (3'b001));
      if(_zz_6)begin
        bitTimer_counter <= (3'b100);
      end
    end
    if(bitTimer_tick)begin
      bitCounter_value <= (bitCounter_value + (3'b001));
    end
    if(bitTimer_tick)begin
      stateMachine_parity <= (stateMachine_parity ^ sampler_value);
    end
    case(stateMachine_state)
      `UartCtrlRxState_binary_sequancial_IDLE : begin
        if(_zz_4)begin
          bitTimer_counter <= (3'b001);
        end
      end
      `UartCtrlRxState_binary_sequancial_START : begin
        if(bitTimer_tick)begin
          bitCounter_value <= (3'b000);
          stateMachine_parity <= (io_configFrame_parity == `UartParityType_binary_sequancial_ODD);
        end
      end
      `UartCtrlRxState_binary_sequancial_DATA : begin
        if(bitTimer_tick)begin
          stateMachine_shifter[bitCounter_value] <= sampler_value;
          if(_zz_5)begin
            bitCounter_value <= (3'b000);
          end
        end
      end
      `UartCtrlRxState_binary_sequancial_PARITY : begin
        if(bitTimer_tick)begin
          bitCounter_value <= (3'b000);
        end
      end
      default : begin
      end
    endcase
  end

endmodule

module StreamFifo (
      input   io_push_valid,
      output  io_push_ready,
      input  [31:0] io_push_payload_startAddr,
      input  [31:0] io_push_payload_length,
      input  [31:0] io_push_payload_timerInit,
      input  [31:0] io_push_payload_slicer,
      input   io_push_payload_reverse,
      input   io_push_payload_last_or_run_till_last,
      input  [3:0] io_push_payload_demapper_constellation,
      input  [15:0] io_push_payload_demapper_two_over_sigma_sq,
      output  io_pop_valid,
      input   io_pop_ready,
      output [31:0] io_pop_payload_startAddr,
      output [31:0] io_pop_payload_length,
      output [31:0] io_pop_payload_timerInit,
      output [31:0] io_pop_payload_slicer,
      output  io_pop_payload_reverse,
      output  io_pop_payload_last_or_run_till_last,
      output [3:0] io_pop_payload_demapper_constellation,
      output [15:0] io_pop_payload_demapper_two_over_sigma_sq,
      input   io_flush,
      output [4:0] io_occupancy,
      output [4:0] io_availability,
      input   io_mainClk,
      input   resetCtrl_systemReset);
  reg [149:0] _zz_5;
  wire  _zz_6;
  wire  _zz_7;
  wire [0:0] _zz_8;
  wire [3:0] _zz_9;
  wire [0:0] _zz_10;
  wire [3:0] _zz_11;
  wire [0:0] _zz_12;
  wire [0:0] _zz_13;
  wire [3:0] _zz_14;
  wire [149:0] _zz_15;
  reg  _zz_1;
  reg  pushPtr_willIncrement;
  reg  pushPtr_willClear;
  reg [3:0] pushPtr_valueNext;
  reg [3:0] pushPtr_value;
  wire  pushPtr_willOverflowIfInc;
  wire  pushPtr_willOverflow;
  reg  popPtr_willIncrement;
  reg  popPtr_willClear;
  reg [3:0] popPtr_valueNext;
  reg [3:0] popPtr_value;
  wire  popPtr_willOverflowIfInc;
  wire  popPtr_willOverflow;
  wire  ptrMatch;
  reg  risingOccupancy;
  wire  pushing;
  wire  popping;
  wire  empty;
  wire  full;
  reg  _zz_2;
  wire [149:0] _zz_3;
  wire  _zz_4;
  wire [3:0] ptrDif;
  reg [149:0] ram [0:15];
  assign io_push_ready = _zz_6;
  assign io_pop_valid = _zz_7;
  assign _zz_8 = pushPtr_willIncrement;
  assign _zz_9 = {3'd0, _zz_8};
  assign _zz_10 = popPtr_willIncrement;
  assign _zz_11 = {3'd0, _zz_10};
  assign _zz_12 = _zz_3[128 : 128];
  assign _zz_13 = _zz_3[129 : 129];
  assign _zz_14 = (popPtr_value - pushPtr_value);
  assign _zz_15 = {io_push_payload_demapper_two_over_sigma_sq,{io_push_payload_demapper_constellation,{io_push_payload_last_or_run_till_last,{io_push_payload_reverse,{io_push_payload_slicer,{io_push_payload_timerInit,{io_push_payload_length,io_push_payload_startAddr}}}}}}};
  always @ (posedge io_mainClk) begin
    if(_zz_1) begin
      ram[pushPtr_value] <= _zz_15;
    end
  end

  always @ (posedge io_mainClk) begin
    if(_zz_4) begin
      _zz_5 <= ram[popPtr_valueNext];
    end
  end

  always @ (*) begin
    _zz_1 = 1'b0;
    pushPtr_willIncrement = 1'b0;
    if(pushing)begin
      _zz_1 = 1'b1;
      pushPtr_willIncrement = 1'b1;
    end
  end

  always @ (*) begin
    pushPtr_willClear = 1'b0;
    popPtr_willClear = 1'b0;
    if(io_flush)begin
      pushPtr_willClear = 1'b1;
      popPtr_willClear = 1'b1;
    end
  end

  assign pushPtr_willOverflowIfInc = (pushPtr_value == (4'b1111));
  assign pushPtr_willOverflow = (pushPtr_willOverflowIfInc && pushPtr_willIncrement);
  always @ (*) begin
    pushPtr_valueNext = (pushPtr_value + _zz_9);
    if(pushPtr_willClear)begin
      pushPtr_valueNext = (4'b0000);
    end
  end

  always @ (*) begin
    popPtr_willIncrement = 1'b0;
    if(popping)begin
      popPtr_willIncrement = 1'b1;
    end
  end

  assign popPtr_willOverflowIfInc = (popPtr_value == (4'b1111));
  assign popPtr_willOverflow = (popPtr_willOverflowIfInc && popPtr_willIncrement);
  always @ (*) begin
    popPtr_valueNext = (popPtr_value + _zz_11);
    if(popPtr_willClear)begin
      popPtr_valueNext = (4'b0000);
    end
  end

  assign ptrMatch = (pushPtr_value == popPtr_value);
  assign pushing = (io_push_valid && _zz_6);
  assign popping = (_zz_7 && io_pop_ready);
  assign empty = (ptrMatch && (! risingOccupancy));
  assign full = (ptrMatch && risingOccupancy);
  assign _zz_6 = (! full);
  assign _zz_7 = ((! empty) && (! (_zz_2 && (! full))));
  assign _zz_4 = 1'b1;
  assign _zz_3 = _zz_5;
  assign io_pop_payload_startAddr = _zz_3[31 : 0];
  assign io_pop_payload_length = _zz_3[63 : 32];
  assign io_pop_payload_timerInit = _zz_3[95 : 64];
  assign io_pop_payload_slicer = _zz_3[127 : 96];
  assign io_pop_payload_reverse = _zz_12[0];
  assign io_pop_payload_last_or_run_till_last = _zz_13[0];
  assign io_pop_payload_demapper_constellation = _zz_3[133 : 130];
  assign io_pop_payload_demapper_two_over_sigma_sq = _zz_3[149 : 134];
  assign ptrDif = (pushPtr_value - popPtr_value);
  assign io_occupancy = {(risingOccupancy && ptrMatch),ptrDif};
  assign io_availability = {((! risingOccupancy) && ptrMatch),_zz_14};
  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      pushPtr_value <= (4'b0000);
      popPtr_value <= (4'b0000);
      risingOccupancy <= 1'b0;
      _zz_2 <= 1'b0;
    end else begin
      pushPtr_value <= pushPtr_valueNext;
      popPtr_value <= popPtr_valueNext;
      _zz_2 <= (popPtr_valueNext == pushPtr_value);
      if((pushing != popping))begin
        risingOccupancy <= pushing;
      end
      if(io_flush)begin
        risingOccupancy <= 1'b0;
      end
    end
  end

endmodule


//StreamFifo_1 remplaced by StreamFifo


//StreamFifo_2 remplaced by StreamFifo

module StreamFifo_3 (
      input   io_push_valid,
      output  io_push_ready,
      input  [31:0] io_push_payload_write_data,
      input  [31:0] io_push_payload_write_addr,
      output  io_pop_valid,
      input   io_pop_ready,
      output [31:0] io_pop_payload_write_data,
      output [31:0] io_pop_payload_write_addr,
      input   io_flush,
      output [4:0] io_occupancy,
      output [4:0] io_availability,
      input   io_mainClk,
      input   resetCtrl_systemReset);
  reg [63:0] _zz_5;
  wire  _zz_6;
  wire  _zz_7;
  wire [0:0] _zz_8;
  wire [3:0] _zz_9;
  wire [0:0] _zz_10;
  wire [3:0] _zz_11;
  wire [3:0] _zz_12;
  wire [63:0] _zz_13;
  reg  _zz_1;
  reg  pushPtr_willIncrement;
  reg  pushPtr_willClear;
  reg [3:0] pushPtr_valueNext;
  reg [3:0] pushPtr_value;
  wire  pushPtr_willOverflowIfInc;
  wire  pushPtr_willOverflow;
  reg  popPtr_willIncrement;
  reg  popPtr_willClear;
  reg [3:0] popPtr_valueNext;
  reg [3:0] popPtr_value;
  wire  popPtr_willOverflowIfInc;
  wire  popPtr_willOverflow;
  wire  ptrMatch;
  reg  risingOccupancy;
  wire  pushing;
  wire  popping;
  wire  empty;
  wire  full;
  reg  _zz_2;
  wire [63:0] _zz_3;
  wire  _zz_4;
  wire [3:0] ptrDif;
  reg [63:0] ram [0:15];
  assign io_push_ready = _zz_6;
  assign io_pop_valid = _zz_7;
  assign _zz_8 = pushPtr_willIncrement;
  assign _zz_9 = {3'd0, _zz_8};
  assign _zz_10 = popPtr_willIncrement;
  assign _zz_11 = {3'd0, _zz_10};
  assign _zz_12 = (popPtr_value - pushPtr_value);
  assign _zz_13 = {io_push_payload_write_addr,io_push_payload_write_data};
  always @ (posedge io_mainClk) begin
    if(_zz_1) begin
      ram[pushPtr_value] <= _zz_13;
    end
  end

  always @ (posedge io_mainClk) begin
    if(_zz_4) begin
      _zz_5 <= ram[popPtr_valueNext];
    end
  end

  always @ (*) begin
    _zz_1 = 1'b0;
    pushPtr_willIncrement = 1'b0;
    if(pushing)begin
      _zz_1 = 1'b1;
      pushPtr_willIncrement = 1'b1;
    end
  end

  always @ (*) begin
    pushPtr_willClear = 1'b0;
    popPtr_willClear = 1'b0;
    if(io_flush)begin
      pushPtr_willClear = 1'b1;
      popPtr_willClear = 1'b1;
    end
  end

  assign pushPtr_willOverflowIfInc = (pushPtr_value == (4'b1111));
  assign pushPtr_willOverflow = (pushPtr_willOverflowIfInc && pushPtr_willIncrement);
  always @ (*) begin
    pushPtr_valueNext = (pushPtr_value + _zz_9);
    if(pushPtr_willClear)begin
      pushPtr_valueNext = (4'b0000);
    end
  end

  always @ (*) begin
    popPtr_willIncrement = 1'b0;
    if(popping)begin
      popPtr_willIncrement = 1'b1;
    end
  end

  assign popPtr_willOverflowIfInc = (popPtr_value == (4'b1111));
  assign popPtr_willOverflow = (popPtr_willOverflowIfInc && popPtr_willIncrement);
  always @ (*) begin
    popPtr_valueNext = (popPtr_value + _zz_11);
    if(popPtr_willClear)begin
      popPtr_valueNext = (4'b0000);
    end
  end

  assign ptrMatch = (pushPtr_value == popPtr_value);
  assign pushing = (io_push_valid && _zz_6);
  assign popping = (_zz_7 && io_pop_ready);
  assign empty = (ptrMatch && (! risingOccupancy));
  assign full = (ptrMatch && risingOccupancy);
  assign _zz_6 = (! full);
  assign _zz_7 = ((! empty) && (! (_zz_2 && (! full))));
  assign _zz_4 = 1'b1;
  assign _zz_3 = _zz_5;
  assign io_pop_payload_write_data = _zz_3[31 : 0];
  assign io_pop_payload_write_addr = _zz_3[63 : 32];
  assign ptrDif = (pushPtr_value - popPtr_value);
  assign io_occupancy = {(risingOccupancy && ptrMatch),ptrDif};
  assign io_availability = {((! risingOccupancy) && ptrMatch),_zz_12};
  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      pushPtr_value <= (4'b0000);
      popPtr_value <= (4'b0000);
      risingOccupancy <= 1'b0;
      _zz_2 <= 1'b0;
    end else begin
      pushPtr_value <= pushPtr_valueNext;
      popPtr_value <= popPtr_valueNext;
      _zz_2 <= (popPtr_valueNext == pushPtr_value);
      if((pushing != popping))begin
        risingOccupancy <= pushing;
      end
      if(io_flush)begin
        risingOccupancy <= 1'b0;
      end
    end
  end

endmodule

module StreamFifo_4 (
      input   io_push_valid,
      output  io_push_ready,
      input  [31:0] io_push_payload_read_data,
      output  io_pop_valid,
      input   io_pop_ready,
      output [31:0] io_pop_payload_read_data,
      input   io_flush,
      output [4:0] io_occupancy,
      output [4:0] io_availability,
      input   io_mainClk,
      input   resetCtrl_systemReset);
  reg [31:0] _zz_4;
  wire  _zz_5;
  wire  _zz_6;
  wire [0:0] _zz_7;
  wire [3:0] _zz_8;
  wire [0:0] _zz_9;
  wire [3:0] _zz_10;
  wire [3:0] _zz_11;
  wire [31:0] _zz_12;
  reg  _zz_1;
  reg  pushPtr_willIncrement;
  reg  pushPtr_willClear;
  reg [3:0] pushPtr_valueNext;
  reg [3:0] pushPtr_value;
  wire  pushPtr_willOverflowIfInc;
  wire  pushPtr_willOverflow;
  reg  popPtr_willIncrement;
  reg  popPtr_willClear;
  reg [3:0] popPtr_valueNext;
  reg [3:0] popPtr_value;
  wire  popPtr_willOverflowIfInc;
  wire  popPtr_willOverflow;
  wire  ptrMatch;
  reg  risingOccupancy;
  wire  pushing;
  wire  popping;
  wire  empty;
  wire  full;
  reg  _zz_2;
  wire  _zz_3;
  wire [3:0] ptrDif;
  reg [31:0] ram [0:15];
  assign io_push_ready = _zz_5;
  assign io_pop_valid = _zz_6;
  assign _zz_7 = pushPtr_willIncrement;
  assign _zz_8 = {3'd0, _zz_7};
  assign _zz_9 = popPtr_willIncrement;
  assign _zz_10 = {3'd0, _zz_9};
  assign _zz_11 = (popPtr_value - pushPtr_value);
  assign _zz_12 = io_push_payload_read_data;
  always @ (posedge io_mainClk) begin
    if(_zz_1) begin
      ram[pushPtr_value] <= _zz_12;
    end
  end

  always @ (posedge io_mainClk) begin
    if(_zz_3) begin
      _zz_4 <= ram[popPtr_valueNext];
    end
  end

  always @ (*) begin
    _zz_1 = 1'b0;
    pushPtr_willIncrement = 1'b0;
    if(pushing)begin
      _zz_1 = 1'b1;
      pushPtr_willIncrement = 1'b1;
    end
  end

  always @ (*) begin
    pushPtr_willClear = 1'b0;
    popPtr_willClear = 1'b0;
    if(io_flush)begin
      pushPtr_willClear = 1'b1;
      popPtr_willClear = 1'b1;
    end
  end

  assign pushPtr_willOverflowIfInc = (pushPtr_value == (4'b1111));
  assign pushPtr_willOverflow = (pushPtr_willOverflowIfInc && pushPtr_willIncrement);
  always @ (*) begin
    pushPtr_valueNext = (pushPtr_value + _zz_8);
    if(pushPtr_willClear)begin
      pushPtr_valueNext = (4'b0000);
    end
  end

  always @ (*) begin
    popPtr_willIncrement = 1'b0;
    if(popping)begin
      popPtr_willIncrement = 1'b1;
    end
  end

  assign popPtr_willOverflowIfInc = (popPtr_value == (4'b1111));
  assign popPtr_willOverflow = (popPtr_willOverflowIfInc && popPtr_willIncrement);
  always @ (*) begin
    popPtr_valueNext = (popPtr_value + _zz_10);
    if(popPtr_willClear)begin
      popPtr_valueNext = (4'b0000);
    end
  end

  assign ptrMatch = (pushPtr_value == popPtr_value);
  assign pushing = (io_push_valid && _zz_5);
  assign popping = (_zz_6 && io_pop_ready);
  assign empty = (ptrMatch && (! risingOccupancy));
  assign full = (ptrMatch && risingOccupancy);
  assign _zz_5 = (! full);
  assign _zz_6 = ((! empty) && (! (_zz_2 && (! full))));
  assign _zz_3 = 1'b1;
  assign io_pop_payload_read_data = _zz_4[31 : 0];
  assign ptrDif = (pushPtr_value - popPtr_value);
  assign io_occupancy = {(risingOccupancy && ptrMatch),ptrDif};
  assign io_availability = {((! risingOccupancy) && ptrMatch),_zz_11};
  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      pushPtr_value <= (4'b0000);
      popPtr_value <= (4'b0000);
      risingOccupancy <= 1'b0;
      _zz_2 <= 1'b0;
    end else begin
      pushPtr_value <= pushPtr_valueNext;
      popPtr_value <= popPtr_valueNext;
      _zz_2 <= (popPtr_valueNext == pushPtr_value);
      if((pushing != popping))begin
        risingOccupancy <= pushing;
      end
      if(io_flush)begin
        risingOccupancy <= 1'b0;
      end
    end
  end

endmodule


//StreamFifo_5 remplaced by StreamFifo_3


//StreamFifo_6 remplaced by StreamFifo_4

module StreamFifo_7 (
      input   io_push_valid,
      output  io_push_ready,
      input  [31:0] io_push_payload_startAngle,
      input  [31:0] io_push_payload_length,
      input  [31:0] io_push_payload_delta,
      output  io_pop_valid,
      input   io_pop_ready,
      output [31:0] io_pop_payload_startAngle,
      output [31:0] io_pop_payload_length,
      output [31:0] io_pop_payload_delta,
      input   io_flush,
      output [4:0] io_occupancy,
      output [4:0] io_availability,
      input   io_mainClk,
      input   resetCtrl_systemReset);
  reg [95:0] _zz_5;
  wire  _zz_6;
  wire  _zz_7;
  wire [0:0] _zz_8;
  wire [3:0] _zz_9;
  wire [0:0] _zz_10;
  wire [3:0] _zz_11;
  wire [3:0] _zz_12;
  wire [95:0] _zz_13;
  reg  _zz_1;
  reg  pushPtr_willIncrement;
  reg  pushPtr_willClear;
  reg [3:0] pushPtr_valueNext;
  reg [3:0] pushPtr_value;
  wire  pushPtr_willOverflowIfInc;
  wire  pushPtr_willOverflow;
  reg  popPtr_willIncrement;
  reg  popPtr_willClear;
  reg [3:0] popPtr_valueNext;
  reg [3:0] popPtr_value;
  wire  popPtr_willOverflowIfInc;
  wire  popPtr_willOverflow;
  wire  ptrMatch;
  reg  risingOccupancy;
  wire  pushing;
  wire  popping;
  wire  empty;
  wire  full;
  reg  _zz_2;
  wire [95:0] _zz_3;
  wire  _zz_4;
  wire [3:0] ptrDif;
  reg [95:0] ram [0:15];
  assign io_push_ready = _zz_6;
  assign io_pop_valid = _zz_7;
  assign _zz_8 = pushPtr_willIncrement;
  assign _zz_9 = {3'd0, _zz_8};
  assign _zz_10 = popPtr_willIncrement;
  assign _zz_11 = {3'd0, _zz_10};
  assign _zz_12 = (popPtr_value - pushPtr_value);
  assign _zz_13 = {io_push_payload_delta,{io_push_payload_length,io_push_payload_startAngle}};
  always @ (posedge io_mainClk) begin
    if(_zz_1) begin
      ram[pushPtr_value] <= _zz_13;
    end
  end

  always @ (posedge io_mainClk) begin
    if(_zz_4) begin
      _zz_5 <= ram[popPtr_valueNext];
    end
  end

  always @ (*) begin
    _zz_1 = 1'b0;
    pushPtr_willIncrement = 1'b0;
    if(pushing)begin
      _zz_1 = 1'b1;
      pushPtr_willIncrement = 1'b1;
    end
  end

  always @ (*) begin
    pushPtr_willClear = 1'b0;
    popPtr_willClear = 1'b0;
    if(io_flush)begin
      pushPtr_willClear = 1'b1;
      popPtr_willClear = 1'b1;
    end
  end

  assign pushPtr_willOverflowIfInc = (pushPtr_value == (4'b1111));
  assign pushPtr_willOverflow = (pushPtr_willOverflowIfInc && pushPtr_willIncrement);
  always @ (*) begin
    pushPtr_valueNext = (pushPtr_value + _zz_9);
    if(pushPtr_willClear)begin
      pushPtr_valueNext = (4'b0000);
    end
  end

  always @ (*) begin
    popPtr_willIncrement = 1'b0;
    if(popping)begin
      popPtr_willIncrement = 1'b1;
    end
  end

  assign popPtr_willOverflowIfInc = (popPtr_value == (4'b1111));
  assign popPtr_willOverflow = (popPtr_willOverflowIfInc && popPtr_willIncrement);
  always @ (*) begin
    popPtr_valueNext = (popPtr_value + _zz_11);
    if(popPtr_willClear)begin
      popPtr_valueNext = (4'b0000);
    end
  end

  assign ptrMatch = (pushPtr_value == popPtr_value);
  assign pushing = (io_push_valid && _zz_6);
  assign popping = (_zz_7 && io_pop_ready);
  assign empty = (ptrMatch && (! risingOccupancy));
  assign full = (ptrMatch && risingOccupancy);
  assign _zz_6 = (! full);
  assign _zz_7 = ((! empty) && (! (_zz_2 && (! full))));
  assign _zz_4 = 1'b1;
  assign _zz_3 = _zz_5;
  assign io_pop_payload_startAngle = _zz_3[31 : 0];
  assign io_pop_payload_length = _zz_3[63 : 32];
  assign io_pop_payload_delta = _zz_3[95 : 64];
  assign ptrDif = (pushPtr_value - popPtr_value);
  assign io_occupancy = {(risingOccupancy && ptrMatch),ptrDif};
  assign io_availability = {((! risingOccupancy) && ptrMatch),_zz_12};
  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      pushPtr_value <= (4'b0000);
      popPtr_value <= (4'b0000);
      risingOccupancy <= 1'b0;
      _zz_2 <= 1'b0;
    end else begin
      pushPtr_value <= pushPtr_valueNext;
      popPtr_value <= popPtr_valueNext;
      _zz_2 <= (popPtr_valueNext == pushPtr_value);
      if((pushing != popping))begin
        risingOccupancy <= pushing;
      end
      if(io_flush)begin
        risingOccupancy <= 1'b0;
      end
    end
  end

endmodule

module FlowCCByToggle (
      input   io_input_valid,
      input   io_input_payload_last,
      input  [0:0] io_input_payload_fragment,
      output  io_output_valid,
      output  io_output_payload_last,
      output [0:0] io_output_payload_fragment,
      input   io_jtag_tck,
      input   io_mainClk,
      input   resetCtrl_mainClkReset);
  wire  _zz_4;
  wire  outHitSignal;
  reg  inputArea_target = 0;
  reg  inputArea_data_last;
  reg [0:0] inputArea_data_fragment;
  wire  outputArea_target;
  reg  outputArea_hit;
  wire  outputArea_flow_valid;
  wire  outputArea_flow_payload_last;
  wire [0:0] outputArea_flow_payload_fragment;
  reg  _zz_1;
  reg  _zz_2;
  reg [0:0] _zz_3;
  BufferCC_1 bufferCC_3 ( 
    .io_dataIn(inputArea_target),
    .io_dataOut(_zz_4),
    .io_mainClk(io_mainClk),
    .resetCtrl_mainClkReset(resetCtrl_mainClkReset) 
  );
  assign outputArea_target = _zz_4;
  assign outputArea_flow_valid = (outputArea_target != outputArea_hit);
  assign outputArea_flow_payload_last = inputArea_data_last;
  assign outputArea_flow_payload_fragment = inputArea_data_fragment;
  assign io_output_valid = _zz_1;
  assign io_output_payload_last = _zz_2;
  assign io_output_payload_fragment = _zz_3;
  always @ (posedge io_jtag_tck) begin
    if(io_input_valid)begin
      inputArea_target <= (! inputArea_target);
      inputArea_data_last <= io_input_payload_last;
      inputArea_data_fragment <= io_input_payload_fragment;
    end
  end

  always @ (posedge io_mainClk) begin
    outputArea_hit <= outputArea_target;
    _zz_2 <= outputArea_flow_payload_last;
    _zz_3 <= outputArea_flow_payload_fragment;
  end

  always @ (posedge io_mainClk or posedge resetCtrl_mainClkReset) begin
    if (resetCtrl_mainClkReset) begin
      _zz_1 <= 1'b0;
    end else begin
      _zz_1 <= outputArea_flow_valid;
    end
  end

endmodule

module UartCtrl (
      input  [2:0] io_config_frame_dataLength,
      input  `UartStopType_binary_sequancial_type io_config_frame_stop,
      input  `UartParityType_binary_sequancial_type io_config_frame_parity,
      input  [19:0] io_config_clockDivider,
      input   io_write_valid,
      output  io_write_ready,
      input  [7:0] io_write_payload,
      output  io_read_valid,
      output [7:0] io_read_payload,
      output  io_uart_txd,
      input   io_uart_rxd,
      input   io_mainClk,
      input   resetCtrl_systemReset);
  wire  _zz_1;
  wire  _zz_2;
  wire  _zz_3;
  wire [7:0] _zz_4;
  reg [19:0] clockDivider_counter;
  wire  clockDivider_tick;
  UartCtrlTx tx ( 
    .io_configFrame_dataLength(io_config_frame_dataLength),
    .io_configFrame_stop(io_config_frame_stop),
    .io_configFrame_parity(io_config_frame_parity),
    .io_samplingTick(clockDivider_tick),
    .io_write_valid(io_write_valid),
    .io_write_ready(_zz_1),
    .io_write_payload(io_write_payload),
    .io_txd(_zz_2),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  UartCtrlRx rx ( 
    .io_configFrame_dataLength(io_config_frame_dataLength),
    .io_configFrame_stop(io_config_frame_stop),
    .io_configFrame_parity(io_config_frame_parity),
    .io_samplingTick(clockDivider_tick),
    .io_read_valid(_zz_3),
    .io_read_payload(_zz_4),
    .io_rxd(io_uart_rxd),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  assign clockDivider_tick = (clockDivider_counter == (20'b00000000000000000000));
  assign io_write_ready = _zz_1;
  assign io_read_valid = _zz_3;
  assign io_read_payload = _zz_4;
  assign io_uart_txd = _zz_2;
  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      clockDivider_counter <= (20'b00000000000000000000);
    end else begin
      clockDivider_counter <= (clockDivider_counter - (20'b00000000000000000001));
      if(clockDivider_tick)begin
        clockDivider_counter <= io_config_clockDivider;
      end
    end
  end

endmodule

module StreamFifo_8 (
      input   io_push_valid,
      output  io_push_ready,
      input  [7:0] io_push_payload,
      output  io_pop_valid,
      input   io_pop_ready,
      output [7:0] io_pop_payload,
      input   io_flush,
      output [4:0] io_occupancy,
      output [4:0] io_availability,
      input   io_mainClk,
      input   resetCtrl_systemReset);
  reg [7:0] _zz_4;
  wire  _zz_5;
  wire  _zz_6;
  wire [0:0] _zz_7;
  wire [3:0] _zz_8;
  wire [0:0] _zz_9;
  wire [3:0] _zz_10;
  wire [3:0] _zz_11;
  reg  _zz_1;
  reg  pushPtr_willIncrement;
  reg  pushPtr_willClear;
  reg [3:0] pushPtr_valueNext;
  reg [3:0] pushPtr_value;
  wire  pushPtr_willOverflowIfInc;
  wire  pushPtr_willOverflow;
  reg  popPtr_willIncrement;
  reg  popPtr_willClear;
  reg [3:0] popPtr_valueNext;
  reg [3:0] popPtr_value;
  wire  popPtr_willOverflowIfInc;
  wire  popPtr_willOverflow;
  wire  ptrMatch;
  reg  risingOccupancy;
  wire  pushing;
  wire  popping;
  wire  empty;
  wire  full;
  reg  _zz_2;
  wire  _zz_3;
  wire [3:0] ptrDif;
  reg [7:0] ram [0:15];
  assign io_push_ready = _zz_5;
  assign io_pop_valid = _zz_6;
  assign _zz_7 = pushPtr_willIncrement;
  assign _zz_8 = {3'd0, _zz_7};
  assign _zz_9 = popPtr_willIncrement;
  assign _zz_10 = {3'd0, _zz_9};
  assign _zz_11 = (popPtr_value - pushPtr_value);
  always @ (posedge io_mainClk) begin
    if(_zz_1) begin
      ram[pushPtr_value] <= io_push_payload;
    end
  end

  always @ (posedge io_mainClk) begin
    if(_zz_3) begin
      _zz_4 <= ram[popPtr_valueNext];
    end
  end

  always @ (*) begin
    _zz_1 = 1'b0;
    pushPtr_willIncrement = 1'b0;
    if(pushing)begin
      _zz_1 = 1'b1;
      pushPtr_willIncrement = 1'b1;
    end
  end

  always @ (*) begin
    pushPtr_willClear = 1'b0;
    popPtr_willClear = 1'b0;
    if(io_flush)begin
      pushPtr_willClear = 1'b1;
      popPtr_willClear = 1'b1;
    end
  end

  assign pushPtr_willOverflowIfInc = (pushPtr_value == (4'b1111));
  assign pushPtr_willOverflow = (pushPtr_willOverflowIfInc && pushPtr_willIncrement);
  always @ (*) begin
    pushPtr_valueNext = (pushPtr_value + _zz_8);
    if(pushPtr_willClear)begin
      pushPtr_valueNext = (4'b0000);
    end
  end

  always @ (*) begin
    popPtr_willIncrement = 1'b0;
    if(popping)begin
      popPtr_willIncrement = 1'b1;
    end
  end

  assign popPtr_willOverflowIfInc = (popPtr_value == (4'b1111));
  assign popPtr_willOverflow = (popPtr_willOverflowIfInc && popPtr_willIncrement);
  always @ (*) begin
    popPtr_valueNext = (popPtr_value + _zz_10);
    if(popPtr_willClear)begin
      popPtr_valueNext = (4'b0000);
    end
  end

  assign ptrMatch = (pushPtr_value == popPtr_value);
  assign pushing = (io_push_valid && _zz_5);
  assign popping = (_zz_6 && io_pop_ready);
  assign empty = (ptrMatch && (! risingOccupancy));
  assign full = (ptrMatch && risingOccupancy);
  assign _zz_5 = (! full);
  assign _zz_6 = ((! empty) && (! (_zz_2 && (! full))));
  assign _zz_3 = 1'b1;
  assign io_pop_payload = _zz_4;
  assign ptrDif = (pushPtr_value - popPtr_value);
  assign io_occupancy = {(risingOccupancy && ptrMatch),ptrDif};
  assign io_availability = {((! risingOccupancy) && ptrMatch),_zz_11};
  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      pushPtr_value <= (4'b0000);
      popPtr_value <= (4'b0000);
      risingOccupancy <= 1'b0;
      _zz_2 <= 1'b0;
    end else begin
      pushPtr_value <= pushPtr_valueNext;
      popPtr_value <= popPtr_valueNext;
      _zz_2 <= (popPtr_valueNext == pushPtr_value);
      if((pushing != popping))begin
        risingOccupancy <= pushing;
      end
      if(io_flush)begin
        risingOccupancy <= 1'b0;
      end
    end
  end

endmodule


//StreamFifo_9 remplaced by StreamFifo_8

module BufferCC_2 (
      input   io_dataIn,
      output  io_dataOut,
      input   io_mainClk);
  reg  buffers_0;
  reg  buffers_1;
  assign io_dataOut = buffers_1;
  always @ (posedge io_mainClk) begin
    buffers_0 <= io_dataIn;
    buffers_1 <= buffers_0;
  end

endmodule

module VexRiscv (
      input   timerInterrupt,
      input  [5:0] externalInterrupt,
      output  dma_0_config_valid,
      input   dma_0_config_ready,
      output [31:0] dma_0_config_payload_startAddr,
      output [31:0] dma_0_config_payload_length,
      output [31:0] dma_0_config_payload_timerInit,
      output [31:0] dma_0_config_payload_slicer,
      output  dma_0_config_payload_reverse,
      output  dma_0_config_payload_last_or_run_till_last,
      output [3:0] dma_0_config_payload_demapper_constellation,
      output [15:0] dma_0_config_payload_demapper_two_over_sigma_sq,
      input  [31:0] dma_0_status,
      output  dma_0_interrupt_clear,
      output  dma_0_dmaReset,
      output  dma_1_config_valid,
      input   dma_1_config_ready,
      output [31:0] dma_1_config_payload_startAddr,
      output [31:0] dma_1_config_payload_length,
      output [31:0] dma_1_config_payload_timerInit,
      output [31:0] dma_1_config_payload_slicer,
      output  dma_1_config_payload_reverse,
      output  dma_1_config_payload_last_or_run_till_last,
      output [3:0] dma_1_config_payload_demapper_constellation,
      output [15:0] dma_1_config_payload_demapper_two_over_sigma_sq,
      input  [31:0] dma_1_status,
      output  dma_1_interrupt_clear,
      output  dma_1_dmaReset,
      output  dma_2_config_valid,
      input   dma_2_config_ready,
      output [31:0] dma_2_config_payload_startAddr,
      output [31:0] dma_2_config_payload_length,
      output [31:0] dma_2_config_payload_timerInit,
      output [31:0] dma_2_config_payload_slicer,
      output  dma_2_config_payload_reverse,
      output  dma_2_config_payload_last_or_run_till_last,
      output [3:0] dma_2_config_payload_demapper_constellation,
      output [15:0] dma_2_config_payload_demapper_two_over_sigma_sq,
      input  [31:0] dma_2_status,
      output  dma_2_interrupt_clear,
      output  dma_2_dmaReset,
      output [1023:0] mapmovCsr_mover_active,
      output [31:0] mapmovCsr_trim_start,
      output [31:0] mapmovCsr_trim_end,
      output [9:0] mapmovCsr_pilot_ram_addr,
      output [31:0] mapmovCsr_pilot_ram_wdata,
      output  mapmovCsr_pilot_ram_we,
      output  mapmovCsr_reset,
      output [15:0] mapmovCsr_one_value,
      output [15:0] mapmovCsr_zero_value,
      output [31:0] timerCsr_gtimer,
      output  ringbus_0_interrupt_clear,
      output  ringbus_0_config_valid,
      input   ringbus_0_config_ready,
      output [31:0] ringbus_0_config_payload_write_data,
      output [31:0] ringbus_0_config_payload_write_addr,
      input   ringbus_0_read_valid,
      output  ringbus_0_read_ready,
      input  [31:0] ringbus_0_read_payload_read_data,
      input   ringbus_0_write_done,
      input  [31:0] gpio_read,
      output [31:0] gpio_write,
      output [31:0] gpio_writeEnable,
      output  ringbus_1_interrupt_clear,
      output  ringbus_1_config_valid,
      input   ringbus_1_config_ready,
      output [31:0] ringbus_1_config_payload_write_data,
      output [31:0] ringbus_1_config_payload_write_addr,
      input   ringbus_1_read_valid,
      output  ringbus_1_read_ready,
      input  [31:0] ringbus_1_read_payload_read_data,
      input   ringbus_1_write_done,
      output  nco_0_config_valid,
      input   nco_0_config_ready,
      output [31:0] nco_0_config_payload_startAngle,
      output [31:0] nco_0_config_payload_length,
      output [31:0] nco_0_config_payload_delta,
      input   nco_0_busy,
      output  nco_0_ncoReset,
      output [31:0] slicer_value,
      input   _zz_104,
      input  [31:0] status_status,
      output [31:0] control_control,
      output  dengine_reset,
      output [31:0] dengine_func0MinThreshold,
      output [31:0] dengine_func0MaxThreshold,
      output [31:0] dengine_func1MinThreshold,
      output [31:0] dengine_func1MaxThreshold,
      input   debug_bus_cmd_valid,
      output  debug_bus_cmd_ready,
      input   debug_bus_cmd_payload_wr,
      input  [7:0] debug_bus_cmd_payload_address,
      input  [31:0] debug_bus_cmd_payload_data,
      output reg [31:0] debug_bus_rsp_data,
      output  debug_resetOut,
      output  iBus_cmd_valid,
      input   iBus_cmd_ready,
      output [31:0] iBus_cmd_payload_pc,
      input   iBus_rsp_ready,
      input   iBus_rsp_error,
      input  [31:0] iBus_rsp_inst,
      output  dBus_cmd_valid,
      input   dBus_cmd_ready,
      output  dBus_cmd_payload_wr,
      output [31:0] dBus_cmd_payload_address,
      output [31:0] dBus_cmd_payload_data,
      output [1:0] dBus_cmd_payload_size,
      input   dBus_rsp_ready,
      input   dBus_rsp_error,
      input  [31:0] dBus_rsp_data,
      output  xbaseband_cmd_valid,
      input   xbaseband_cmd_ready,
      output [31:0] xbaseband_cmd_payload_instruction,
      output [31:0] xbaseband_cmd_payload_rs1,
      input   io_mainClk,
      input   resetCtrl_systemReset,
      input   resetCtrl_mainClkReset);
  reg [31:0] _zz_294;
  reg [31:0] _zz_295;
  wire  _zz_296;
  wire [1:0] _zz_297;
  wire [31:0] _zz_298;
  reg  _zz_299;
  reg [31:0] _zz_300;
  reg [4:0] _zz_301;
  reg [31:0] _zz_302;
  wire  _zz_303;
  wire  _zz_304;
  wire [31:0] _zz_305;
  wire [31:0] _zz_306;
  wire [31:0] _zz_307;
  wire [31:0] _zz_308;
  wire  _zz_309;
  wire  _zz_310;
  wire [3:0] _zz_311;
  wire [15:0] _zz_312;
  wire [4:0] _zz_313;
  wire [4:0] _zz_314;
  wire  _zz_315;
  wire  _zz_316;
  wire [31:0] _zz_317;
  wire [31:0] _zz_318;
  wire [31:0] _zz_319;
  wire [31:0] _zz_320;
  wire  _zz_321;
  wire  _zz_322;
  wire [3:0] _zz_323;
  wire [15:0] _zz_324;
  wire [4:0] _zz_325;
  wire [4:0] _zz_326;
  wire  _zz_327;
  wire  _zz_328;
  wire [31:0] _zz_329;
  wire [31:0] _zz_330;
  wire [31:0] _zz_331;
  wire [31:0] _zz_332;
  wire  _zz_333;
  wire  _zz_334;
  wire [3:0] _zz_335;
  wire [15:0] _zz_336;
  wire [4:0] _zz_337;
  wire [4:0] _zz_338;
  wire  _zz_339;
  wire  _zz_340;
  wire [31:0] _zz_341;
  wire [31:0] _zz_342;
  wire [4:0] _zz_343;
  wire [4:0] _zz_344;
  wire  _zz_345;
  wire  _zz_346;
  wire [31:0] _zz_347;
  wire [4:0] _zz_348;
  wire [4:0] _zz_349;
  wire  _zz_350;
  wire  _zz_351;
  wire [31:0] _zz_352;
  wire [31:0] _zz_353;
  wire [4:0] _zz_354;
  wire [4:0] _zz_355;
  wire  _zz_356;
  wire  _zz_357;
  wire [31:0] _zz_358;
  wire [4:0] _zz_359;
  wire [4:0] _zz_360;
  wire  _zz_361;
  wire  _zz_362;
  wire [31:0] _zz_363;
  wire [31:0] _zz_364;
  wire [31:0] _zz_365;
  wire [4:0] _zz_366;
  wire [4:0] _zz_367;
  wire  _zz_368;
  wire  _zz_369;
  wire  _zz_370;
  wire  _zz_371;
  wire  _zz_372;
  wire  _zz_373;
  wire [0:0] _zz_374;
  wire  _zz_375;
  wire  _zz_376;
  wire  _zz_377;
  wire  _zz_378;
  wire [1:0] _zz_379;
  wire  _zz_380;
  wire [1:0] _zz_381;
  wire [1:0] _zz_382;
  wire [2:0] _zz_383;
  wire [1:0] _zz_384;
  wire [1:0] _zz_385;
  wire [3:0] _zz_386;
  wire [4:0] _zz_387;
  wire [2:0] _zz_388;
  wire [3:0] _zz_389;
  wire [4:0] _zz_390;
  wire [31:0] _zz_391;
  wire [0:0] _zz_392;
  wire [0:0] _zz_393;
  wire [0:0] _zz_394;
  wire [0:0] _zz_395;
  wire [0:0] _zz_396;
  wire [0:0] _zz_397;
  wire [0:0] _zz_398;
  wire [0:0] _zz_399;
  wire [0:0] _zz_400;
  wire [0:0] _zz_401;
  wire [0:0] _zz_402;
  wire [0:0] _zz_403;
  wire [0:0] _zz_404;
  wire [0:0] _zz_405;
  wire [0:0] _zz_406;
  wire [0:0] _zz_407;
  wire [0:0] _zz_408;
  wire [11:0] _zz_409;
  wire [11:0] _zz_410;
  wire [31:0] _zz_411;
  wire [31:0] _zz_412;
  wire [31:0] _zz_413;
  wire [31:0] _zz_414;
  wire [1:0] _zz_415;
  wire [31:0] _zz_416;
  wire [1:0] _zz_417;
  wire [1:0] _zz_418;
  wire [51:0] _zz_419;
  wire [51:0] _zz_420;
  wire [51:0] _zz_421;
  wire [32:0] _zz_422;
  wire [51:0] _zz_423;
  wire [49:0] _zz_424;
  wire [51:0] _zz_425;
  wire [49:0] _zz_426;
  wire [51:0] _zz_427;
  wire [65:0] _zz_428;
  wire [65:0] _zz_429;
  wire [31:0] _zz_430;
  wire [31:0] _zz_431;
  wire [0:0] _zz_432;
  wire [5:0] _zz_433;
  wire [32:0] _zz_434;
  wire [32:0] _zz_435;
  wire [31:0] _zz_436;
  wire [31:0] _zz_437;
  wire [32:0] _zz_438;
  wire [32:0] _zz_439;
  wire [32:0] _zz_440;
  wire [0:0] _zz_441;
  wire [32:0] _zz_442;
  wire [0:0] _zz_443;
  wire [32:0] _zz_444;
  wire [0:0] _zz_445;
  wire [31:0] _zz_446;
  wire [32:0] _zz_447;
  wire [31:0] _zz_448;
  wire [32:0] _zz_449;
  wire [11:0] _zz_450;
  wire [31:0] _zz_451;
  wire [19:0] _zz_452;
  wire [11:0] _zz_453;
  wire [11:0] _zz_454;
  wire [11:0] _zz_455;
  wire [0:0] _zz_456;
  wire [0:0] _zz_457;
  wire [0:0] _zz_458;
  wire [0:0] _zz_459;
  wire [0:0] _zz_460;
  wire [0:0] _zz_461;
  wire [0:0] _zz_462;
  wire [0:0] _zz_463;
  wire [0:0] _zz_464;
  wire [0:0] _zz_465;
  wire [0:0] _zz_466;
  wire [0:0] _zz_467;
  wire [0:0] _zz_468;
  wire [0:0] _zz_469;
  wire [0:0] _zz_470;
  wire [0:0] _zz_471;
  wire [0:0] _zz_472;
  wire [0:0] _zz_473;
  wire [17:0] _zz_474;
  wire [17:0] _zz_475;
  wire [16:0] _zz_476;
  wire [16:0] _zz_477;
  wire [17:0] _zz_478;
  wire [16:0] _zz_479;
  wire [16:0] _zz_480;
  wire [17:0] _zz_481;
  wire [16:0] _zz_482;
  wire [16:0] _zz_483;
  wire [17:0] _zz_484;
  wire [16:0] _zz_485;
  wire [16:0] _zz_486;
  wire [17:0] _zz_487;
  wire [16:0] _zz_488;
  wire [16:0] _zz_489;
  wire [17:0] _zz_490;
  wire [16:0] _zz_491;
  wire [16:0] _zz_492;
  wire [17:0] _zz_493;
  wire [16:0] _zz_494;
  wire [16:0] _zz_495;
  wire [17:0] _zz_496;
  wire [16:0] _zz_497;
  wire [16:0] _zz_498;
  wire [17:0] _zz_499;
  wire [16:0] _zz_500;
  wire [16:0] _zz_501;
  wire [17:0] _zz_502;
  wire [16:0] _zz_503;
  wire [16:0] _zz_504;
  wire [17:0] _zz_505;
  wire [16:0] _zz_506;
  wire [16:0] _zz_507;
  wire [17:0] _zz_508;
  wire [16:0] _zz_509;
  wire [16:0] _zz_510;
  wire [17:0] _zz_511;
  wire [16:0] _zz_512;
  wire [16:0] _zz_513;
  wire [17:0] _zz_514;
  wire [16:0] _zz_515;
  wire [16:0] _zz_516;
  wire [17:0] _zz_517;
  wire [16:0] _zz_518;
  wire [16:0] _zz_519;
  wire [17:0] _zz_520;
  wire [16:0] _zz_521;
  wire [16:0] _zz_522;
  wire [16:0] _zz_523;
  wire [16:0] _zz_524;
  wire [16:0] _zz_525;
  wire [16:0] _zz_526;
  wire [16:0] _zz_527;
  wire [16:0] _zz_528;
  wire [15:0] _zz_529;
  wire [15:0] _zz_530;
  wire [1:0] _zz_531;
  wire  _zz_532;
  wire  _zz_533;
  wire [671:0] _zz_534;
  wire [31:0] _zz_535;
  wire [319:0] _zz_536;
  wire [31:0] _zz_537;
  wire [31:0] _zz_538;
  wire [0:0] _zz_539;
  wire [0:0] _zz_540;
  wire [0:0] _zz_541;
  wire [0:0] _zz_542;
  wire  _zz_543;
  wire [0:0] _zz_544;
  wire [23:0] _zz_545;
  wire [31:0] _zz_546;
  wire [31:0] _zz_547;
  wire [31:0] _zz_548;
  wire [31:0] _zz_549;
  wire [0:0] _zz_550;
  wire [3:0] _zz_551;
  wire [0:0] _zz_552;
  wire [4:0] _zz_553;
  wire [0:0] _zz_554;
  wire [0:0] _zz_555;
  wire  _zz_556;
  wire [0:0] _zz_557;
  wire [19:0] _zz_558;
  wire [31:0] _zz_559;
  wire [31:0] _zz_560;
  wire  _zz_561;
  wire [0:0] _zz_562;
  wire [0:0] _zz_563;
  wire [31:0] _zz_564;
  wire [31:0] _zz_565;
  wire  _zz_566;
  wire [0:0] _zz_567;
  wire [1:0] _zz_568;
  wire [31:0] _zz_569;
  wire [0:0] _zz_570;
  wire [0:0] _zz_571;
  wire  _zz_572;
  wire [0:0] _zz_573;
  wire [16:0] _zz_574;
  wire [31:0] _zz_575;
  wire [31:0] _zz_576;
  wire [31:0] _zz_577;
  wire [31:0] _zz_578;
  wire [31:0] _zz_579;
  wire [31:0] _zz_580;
  wire  _zz_581;
  wire  _zz_582;
  wire [31:0] _zz_583;
  wire [31:0] _zz_584;
  wire  _zz_585;
  wire [0:0] _zz_586;
  wire [0:0] _zz_587;
  wire  _zz_588;
  wire [0:0] _zz_589;
  wire [14:0] _zz_590;
  wire [31:0] _zz_591;
  wire  _zz_592;
  wire [1:0] _zz_593;
  wire [1:0] _zz_594;
  wire  _zz_595;
  wire [0:0] _zz_596;
  wire [11:0] _zz_597;
  wire [31:0] _zz_598;
  wire [31:0] _zz_599;
  wire  _zz_600;
  wire [0:0] _zz_601;
  wire [1:0] _zz_602;
  wire [0:0] _zz_603;
  wire [5:0] _zz_604;
  wire [0:0] _zz_605;
  wire [0:0] _zz_606;
  wire  _zz_607;
  wire [0:0] _zz_608;
  wire [7:0] _zz_609;
  wire [31:0] _zz_610;
  wire [31:0] _zz_611;
  wire [31:0] _zz_612;
  wire  _zz_613;
  wire [31:0] _zz_614;
  wire [31:0] _zz_615;
  wire [0:0] _zz_616;
  wire [3:0] _zz_617;
  wire [31:0] _zz_618;
  wire [31:0] _zz_619;
  wire [0:0] _zz_620;
  wire [0:0] _zz_621;
  wire [2:0] _zz_622;
  wire [2:0] _zz_623;
  wire  _zz_624;
  wire [0:0] _zz_625;
  wire [5:0] _zz_626;
  wire [31:0] _zz_627;
  wire  _zz_628;
  wire [0:0] _zz_629;
  wire [1:0] _zz_630;
  wire [31:0] _zz_631;
  wire [31:0] _zz_632;
  wire [31:0] _zz_633;
  wire [31:0] _zz_634;
  wire [0:0] _zz_635;
  wire [0:0] _zz_636;
  wire [0:0] _zz_637;
  wire [1:0] _zz_638;
  wire [1:0] _zz_639;
  wire [1:0] _zz_640;
  wire  _zz_641;
  wire [0:0] _zz_642;
  wire [3:0] _zz_643;
  wire [31:0] _zz_644;
  wire [31:0] _zz_645;
  wire [31:0] _zz_646;
  wire  _zz_647;
  wire  _zz_648;
  wire [31:0] _zz_649;
  wire [31:0] _zz_650;
  wire  _zz_651;
  wire  _zz_652;
  wire [0:0] _zz_653;
  wire [0:0] _zz_654;
  wire [0:0] _zz_655;
  wire [0:0] _zz_656;
  wire  _zz_657;
  wire [0:0] _zz_658;
  wire [1:0] _zz_659;
  wire [31:0] _zz_660;
  wire [31:0] _zz_661;
  wire  _zz_662;
  wire [0:0] _zz_663;
  wire [0:0] _zz_664;
  wire [0:0] _zz_665;
  wire [0:0] _zz_666;
  wire [2:0] _zz_667;
  wire [2:0] _zz_668;
  wire [0:0] _zz_669;
  wire [0:0] _zz_670;
  wire [31:0] _zz_671;
  wire [31:0] _zz_672;
  wire [31:0] _zz_673;
  wire [31:0] _zz_674;
  wire [31:0] _zz_675;
  wire [31:0] _zz_676;
  wire [31:0] _zz_677;
  wire [31:0] _zz_678;
  wire  _zz_679;
  wire [0:0] _zz_680;
  wire [11:0] _zz_681;
  wire [31:0] _zz_682;
  wire [31:0] _zz_683;
  wire [31:0] _zz_684;
  wire  _zz_685;
  wire [0:0] _zz_686;
  wire [5:0] _zz_687;
  wire [31:0] _zz_688;
  wire [31:0] _zz_689;
  wire [31:0] _zz_690;
  wire  _zz_691;
  wire  _zz_692;
  wire [0:0] _zz_693;
  wire [7:0] _zz_694;
  wire  _zz_695;
  wire [0:0] _zz_696;
  wire [0:0] _zz_697;
  wire [31:0] execute_SHIFT_RIGHT;
  wire [31:0] execute_MUL_LL;
  wire [31:0] execute_BRANCH_CALC;
  wire `AluCtrlEnum_binary_sequancial_type decode_ALU_CTRL;
  wire `AluCtrlEnum_binary_sequancial_type _zz_1;
  wire `AluCtrlEnum_binary_sequancial_type _zz_2;
  wire `AluCtrlEnum_binary_sequancial_type _zz_3;
  wire [33:0] execute_MUL_LH;
  wire  decode_MEMORY_ENABLE;
  wire  decode_BYPASSABLE_EXECUTE_STAGE;
  wire [31:0] memory_FORMAL_PC_NEXT;
  wire [31:0] execute_FORMAL_PC_NEXT;
  wire [31:0] decode_FORMAL_PC_NEXT;
  wire [31:0] fetch_FORMAL_PC_NEXT;
  wire [31:0] prefetch_FORMAL_PC_NEXT;
  wire  decode_IS_RS2_SIGNED;
  wire [33:0] execute_MUL_HL;
  wire  decode_CSR_READ_OPCODE;
  wire  decode_IS_DIV;
  wire [31:0] memory_PC;
  wire [31:0] fetch_PC;
  wire  decode_SRC_USE_SUB_LESS;
  wire `Src2CtrlEnum_binary_sequancial_type decode_SRC2_CTRL;
  wire `Src2CtrlEnum_binary_sequancial_type _zz_4;
  wire `Src2CtrlEnum_binary_sequancial_type _zz_5;
  wire `Src2CtrlEnum_binary_sequancial_type _zz_6;
  wire  memory_IS_MUL;
  wire  execute_IS_MUL;
  wire  decode_IS_MUL;
  wire  decode_CSR_WRITE_OPCODE;
  wire  execute_BRANCH_DO;
  wire [31:0] fetch_INSTRUCTION;
  wire `ShiftCtrlEnum_binary_sequancial_type _zz_7;
  wire `ShiftCtrlEnum_binary_sequancial_type _zz_8;
  wire `ShiftCtrlEnum_binary_sequancial_type decode_SHIFT_CTRL;
  wire `ShiftCtrlEnum_binary_sequancial_type _zz_9;
  wire `ShiftCtrlEnum_binary_sequancial_type _zz_10;
  wire `ShiftCtrlEnum_binary_sequancial_type _zz_11;
  wire  decode_IS_RS1_SIGNED;
  wire [1:0] memory_MEMORY_ADDRESS_LOW;
  wire [1:0] execute_MEMORY_ADDRESS_LOW;
  wire `AluBitwiseCtrlEnum_binary_sequancial_type decode_ALU_BITWISE_CTRL;
  wire `AluBitwiseCtrlEnum_binary_sequancial_type _zz_12;
  wire `AluBitwiseCtrlEnum_binary_sequancial_type _zz_13;
  wire `AluBitwiseCtrlEnum_binary_sequancial_type _zz_14;
  wire [51:0] memory_MUL_LOW;
  wire [31:0] memory_MEMORY_READ_DATA;
  wire `Src1CtrlEnum_binary_sequancial_type decode_SRC1_CTRL;
  wire `Src1CtrlEnum_binary_sequancial_type _zz_15;
  wire `Src1CtrlEnum_binary_sequancial_type _zz_16;
  wire `Src1CtrlEnum_binary_sequancial_type _zz_17;
  wire  writeBack_IS_XBASEBAND;
  wire  memory_IS_XBASEBAND;
  wire  execute_IS_XBASEBAND;
  wire  decode_IS_XBASEBAND;
  wire `BranchCtrlEnum_binary_sequancial_type _zz_18;
  wire `BranchCtrlEnum_binary_sequancial_type _zz_19;
  wire  decode_SRC_LESS_UNSIGNED;
  wire  decode_IS_VCORDIC;
  wire `EnvCtrlEnum_binary_sequancial_type execute_ENV_CTRL;
  wire `EnvCtrlEnum_binary_sequancial_type _zz_20;
  wire `EnvCtrlEnum_binary_sequancial_type _zz_21;
  wire `EnvCtrlEnum_binary_sequancial_type _zz_22;
  wire `EnvCtrlEnum_binary_sequancial_type decode_ENV_CTRL;
  wire `EnvCtrlEnum_binary_sequancial_type _zz_23;
  wire `EnvCtrlEnum_binary_sequancial_type _zz_24;
  wire `EnvCtrlEnum_binary_sequancial_type _zz_25;
  wire  execute_INSTRUCTION_READY;
  wire [33:0] memory_MUL_HH;
  wire [33:0] execute_MUL_HH;
  wire  execute_BYPASSABLE_MEMORY_STAGE;
  wire  decode_BYPASSABLE_MEMORY_STAGE;
  wire [31:0] memory_RS1;
  wire [31:0] writeBack_REGFILE_WRITE_DATA;
  wire [31:0] execute_REGFILE_WRITE_DATA;
  wire  decode_IS_EBREAK;
  wire  execute_IS_EBREAK;
  wire  memory_INSTRUCTION_READY;
  wire [31:0] memory_BRANCH_CALC;
  wire  memory_BRANCH_DO;
  wire [31:0] _zz_26;
  wire [31:0] execute_PC;
  wire  execute_PREDICTION_HAD_BRANCHED2;
  wire  _zz_27;
  wire `BranchCtrlEnum_binary_sequancial_type execute_BRANCH_CTRL;
  wire `BranchCtrlEnum_binary_sequancial_type _zz_28;
  wire  decode_PREDICTION_HAD_BRANCHED2;
  wire `BranchCtrlEnum_binary_sequancial_type decode_BRANCH_CTRL;
  wire `BranchCtrlEnum_binary_sequancial_type _zz_29;
  wire  _zz_30;
  wire  execute_IS_VCORDIC;
  wire [31:0] writeBack_RS1;
  wire  decode_RS2_USE;
  wire  decode_RS1_USE;
  wire  execute_REGFILE_WRITE_VALID;
  wire  execute_BYPASSABLE_EXECUTE_STAGE;
  wire  memory_REGFILE_WRITE_VALID;
  wire  memory_BYPASSABLE_MEMORY_STAGE;
  wire  writeBack_REGFILE_WRITE_VALID;
  reg [31:0] decode_RS2;
  reg [31:0] decode_RS1;
  wire [31:0] memory_SHIFT_RIGHT;
  wire `ShiftCtrlEnum_binary_sequancial_type memory_SHIFT_CTRL;
  wire `ShiftCtrlEnum_binary_sequancial_type _zz_31;
  wire [31:0] _zz_32;
  wire `ShiftCtrlEnum_binary_sequancial_type execute_SHIFT_CTRL;
  wire `ShiftCtrlEnum_binary_sequancial_type _zz_33;
  wire  execute_IS_RS1_SIGNED;
  wire [31:0] execute_RS1;
  wire  execute_IS_DIV;
  wire  execute_IS_RS2_SIGNED;
  reg [31:0] _zz_34;
  wire  memory_IS_DIV;
  wire  writeBack_IS_MUL;
  wire [33:0] writeBack_MUL_HH;
  wire [51:0] writeBack_MUL_LOW;
  wire [33:0] memory_MUL_HL;
  wire [33:0] memory_MUL_LH;
  wire [31:0] memory_MUL_LL;
  wire [51:0] _zz_35;
  wire [33:0] _zz_36;
  wire [33:0] _zz_37;
  wire [33:0] _zz_38;
  wire [31:0] _zz_39;
  wire  _zz_40;
  wire [31:0] _zz_41;
  wire [31:0] _zz_42;
  wire  execute_SRC_LESS_UNSIGNED;
  wire  execute_SRC_USE_SUB_LESS;
  wire [31:0] _zz_43;
  wire `Src2CtrlEnum_binary_sequancial_type execute_SRC2_CTRL;
  wire `Src2CtrlEnum_binary_sequancial_type _zz_44;
  wire [31:0] _zz_45;
  wire [31:0] _zz_46;
  wire `Src1CtrlEnum_binary_sequancial_type execute_SRC1_CTRL;
  wire `Src1CtrlEnum_binary_sequancial_type _zz_47;
  wire [31:0] _zz_48;
  wire [31:0] execute_SRC_ADD_SUB;
  wire  execute_SRC_LESS;
  wire `AluCtrlEnum_binary_sequancial_type execute_ALU_CTRL;
  wire `AluCtrlEnum_binary_sequancial_type _zz_49;
  wire [31:0] _zz_50;
  wire [31:0] execute_SRC2;
  wire `AluBitwiseCtrlEnum_binary_sequancial_type execute_ALU_BITWISE_CTRL;
  wire `AluBitwiseCtrlEnum_binary_sequancial_type _zz_51;
  wire [31:0] _zz_52;
  wire  _zz_53;
  reg  _zz_54;
  wire [31:0] _zz_55;
  wire [31:0] _zz_56;
  wire [31:0] decode_INSTRUCTION_ANTICIPATED;
  reg  decode_REGFILE_WRITE_VALID;
  wire  decode_LEGAL_INSTRUCTION;
  wire  decode_INSTRUCTION_READY;
  wire  _zz_57;
  wire  _zz_58;
  wire  _zz_59;
  wire  _zz_60;
  wire  _zz_61;
  wire  _zz_62;
  wire  _zz_63;
  wire `EnvCtrlEnum_binary_sequancial_type _zz_64;
  wire `BranchCtrlEnum_binary_sequancial_type _zz_65;
  wire  _zz_66;
  wire  _zz_67;
  wire `Src1CtrlEnum_binary_sequancial_type _zz_68;
  wire `AluCtrlEnum_binary_sequancial_type _zz_69;
  wire  _zz_70;
  wire  _zz_71;
  wire  _zz_72;
  wire  _zz_73;
  wire `Src2CtrlEnum_binary_sequancial_type _zz_74;
  wire `AluBitwiseCtrlEnum_binary_sequancial_type _zz_75;
  wire  _zz_76;
  wire  _zz_77;
  wire `ShiftCtrlEnum_binary_sequancial_type _zz_78;
  wire  _zz_79;
  wire  _zz_80;
  reg [31:0] _zz_81;
  wire  execute_CSR_READ_OPCODE;
  wire  execute_CSR_WRITE_OPCODE;
  wire [31:0] memory_REGFILE_WRITE_DATA;
  wire [31:0] execute_SRC1;
  wire  execute_IS_CSR;
  wire  decode_IS_CSR;
  wire  _zz_82;
  wire  _zz_83;
  wire `EnvCtrlEnum_binary_sequancial_type memory_ENV_CTRL;
  wire `EnvCtrlEnum_binary_sequancial_type _zz_84;
  wire [31:0] prefetch_PC_CALC_WITHOUT_JUMP;
  reg [31:0] _zz_85;
  wire  writeBack_MEMORY_ENABLE;
  wire [1:0] writeBack_MEMORY_ADDRESS_LOW;
  wire [31:0] writeBack_MEMORY_READ_DATA;
  wire [31:0] memory_INSTRUCTION;
  wire  memory_MEMORY_ENABLE;
  wire [31:0] _zz_86;
  wire [1:0] _zz_87;
  wire [31:0] execute_RS2;
  wire [31:0] execute_SRC_ADD;
  wire [31:0] execute_INSTRUCTION;
  wire  execute_ALIGNEMENT_FAULT;
  wire  execute_MEMORY_ENABLE;
  wire  _zz_88;
  wire  _zz_89;
  wire [31:0] _zz_90;
  wire [31:0] _zz_91;
  reg [31:0] _zz_92;
  wire [31:0] _zz_93;
  reg [31:0] _zz_94;
  reg [31:0] _zz_95;
  wire [31:0] prefetch_PC;
  wire [31:0] _zz_96;
  wire [31:0] _zz_97;
  wire [31:0] _zz_98;
  wire [31:0] writeBack_PC;
  wire [31:0] writeBack_INSTRUCTION;
  wire [31:0] decode_PC;
  wire [31:0] decode_INSTRUCTION;
  reg  prefetch_arbitration_haltItself;
  reg  prefetch_arbitration_haltByOther;
  reg  prefetch_arbitration_removeIt;
  wire  prefetch_arbitration_flushAll;
  wire  prefetch_arbitration_redoIt;
  reg  prefetch_arbitration_isValid;
  wire  prefetch_arbitration_isStuck;
  wire  prefetch_arbitration_isStuckByOthers;
  wire  prefetch_arbitration_isFlushed;
  wire  prefetch_arbitration_isMoving;
  wire  prefetch_arbitration_isFiring;
  reg  fetch_arbitration_haltItself;
  wire  fetch_arbitration_haltByOther;
  reg  fetch_arbitration_removeIt;
  reg  fetch_arbitration_flushAll;
  wire  fetch_arbitration_redoIt;
  reg  fetch_arbitration_isValid;
  wire  fetch_arbitration_isStuck;
  wire  fetch_arbitration_isStuckByOthers;
  wire  fetch_arbitration_isFlushed;
  wire  fetch_arbitration_isMoving;
  wire  fetch_arbitration_isFiring;
  reg  decode_arbitration_haltItself;
  wire  decode_arbitration_haltByOther;
  reg  decode_arbitration_removeIt;
  reg  decode_arbitration_flushAll;
  wire  decode_arbitration_redoIt;
  reg  decode_arbitration_isValid;
  wire  decode_arbitration_isStuck;
  wire  decode_arbitration_isStuckByOthers;
  wire  decode_arbitration_isFlushed;
  wire  decode_arbitration_isMoving;
  wire  decode_arbitration_isFiring;
  reg  execute_arbitration_haltItself;
  wire  execute_arbitration_haltByOther;
  reg  execute_arbitration_removeIt;
  reg  execute_arbitration_flushAll;
  wire  execute_arbitration_redoIt;
  reg  execute_arbitration_isValid;
  wire  execute_arbitration_isStuck;
  wire  execute_arbitration_isStuckByOthers;
  wire  execute_arbitration_isFlushed;
  wire  execute_arbitration_isMoving;
  wire  execute_arbitration_isFiring;
  reg  memory_arbitration_haltItself;
  wire  memory_arbitration_haltByOther;
  reg  memory_arbitration_removeIt;
  wire  memory_arbitration_flushAll;
  wire  memory_arbitration_redoIt;
  reg  memory_arbitration_isValid;
  wire  memory_arbitration_isStuck;
  wire  memory_arbitration_isStuckByOthers;
  wire  memory_arbitration_isFlushed;
  wire  memory_arbitration_isMoving;
  wire  memory_arbitration_isFiring;
  reg  writeBack_arbitration_haltItself;
  wire  writeBack_arbitration_haltByOther;
  reg  writeBack_arbitration_removeIt;
  wire  writeBack_arbitration_flushAll;
  wire  writeBack_arbitration_redoIt;
  reg  writeBack_arbitration_isValid;
  wire  writeBack_arbitration_isStuck;
  wire  writeBack_arbitration_isStuckByOthers;
  wire  writeBack_arbitration_isFlushed;
  wire  writeBack_arbitration_isMoving;
  wire  writeBack_arbitration_isFiring;
  reg  _zz_99;
  reg [31:0] _zz_100;
  wire  contextSwitching;
  reg [1:0] _zz_101;
  reg  _zz_102;
  reg  _zz_103;
  wire  decodeExceptionPort_valid;
  wire [4:0] decodeExceptionPort_payload_code;
  wire [31:0] decodeExceptionPort_payload_badAddr;
  wire  _zz_105;
  wire [31:0] _zz_106;
  wire  _zz_107;
  wire [31:0] _zz_108;
  wire  _zz_109;
  reg [31:0] prefetch_PcManagerSimplePlugin_pcReg;
  (* keep , syn_keep *) wire [31:0] prefetch_PcManagerSimplePlugin_pcPlus4 /* synthesis syn_keep = 1 */ ;
  wire  prefetch_PcManagerSimplePlugin_jump_pcLoad_valid;
  wire [31:0] prefetch_PcManagerSimplePlugin_jump_pcLoad_payload;
  wire [2:0] _zz_110;
  wire [2:0] _zz_111;
  wire  _zz_112;
  wire  _zz_113;
  reg  prefetch_IBusSimplePlugin_pendingCmd;
  reg  _zz_114;
  reg [31:0] _zz_115;
  reg [31:0] _zz_116;
  reg [3:0] _zz_117;
  wire [3:0] execute_DBusSimplePlugin_formalMask;
  reg [31:0] writeBack_DBusSimplePlugin_rspShifted;
  wire  _zz_118;
  reg [31:0] _zz_119;
  wire  _zz_120;
  reg [31:0] _zz_121;
  reg [31:0] writeBack_DBusSimplePlugin_rspFormated;
  wire [1:0] CsrPlugin_misa_base;
  wire [25:0] CsrPlugin_misa_extensions;
  wire [31:0] CsrPlugin_mtvec;
  reg [31:0] CsrPlugin_mepc;
  reg  CsrPlugin_mstatus_MIE;
  reg  CsrPlugin_mstatus_MPIE;
  reg [1:0] CsrPlugin_mstatus_MPP;
  reg [5:0] CsrPlugin_mip_MEIP;
  reg  CsrPlugin_mip_MTIP;
  reg  CsrPlugin_mip_MSIP;
  reg [5:0] CsrPlugin_mie_MEIE;
  reg  CsrPlugin_mie_MTIE;
  reg  CsrPlugin_mie_MSIE;
  reg  CsrPlugin_mcause_interrupt;
  reg [4:0] CsrPlugin_mcause_exceptionCode;
  reg [31:0] CsrPlugin_mbadaddr;
  reg [63:0] CsrPlugin_mcycle = 64'b1111100111010100000110110010010100001010110011100010110100000110;
  reg [63:0] CsrPlugin_minstret = 64'b1110110010010010010001010011100111010110001011000001110001010001;
  reg  CsrPlugin_pipelineLiberator_enable;
  wire  CsrPlugin_pipelineLiberator_done;
  wire  CsrPlugin_exceptionPortCtrl_exceptionValids_0;
  wire  CsrPlugin_exceptionPortCtrl_exceptionValids_1;
  reg  CsrPlugin_exceptionPortCtrl_exceptionValids_2;
  reg  CsrPlugin_exceptionPortCtrl_exceptionValids_3;
  reg  CsrPlugin_exceptionPortCtrl_exceptionValids_4;
  reg  CsrPlugin_exceptionPortCtrl_exceptionValids_5;
  wire  CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_0;
  wire  CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_1;
  reg  CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_2;
  reg  CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_3;
  reg  CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_4;
  reg  CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_5;
  reg [4:0] CsrPlugin_exceptionPortCtrl_exceptionContext_code;
  reg [31:0] CsrPlugin_exceptionPortCtrl_exceptionContext_badAddr;
  wire  CsrPlugin_exceptionPortCtrl_pipelineHasException;
  wire [1:0] _zz_122;
  wire  _zz_123;
  wire [0:0] _zz_124;
  wire  CsrPlugin_interruptRequest;
  wire  CsrPlugin_interrupt;
  wire  CsrPlugin_exception;
  wire  CsrPlugin_writeBackWasWfi;
  reg [31:0] _zz_125;
  reg  _zz_126;
  reg  execute_CsrPlugin_illegalAccess;
  wire [31:0] execute_CsrPlugin_writeSrc;
  reg [31:0] execute_CsrPlugin_readData;
  reg  execute_CsrPlugin_readDataRegValid;
  reg [31:0] execute_CsrPlugin_writeData;
  wire  execute_CsrPlugin_writeInstruction;
  wire  execute_CsrPlugin_readInstruction;
  wire  execute_CsrPlugin_writeEnable;
  wire  execute_CsrPlugin_readEnable;
  wire [11:0] execute_CsrPlugin_csrAddress;
  reg [31:0] DmaCsrPlugin_startAddrReg;
  reg [31:0] DmaCsrPlugin_lengthReg;
  reg [31:0] DmaCsrPlugin_timerInitReg;
  reg [31:0] DmaCsrPlugin_slicerReg;
  reg  DmaCsrPlugin_reverseReg;
  reg  DmaCsrPlugin_last_or_run_till_lastReg;
  reg [3:0] DmaCsrPlugin_demapper_constellationReg;
  reg [15:0] DmaCsrPlugin_demapper_two_over_sigma_sqReg;
  wire  DmaCsrPlugin_configPush_valid;
  wire  DmaCsrPlugin_configPush_ready;
  wire [31:0] DmaCsrPlugin_configPush_payload_startAddr;
  wire [31:0] DmaCsrPlugin_configPush_payload_length;
  wire [31:0] DmaCsrPlugin_configPush_payload_timerInit;
  wire [31:0] DmaCsrPlugin_configPush_payload_slicer;
  wire  DmaCsrPlugin_configPush_payload_reverse;
  wire  DmaCsrPlugin_configPush_payload_last_or_run_till_last;
  wire [3:0] DmaCsrPlugin_configPush_payload_demapper_constellation;
  wire [15:0] DmaCsrPlugin_configPush_payload_demapper_two_over_sigma_sq;
  reg  _zz_127;
  reg  _zz_128;
  reg  _zz_129;
  reg  _zz_130;
  reg  _zz_131;
  reg  _zz_132;
  reg [31:0] DmaCsrPlugin_startAddrReg_1;
  reg [31:0] DmaCsrPlugin_lengthReg_1;
  reg [31:0] DmaCsrPlugin_timerInitReg_1;
  reg [31:0] DmaCsrPlugin_slicerReg_1;
  reg  DmaCsrPlugin_reverseReg_1;
  reg  DmaCsrPlugin_last_or_run_till_lastReg_1;
  reg [3:0] DmaCsrPlugin_demapper_constellationReg_1;
  reg [15:0] DmaCsrPlugin_demapper_two_over_sigma_sqReg_1;
  wire  DmaCsrPlugin_configPush_valid_1;
  wire  DmaCsrPlugin_configPush_ready_1;
  wire [31:0] DmaCsrPlugin_configPush_payload_startAddr_1;
  wire [31:0] DmaCsrPlugin_configPush_payload_length_1;
  wire [31:0] DmaCsrPlugin_configPush_payload_timerInit_1;
  wire [31:0] DmaCsrPlugin_configPush_payload_slicer_1;
  wire  DmaCsrPlugin_configPush_payload_reverse_1;
  wire  DmaCsrPlugin_configPush_payload_last_or_run_till_last_1;
  wire [3:0] DmaCsrPlugin_configPush_payload_demapper_constellation_1;
  wire [15:0] DmaCsrPlugin_configPush_payload_demapper_two_over_sigma_sq_1;
  reg  _zz_133;
  reg  _zz_134;
  reg  _zz_135;
  reg  _zz_136;
  reg  _zz_137;
  reg  _zz_138;
  reg [31:0] DmaCsrPlugin_startAddrReg_2;
  reg [31:0] DmaCsrPlugin_lengthReg_2;
  reg [31:0] DmaCsrPlugin_timerInitReg_2;
  reg [31:0] DmaCsrPlugin_slicerReg_2;
  reg  DmaCsrPlugin_reverseReg_2;
  reg  DmaCsrPlugin_last_or_run_till_lastReg_2;
  reg [3:0] DmaCsrPlugin_demapper_constellationReg_2;
  reg [15:0] DmaCsrPlugin_demapper_two_over_sigma_sqReg_2;
  wire  DmaCsrPlugin_configPush_valid_2;
  wire  DmaCsrPlugin_configPush_ready_2;
  wire [31:0] DmaCsrPlugin_configPush_payload_startAddr_2;
  wire [31:0] DmaCsrPlugin_configPush_payload_length_2;
  wire [31:0] DmaCsrPlugin_configPush_payload_timerInit_2;
  wire [31:0] DmaCsrPlugin_configPush_payload_slicer_2;
  wire  DmaCsrPlugin_configPush_payload_reverse_2;
  wire  DmaCsrPlugin_configPush_payload_last_or_run_till_last_2;
  wire [3:0] DmaCsrPlugin_configPush_payload_demapper_constellation_2;
  wire [15:0] DmaCsrPlugin_configPush_payload_demapper_two_over_sigma_sq_2;
  reg  _zz_139;
  reg  _zz_140;
  reg  _zz_141;
  reg  _zz_142;
  reg  _zz_143;
  reg  _zz_144;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg0;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg1;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg2;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg3;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg4;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg5;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg6;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg7;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg8;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg9;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg10;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg11;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg12;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg13;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg14;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg15;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg16;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg17;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg18;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg19;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg20;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg21;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg22;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg23;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg24;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg25;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg26;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg27;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg28;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg29;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg30;
  reg [31:0] MapperMoverCsrPlugin_mover_active_reg31;
  reg [31:0] MapperMoverCsrPlugin_trim_start_reg;
  reg [31:0] MapperMoverCsrPlugin_trim_end_reg;
  reg [31:0] MapperMoverCsrPlugin_pilot_ram_wdata;
  reg [9:0] MapperMoverCsrPlugin_pilot_ram_addr;
  reg  MapperMoverCsrPlugin_pilot_ram_we;
  reg  MapperMoverCsrPlugin_reset;
  reg [15:0] MapperMoverCsrPlugin_one_value_reg;
  reg [15:0] MapperMoverCsrPlugin_zero_value_reg;
  reg  _zz_145;
  reg  _zz_146;
  reg [31:0] TimerCsrPlugin_timerReg;
  reg [31:0] RingBusCsrPlugin_writeAddrReg;
  reg [31:0] RingBusCsrPlugin_writeDataReg;
  wire  RingBusCsrPlugin_writePush_valid;
  wire  RingBusCsrPlugin_writePush_ready;
  wire [31:0] RingBusCsrPlugin_writePush_payload_write_data;
  wire [31:0] RingBusCsrPlugin_writePush_payload_write_addr;
  wire  RingBusCsrPlugin_readPush_valid;
  wire  RingBusCsrPlugin_readPush_ready;
  wire [31:0] RingBusCsrPlugin_readPush_payload_read_data;
  wire  RingBusCsrPlugin_readPop_valid;
  wire  RingBusCsrPlugin_readPop_ready;
  wire [31:0] RingBusCsrPlugin_readPop_payload_read_data;
  reg  _zz_147;
  reg  _zz_148;
  reg  _zz_149;
  reg  _zz_150;
  reg  _zz_151;
  reg [31:0] GpioCsrPlugin_writeReg;
  reg [31:0] GpioCsrPlugin_writeEnableReg;
  reg [31:0] RingBusCsrPlugin_writeAddrReg_1;
  reg [31:0] RingBusCsrPlugin_writeDataReg_1;
  wire  RingBusCsrPlugin_writePush_valid_1;
  wire  RingBusCsrPlugin_writePush_ready_1;
  wire [31:0] RingBusCsrPlugin_writePush_payload_write_data_1;
  wire [31:0] RingBusCsrPlugin_writePush_payload_write_addr_1;
  wire  RingBusCsrPlugin_readPush_valid_1;
  wire  RingBusCsrPlugin_readPush_ready_1;
  wire [31:0] RingBusCsrPlugin_readPush_payload_read_data_1;
  wire  RingBusCsrPlugin_readPop_valid_1;
  wire  RingBusCsrPlugin_readPop_ready_1;
  wire [31:0] RingBusCsrPlugin_readPop_payload_read_data_1;
  reg  _zz_152;
  reg  _zz_153;
  reg  _zz_154;
  reg  _zz_155;
  reg  _zz_156;
  reg [31:0] NCOCsrPlugin_startAngleReg;
  reg [31:0] NCOCsrPlugin_lengthReg;
  reg [31:0] NCOCsrPlugin_deltaReg;
  wire  NCOCsrPlugin_configPush_valid;
  wire  NCOCsrPlugin_configPush_ready;
  wire [31:0] NCOCsrPlugin_configPush_payload_startAngle;
  wire [31:0] NCOCsrPlugin_configPush_payload_length;
  wire [31:0] NCOCsrPlugin_configPush_payload_delta;
  reg  _zz_157;
  reg  _zz_158;
  reg  _zz_159;
  reg  _zz_160;
  reg [31:0] GenericOutCsrPlugin_valueReg;
  reg [31:0] _zz_161;
  reg  SatDetectCsrPlugin_satDetectReg;
  reg [15:0] SatDetectCsrPlugin_satCountReg;
  reg [15:0] SatDetectCsrPlugin_satTimeReg;
  wire [31:0] SatDetectCsrPlugin_satReg;
  reg  _zz_162;
  reg [31:0] ControlStatusCsrPlugin_controlReg;
  reg  DEngineCsrPlugin_resetReg;
  reg [31:0] DEngineCsrPlugin_func0MinThresholdReg;
  reg [31:0] DEngineCsrPlugin_func0MaxThresholdReg;
  reg [31:0] DEngineCsrPlugin_func1MinThresholdReg;
  reg [31:0] DEngineCsrPlugin_func1MaxThresholdReg;
  wire [29:0] _zz_163;
  wire  _zz_164;
  wire  _zz_165;
  wire  _zz_166;
  wire  _zz_167;
  wire  _zz_168;
  wire  _zz_169;
  wire  _zz_170;
  wire `ShiftCtrlEnum_binary_sequancial_type _zz_171;
  wire `AluBitwiseCtrlEnum_binary_sequancial_type _zz_172;
  wire `Src2CtrlEnum_binary_sequancial_type _zz_173;
  wire `AluCtrlEnum_binary_sequancial_type _zz_174;
  wire `Src1CtrlEnum_binary_sequancial_type _zz_175;
  wire `BranchCtrlEnum_binary_sequancial_type _zz_176;
  wire `EnvCtrlEnum_binary_sequancial_type _zz_177;
  wire [4:0] decode_RegFilePlugin_regFileReadAddress1;
  wire [4:0] decode_RegFilePlugin_regFileReadAddress2;
  wire [31:0] decode_RegFilePlugin_rs1Data;
  wire  _zz_178;
  wire [31:0] decode_RegFilePlugin_rs2Data;
  wire  _zz_179;
  reg  writeBack_RegFilePlugin_regFileWrite_valid;
  wire [4:0] writeBack_RegFilePlugin_regFileWrite_payload_address;
  wire [31:0] writeBack_RegFilePlugin_regFileWrite_payload_data;
  reg  _zz_180;
  reg [31:0] execute_IntAluPlugin_bitwise;
  reg [31:0] _zz_181;
  reg [31:0] _zz_182;
  wire  _zz_183;
  reg [19:0] _zz_184;
  wire  _zz_185;
  reg [19:0] _zz_186;
  reg [31:0] _zz_187;
  wire [31:0] execute_SrcPlugin_addSub;
  wire  execute_SrcPlugin_less;
  reg  execute_MulPlugin_aSigned;
  reg  execute_MulPlugin_bSigned;
  wire [31:0] execute_MulPlugin_a;
  wire [31:0] execute_MulPlugin_b;
  wire [15:0] execute_MulPlugin_aULow;
  wire [15:0] execute_MulPlugin_bULow;
  wire [16:0] execute_MulPlugin_aSLow;
  wire [16:0] execute_MulPlugin_bSLow;
  wire [16:0] execute_MulPlugin_aHigh;
  wire [16:0] execute_MulPlugin_bHigh;
  wire [65:0] writeBack_MulPlugin_result;
  reg [32:0] memory_DivPlugin_rs1;
  reg [31:0] memory_DivPlugin_rs2;
  reg [64:0] memory_DivPlugin_accumulator;
  reg  memory_DivPlugin_div_needRevert;
  reg  memory_DivPlugin_div_counter_willIncrement;
  reg  memory_DivPlugin_div_counter_willClear;
  reg [5:0] memory_DivPlugin_div_counter_valueNext;
  reg [5:0] memory_DivPlugin_div_counter_value;
  wire  memory_DivPlugin_div_done;
  wire  memory_DivPlugin_div_counter_willOverflow;
  reg [31:0] memory_DivPlugin_div_result;
  wire [31:0] _zz_188;
  wire [32:0] _zz_189;
  wire [32:0] _zz_190;
  wire [31:0] _zz_191;
  wire  _zz_192;
  wire  _zz_193;
  reg [32:0] _zz_194;
  wire [4:0] execute_FullBarrielShifterPlugin_amplitude;
  reg [31:0] _zz_195;
  wire [31:0] execute_FullBarrielShifterPlugin_reversed;
  reg [31:0] _zz_196;
  reg  _zz_197;
  reg  _zz_198;
  reg  _zz_199;
  reg [4:0] _zz_200;
  reg [31:0] _zz_201;
  wire  _zz_202;
  wire  _zz_203;
  wire  _zz_204;
  wire  _zz_205;
  wire  _zz_206;
  wire  _zz_207;
  wire  _zz_208;
  wire [31:0] execute_XbbVectorCordic_rs1;
  wire [31:0] execute_XbbVectorCordic_rs2;
  reg [3:0] execute_XbbVectorCordic_iters;
  wire [31:0] execute_XbbVectorCordic_rd;
  wire [16:0] execute_XbbVectorCordic_theta_0;
  wire [16:0] execute_XbbVectorCordic_theta_1;
  wire [16:0] execute_XbbVectorCordic_theta_2;
  wire [16:0] execute_XbbVectorCordic_theta_3;
  wire [16:0] execute_XbbVectorCordic_theta_4;
  wire [16:0] execute_XbbVectorCordic_theta_5;
  wire [16:0] execute_XbbVectorCordic_theta_6;
  wire [16:0] execute_XbbVectorCordic_theta_7;
  wire [16:0] execute_XbbVectorCordic_theta_8;
  wire [16:0] execute_XbbVectorCordic_theta_9;
  wire [16:0] execute_XbbVectorCordic_theta_10;
  wire [16:0] execute_XbbVectorCordic_theta_11;
  wire [16:0] execute_XbbVectorCordic_theta_12;
  wire [16:0] execute_XbbVectorCordic_theta_13;
  wire [16:0] execute_XbbVectorCordic_theta_14;
  wire [16:0] execute_XbbVectorCordic_theta_15;
  wire  execute_XbbVectorCordic_vfsm_wantExit;
  reg [17:0] execute_XbbVectorCordic_vfsm_x;
  reg [17:0] execute_XbbVectorCordic_vfsm_y;
  reg [17:0] execute_XbbVectorCordic_vfsm_xtmp;
  reg [17:0] execute_XbbVectorCordic_vfsm_ytmp;
  reg [16:0] execute_XbbVectorCordic_vfsm_z;
  reg [3:0] execute_XbbVectorCordic_vfsm_viter;
  reg [1:0] execute_XbbVectorCordic_vfsm_sign;
  wire  execute_XbbVectorCordic_vfsm_isvcordic;
  reg [17:0] execute_XbbVectorCordic_vfsm_stateCompute_xval;
  reg [17:0] execute_XbbVectorCordic_vfsm_stateCompute_yval;
  wire  _zz_209;
  reg [18:0] _zz_210;
  wire  decode_BranchPlugin_conditionalBranchPrediction;
  wire  _zz_211;
  reg [10:0] _zz_212;
  wire  _zz_213;
  reg [18:0] _zz_214;
  wire  execute_BranchPlugin_eq;
  wire [2:0] _zz_215;
  reg  _zz_216;
  reg  _zz_217;
  reg [31:0] execute_BranchPlugin_branch_src1;
  reg [31:0] execute_BranchPlugin_branch_src2;
  wire  _zz_218;
  reg [19:0] _zz_219;
  wire  _zz_220;
  reg [18:0] _zz_221;
  wire [31:0] execute_BranchPlugin_branchAdder;
  reg  DebugPlugin_insertDecodeInstruction;
  reg  DebugPlugin_firstCycle;
  reg  DebugPlugin_secondCycle;
  reg  DebugPlugin_resetIt;
  reg  DebugPlugin_haltIt;
  reg  DebugPlugin_stepIt;
  reg  DebugPlugin_isPipActive;
  reg  _zz_222;
  wire  DebugPlugin_isPipBusy;
  reg  DebugPlugin_haltedByBreak;
  reg [31:0] DebugPlugin_busReadDataReg;
  reg  _zz_223;
  reg  _zz_224;
  reg  _zz_225;
  reg [31:0] _zz_226;
  reg [31:0] _zz_227;
  reg [31:0] _zz_228;
  reg [31:0] _zz_229;
  reg [31:0] _zz_230;
  reg  _zz_231;
  reg  _zz_232;
  reg [33:0] _zz_233;
  reg [33:0] _zz_234;
  reg  _zz_235;
  reg  _zz_236;
  reg  _zz_237;
  reg `EnvCtrlEnum_binary_sequancial_type _zz_238;
  reg `EnvCtrlEnum_binary_sequancial_type _zz_239;
  reg  _zz_240;
  reg  _zz_241;
  reg [31:0] _zz_242;
  reg `BranchCtrlEnum_binary_sequancial_type _zz_243;
  reg  _zz_244;
  reg  _zz_245;
  reg  _zz_246;
  reg `Src1CtrlEnum_binary_sequancial_type _zz_247;
  reg [31:0] _zz_248;
  reg [51:0] _zz_249;
  reg `AluBitwiseCtrlEnum_binary_sequancial_type _zz_250;
  reg [1:0] _zz_251;
  reg [1:0] _zz_252;
  reg  _zz_253;
  reg  _zz_254;
  reg `ShiftCtrlEnum_binary_sequancial_type _zz_255;
  reg `ShiftCtrlEnum_binary_sequancial_type _zz_256;
  reg [31:0] _zz_257;
  reg [31:0] _zz_258;
  reg [31:0] _zz_259;
  reg [31:0] _zz_260;
  reg  _zz_261;
  reg  _zz_262;
  reg  _zz_263;
  reg  _zz_264;
  reg  _zz_265;
  reg `Src2CtrlEnum_binary_sequancial_type _zz_266;
  reg  _zz_267;
  reg [31:0] _zz_268;
  reg [31:0] _zz_269;
  reg [31:0] _zz_270;
  reg [31:0] _zz_271;
  reg [31:0] _zz_272;
  reg  _zz_273;
  reg  _zz_274;
  reg  _zz_275;
  reg [33:0] _zz_276;
  reg  _zz_277;
  reg [31:0] _zz_278;
  reg [31:0] _zz_279;
  reg [31:0] _zz_280;
  reg [31:0] _zz_281;
  reg  _zz_282;
  reg  _zz_283;
  reg  _zz_284;
  reg  _zz_285;
  reg [33:0] _zz_286;
  reg `AluCtrlEnum_binary_sequancial_type _zz_287;
  reg [31:0] _zz_288;
  reg  _zz_289;
  reg  _zz_290;
  reg  _zz_291;
  reg [31:0] _zz_292;
  reg [31:0] _zz_293;
  reg `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_type execute_XbbVectorCordic_vfsm_stateReg;
  reg `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_type execute_XbbVectorCordic_vfsm_stateNext;
  reg [31:0] RegFilePlugin_regFile [0:31];
  assign iBus_cmd_valid = _zz_296;
  assign dBus_cmd_payload_size = _zz_297;
  assign dBus_cmd_payload_address = _zz_298;
  assign debug_bus_cmd_ready = _zz_299;
  assign _zz_368 = (memory_ENV_CTRL == `EnvCtrlEnum_binary_sequancial_MRET);
  assign _zz_369 = (execute_arbitration_isFiring && execute_IS_EBREAK);
  assign _zz_370 = (memory_arbitration_isValid && memory_IS_DIV);
  assign _zz_371 = (! memory_DivPlugin_div_done);
  assign _zz_372 = (execute_XbbVectorCordic_vfsm_viter == execute_XbbVectorCordic_iters);
  assign _zz_373 = (((memory_INSTRUCTION_READY && memory_arbitration_isValid) && memory_BRANCH_DO) && (_zz_106[1 : 0] != (2'b00)));
  assign _zz_374 = debug_bus_cmd_payload_address[2 : 2];
  assign _zz_375 = (CsrPlugin_exception || (CsrPlugin_interrupt && CsrPlugin_pipelineLiberator_done));
  assign _zz_376 = (! memory_arbitration_isStuck);
  assign _zz_377 = (execute_arbitration_isValid && execute_XbbVectorCordic_vfsm_isvcordic);
  assign _zz_378 = (decodeExceptionPort_valid || _zz_109);
  assign _zz_379 = writeBack_INSTRUCTION[13 : 12];
  assign _zz_380 = execute_INSTRUCTION[13];
  assign _zz_381 = execute_INSTRUCTION[13 : 12];
  assign _zz_382 = writeBack_INSTRUCTION[13 : 12];
  assign _zz_383 = (_zz_110 - (3'b001));
  assign _zz_384 = (_zz_122 & (~ _zz_385));
  assign _zz_385 = (_zz_122 - (2'b01));
  assign _zz_386 = ((CsrPlugin_mip_MEIP[1] && CsrPlugin_mie_MEIE[1]) ? (4'b1111) : ((CsrPlugin_mip_MEIP[0] && CsrPlugin_mie_MEIE[0]) ? (4'b1011) : _zz_389));
  assign _zz_387 = {1'd0, _zz_386};
  assign _zz_388 = ((CsrPlugin_mip_MSIP && CsrPlugin_mie_MSIE) ? (3'b011) : (3'b111));
  assign _zz_389 = {1'd0, _zz_388};
  assign _zz_390 = execute_INSTRUCTION[19 : 15];
  assign _zz_391 = {27'd0, _zz_390};
  assign _zz_392 = _zz_163[0 : 0];
  assign _zz_393 = _zz_163[3 : 3];
  assign _zz_394 = _zz_163[4 : 4];
  assign _zz_395 = _zz_163[9 : 9];
  assign _zz_396 = _zz_163[10 : 10];
  assign _zz_397 = _zz_163[11 : 11];
  assign _zz_398 = _zz_163[12 : 12];
  assign _zz_399 = _zz_163[17 : 17];
  assign _zz_400 = _zz_163[18 : 18];
  assign _zz_401 = _zz_163[23 : 23];
  assign _zz_402 = _zz_163[24 : 24];
  assign _zz_403 = _zz_163[25 : 25];
  assign _zz_404 = _zz_163[26 : 26];
  assign _zz_405 = _zz_163[27 : 27];
  assign _zz_406 = _zz_163[28 : 28];
  assign _zz_407 = _zz_163[29 : 29];
  assign _zz_408 = execute_SRC_LESS;
  assign _zz_409 = execute_INSTRUCTION[31 : 20];
  assign _zz_410 = {execute_INSTRUCTION[31 : 25],execute_INSTRUCTION[11 : 7]};
  assign _zz_411 = ($signed(_zz_412) + $signed(_zz_416));
  assign _zz_412 = ($signed(_zz_413) + $signed(_zz_414));
  assign _zz_413 = execute_SRC1;
  assign _zz_414 = (execute_SRC_USE_SUB_LESS ? (~ execute_SRC2) : execute_SRC2);
  assign _zz_415 = (execute_SRC_USE_SUB_LESS ? _zz_417 : _zz_418);
  assign _zz_416 = {{30{_zz_415[1]}}, _zz_415};
  assign _zz_417 = (2'b01);
  assign _zz_418 = (2'b00);
  assign _zz_419 = ($signed(_zz_420) + $signed(_zz_425));
  assign _zz_420 = ($signed(_zz_421) + $signed(_zz_423));
  assign _zz_421 = (52'b0000000000000000000000000000000000000000000000000000);
  assign _zz_422 = {1'b0,memory_MUL_LL};
  assign _zz_423 = {{19{_zz_422[32]}}, _zz_422};
  assign _zz_424 = ({16'd0,memory_MUL_LH} <<< 16);
  assign _zz_425 = {{2{_zz_424[49]}}, _zz_424};
  assign _zz_426 = ({16'd0,memory_MUL_HL} <<< 16);
  assign _zz_427 = {{2{_zz_426[49]}}, _zz_426};
  assign _zz_428 = {{14{writeBack_MUL_LOW[51]}}, writeBack_MUL_LOW};
  assign _zz_429 = ({32'd0,writeBack_MUL_HH} <<< 32);
  assign _zz_430 = writeBack_MUL_LOW[31 : 0];
  assign _zz_431 = writeBack_MulPlugin_result[63 : 32];
  assign _zz_432 = memory_DivPlugin_div_counter_willIncrement;
  assign _zz_433 = {5'd0, _zz_432};
  assign _zz_434 = {1'd0, memory_DivPlugin_rs2};
  assign _zz_435 = {_zz_188,(! _zz_190[32])};
  assign _zz_436 = _zz_190[31:0];
  assign _zz_437 = _zz_189[31:0];
  assign _zz_438 = _zz_439;
  assign _zz_439 = _zz_440;
  assign _zz_440 = ({1'b0,(memory_DivPlugin_div_needRevert ? (~ _zz_191) : _zz_191)} + _zz_442);
  assign _zz_441 = memory_DivPlugin_div_needRevert;
  assign _zz_442 = {32'd0, _zz_441};
  assign _zz_443 = _zz_193;
  assign _zz_444 = {32'd0, _zz_443};
  assign _zz_445 = _zz_192;
  assign _zz_446 = {31'd0, _zz_445};
  assign _zz_447 = ($signed(_zz_449) >>> execute_FullBarrielShifterPlugin_amplitude);
  assign _zz_448 = _zz_447[31 : 0];
  assign _zz_449 = {((execute_SHIFT_CTRL == `ShiftCtrlEnum_binary_sequancial_SRA_1) && execute_FullBarrielShifterPlugin_reversed[31]),execute_FullBarrielShifterPlugin_reversed};
  assign _zz_450 = {{{decode_INSTRUCTION[31],decode_INSTRUCTION[7]},decode_INSTRUCTION[30 : 25]},decode_INSTRUCTION[11 : 8]};
  assign _zz_451 = {{_zz_210,{{{decode_INSTRUCTION[31],decode_INSTRUCTION[7]},decode_INSTRUCTION[30 : 25]},decode_INSTRUCTION[11 : 8]}},1'b0};
  assign _zz_452 = {{{decode_INSTRUCTION[31],decode_INSTRUCTION[19 : 12]},decode_INSTRUCTION[20]},decode_INSTRUCTION[30 : 21]};
  assign _zz_453 = {{{decode_INSTRUCTION[31],decode_INSTRUCTION[7]},decode_INSTRUCTION[30 : 25]},decode_INSTRUCTION[11 : 8]};
  assign _zz_454 = execute_INSTRUCTION[31 : 20];
  assign _zz_455 = {{{execute_INSTRUCTION[31],execute_INSTRUCTION[7]},execute_INSTRUCTION[30 : 25]},execute_INSTRUCTION[11 : 8]};
  assign _zz_456 = execute_CsrPlugin_writeData[7 : 7];
  assign _zz_457 = execute_CsrPlugin_writeData[3 : 3];
  assign _zz_458 = execute_CsrPlugin_writeData[0 : 0];
  assign _zz_459 = execute_CsrPlugin_writeData[0 : 0];
  assign _zz_460 = execute_CsrPlugin_writeData[3 : 3];
  assign _zz_461 = execute_CsrPlugin_writeData[0 : 0];
  assign _zz_462 = execute_CsrPlugin_writeData[0 : 0];
  assign _zz_463 = execute_CsrPlugin_writeData[0 : 0];
  assign _zz_464 = execute_CsrPlugin_writeData[31 : 31];
  assign _zz_465 = execute_CsrPlugin_writeData[27 : 27];
  assign _zz_466 = execute_CsrPlugin_writeData[23 : 23];
  assign _zz_467 = execute_CsrPlugin_writeData[19 : 19];
  assign _zz_468 = execute_CsrPlugin_writeData[15 : 15];
  assign _zz_469 = execute_CsrPlugin_writeData[11 : 11];
  assign _zz_470 = execute_CsrPlugin_writeData[7 : 7];
  assign _zz_471 = execute_CsrPlugin_writeData[3 : 3];
  assign _zz_472 = execute_CsrPlugin_writeData[0 : 0];
  assign _zz_473 = execute_CsrPlugin_writeData[0 : 0];
  assign _zz_474 = (18'b000000000000000000);
  assign _zz_475 = (18'b000000000000000000);
  assign _zz_476 = execute_XbbVectorCordic_theta_0;
  assign _zz_477 = execute_XbbVectorCordic_theta_0;
  assign _zz_478 = (18'b000000000000000000);
  assign _zz_479 = execute_XbbVectorCordic_theta_1;
  assign _zz_480 = execute_XbbVectorCordic_theta_1;
  assign _zz_481 = (18'b000000000000000000);
  assign _zz_482 = execute_XbbVectorCordic_theta_2;
  assign _zz_483 = execute_XbbVectorCordic_theta_2;
  assign _zz_484 = (18'b000000000000000000);
  assign _zz_485 = execute_XbbVectorCordic_theta_3;
  assign _zz_486 = execute_XbbVectorCordic_theta_3;
  assign _zz_487 = (18'b000000000000000000);
  assign _zz_488 = execute_XbbVectorCordic_theta_4;
  assign _zz_489 = execute_XbbVectorCordic_theta_4;
  assign _zz_490 = (18'b000000000000000000);
  assign _zz_491 = execute_XbbVectorCordic_theta_5;
  assign _zz_492 = execute_XbbVectorCordic_theta_5;
  assign _zz_493 = (18'b000000000000000000);
  assign _zz_494 = execute_XbbVectorCordic_theta_6;
  assign _zz_495 = execute_XbbVectorCordic_theta_6;
  assign _zz_496 = (18'b000000000000000000);
  assign _zz_497 = execute_XbbVectorCordic_theta_7;
  assign _zz_498 = execute_XbbVectorCordic_theta_7;
  assign _zz_499 = (18'b000000000000000000);
  assign _zz_500 = execute_XbbVectorCordic_theta_8;
  assign _zz_501 = execute_XbbVectorCordic_theta_8;
  assign _zz_502 = (18'b000000000000000000);
  assign _zz_503 = execute_XbbVectorCordic_theta_9;
  assign _zz_504 = execute_XbbVectorCordic_theta_9;
  assign _zz_505 = (18'b000000000000000000);
  assign _zz_506 = execute_XbbVectorCordic_theta_10;
  assign _zz_507 = execute_XbbVectorCordic_theta_10;
  assign _zz_508 = (18'b000000000000000000);
  assign _zz_509 = execute_XbbVectorCordic_theta_11;
  assign _zz_510 = execute_XbbVectorCordic_theta_11;
  assign _zz_511 = (18'b000000000000000000);
  assign _zz_512 = execute_XbbVectorCordic_theta_12;
  assign _zz_513 = execute_XbbVectorCordic_theta_12;
  assign _zz_514 = (18'b000000000000000000);
  assign _zz_515 = execute_XbbVectorCordic_theta_13;
  assign _zz_516 = execute_XbbVectorCordic_theta_13;
  assign _zz_517 = (18'b000000000000000000);
  assign _zz_518 = execute_XbbVectorCordic_theta_14;
  assign _zz_519 = execute_XbbVectorCordic_theta_14;
  assign _zz_520 = (18'b000000000000000000);
  assign _zz_521 = execute_XbbVectorCordic_theta_15;
  assign _zz_522 = execute_XbbVectorCordic_theta_15;
  assign _zz_523 = (17'b11111111111111111);
  assign _zz_524 = (17'b00000000000000000);
  assign _zz_525 = (17'b00111111111111111);
  assign _zz_526 = ($signed(execute_XbbVectorCordic_vfsm_z) >>> (1'b1));
  assign _zz_527 = (17'b01000000000000000);
  assign _zz_528 = ($signed(execute_XbbVectorCordic_vfsm_z) >>> (1'b1));
  assign _zz_529 = execute_XbbVectorCordic_vfsm_x[17 : 2];
  assign _zz_530 = execute_XbbVectorCordic_vfsm_z[15 : 0];
  assign _zz_531 = {_zz_113,_zz_112};
  assign _zz_532 = CsrPlugin_mip_MEIP[5];
  assign _zz_533 = CsrPlugin_mie_MEIE[5];
  assign _zz_534 = {{{{{{{{{{{_zz_536,_zz_537},MapperMoverCsrPlugin_mover_active_reg20},MapperMoverCsrPlugin_mover_active_reg19},MapperMoverCsrPlugin_mover_active_reg18},MapperMoverCsrPlugin_mover_active_reg17},MapperMoverCsrPlugin_mover_active_reg16},MapperMoverCsrPlugin_mover_active_reg15},MapperMoverCsrPlugin_mover_active_reg14},MapperMoverCsrPlugin_mover_active_reg13},MapperMoverCsrPlugin_mover_active_reg12},MapperMoverCsrPlugin_mover_active_reg11};
  assign _zz_535 = MapperMoverCsrPlugin_mover_active_reg10;
  assign _zz_536 = {{{{{{{{{MapperMoverCsrPlugin_mover_active_reg31,MapperMoverCsrPlugin_mover_active_reg30},MapperMoverCsrPlugin_mover_active_reg29},MapperMoverCsrPlugin_mover_active_reg28},MapperMoverCsrPlugin_mover_active_reg27},MapperMoverCsrPlugin_mover_active_reg26},MapperMoverCsrPlugin_mover_active_reg25},MapperMoverCsrPlugin_mover_active_reg24},MapperMoverCsrPlugin_mover_active_reg23},MapperMoverCsrPlugin_mover_active_reg22};
  assign _zz_537 = MapperMoverCsrPlugin_mover_active_reg21;
  assign _zz_538 = (32'b00000000000000000000000001011000);
  assign _zz_539 = ((decode_INSTRUCTION & (32'b00000000000000000010000000010000)) == (32'b00000000000000000010000000000000));
  assign _zz_540 = ((decode_INSTRUCTION & (32'b00000000000000000101000000000000)) == (32'b00000000000000000001000000000000));
  assign _zz_541 = _zz_164;
  assign _zz_542 = (1'b0);
  assign _zz_543 = ({(_zz_546 == _zz_547),(_zz_548 == _zz_549)} != (2'b00));
  assign _zz_544 = ({_zz_167,{_zz_550,_zz_551}} != (6'b000000));
  assign _zz_545 = {({_zz_552,_zz_553} != (6'b000000)),{(_zz_554 != _zz_555),{_zz_556,{_zz_557,_zz_558}}}};
  assign _zz_546 = (decode_INSTRUCTION & (32'b00000000000000000001000001010000));
  assign _zz_547 = (32'b00000000000000000001000001010000);
  assign _zz_548 = (decode_INSTRUCTION & (32'b00000000000000000010000001010000));
  assign _zz_549 = (32'b00000000000000000010000001010000);
  assign _zz_550 = _zz_165;
  assign _zz_551 = {(_zz_559 == _zz_560),{_zz_561,{_zz_562,_zz_563}}};
  assign _zz_552 = _zz_165;
  assign _zz_553 = {(_zz_564 == _zz_565),{_zz_566,{_zz_567,_zz_568}}};
  assign _zz_554 = ((decode_INSTRUCTION & _zz_569) == (32'b00000000000000000000000001010000));
  assign _zz_555 = (1'b0);
  assign _zz_556 = 1'b0;
  assign _zz_557 = (_zz_169 != (1'b0));
  assign _zz_558 = {(_zz_570 != _zz_571),{_zz_572,{_zz_573,_zz_574}}};
  assign _zz_559 = (decode_INSTRUCTION & (32'b00000000000000000100000000010000));
  assign _zz_560 = (32'b00000000000000000100000000010000);
  assign _zz_561 = ((decode_INSTRUCTION & _zz_575) == (32'b00000000000000000000000000010000));
  assign _zz_562 = _zz_170;
  assign _zz_563 = (_zz_576 == _zz_577);
  assign _zz_564 = (decode_INSTRUCTION & (32'b00000000000000000000000000101000));
  assign _zz_565 = (32'b00000000000000000000000000101000);
  assign _zz_566 = ((decode_INSTRUCTION & _zz_578) == (32'b00000000000000000001000000010000));
  assign _zz_567 = (_zz_579 == _zz_580);
  assign _zz_568 = {_zz_581,_zz_582};
  assign _zz_569 = (32'b00000000000100000011000001010000);
  assign _zz_570 = (_zz_583 == _zz_584);
  assign _zz_571 = (1'b0);
  assign _zz_572 = (_zz_585 != (1'b0));
  assign _zz_573 = (_zz_586 != _zz_587);
  assign _zz_574 = {_zz_588,{_zz_589,_zz_590}};
  assign _zz_575 = (32'b00000000000000000000000000110000);
  assign _zz_576 = (decode_INSTRUCTION & (32'b00000010000000000000000000101000));
  assign _zz_577 = (32'b00000000000000000000000000100000);
  assign _zz_578 = (32'b00000000000000000001000000010000);
  assign _zz_579 = (decode_INSTRUCTION & (32'b00000000000000000010000000010000));
  assign _zz_580 = (32'b00000000000000000010000000010000);
  assign _zz_581 = ((decode_INSTRUCTION & (32'b00000000000000000000000001010000)) == (32'b00000000000000000000000000010000));
  assign _zz_582 = ((decode_INSTRUCTION & (32'b00000000000000000000000000101000)) == (32'b00000000000000000000000000000000));
  assign _zz_583 = (decode_INSTRUCTION & (32'b00000000000000000000000001011000));
  assign _zz_584 = (32'b00000000000000000000000001000000);
  assign _zz_585 = ((decode_INSTRUCTION & (32'b00000010000000000100000001101100)) == (32'b00000010000000000100000000100000));
  assign _zz_586 = ((decode_INSTRUCTION & _zz_591) == (32'b00000000000000000000000001010000));
  assign _zz_587 = (1'b0);
  assign _zz_588 = (_zz_169 != (1'b0));
  assign _zz_589 = (_zz_592 != (1'b0));
  assign _zz_590 = {(_zz_593 != _zz_594),{_zz_595,{_zz_596,_zz_597}}};
  assign _zz_591 = (32'b00100000000000000011000001010000);
  assign _zz_592 = ((decode_INSTRUCTION & (32'b00000000000000000000000001000100)) == (32'b00000000000000000000000000000100));
  assign _zz_593 = {((decode_INSTRUCTION & _zz_598) == (32'b00000000000000000100000000000000)),((decode_INSTRUCTION & _zz_599) == (32'b00000000000000000000000000100100))};
  assign _zz_594 = (2'b00);
  assign _zz_595 = (_zz_168 != (1'b0));
  assign _zz_596 = ({_zz_600,{_zz_601,_zz_602}} != (4'b0000));
  assign _zz_597 = {({_zz_603,_zz_604} != (7'b0000000)),{(_zz_605 != _zz_606),{_zz_607,{_zz_608,_zz_609}}}};
  assign _zz_598 = (32'b00000000000000000100000000000100);
  assign _zz_599 = (32'b00000000000000000000000001100100);
  assign _zz_600 = ((decode_INSTRUCTION & _zz_610) == (32'b00000000000000000000000000000000));
  assign _zz_601 = (_zz_611 == _zz_612);
  assign _zz_602 = {_zz_168,_zz_613};
  assign _zz_603 = (_zz_614 == _zz_615);
  assign _zz_604 = {_zz_167,{_zz_616,_zz_617}};
  assign _zz_605 = (_zz_618 == _zz_619);
  assign _zz_606 = (1'b0);
  assign _zz_607 = ({_zz_620,_zz_621} != (2'b00));
  assign _zz_608 = (_zz_622 != _zz_623);
  assign _zz_609 = {_zz_624,{_zz_625,_zz_626}};
  assign _zz_610 = (32'b00000000000000000000000001000100);
  assign _zz_611 = (decode_INSTRUCTION & (32'b00000000000000000000000000011000));
  assign _zz_612 = (32'b00000000000000000000000000000000);
  assign _zz_613 = ((decode_INSTRUCTION & _zz_627) == (32'b00000000000000000001000000000000));
  assign _zz_614 = (decode_INSTRUCTION & (32'b00000000000000000000000000001000));
  assign _zz_615 = (32'b00000000000000000000000000001000);
  assign _zz_616 = _zz_165;
  assign _zz_617 = {_zz_628,{_zz_629,_zz_630}};
  assign _zz_618 = (decode_INSTRUCTION & (32'b00000010000000000100000001110100));
  assign _zz_619 = (32'b00000010000000000000000000110000);
  assign _zz_620 = (_zz_631 == _zz_632);
  assign _zz_621 = (_zz_633 == _zz_634);
  assign _zz_622 = {_zz_165,{_zz_635,_zz_636}};
  assign _zz_623 = (3'b000);
  assign _zz_624 = ({_zz_637,_zz_638} != (3'b000));
  assign _zz_625 = (_zz_639 != _zz_640);
  assign _zz_626 = {_zz_641,{_zz_642,_zz_643}};
  assign _zz_627 = (32'b00000000000000000101000000000100);
  assign _zz_628 = ((decode_INSTRUCTION & _zz_644) == (32'b00000000000000000010000000010000));
  assign _zz_629 = (_zz_645 == _zz_646);
  assign _zz_630 = {_zz_647,_zz_648};
  assign _zz_631 = (decode_INSTRUCTION & (32'b00000000000000000000000000110100));
  assign _zz_632 = (32'b00000000000000000000000000100000);
  assign _zz_633 = (decode_INSTRUCTION & (32'b00000000000000000000000001100100));
  assign _zz_634 = (32'b00000000000000000000000000100000);
  assign _zz_635 = _zz_166;
  assign _zz_636 = (_zz_649 == _zz_650);
  assign _zz_637 = _zz_165;
  assign _zz_638 = {_zz_651,_zz_166};
  assign _zz_639 = {_zz_652,_zz_165};
  assign _zz_640 = (2'b00);
  assign _zz_641 = ({_zz_653,_zz_654} != (2'b00));
  assign _zz_642 = (_zz_655 != _zz_656);
  assign _zz_643 = {_zz_657,{_zz_658,_zz_659}};
  assign _zz_644 = (32'b00000000000000000010000000110000);
  assign _zz_645 = (decode_INSTRUCTION & (32'b00000010000000000010000000100000));
  assign _zz_646 = (32'b00000000000000000010000000100000);
  assign _zz_647 = ((decode_INSTRUCTION & (32'b00000010000000000001000000100000)) == (32'b00000000000000000000000000100000));
  assign _zz_648 = ((decode_INSTRUCTION & (32'b00000000000000000001000000110000)) == (32'b00000000000000000000000000010000));
  assign _zz_649 = (decode_INSTRUCTION & (32'b00000000000000000000000001110000));
  assign _zz_650 = (32'b00000000000000000000000000100000);
  assign _zz_651 = ((decode_INSTRUCTION & (32'b00000000000000000000000000100000)) == (32'b00000000000000000000000000000000));
  assign _zz_652 = ((decode_INSTRUCTION & (32'b00000000000000000001000000000000)) == (32'b00000000000000000001000000000000));
  assign _zz_653 = _zz_165;
  assign _zz_654 = ((decode_INSTRUCTION & _zz_660) == (32'b00000000000000000010000000000000));
  assign _zz_655 = ((decode_INSTRUCTION & _zz_661) == (32'b00000000000000000000000000101000));
  assign _zz_656 = (1'b0);
  assign _zz_657 = ({_zz_662,{_zz_663,_zz_664}} != (3'b000));
  assign _zz_658 = ({_zz_665,_zz_666} != (2'b00));
  assign _zz_659 = {(_zz_667 != _zz_668),(_zz_669 != _zz_670)};
  assign _zz_660 = (32'b00000000000000000011000000000000);
  assign _zz_661 = (32'b00000000000000000000000001101000);
  assign _zz_662 = ((decode_INSTRUCTION & (32'b01000000000000000000000000110000)) == (32'b01000000000000000000000000110000));
  assign _zz_663 = ((decode_INSTRUCTION & (32'b00000000000000000010000000010100)) == (32'b00000000000000000010000000010000));
  assign _zz_664 = ((decode_INSTRUCTION & (32'b00000000000000000000000001010100)) == (32'b00000000000000000000000001000000));
  assign _zz_665 = ((decode_INSTRUCTION & (32'b00000000000000000111000000110100)) == (32'b00000000000000000101000000010000));
  assign _zz_666 = ((decode_INSTRUCTION & (32'b00000010000000000111000001101100)) == (32'b00000000000000000101000000100000));
  assign _zz_667 = {((decode_INSTRUCTION & _zz_671) == (32'b01000000000000000001000000010000)),{(_zz_672 == _zz_673),(_zz_674 == _zz_675)}};
  assign _zz_668 = (3'b000);
  assign _zz_669 = _zz_164;
  assign _zz_670 = (1'b0);
  assign _zz_671 = (32'b01000000000000000011000001010100);
  assign _zz_672 = (decode_INSTRUCTION & (32'b00000000000000000111000000110100));
  assign _zz_673 = (32'b00000000000000000001000000010000);
  assign _zz_674 = (decode_INSTRUCTION & (32'b00000010000000000111000001010100));
  assign _zz_675 = (32'b00000000000000000001000000010000);
  assign _zz_676 = (32'b00000000000000000001000001101111);
  assign _zz_677 = (decode_INSTRUCTION & (32'b00000000000000000001000001111111));
  assign _zz_678 = (32'b00000000000000000001000001110011);
  assign _zz_679 = ((decode_INSTRUCTION & (32'b00000000000000000010000001111111)) == (32'b00000000000000000010000001110011));
  assign _zz_680 = ((decode_INSTRUCTION & (32'b00000000000000000100000001111111)) == (32'b00000000000000000100000001100011));
  assign _zz_681 = {((decode_INSTRUCTION & (32'b00000000000000000010000001111111)) == (32'b00000000000000000010000000010011)),{((decode_INSTRUCTION & (32'b00000000000000000110000000111111)) == (32'b00000000000000000000000000100011)),{((decode_INSTRUCTION & _zz_682) == (32'b00000000000000000000000000000011)),{(_zz_683 == _zz_684),{_zz_685,{_zz_686,_zz_687}}}}}};
  assign _zz_682 = (32'b00000000000000000010000001111111);
  assign _zz_683 = (decode_INSTRUCTION & (32'b00000000000000000101000001011111));
  assign _zz_684 = (32'b00000000000000000000000000000011);
  assign _zz_685 = ((decode_INSTRUCTION & (32'b00000000000000000111000001111011)) == (32'b00000000000000000000000001100011));
  assign _zz_686 = ((decode_INSTRUCTION & (32'b11111100000000000000000001111111)) == (32'b00000000000000000000000000110011));
  assign _zz_687 = {((decode_INSTRUCTION & (32'b10111100000000000111000001111111)) == (32'b00000000000000000101000000010011)),{((decode_INSTRUCTION & (32'b11111100000000000011000001111111)) == (32'b00000000000000000001000000010011)),{((decode_INSTRUCTION & _zz_688) == (32'b00000000000000000101000000110011)),{(_zz_689 == _zz_690),{_zz_691,_zz_692}}}}};
  assign _zz_688 = (32'b10111110000000000111000001111111);
  assign _zz_689 = (decode_INSTRUCTION & (32'b10111110000000000111000001111111));
  assign _zz_690 = (32'b00000000000000000000000000110011);
  assign _zz_691 = ((decode_INSTRUCTION & (32'b11111111111111111111111111111111)) == (32'b00110000001000000000000001110011));
  assign _zz_692 = ((decode_INSTRUCTION & (32'b11111111111111111111111111111111)) == (32'b00000000000100000000000001110011));
  assign _zz_693 = decode_INSTRUCTION[31];
  assign _zz_694 = decode_INSTRUCTION[19 : 12];
  assign _zz_695 = decode_INSTRUCTION[20];
  assign _zz_696 = decode_INSTRUCTION[31];
  assign _zz_697 = decode_INSTRUCTION[7];
  always @ (posedge io_mainClk) begin
    if(_zz_54) begin
      RegFilePlugin_regFile[writeBack_RegFilePlugin_regFileWrite_payload_address] <= writeBack_RegFilePlugin_regFileWrite_payload_data;
    end
  end

  always @ (posedge io_mainClk) begin
    if(_zz_178) begin
      _zz_294 <= RegFilePlugin_regFile[decode_RegFilePlugin_regFileReadAddress1];
    end
  end

  always @ (posedge io_mainClk) begin
    if(_zz_179) begin
      _zz_295 <= RegFilePlugin_regFile[decode_RegFilePlugin_regFileReadAddress2];
    end
  end

  StreamFifo DmaCsrPlugin_configFifo ( 
    .io_push_valid(DmaCsrPlugin_configPush_valid),
    .io_push_ready(_zz_303),
    .io_push_payload_startAddr(DmaCsrPlugin_configPush_payload_startAddr),
    .io_push_payload_length(DmaCsrPlugin_configPush_payload_length),
    .io_push_payload_timerInit(DmaCsrPlugin_configPush_payload_timerInit),
    .io_push_payload_slicer(DmaCsrPlugin_configPush_payload_slicer),
    .io_push_payload_reverse(DmaCsrPlugin_configPush_payload_reverse),
    .io_push_payload_last_or_run_till_last(DmaCsrPlugin_configPush_payload_last_or_run_till_last),
    .io_push_payload_demapper_constellation(DmaCsrPlugin_configPush_payload_demapper_constellation),
    .io_push_payload_demapper_two_over_sigma_sq(DmaCsrPlugin_configPush_payload_demapper_two_over_sigma_sq),
    .io_pop_valid(_zz_304),
    .io_pop_ready(dma_0_config_ready),
    .io_pop_payload_startAddr(_zz_305),
    .io_pop_payload_length(_zz_306),
    .io_pop_payload_timerInit(_zz_307),
    .io_pop_payload_slicer(_zz_308),
    .io_pop_payload_reverse(_zz_309),
    .io_pop_payload_last_or_run_till_last(_zz_310),
    .io_pop_payload_demapper_constellation(_zz_311),
    .io_pop_payload_demapper_two_over_sigma_sq(_zz_312),
    .io_flush(_zz_129),
    .io_occupancy(_zz_313),
    .io_availability(_zz_314),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  StreamFifo DmaCsrPlugin_configFifo_1 ( 
    .io_push_valid(DmaCsrPlugin_configPush_valid_1),
    .io_push_ready(_zz_315),
    .io_push_payload_startAddr(DmaCsrPlugin_configPush_payload_startAddr_1),
    .io_push_payload_length(DmaCsrPlugin_configPush_payload_length_1),
    .io_push_payload_timerInit(DmaCsrPlugin_configPush_payload_timerInit_1),
    .io_push_payload_slicer(DmaCsrPlugin_configPush_payload_slicer_1),
    .io_push_payload_reverse(DmaCsrPlugin_configPush_payload_reverse_1),
    .io_push_payload_last_or_run_till_last(DmaCsrPlugin_configPush_payload_last_or_run_till_last_1),
    .io_push_payload_demapper_constellation(DmaCsrPlugin_configPush_payload_demapper_constellation_1),
    .io_push_payload_demapper_two_over_sigma_sq(DmaCsrPlugin_configPush_payload_demapper_two_over_sigma_sq_1),
    .io_pop_valid(_zz_316),
    .io_pop_ready(dma_1_config_ready),
    .io_pop_payload_startAddr(_zz_317),
    .io_pop_payload_length(_zz_318),
    .io_pop_payload_timerInit(_zz_319),
    .io_pop_payload_slicer(_zz_320),
    .io_pop_payload_reverse(_zz_321),
    .io_pop_payload_last_or_run_till_last(_zz_322),
    .io_pop_payload_demapper_constellation(_zz_323),
    .io_pop_payload_demapper_two_over_sigma_sq(_zz_324),
    .io_flush(_zz_135),
    .io_occupancy(_zz_325),
    .io_availability(_zz_326),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  StreamFifo DmaCsrPlugin_configFifo_2 ( 
    .io_push_valid(DmaCsrPlugin_configPush_valid_2),
    .io_push_ready(_zz_327),
    .io_push_payload_startAddr(DmaCsrPlugin_configPush_payload_startAddr_2),
    .io_push_payload_length(DmaCsrPlugin_configPush_payload_length_2),
    .io_push_payload_timerInit(DmaCsrPlugin_configPush_payload_timerInit_2),
    .io_push_payload_slicer(DmaCsrPlugin_configPush_payload_slicer_2),
    .io_push_payload_reverse(DmaCsrPlugin_configPush_payload_reverse_2),
    .io_push_payload_last_or_run_till_last(DmaCsrPlugin_configPush_payload_last_or_run_till_last_2),
    .io_push_payload_demapper_constellation(DmaCsrPlugin_configPush_payload_demapper_constellation_2),
    .io_push_payload_demapper_two_over_sigma_sq(DmaCsrPlugin_configPush_payload_demapper_two_over_sigma_sq_2),
    .io_pop_valid(_zz_328),
    .io_pop_ready(dma_2_config_ready),
    .io_pop_payload_startAddr(_zz_329),
    .io_pop_payload_length(_zz_330),
    .io_pop_payload_timerInit(_zz_331),
    .io_pop_payload_slicer(_zz_332),
    .io_pop_payload_reverse(_zz_333),
    .io_pop_payload_last_or_run_till_last(_zz_334),
    .io_pop_payload_demapper_constellation(_zz_335),
    .io_pop_payload_demapper_two_over_sigma_sq(_zz_336),
    .io_flush(_zz_141),
    .io_occupancy(_zz_337),
    .io_availability(_zz_338),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  StreamFifo_3 RingBusCsrPlugin_writeFifo ( 
    .io_push_valid(RingBusCsrPlugin_writePush_valid),
    .io_push_ready(_zz_339),
    .io_push_payload_write_data(RingBusCsrPlugin_writePush_payload_write_data),
    .io_push_payload_write_addr(RingBusCsrPlugin_writePush_payload_write_addr),
    .io_pop_valid(_zz_340),
    .io_pop_ready(ringbus_0_config_ready),
    .io_pop_payload_write_data(_zz_341),
    .io_pop_payload_write_addr(_zz_342),
    .io_flush(_zz_149),
    .io_occupancy(_zz_343),
    .io_availability(_zz_344),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  StreamFifo_4 RingBusCsrPlugin_readFifo ( 
    .io_push_valid(RingBusCsrPlugin_readPush_valid),
    .io_push_ready(_zz_345),
    .io_push_payload_read_data(RingBusCsrPlugin_readPush_payload_read_data),
    .io_pop_valid(_zz_346),
    .io_pop_ready(RingBusCsrPlugin_readPop_ready),
    .io_pop_payload_read_data(_zz_347),
    .io_flush(_zz_151),
    .io_occupancy(_zz_348),
    .io_availability(_zz_349),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  StreamFifo_3 RingBusCsrPlugin_writeFifo_1 ( 
    .io_push_valid(RingBusCsrPlugin_writePush_valid_1),
    .io_push_ready(_zz_350),
    .io_push_payload_write_data(RingBusCsrPlugin_writePush_payload_write_data_1),
    .io_push_payload_write_addr(RingBusCsrPlugin_writePush_payload_write_addr_1),
    .io_pop_valid(_zz_351),
    .io_pop_ready(ringbus_1_config_ready),
    .io_pop_payload_write_data(_zz_352),
    .io_pop_payload_write_addr(_zz_353),
    .io_flush(_zz_154),
    .io_occupancy(_zz_354),
    .io_availability(_zz_355),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  StreamFifo_4 RingBusCsrPlugin_readFifo_1 ( 
    .io_push_valid(RingBusCsrPlugin_readPush_valid_1),
    .io_push_ready(_zz_356),
    .io_push_payload_read_data(RingBusCsrPlugin_readPush_payload_read_data_1),
    .io_pop_valid(_zz_357),
    .io_pop_ready(RingBusCsrPlugin_readPop_ready_1),
    .io_pop_payload_read_data(_zz_358),
    .io_flush(_zz_156),
    .io_occupancy(_zz_359),
    .io_availability(_zz_360),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  StreamFifo_7 NCOCsrPlugin_configFifo ( 
    .io_push_valid(NCOCsrPlugin_configPush_valid),
    .io_push_ready(_zz_361),
    .io_push_payload_startAngle(NCOCsrPlugin_configPush_payload_startAngle),
    .io_push_payload_length(NCOCsrPlugin_configPush_payload_length),
    .io_push_payload_delta(NCOCsrPlugin_configPush_payload_delta),
    .io_pop_valid(_zz_362),
    .io_pop_ready(nco_0_config_ready),
    .io_pop_payload_startAngle(_zz_363),
    .io_pop_payload_length(_zz_364),
    .io_pop_payload_delta(_zz_365),
    .io_flush(_zz_158),
    .io_occupancy(_zz_366),
    .io_availability(_zz_367),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  always @(*) begin
    case(_zz_531)
      2'b00 : begin
        _zz_300 = _zz_106;
      end
      2'b01 : begin
        _zz_300 = _zz_100;
      end
      default : begin
        _zz_300 = _zz_108;
      end
    endcase
  end

  always @(*) begin
    case(_zz_124)
      1'b0 : begin
        _zz_301 = decodeExceptionPort_payload_code;
        _zz_302 = decodeExceptionPort_payload_badAddr;
      end
      default : begin
        _zz_301 = (5'b00000);
        _zz_302 = _zz_108;
      end
    endcase
  end

  assign execute_SHIFT_RIGHT = _zz_32;
  assign execute_MUL_LL = _zz_39;
  assign execute_BRANCH_CALC = _zz_26;
  assign decode_ALU_CTRL = _zz_1;
  assign _zz_2 = _zz_3;
  assign execute_MUL_LH = _zz_38;
  assign decode_MEMORY_ENABLE = _zz_57;
  assign decode_BYPASSABLE_EXECUTE_STAGE = _zz_71;
  assign memory_FORMAL_PC_NEXT = _zz_281;
  assign execute_FORMAL_PC_NEXT = _zz_280;
  assign decode_FORMAL_PC_NEXT = _zz_279;
  assign fetch_FORMAL_PC_NEXT = _zz_278;
  assign prefetch_FORMAL_PC_NEXT = _zz_96;
  assign decode_IS_RS2_SIGNED = _zz_79;
  assign execute_MUL_HL = _zz_37;
  assign decode_CSR_READ_OPCODE = _zz_82;
  assign decode_IS_DIV = _zz_66;
  assign memory_PC = _zz_271;
  assign fetch_PC = _zz_268;
  assign decode_SRC_USE_SUB_LESS = _zz_77;
  assign decode_SRC2_CTRL = _zz_4;
  assign _zz_5 = _zz_6;
  assign memory_IS_MUL = _zz_264;
  assign execute_IS_MUL = _zz_263;
  assign decode_IS_MUL = _zz_72;
  assign decode_CSR_WRITE_OPCODE = _zz_83;
  assign execute_BRANCH_DO = _zz_27;
  assign fetch_INSTRUCTION = _zz_92;
  assign _zz_7 = _zz_8;
  assign decode_SHIFT_CTRL = _zz_9;
  assign _zz_10 = _zz_11;
  assign decode_IS_RS1_SIGNED = _zz_60;
  assign memory_MEMORY_ADDRESS_LOW = _zz_251;
  assign execute_MEMORY_ADDRESS_LOW = _zz_87;
  assign decode_ALU_BITWISE_CTRL = _zz_12;
  assign _zz_13 = _zz_14;
  assign memory_MUL_LOW = _zz_35;
  assign memory_MEMORY_READ_DATA = _zz_86;
  assign decode_SRC1_CTRL = _zz_15;
  assign _zz_16 = _zz_17;
  assign writeBack_IS_XBASEBAND = _zz_246;
  assign memory_IS_XBASEBAND = _zz_245;
  assign execute_IS_XBASEBAND = _zz_244;
  assign decode_IS_XBASEBAND = _zz_58;
  assign _zz_18 = _zz_19;
  assign decode_SRC_LESS_UNSIGNED = _zz_59;
  assign decode_IS_VCORDIC = _zz_76;
  assign execute_ENV_CTRL = _zz_20;
  assign _zz_21 = _zz_22;
  assign decode_ENV_CTRL = _zz_23;
  assign _zz_24 = _zz_25;
  assign execute_INSTRUCTION_READY = _zz_236;
  assign memory_MUL_HH = _zz_233;
  assign execute_MUL_HH = _zz_36;
  assign execute_BYPASSABLE_MEMORY_STAGE = _zz_231;
  assign decode_BYPASSABLE_MEMORY_STAGE = _zz_62;
  assign memory_RS1 = _zz_229;
  assign writeBack_REGFILE_WRITE_DATA = _zz_227;
  assign execute_REGFILE_WRITE_DATA = _zz_50;
  assign decode_IS_EBREAK = _zz_67;
  assign execute_IS_EBREAK = _zz_225;
  assign memory_INSTRUCTION_READY = _zz_237;
  assign memory_BRANCH_CALC = _zz_288;
  assign memory_BRANCH_DO = _zz_261;
  assign execute_PC = _zz_270;
  assign execute_PREDICTION_HAD_BRANCHED2 = _zz_235;
  assign execute_BRANCH_CTRL = _zz_28;
  assign decode_PREDICTION_HAD_BRANCHED2 = _zz_30;
  assign decode_BRANCH_CTRL = _zz_29;
  assign execute_IS_VCORDIC = _zz_240;
  assign writeBack_RS1 = _zz_230;
  assign decode_RS2_USE = _zz_73;
  assign decode_RS1_USE = _zz_70;
  assign execute_REGFILE_WRITE_VALID = _zz_289;
  assign execute_BYPASSABLE_EXECUTE_STAGE = _zz_282;
  assign memory_REGFILE_WRITE_VALID = _zz_290;
  assign memory_BYPASSABLE_MEMORY_STAGE = _zz_232;
  assign writeBack_REGFILE_WRITE_VALID = _zz_291;
  always @ (*) begin
    decode_RS2 = _zz_55;
    decode_RS1 = _zz_56;
    if(_zz_199)begin
      if((_zz_200 == decode_INSTRUCTION[19 : 15]))begin
        decode_RS1 = _zz_201;
      end
      if((_zz_200 == decode_INSTRUCTION[24 : 20]))begin
        decode_RS2 = _zz_201;
      end
    end
    if((writeBack_arbitration_isValid && writeBack_REGFILE_WRITE_VALID))begin
      if(_zz_202)begin
        if(_zz_203)begin
          decode_RS1 = _zz_85;
        end
        if(_zz_204)begin
          decode_RS2 = _zz_85;
        end
      end
    end
    if((memory_arbitration_isValid && memory_REGFILE_WRITE_VALID))begin
      if(memory_BYPASSABLE_MEMORY_STAGE)begin
        if(_zz_205)begin
          decode_RS1 = _zz_34;
        end
        if(_zz_206)begin
          decode_RS2 = _zz_34;
        end
      end
    end
    if((execute_arbitration_isValid && execute_REGFILE_WRITE_VALID))begin
      if(execute_BYPASSABLE_EXECUTE_STAGE)begin
        if(_zz_207)begin
          decode_RS1 = _zz_81;
        end
        if(_zz_208)begin
          decode_RS2 = _zz_81;
        end
      end
    end
  end

  assign memory_SHIFT_RIGHT = _zz_293;
  assign memory_SHIFT_CTRL = _zz_31;
  assign execute_SHIFT_CTRL = _zz_33;
  assign execute_IS_RS1_SIGNED = _zz_254;
  assign execute_RS1 = _zz_228;
  assign execute_IS_DIV = _zz_273;
  assign execute_IS_RS2_SIGNED = _zz_277;
  always @ (*) begin
    _zz_34 = memory_REGFILE_WRITE_DATA;
    memory_arbitration_haltItself = 1'b0;
    _zz_99 = 1'b0;
    _zz_100 = (32'bxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx);
    if((((memory_arbitration_isValid && memory_MEMORY_ENABLE) && (! memory_INSTRUCTION[5])) && (! dBus_rsp_ready)))begin
      memory_arbitration_haltItself = 1'b1;
    end
    if(_zz_375)begin
      _zz_99 = 1'b1;
      _zz_100 = CsrPlugin_mtvec;
    end
    if(_zz_368)begin
      memory_arbitration_haltItself = writeBack_arbitration_isValid;
      if(memory_arbitration_isFiring)begin
        _zz_99 = 1'b1;
        _zz_100 = CsrPlugin_mepc;
      end
    end
    memory_DivPlugin_div_counter_willIncrement = 1'b0;
    if(_zz_370)begin
      if(_zz_371)begin
        memory_arbitration_haltItself = 1'b1;
        memory_DivPlugin_div_counter_willIncrement = 1'b1;
      end
      _zz_34 = memory_DivPlugin_div_result;
    end
    case(memory_SHIFT_CTRL)
      `ShiftCtrlEnum_binary_sequancial_SLL_1 : begin
        _zz_34 = _zz_196;
      end
      `ShiftCtrlEnum_binary_sequancial_SRL_1, `ShiftCtrlEnum_binary_sequancial_SRA_1 : begin
        _zz_34 = memory_SHIFT_RIGHT;
      end
      default : begin
      end
    endcase
  end

  assign memory_IS_DIV = _zz_274;
  assign writeBack_IS_MUL = _zz_265;
  assign writeBack_MUL_HH = _zz_234;
  assign writeBack_MUL_LOW = _zz_249;
  assign memory_MUL_HL = _zz_276;
  assign memory_MUL_LH = _zz_286;
  assign memory_MUL_LL = _zz_292;
  assign execute_SRC_LESS_UNSIGNED = _zz_241;
  assign execute_SRC_USE_SUB_LESS = _zz_267;
  assign _zz_43 = execute_PC;
  assign execute_SRC2_CTRL = _zz_44;
  assign _zz_46 = execute_RS1;
  assign execute_SRC1_CTRL = _zz_47;
  assign execute_SRC_ADD_SUB = _zz_42;
  assign execute_SRC_LESS = _zz_40;
  assign execute_ALU_CTRL = _zz_49;
  assign execute_SRC2 = _zz_45;
  assign execute_ALU_BITWISE_CTRL = _zz_51;
  assign _zz_52 = writeBack_INSTRUCTION;
  assign _zz_53 = writeBack_REGFILE_WRITE_VALID;
  always @ (*) begin
    _zz_54 = 1'b0;
    if(writeBack_RegFilePlugin_regFileWrite_valid)begin
      _zz_54 = 1'b1;
    end
  end

  assign decode_INSTRUCTION_ANTICIPATED = _zz_91;
  always @ (*) begin
    decode_REGFILE_WRITE_VALID = _zz_63;
    if((decode_INSTRUCTION[11 : 7] == (5'b00000)))begin
      decode_REGFILE_WRITE_VALID = 1'b0;
    end
  end

  assign decode_LEGAL_INSTRUCTION = _zz_80;
  assign decode_INSTRUCTION_READY = _zz_89;
  always @ (*) begin
    _zz_81 = execute_REGFILE_WRITE_DATA;
    execute_arbitration_haltItself = 1'b0;
    if((((execute_arbitration_isValid && execute_MEMORY_ENABLE) && (! dBus_cmd_ready)) && (! execute_ALIGNEMENT_FAULT)))begin
      execute_arbitration_haltItself = 1'b1;
    end
    if((execute_CsrPlugin_writeInstruction && (! execute_CsrPlugin_readDataRegValid)))begin
      execute_arbitration_haltItself = 1'b1;
    end
    if((execute_arbitration_isValid && execute_IS_CSR))begin
      _zz_81 = execute_CsrPlugin_readData;
    end
    execute_XbbVectorCordic_vfsm_stateCompute_xval = (18'b000000000000000000);
    execute_XbbVectorCordic_vfsm_stateCompute_yval = (18'b000000000000000000);
    execute_XbbVectorCordic_vfsm_stateNext = execute_XbbVectorCordic_vfsm_stateReg;
    case(execute_XbbVectorCordic_vfsm_stateReg)
      `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateInit : begin
        if(_zz_377)begin
          execute_arbitration_haltItself = 1'b1;
          execute_XbbVectorCordic_vfsm_stateNext = `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateCompute;
        end
      end
      `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateCompute : begin
        execute_arbitration_haltItself = 1'b1;
        if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_474)))begin
          execute_XbbVectorCordic_vfsm_stateCompute_xval = ($signed(execute_XbbVectorCordic_vfsm_x) - $signed(execute_XbbVectorCordic_vfsm_ytmp));
          execute_XbbVectorCordic_vfsm_stateCompute_yval = ($signed(execute_XbbVectorCordic_vfsm_y) + $signed(execute_XbbVectorCordic_vfsm_xtmp));
        end else begin
          execute_XbbVectorCordic_vfsm_stateCompute_xval = ($signed(execute_XbbVectorCordic_vfsm_x) + $signed(execute_XbbVectorCordic_vfsm_ytmp));
          execute_XbbVectorCordic_vfsm_stateCompute_yval = ($signed(execute_XbbVectorCordic_vfsm_y) - $signed(execute_XbbVectorCordic_vfsm_xtmp));
        end
        if(_zz_372)begin
          execute_XbbVectorCordic_vfsm_stateNext = `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateSaturate;
        end
      end
      `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateSaturate : begin
        execute_arbitration_haltItself = 1'b1;
        execute_XbbVectorCordic_vfsm_stateNext = `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateNormalize;
      end
      `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateNormalize : begin
        execute_arbitration_haltItself = 1'b1;
        execute_XbbVectorCordic_vfsm_stateNext = `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateOutput;
      end
      `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateOutput : begin
        execute_arbitration_haltItself = 1'b0;
        execute_XbbVectorCordic_vfsm_stateNext = `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateInit;
        _zz_81 = {_zz_529,_zz_530};
      end
      default : begin
        execute_XbbVectorCordic_vfsm_stateNext = `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateInit;
      end
    endcase
  end

  assign execute_CSR_READ_OPCODE = _zz_275;
  assign execute_CSR_WRITE_OPCODE = _zz_262;
  assign memory_REGFILE_WRITE_DATA = _zz_226;
  assign execute_SRC1 = _zz_48;
  assign execute_IS_CSR = _zz_253;
  assign decode_IS_CSR = _zz_61;
  assign memory_ENV_CTRL = _zz_84;
  assign prefetch_PC_CALC_WITHOUT_JUMP = _zz_98;
  always @ (*) begin
    _zz_85 = writeBack_REGFILE_WRITE_DATA;
    if((writeBack_arbitration_isValid && writeBack_MEMORY_ENABLE))begin
      _zz_85 = writeBack_DBusSimplePlugin_rspFormated;
    end
    if((writeBack_arbitration_isValid && writeBack_IS_MUL))begin
      case(_zz_382)
        2'b00 : begin
          _zz_85 = _zz_430;
        end
        2'b01, 2'b10, 2'b11 : begin
          _zz_85 = _zz_431;
        end
        default : begin
        end
      endcase
    end
  end

  assign writeBack_MEMORY_ENABLE = _zz_285;
  assign writeBack_MEMORY_ADDRESS_LOW = _zz_252;
  assign writeBack_MEMORY_READ_DATA = _zz_248;
  assign memory_INSTRUCTION = _zz_259;
  assign memory_MEMORY_ENABLE = _zz_284;
  assign execute_RS2 = _zz_242;
  assign execute_SRC_ADD = _zz_41;
  assign execute_INSTRUCTION = _zz_258;
  assign execute_ALIGNEMENT_FAULT = _zz_88;
  assign execute_MEMORY_ENABLE = _zz_283;
  assign _zz_90 = fetch_INSTRUCTION;
  assign _zz_93 = prefetch_PC;
  always @ (*) begin
    _zz_94 = decode_FORMAL_PC_NEXT;
    if(_zz_107)begin
      _zz_94 = _zz_108;
    end
  end

  always @ (*) begin
    _zz_95 = execute_FORMAL_PC_NEXT;
    if(_zz_99)begin
      _zz_95 = _zz_100;
    end
  end

  assign prefetch_PC = _zz_97;
  assign writeBack_PC = _zz_272;
  assign writeBack_INSTRUCTION = _zz_260;
  assign decode_PC = _zz_269;
  assign decode_INSTRUCTION = _zz_257;
  always @ (*) begin
    prefetch_arbitration_haltItself = 1'b0;
    if(((! iBus_cmd_ready) || (prefetch_IBusSimplePlugin_pendingCmd && (! iBus_rsp_ready))))begin
      prefetch_arbitration_haltItself = 1'b1;
    end
  end

  always @ (*) begin
    prefetch_arbitration_haltByOther = 1'b0;
    decode_arbitration_flushAll = 1'b0;
    if(CsrPlugin_pipelineLiberator_enable)begin
      prefetch_arbitration_haltByOther = 1'b1;
    end
    if(_zz_369)begin
      prefetch_arbitration_haltByOther = 1'b1;
      decode_arbitration_flushAll = 1'b1;
    end
    if(DebugPlugin_haltIt)begin
      prefetch_arbitration_haltByOther = 1'b1;
    end
  end

  always @ (*) begin
    prefetch_arbitration_removeIt = 1'b0;
    if(prefetch_arbitration_isFlushed)begin
      prefetch_arbitration_removeIt = 1'b1;
    end
  end

  assign prefetch_arbitration_flushAll = 1'b0;
  assign prefetch_arbitration_redoIt = 1'b0;
  always @ (*) begin
    fetch_arbitration_haltItself = 1'b0;
    if(((fetch_arbitration_isValid && (! iBus_rsp_ready)) && (! _zz_114)))begin
      fetch_arbitration_haltItself = 1'b1;
    end
  end

  assign fetch_arbitration_haltByOther = 1'b0;
  always @ (*) begin
    fetch_arbitration_removeIt = 1'b0;
    if(fetch_arbitration_isFlushed)begin
      fetch_arbitration_removeIt = 1'b1;
    end
  end

  always @ (*) begin
    fetch_arbitration_flushAll = 1'b0;
    CsrPlugin_exceptionPortCtrl_exceptionValids_2 = CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_2;
    if(_zz_378)begin
      fetch_arbitration_flushAll = 1'b1;
      CsrPlugin_exceptionPortCtrl_exceptionValids_2 = 1'b1;
    end
    if(decode_arbitration_isFlushed)begin
      CsrPlugin_exceptionPortCtrl_exceptionValids_2 = 1'b0;
    end
    if(_zz_107)begin
      fetch_arbitration_flushAll = 1'b1;
    end
  end

  assign fetch_arbitration_redoIt = 1'b0;
  always @ (*) begin
    decode_arbitration_haltItself = 1'b0;
    if(((decode_arbitration_isValid && decode_IS_CSR) && (execute_arbitration_isValid || memory_arbitration_isValid)))begin
      decode_arbitration_haltItself = 1'b1;
    end
    if((decode_arbitration_isValid && (_zz_197 || _zz_198)))begin
      decode_arbitration_haltItself = 1'b1;
    end
    DebugPlugin_insertDecodeInstruction = 1'b0;
    _zz_299 = 1'b1;
    if(debug_bus_cmd_valid)begin
      case(_zz_374)
        1'b0 : begin
        end
        default : begin
          if(debug_bus_cmd_payload_wr)begin
            DebugPlugin_insertDecodeInstruction = 1'b1;
            if(DebugPlugin_secondCycle)begin
              decode_arbitration_haltItself = 1'b1;
            end
            _zz_299 = (! ((DebugPlugin_firstCycle || DebugPlugin_secondCycle) || decode_arbitration_isValid));
          end
        end
      endcase
    end
  end

  assign decode_arbitration_haltByOther = 1'b0;
  always @ (*) begin
    decode_arbitration_removeIt = 1'b0;
    if(_zz_378)begin
      decode_arbitration_removeIt = 1'b1;
    end
    if(decode_arbitration_isFlushed)begin
      decode_arbitration_removeIt = 1'b1;
    end
  end

  assign decode_arbitration_redoIt = 1'b0;
  assign execute_arbitration_haltByOther = 1'b0;
  always @ (*) begin
    execute_arbitration_removeIt = 1'b0;
    if(execute_arbitration_isFlushed)begin
      execute_arbitration_removeIt = 1'b1;
    end
  end

  always @ (*) begin
    execute_arbitration_flushAll = 1'b0;
    if(_zz_373)begin
      execute_arbitration_flushAll = 1'b1;
    end
    if(_zz_368)begin
      if(memory_arbitration_isFiring)begin
        execute_arbitration_flushAll = 1'b1;
      end
    end
    if(_zz_105)begin
      execute_arbitration_flushAll = 1'b1;
    end
  end

  assign execute_arbitration_redoIt = 1'b0;
  assign memory_arbitration_haltByOther = 1'b0;
  always @ (*) begin
    memory_arbitration_removeIt = 1'b0;
    if(_zz_373)begin
      memory_arbitration_removeIt = 1'b1;
    end
    if(memory_arbitration_isFlushed)begin
      memory_arbitration_removeIt = 1'b1;
    end
  end

  assign memory_arbitration_flushAll = 1'b0;
  assign memory_arbitration_redoIt = 1'b0;
  always @ (*) begin
    writeBack_arbitration_haltItself = 1'b0;
    if((writeBack_arbitration_isValid && (! xbaseband_cmd_ready)))begin
      writeBack_arbitration_haltItself = 1'b1;
    end
  end

  assign writeBack_arbitration_haltByOther = 1'b0;
  always @ (*) begin
    writeBack_arbitration_removeIt = 1'b0;
    if(writeBack_arbitration_isFlushed)begin
      writeBack_arbitration_removeIt = 1'b1;
    end
  end

  assign writeBack_arbitration_flushAll = 1'b0;
  assign writeBack_arbitration_redoIt = 1'b0;
  always @ (*) begin
    _zz_102 = 1'b1;
    if((DebugPlugin_haltIt || DebugPlugin_stepIt))begin
      _zz_102 = 1'b0;
    end
  end

  always @ (*) begin
    _zz_103 = 1'b1;
    if(DebugPlugin_haltIt)begin
      _zz_103 = 1'b0;
    end
  end

  assign prefetch_PcManagerSimplePlugin_pcPlus4 = (prefetch_PcManagerSimplePlugin_pcReg + (32'b00000000000000000000000000000100));
  assign prefetch_PcManagerSimplePlugin_jump_pcLoad_valid = ((_zz_99 || _zz_105) || _zz_107);
  assign _zz_110 = {_zz_107,{_zz_99,_zz_105}};
  assign _zz_111 = (_zz_110 & (~ _zz_383));
  assign _zz_112 = _zz_111[1];
  assign _zz_113 = _zz_111[2];
  assign prefetch_PcManagerSimplePlugin_jump_pcLoad_payload = _zz_300;
  assign _zz_98 = prefetch_PcManagerSimplePlugin_pcReg;
  assign _zz_97 = prefetch_PcManagerSimplePlugin_pcReg;
  assign _zz_96 = (prefetch_PC + (32'b00000000000000000000000000000100));
  assign _zz_296 = (((prefetch_arbitration_isValid && (! prefetch_arbitration_removeIt)) && (! prefetch_arbitration_isStuckByOthers)) && (! (prefetch_IBusSimplePlugin_pendingCmd && (! iBus_rsp_ready))));
  assign iBus_cmd_payload_pc = _zz_93;
  always @ (*) begin
    _zz_92 = iBus_rsp_inst;
    if(_zz_114)begin
      _zz_92 = _zz_115;
    end
  end

  assign _zz_91 = (decode_arbitration_isStuck ? decode_INSTRUCTION : _zz_90);
  assign _zz_89 = 1'b1;
  assign _zz_88 = 1'b0;
  assign dBus_cmd_valid = ((((execute_arbitration_isValid && execute_MEMORY_ENABLE) && (! execute_arbitration_isStuckByOthers)) && (! execute_arbitration_removeIt)) && (! execute_ALIGNEMENT_FAULT));
  assign dBus_cmd_payload_wr = execute_INSTRUCTION[5];
  assign _zz_298 = execute_SRC_ADD;
  assign _zz_297 = execute_INSTRUCTION[13 : 12];
  always @ (*) begin
    case(_zz_297)
      2'b00 : begin
        _zz_116 = {{{execute_RS2[7 : 0],execute_RS2[7 : 0]},execute_RS2[7 : 0]},execute_RS2[7 : 0]};
      end
      2'b01 : begin
        _zz_116 = {execute_RS2[15 : 0],execute_RS2[15 : 0]};
      end
      default : begin
        _zz_116 = execute_RS2[31 : 0];
      end
    endcase
  end

  assign dBus_cmd_payload_data = _zz_116;
  assign _zz_87 = _zz_298[1 : 0];
  always @ (*) begin
    case(_zz_297)
      2'b00 : begin
        _zz_117 = (4'b0001);
      end
      2'b01 : begin
        _zz_117 = (4'b0011);
      end
      default : begin
        _zz_117 = (4'b1111);
      end
    endcase
  end

  assign execute_DBusSimplePlugin_formalMask = (_zz_117 <<< _zz_298[1 : 0]);
  assign _zz_86 = dBus_rsp_data;
  always @ (*) begin
    writeBack_DBusSimplePlugin_rspShifted = writeBack_MEMORY_READ_DATA;
    case(writeBack_MEMORY_ADDRESS_LOW)
      2'b01 : begin
        writeBack_DBusSimplePlugin_rspShifted[7 : 0] = writeBack_MEMORY_READ_DATA[15 : 8];
      end
      2'b10 : begin
        writeBack_DBusSimplePlugin_rspShifted[15 : 0] = writeBack_MEMORY_READ_DATA[31 : 16];
      end
      2'b11 : begin
        writeBack_DBusSimplePlugin_rspShifted[7 : 0] = writeBack_MEMORY_READ_DATA[31 : 24];
      end
      default : begin
      end
    endcase
  end

  assign _zz_118 = (writeBack_DBusSimplePlugin_rspShifted[7] && (! writeBack_INSTRUCTION[14]));
  always @ (*) begin
    _zz_119[31] = _zz_118;
    _zz_119[30] = _zz_118;
    _zz_119[29] = _zz_118;
    _zz_119[28] = _zz_118;
    _zz_119[27] = _zz_118;
    _zz_119[26] = _zz_118;
    _zz_119[25] = _zz_118;
    _zz_119[24] = _zz_118;
    _zz_119[23] = _zz_118;
    _zz_119[22] = _zz_118;
    _zz_119[21] = _zz_118;
    _zz_119[20] = _zz_118;
    _zz_119[19] = _zz_118;
    _zz_119[18] = _zz_118;
    _zz_119[17] = _zz_118;
    _zz_119[16] = _zz_118;
    _zz_119[15] = _zz_118;
    _zz_119[14] = _zz_118;
    _zz_119[13] = _zz_118;
    _zz_119[12] = _zz_118;
    _zz_119[11] = _zz_118;
    _zz_119[10] = _zz_118;
    _zz_119[9] = _zz_118;
    _zz_119[8] = _zz_118;
    _zz_119[7 : 0] = writeBack_DBusSimplePlugin_rspShifted[7 : 0];
  end

  assign _zz_120 = (writeBack_DBusSimplePlugin_rspShifted[15] && (! writeBack_INSTRUCTION[14]));
  always @ (*) begin
    _zz_121[31] = _zz_120;
    _zz_121[30] = _zz_120;
    _zz_121[29] = _zz_120;
    _zz_121[28] = _zz_120;
    _zz_121[27] = _zz_120;
    _zz_121[26] = _zz_120;
    _zz_121[25] = _zz_120;
    _zz_121[24] = _zz_120;
    _zz_121[23] = _zz_120;
    _zz_121[22] = _zz_120;
    _zz_121[21] = _zz_120;
    _zz_121[20] = _zz_120;
    _zz_121[19] = _zz_120;
    _zz_121[18] = _zz_120;
    _zz_121[17] = _zz_120;
    _zz_121[16] = _zz_120;
    _zz_121[15 : 0] = writeBack_DBusSimplePlugin_rspShifted[15 : 0];
  end

  always @ (*) begin
    case(_zz_379)
      2'b00 : begin
        writeBack_DBusSimplePlugin_rspFormated = _zz_119;
      end
      2'b01 : begin
        writeBack_DBusSimplePlugin_rspFormated = _zz_121;
      end
      default : begin
        writeBack_DBusSimplePlugin_rspFormated = writeBack_DBusSimplePlugin_rspShifted;
      end
    endcase
  end

  assign CsrPlugin_misa_base = (2'b01);
  assign CsrPlugin_misa_extensions = (26'b00000000000000000001000010);
  assign CsrPlugin_mtvec = (32'b00000000000000000000000000100000);
  always @ (*) begin
    CsrPlugin_pipelineLiberator_enable = 1'b0;
    if(CsrPlugin_exceptionPortCtrl_pipelineHasException)begin
      CsrPlugin_pipelineLiberator_enable = 1'b1;
    end
    if(CsrPlugin_interrupt)begin
      CsrPlugin_pipelineLiberator_enable = 1'b1;
    end
  end

  assign CsrPlugin_pipelineLiberator_done = (! ((((fetch_arbitration_isValid || decode_arbitration_isValid) || execute_arbitration_isValid) || memory_arbitration_isValid) || writeBack_arbitration_isValid));
  assign CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_0 = 1'b0;
  assign CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_1 = 1'b0;
  assign CsrPlugin_exceptionPortCtrl_pipelineHasException = (((((CsrPlugin_exceptionPortCtrl_exceptionValids_0 || CsrPlugin_exceptionPortCtrl_exceptionValids_1) || CsrPlugin_exceptionPortCtrl_exceptionValids_2) || CsrPlugin_exceptionPortCtrl_exceptionValids_3) || CsrPlugin_exceptionPortCtrl_exceptionValids_4) || CsrPlugin_exceptionPortCtrl_exceptionValids_5);
  assign _zz_122 = {_zz_109,decodeExceptionPort_valid};
  assign _zz_123 = _zz_384[1];
  assign _zz_124 = _zz_123;
  assign CsrPlugin_exceptionPortCtrl_exceptionValids_0 = CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_0;
  assign CsrPlugin_exceptionPortCtrl_exceptionValids_1 = CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_1;
  always @ (*) begin
    CsrPlugin_exceptionPortCtrl_exceptionValids_3 = CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_3;
    if(execute_arbitration_isFlushed)begin
      CsrPlugin_exceptionPortCtrl_exceptionValids_3 = 1'b0;
    end
  end

  always @ (*) begin
    CsrPlugin_exceptionPortCtrl_exceptionValids_4 = CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_4;
    if(_zz_373)begin
      CsrPlugin_exceptionPortCtrl_exceptionValids_4 = 1'b1;
    end
    if(memory_arbitration_isFlushed)begin
      CsrPlugin_exceptionPortCtrl_exceptionValids_4 = 1'b0;
    end
  end

  always @ (*) begin
    CsrPlugin_exceptionPortCtrl_exceptionValids_5 = CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_5;
    if(writeBack_arbitration_isFlushed)begin
      CsrPlugin_exceptionPortCtrl_exceptionValids_5 = 1'b0;
    end
  end

  assign CsrPlugin_interruptRequest = (((((((((CsrPlugin_mip_MSIP && CsrPlugin_mie_MSIE) || (_zz_532 && _zz_533)) || (CsrPlugin_mip_MEIP[4] && CsrPlugin_mie_MEIE[4])) || (CsrPlugin_mip_MEIP[3] && CsrPlugin_mie_MEIE[3])) || (CsrPlugin_mip_MEIP[2] && CsrPlugin_mie_MEIE[2])) || (CsrPlugin_mip_MEIP[1] && CsrPlugin_mie_MEIE[1])) || (CsrPlugin_mip_MEIP[0] && CsrPlugin_mie_MEIE[0])) || (CsrPlugin_mip_MTIP && CsrPlugin_mie_MTIE)) && CsrPlugin_mstatus_MIE);
  assign CsrPlugin_interrupt = (CsrPlugin_interruptRequest && _zz_102);
  assign CsrPlugin_exception = (CsrPlugin_exceptionPortCtrl_exceptionValids_5 && _zz_103);
  assign CsrPlugin_writeBackWasWfi = 1'b0;
  always @ (*) begin
    case(CsrPlugin_exception)
      1'b1 : begin
        _zz_125 = writeBack_PC;
      end
      default : begin
        _zz_125 = (CsrPlugin_writeBackWasWfi ? writeBack_PC : prefetch_PC_CALC_WITHOUT_JUMP);
      end
    endcase
  end

  assign contextSwitching = _zz_99;
  assign _zz_83 = (! (((decode_INSTRUCTION[14 : 13] == (2'b01)) && (decode_INSTRUCTION[19 : 15] == (5'b00000))) || ((decode_INSTRUCTION[14 : 13] == (2'b11)) && (decode_INSTRUCTION[19 : 15] == (5'b00000)))));
  assign _zz_82 = (decode_INSTRUCTION[13 : 7] != (7'b0100000));
  always @ (*) begin
    execute_CsrPlugin_illegalAccess = (execute_arbitration_isValid && execute_IS_CSR);
    execute_CsrPlugin_readData = (32'b00000000000000000000000000000000);
    _zz_127 = 1'b0;
    _zz_128 = 1'b0;
    _zz_129 = 1'b0;
    _zz_130 = 1'b0;
    _zz_132 = 1'b0;
    _zz_133 = 1'b0;
    _zz_134 = 1'b0;
    _zz_135 = 1'b0;
    _zz_136 = 1'b0;
    _zz_138 = 1'b0;
    _zz_139 = 1'b0;
    _zz_140 = 1'b0;
    _zz_141 = 1'b0;
    _zz_142 = 1'b0;
    _zz_144 = 1'b0;
    _zz_145 = 1'b0;
    _zz_146 = 1'b0;
    _zz_147 = 1'b0;
    _zz_148 = 1'b0;
    _zz_149 = 1'b0;
    _zz_150 = 1'b0;
    _zz_151 = 1'b0;
    _zz_152 = 1'b0;
    _zz_153 = 1'b0;
    _zz_154 = 1'b0;
    _zz_155 = 1'b0;
    _zz_156 = 1'b0;
    _zz_157 = 1'b0;
    _zz_158 = 1'b0;
    _zz_159 = 1'b0;
    _zz_162 = 1'b0;
    case(execute_CsrPlugin_csrAddress)
      12'b110000100011 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_pilot_ram_wdata;
      end
      12'b111001000110 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_158 = 1'b1;
          _zz_159 = 1'b1;
        end
      end
      12'b111000100010 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[31 : 0] = gpio_read;
      end
      12'b111000011001 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[4 : 0] = _zz_348;
      end
      12'b110000011010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg26;
      end
      12'b110000001000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg8;
      end
      12'b110000010001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg17;
      end
      12'b111000010000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = RingBusCsrPlugin_writeAddrReg;
      end
      12'b111000000001 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
      end
      12'b111001000000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = NCOCsrPlugin_startAngleReg;
      end
      12'b111000010011 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[0 : 0] = ringbus_0_write_done;
      end
      12'b111000110111 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_154 = 1'b1;
        end
      end
      12'b001100000000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[12 : 11] = CsrPlugin_mstatus_MPP;
        execute_CsrPlugin_readData[7 : 7] = CsrPlugin_mstatus_MPIE;
        execute_CsrPlugin_readData[3 : 3] = CsrPlugin_mstatus_MIE;
      end
      12'b101100100100 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[15 : 0] = DmaCsrPlugin_demapper_two_over_sigma_sqReg_1;
      end
      12'b111000010110 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[4 : 0] = _zz_343;
      end
      12'b101100011011 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_133 = 1'b1;
          _zz_134 = 1'b1;
        end
      end
      12'b101100010010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[0 : 0] = DmaCsrPlugin_last_or_run_till_lastReg;
      end
      12'b111000111010 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_156 = 1'b1;
        end
      end
      12'b111000110001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = RingBusCsrPlugin_writeDataReg_1;
      end
      12'b101100101101 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[4 : 0] = _zz_337;
      end
      12'b110000100010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[9 : 0] = MapperMoverCsrPlugin_pilot_ram_addr;
      end
      12'b101100011110 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_135 = 1'b1;
          _zz_136 = 1'b1;
        end
      end
      12'b110000010000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg16;
      end
      12'b101100110000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DmaCsrPlugin_slicerReg_2;
      end
      12'b110000011001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg25;
      end
      12'b101100001100 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[31 : 0] = dma_0_status;
      end
      12'b110000000001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg1;
      end
      12'b110000011100 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg28;
      end
      12'b110000100101 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_146 = 1'b1;
        end
      end
      12'b101100100001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[0 : 0] = DmaCsrPlugin_reverseReg_1;
      end
      12'b110000001010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg10;
      end
      12'b110000010011 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg19;
      end
      12'b101100001111 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_132 = 1'b1;
        end
      end
      12'b101100011000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DmaCsrPlugin_startAddrReg_1;
      end
      12'b101100110011 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[3 : 0] = DmaCsrPlugin_demapper_constellationReg_2;
      end
      12'b101100101010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DmaCsrPlugin_timerInitReg_2;
      end
      12'b001101000001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = CsrPlugin_mepc;
      end
      12'b110000011111 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg31;
      end
      12'b111001000010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = NCOCsrPlugin_deltaReg;
      end
      12'b110000001101 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg13;
      end
      12'b101100001001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DmaCsrPlugin_lengthReg;
      end
      12'b110000010110 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg22;
      end
      12'b111010000001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DEngineCsrPlugin_func0MinThresholdReg;
      end
      12'b111000111001 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[4 : 0] = _zz_359;
      end
      12'b111000110000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = RingBusCsrPlugin_writeAddrReg_1;
      end
      12'b110000000100 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg4;
      end
      12'b111000010101 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_148 = 1'b1;
        end
      end
      12'b111010000100 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DEngineCsrPlugin_func1MaxThresholdReg;
      end
      12'b111000110011 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[0 : 0] = ringbus_1_write_done;
      end
      12'b111000100001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = GpioCsrPlugin_writeEnableReg;
      end
      12'b111000011000 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[31 : 0] = RingBusCsrPlugin_readPop_payload_read_data;
        if(execute_CsrPlugin_readEnable)begin
          _zz_150 = 1'b1;
        end
      end
      12'b111001000101 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[4 : 0] = _zz_366;
      end
      12'b001101000100 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 31] = CsrPlugin_mip_MEIP[5];
        execute_CsrPlugin_readData[27 : 27] = CsrPlugin_mip_MEIP[4];
        execute_CsrPlugin_readData[23 : 23] = CsrPlugin_mip_MEIP[3];
        execute_CsrPlugin_readData[19 : 19] = CsrPlugin_mip_MEIP[2];
        execute_CsrPlugin_readData[15 : 15] = CsrPlugin_mip_MEIP[1];
        execute_CsrPlugin_readData[11 : 11] = CsrPlugin_mip_MEIP[0];
        execute_CsrPlugin_readData[7 : 7] = CsrPlugin_mip_MTIP;
        execute_CsrPlugin_readData[3 : 3] = CsrPlugin_mip_MSIP;
      end
      12'b111001100000 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[31 : 0] = SatDetectCsrPlugin_satReg;
        if(execute_CsrPlugin_readEnable)begin
          _zz_162 = 1'b1;
        end
      end
      12'b110000000111 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg7;
      end
      12'b111000110110 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[4 : 0] = _zz_354;
      end
      12'b101100101001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DmaCsrPlugin_lengthReg_2;
      end
      12'b101100100000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DmaCsrPlugin_slicerReg_1;
      end
      12'b111000010010 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_147 = 1'b1;
        end
      end
      12'b111000000000 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[31 : 0] = TimerCsrPlugin_timerReg;
      end
      12'b101100110010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[0 : 0] = DmaCsrPlugin_last_or_run_till_lastReg_2;
      end
      12'b101100100011 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[3 : 0] = DmaCsrPlugin_demapper_constellationReg_1;
      end
      12'b101100101100 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[31 : 0] = dma_2_status;
      end
      12'b101100010001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[0 : 0] = DmaCsrPlugin_reverseReg;
      end
      12'b101100011010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DmaCsrPlugin_timerInitReg_1;
      end
      12'b101100001000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DmaCsrPlugin_startAddrReg;
      end
      12'b111010000011 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DEngineCsrPlugin_func1MinThresholdReg;
      end
      12'b101100010100 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[15 : 0] = DmaCsrPlugin_demapper_two_over_sigma_sqReg;
      end
      12'b110000000110 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg6;
      end
      12'b111001110001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = ControlStatusCsrPlugin_controlReg;
      end
      12'b101100011101 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[4 : 0] = _zz_325;
      end
      12'b101100001011 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_127 = 1'b1;
          _zz_128 = 1'b1;
        end
      end
      12'b110000100001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_trim_end_reg;
      end
      12'b110000001111 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg15;
      end
      12'b110000011000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg24;
      end
      12'b001101000011 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[31 : 0] = CsrPlugin_mbadaddr;
      end
      12'b101100101111 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_144 = 1'b1;
        end
      end
      12'b110000100100 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_145 = 1'b1;
        end
      end
      12'b110000011011 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg27;
      end
      12'b101100001110 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_129 = 1'b1;
          _zz_130 = 1'b1;
        end
      end
      12'b110000010010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg18;
      end
      12'b111001010000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = GenericOutCsrPlugin_valueReg;
      end
      12'b111000110101 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_153 = 1'b1;
        end
      end
      12'b110000000000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg0;
      end
      12'b110000001001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg9;
      end
      12'b111000111000 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[31 : 0] = RingBusCsrPlugin_readPop_payload_read_data_1;
        if(execute_CsrPlugin_readEnable)begin
          _zz_155 = 1'b1;
        end
      end
      12'b110000000011 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg3;
      end
      12'b110000011110 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg30;
      end
      12'b111001000001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = NCOCsrPlugin_lengthReg;
      end
      12'b110000010101 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg21;
      end
      12'b110000001100 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg12;
      end
      12'b111010000000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[0 : 0] = DEngineCsrPlugin_resetReg;
      end
      12'b001100000100 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 31] = CsrPlugin_mie_MEIE[5];
        execute_CsrPlugin_readData[27 : 27] = CsrPlugin_mie_MEIE[4];
        execute_CsrPlugin_readData[23 : 23] = CsrPlugin_mie_MEIE[3];
        execute_CsrPlugin_readData[19 : 19] = CsrPlugin_mie_MEIE[2];
        execute_CsrPlugin_readData[15 : 15] = CsrPlugin_mie_MEIE[1];
        execute_CsrPlugin_readData[11 : 11] = CsrPlugin_mie_MEIE[0];
        execute_CsrPlugin_readData[7 : 7] = CsrPlugin_mie_MTIE;
        execute_CsrPlugin_readData[3 : 3] = CsrPlugin_mie_MSIE;
      end
      12'b111000110010 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_152 = 1'b1;
        end
      end
      12'b111001000100 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[0 : 0] = nco_0_busy;
      end
      12'b111000100000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = GpioCsrPlugin_writeReg;
      end
      12'b111000010111 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_149 = 1'b1;
        end
      end
      12'b101100011111 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_138 = 1'b1;
        end
      end
      12'b111000010001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = RingBusCsrPlugin_writeDataReg;
      end
      12'b111000011010 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_151 = 1'b1;
        end
      end
      12'b101100110001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[0 : 0] = DmaCsrPlugin_reverseReg_2;
      end
      12'b101100101000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DmaCsrPlugin_startAddrReg_2;
      end
      12'b101100001101 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[4 : 0] = _zz_313;
      end
      12'b110000000010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg2;
      end
      12'b101100011001 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DmaCsrPlugin_lengthReg_1;
      end
      12'b110000001011 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg11;
      end
      12'b110000100110 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[15 : 0] = MapperMoverCsrPlugin_one_value_reg;
        execute_CsrPlugin_readData[15 : 0] = MapperMoverCsrPlugin_zero_value_reg;
      end
      12'b101100100010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[0 : 0] = DmaCsrPlugin_last_or_run_till_lastReg_1;
      end
      12'b110000010100 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg20;
      end
      12'b110000011101 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg29;
      end
      12'b101100010000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DmaCsrPlugin_slicerReg;
      end
      12'b101100101011 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_139 = 1'b1;
          _zz_140 = 1'b1;
        end
      end
      12'b101100110100 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[15 : 0] = DmaCsrPlugin_demapper_two_over_sigma_sqReg_2;
      end
      12'b001101000010 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[31 : 31] = CsrPlugin_mcause_interrupt;
        execute_CsrPlugin_readData[4 : 0] = CsrPlugin_mcause_exceptionCode;
      end
      12'b101100101110 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_141 = 1'b1;
          _zz_142 = 1'b1;
        end
      end
      12'b110000010111 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg23;
      end
      12'b110000100000 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_trim_start_reg;
      end
      12'b111001000011 : begin
        if(execute_CSR_WRITE_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        if(execute_CsrPlugin_writeEnable)begin
          _zz_157 = 1'b1;
        end
      end
      12'b101100011100 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[31 : 0] = dma_1_status;
      end
      12'b110000001110 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg14;
      end
      12'b101100010011 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[3 : 0] = DmaCsrPlugin_demapper_constellationReg;
      end
      12'b101100001010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DmaCsrPlugin_timerInitReg;
      end
      12'b111010000010 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = DEngineCsrPlugin_func0MaxThresholdReg;
      end
      12'b111001110000 : begin
        if(execute_CSR_READ_OPCODE)begin
          execute_CsrPlugin_illegalAccess = 1'b0;
        end
        execute_CsrPlugin_readData[31 : 0] = status_status;
      end
      12'b110000000101 : begin
        execute_CsrPlugin_illegalAccess = 1'b0;
        execute_CsrPlugin_readData[31 : 0] = MapperMoverCsrPlugin_mover_active_reg5;
      end
      default : begin
      end
    endcase
    if((_zz_101 < execute_CsrPlugin_csrAddress[9 : 8]))begin
      execute_CsrPlugin_illegalAccess = 1'b1;
    end
  end

  assign execute_CsrPlugin_writeSrc = (execute_INSTRUCTION[14] ? _zz_391 : execute_SRC1);
  always @ (*) begin
    case(_zz_380)
      1'b0 : begin
        execute_CsrPlugin_writeData = execute_CsrPlugin_writeSrc;
      end
      default : begin
        execute_CsrPlugin_writeData = (execute_INSTRUCTION[12] ? (memory_REGFILE_WRITE_DATA & (~ execute_CsrPlugin_writeSrc)) : (memory_REGFILE_WRITE_DATA | execute_CsrPlugin_writeSrc));
      end
    endcase
  end

  assign execute_CsrPlugin_writeInstruction = ((execute_arbitration_isValid && execute_IS_CSR) && execute_CSR_WRITE_OPCODE);
  assign execute_CsrPlugin_readInstruction = ((execute_arbitration_isValid && execute_IS_CSR) && execute_CSR_READ_OPCODE);
  assign execute_CsrPlugin_writeEnable = (execute_CsrPlugin_writeInstruction && execute_CsrPlugin_readDataRegValid);
  assign execute_CsrPlugin_readEnable = (execute_CsrPlugin_readInstruction && (! execute_CsrPlugin_readDataRegValid));
  assign execute_CsrPlugin_csrAddress = execute_INSTRUCTION[31 : 20];
  assign DmaCsrPlugin_configPush_payload_startAddr = DmaCsrPlugin_startAddrReg;
  assign DmaCsrPlugin_configPush_payload_length = DmaCsrPlugin_lengthReg;
  assign DmaCsrPlugin_configPush_payload_timerInit = DmaCsrPlugin_timerInitReg;
  assign DmaCsrPlugin_configPush_payload_slicer = DmaCsrPlugin_slicerReg;
  assign DmaCsrPlugin_configPush_payload_reverse = DmaCsrPlugin_reverseReg;
  assign DmaCsrPlugin_configPush_payload_last_or_run_till_last = DmaCsrPlugin_last_or_run_till_lastReg;
  assign DmaCsrPlugin_configPush_payload_demapper_constellation = DmaCsrPlugin_demapper_constellationReg;
  assign DmaCsrPlugin_configPush_payload_demapper_two_over_sigma_sq = DmaCsrPlugin_demapper_two_over_sigma_sqReg;
  assign DmaCsrPlugin_configPush_valid = _zz_128;
  assign DmaCsrPlugin_configPush_ready = _zz_303;
  assign dma_0_config_valid = _zz_304;
  assign dma_0_config_payload_startAddr = _zz_305;
  assign dma_0_config_payload_length = _zz_306;
  assign dma_0_config_payload_timerInit = _zz_307;
  assign dma_0_config_payload_slicer = _zz_308;
  assign dma_0_config_payload_reverse = _zz_309;
  assign dma_0_config_payload_last_or_run_till_last = _zz_310;
  assign dma_0_config_payload_demapper_constellation = _zz_311;
  assign dma_0_config_payload_demapper_two_over_sigma_sq = _zz_312;
  assign dma_0_dmaReset = _zz_131;
  assign dma_0_interrupt_clear = _zz_132;
  assign DmaCsrPlugin_configPush_payload_startAddr_1 = DmaCsrPlugin_startAddrReg_1;
  assign DmaCsrPlugin_configPush_payload_length_1 = DmaCsrPlugin_lengthReg_1;
  assign DmaCsrPlugin_configPush_payload_timerInit_1 = DmaCsrPlugin_timerInitReg_1;
  assign DmaCsrPlugin_configPush_payload_slicer_1 = DmaCsrPlugin_slicerReg_1;
  assign DmaCsrPlugin_configPush_payload_reverse_1 = DmaCsrPlugin_reverseReg_1;
  assign DmaCsrPlugin_configPush_payload_last_or_run_till_last_1 = DmaCsrPlugin_last_or_run_till_lastReg_1;
  assign DmaCsrPlugin_configPush_payload_demapper_constellation_1 = DmaCsrPlugin_demapper_constellationReg_1;
  assign DmaCsrPlugin_configPush_payload_demapper_two_over_sigma_sq_1 = DmaCsrPlugin_demapper_two_over_sigma_sqReg_1;
  assign DmaCsrPlugin_configPush_valid_1 = _zz_134;
  assign DmaCsrPlugin_configPush_ready_1 = _zz_315;
  assign dma_1_config_valid = _zz_316;
  assign dma_1_config_payload_startAddr = _zz_317;
  assign dma_1_config_payload_length = _zz_318;
  assign dma_1_config_payload_timerInit = _zz_319;
  assign dma_1_config_payload_slicer = _zz_320;
  assign dma_1_config_payload_reverse = _zz_321;
  assign dma_1_config_payload_last_or_run_till_last = _zz_322;
  assign dma_1_config_payload_demapper_constellation = _zz_323;
  assign dma_1_config_payload_demapper_two_over_sigma_sq = _zz_324;
  assign dma_1_dmaReset = _zz_137;
  assign dma_1_interrupt_clear = _zz_138;
  assign DmaCsrPlugin_configPush_payload_startAddr_2 = DmaCsrPlugin_startAddrReg_2;
  assign DmaCsrPlugin_configPush_payload_length_2 = DmaCsrPlugin_lengthReg_2;
  assign DmaCsrPlugin_configPush_payload_timerInit_2 = DmaCsrPlugin_timerInitReg_2;
  assign DmaCsrPlugin_configPush_payload_slicer_2 = DmaCsrPlugin_slicerReg_2;
  assign DmaCsrPlugin_configPush_payload_reverse_2 = DmaCsrPlugin_reverseReg_2;
  assign DmaCsrPlugin_configPush_payload_last_or_run_till_last_2 = DmaCsrPlugin_last_or_run_till_lastReg_2;
  assign DmaCsrPlugin_configPush_payload_demapper_constellation_2 = DmaCsrPlugin_demapper_constellationReg_2;
  assign DmaCsrPlugin_configPush_payload_demapper_two_over_sigma_sq_2 = DmaCsrPlugin_demapper_two_over_sigma_sqReg_2;
  assign DmaCsrPlugin_configPush_valid_2 = _zz_140;
  assign DmaCsrPlugin_configPush_ready_2 = _zz_327;
  assign dma_2_config_valid = _zz_328;
  assign dma_2_config_payload_startAddr = _zz_329;
  assign dma_2_config_payload_length = _zz_330;
  assign dma_2_config_payload_timerInit = _zz_331;
  assign dma_2_config_payload_slicer = _zz_332;
  assign dma_2_config_payload_reverse = _zz_333;
  assign dma_2_config_payload_last_or_run_till_last = _zz_334;
  assign dma_2_config_payload_demapper_constellation = _zz_335;
  assign dma_2_config_payload_demapper_two_over_sigma_sq = _zz_336;
  assign dma_2_dmaReset = _zz_143;
  assign dma_2_interrupt_clear = _zz_144;
  assign mapmovCsr_mover_active = {{{{{{{{{{{_zz_534,_zz_535},MapperMoverCsrPlugin_mover_active_reg9},MapperMoverCsrPlugin_mover_active_reg8},MapperMoverCsrPlugin_mover_active_reg7},MapperMoverCsrPlugin_mover_active_reg6},MapperMoverCsrPlugin_mover_active_reg5},MapperMoverCsrPlugin_mover_active_reg4},MapperMoverCsrPlugin_mover_active_reg3},MapperMoverCsrPlugin_mover_active_reg2},MapperMoverCsrPlugin_mover_active_reg1},MapperMoverCsrPlugin_mover_active_reg0};
  assign mapmovCsr_trim_start = MapperMoverCsrPlugin_trim_start_reg;
  assign mapmovCsr_trim_end = MapperMoverCsrPlugin_trim_end_reg;
  assign mapmovCsr_pilot_ram_addr = MapperMoverCsrPlugin_pilot_ram_addr;
  assign mapmovCsr_pilot_ram_wdata = MapperMoverCsrPlugin_pilot_ram_wdata;
  assign mapmovCsr_pilot_ram_we = MapperMoverCsrPlugin_pilot_ram_we;
  assign mapmovCsr_reset = MapperMoverCsrPlugin_reset;
  assign mapmovCsr_one_value = MapperMoverCsrPlugin_one_value_reg;
  assign mapmovCsr_zero_value = MapperMoverCsrPlugin_zero_value_reg;
  assign timerCsr_gtimer = TimerCsrPlugin_timerReg;
  assign RingBusCsrPlugin_writePush_payload_write_addr = RingBusCsrPlugin_writeAddrReg;
  assign RingBusCsrPlugin_writePush_payload_write_data = RingBusCsrPlugin_writeDataReg;
  assign RingBusCsrPlugin_writePush_valid = _zz_147;
  assign RingBusCsrPlugin_writePush_ready = _zz_339;
  assign ringbus_0_config_valid = _zz_340;
  assign ringbus_0_config_payload_write_data = _zz_341;
  assign ringbus_0_config_payload_write_addr = _zz_342;
  assign ringbus_0_interrupt_clear = _zz_148;
  assign RingBusCsrPlugin_readPush_payload_read_data = ringbus_0_read_payload_read_data;
  assign RingBusCsrPlugin_readPush_valid = ringbus_0_read_valid;
  assign ringbus_0_read_ready = RingBusCsrPlugin_readPush_ready;
  assign RingBusCsrPlugin_readPush_ready = _zz_345;
  assign RingBusCsrPlugin_readPop_valid = _zz_346;
  assign RingBusCsrPlugin_readPop_payload_read_data = _zz_347;
  assign RingBusCsrPlugin_readPop_ready = _zz_150;
  assign gpio_writeEnable = GpioCsrPlugin_writeEnableReg;
  assign gpio_write = GpioCsrPlugin_writeReg;
  assign RingBusCsrPlugin_writePush_payload_write_addr_1 = RingBusCsrPlugin_writeAddrReg_1;
  assign RingBusCsrPlugin_writePush_payload_write_data_1 = RingBusCsrPlugin_writeDataReg_1;
  assign RingBusCsrPlugin_writePush_valid_1 = _zz_152;
  assign RingBusCsrPlugin_writePush_ready_1 = _zz_350;
  assign ringbus_1_config_valid = _zz_351;
  assign ringbus_1_config_payload_write_data = _zz_352;
  assign ringbus_1_config_payload_write_addr = _zz_353;
  assign ringbus_1_interrupt_clear = _zz_153;
  assign RingBusCsrPlugin_readPush_payload_read_data_1 = ringbus_1_read_payload_read_data;
  assign RingBusCsrPlugin_readPush_valid_1 = ringbus_1_read_valid;
  assign ringbus_1_read_ready = RingBusCsrPlugin_readPush_ready_1;
  assign RingBusCsrPlugin_readPush_ready_1 = _zz_356;
  assign RingBusCsrPlugin_readPop_valid_1 = _zz_357;
  assign RingBusCsrPlugin_readPop_payload_read_data_1 = _zz_358;
  assign RingBusCsrPlugin_readPop_ready_1 = _zz_155;
  assign NCOCsrPlugin_configPush_payload_startAngle = NCOCsrPlugin_startAngleReg;
  assign NCOCsrPlugin_configPush_payload_length = NCOCsrPlugin_lengthReg;
  assign NCOCsrPlugin_configPush_payload_delta = NCOCsrPlugin_deltaReg;
  assign NCOCsrPlugin_configPush_valid = _zz_157;
  assign NCOCsrPlugin_configPush_ready = _zz_361;
  assign nco_0_config_valid = _zz_362;
  assign nco_0_config_payload_startAngle = _zz_363;
  assign nco_0_config_payload_length = _zz_364;
  assign nco_0_config_payload_delta = _zz_365;
  assign nco_0_ncoReset = _zz_160;
  assign slicer_value = _zz_161;
  assign SatDetectCsrPlugin_satReg = {SatDetectCsrPlugin_satCountReg,SatDetectCsrPlugin_satTimeReg};
  assign control_control = ControlStatusCsrPlugin_controlReg;
  assign dengine_reset = DEngineCsrPlugin_resetReg;
  assign dengine_func0MinThreshold = DEngineCsrPlugin_func0MinThresholdReg;
  assign dengine_func0MaxThreshold = DEngineCsrPlugin_func0MaxThresholdReg;
  assign dengine_func1MinThreshold = DEngineCsrPlugin_func1MinThresholdReg;
  assign dengine_func1MaxThreshold = DEngineCsrPlugin_func1MaxThresholdReg;
  assign _zz_164 = ((decode_INSTRUCTION & (32'b00000000000000000001000000000000)) == (32'b00000000000000000000000000000000));
  assign _zz_165 = ((decode_INSTRUCTION & (32'b00000000000000000000000000000100)) == (32'b00000000000000000000000000000100));
  assign _zz_166 = ((decode_INSTRUCTION & (32'b00000000000000000000000001010000)) == (32'b00000000000000000000000001010000));
  assign _zz_167 = ((decode_INSTRUCTION & (32'b00000000000000000000000001000000)) == (32'b00000000000000000000000001000000));
  assign _zz_168 = ((decode_INSTRUCTION & (32'b00000000000000000110000000000100)) == (32'b00000000000000000010000000000000));
  assign _zz_169 = ((decode_INSTRUCTION & (32'b00000000000000000000000000010100)) == (32'b00000000000000000000000000000100));
  assign _zz_170 = ((decode_INSTRUCTION & (32'b00000000000000000000000000101000)) == (32'b00000000000000000000000000001000));
  assign _zz_163 = {(((decode_INSTRUCTION & _zz_538) == (32'b00000000000000000000000000000000)) != (1'b0)),{(_zz_170 != (1'b0)),{({_zz_539,_zz_540} != (2'b00)),{(_zz_541 != _zz_542),{_zz_543,{_zz_544,_zz_545}}}}}};
  assign _zz_80 = ({((decode_INSTRUCTION & (32'b00000000000000000000000001011111)) == (32'b00000000000000000000000000010111)),{((decode_INSTRUCTION & (32'b00000000000000000000000001011111)) == (32'b00000000000000000000000000001011)),{((decode_INSTRUCTION & (32'b00000000000000000000000001111111)) == (32'b00000000000000000000000001101111)),{((decode_INSTRUCTION & _zz_676) == (32'b00000000000000000000000000000011)),{(_zz_677 == _zz_678),{_zz_679,{_zz_680,_zz_681}}}}}}} != (19'b0000000000000000000));
  assign _zz_79 = _zz_392[0];
  assign _zz_171 = _zz_163[2 : 1];
  assign _zz_78 = _zz_171;
  assign _zz_77 = _zz_393[0];
  assign _zz_76 = _zz_394[0];
  assign _zz_172 = _zz_163[6 : 5];
  assign _zz_75 = _zz_172;
  assign _zz_173 = _zz_163[8 : 7];
  assign _zz_74 = _zz_173;
  assign _zz_73 = _zz_395[0];
  assign _zz_72 = _zz_396[0];
  assign _zz_71 = _zz_397[0];
  assign _zz_70 = _zz_398[0];
  assign _zz_174 = _zz_163[14 : 13];
  assign _zz_69 = _zz_174;
  assign _zz_175 = _zz_163[16 : 15];
  assign _zz_68 = _zz_175;
  assign _zz_67 = _zz_399[0];
  assign _zz_66 = _zz_400[0];
  assign _zz_176 = _zz_163[20 : 19];
  assign _zz_65 = _zz_176;
  assign _zz_177 = _zz_163[22 : 21];
  assign _zz_64 = _zz_177;
  assign _zz_63 = _zz_401[0];
  assign _zz_62 = _zz_402[0];
  assign _zz_61 = _zz_403[0];
  assign _zz_60 = _zz_404[0];
  assign _zz_59 = _zz_405[0];
  assign _zz_58 = _zz_406[0];
  assign _zz_57 = _zz_407[0];
  assign decodeExceptionPort_valid = ((decode_arbitration_isValid && decode_INSTRUCTION_READY) && (! decode_LEGAL_INSTRUCTION));
  assign decodeExceptionPort_payload_code = (5'b00010);
  assign decodeExceptionPort_payload_badAddr = (32'bxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx);
  assign decode_RegFilePlugin_regFileReadAddress1 = decode_INSTRUCTION_ANTICIPATED[19 : 15];
  assign decode_RegFilePlugin_regFileReadAddress2 = decode_INSTRUCTION_ANTICIPATED[24 : 20];
  assign _zz_178 = 1'b1;
  assign decode_RegFilePlugin_rs1Data = _zz_294;
  assign _zz_179 = 1'b1;
  assign decode_RegFilePlugin_rs2Data = _zz_295;
  assign _zz_56 = decode_RegFilePlugin_rs1Data;
  assign _zz_55 = decode_RegFilePlugin_rs2Data;
  always @ (*) begin
    writeBack_RegFilePlugin_regFileWrite_valid = (_zz_53 && writeBack_arbitration_isFiring);
    if(_zz_180)begin
      writeBack_RegFilePlugin_regFileWrite_valid = 1'b1;
    end
  end

  assign writeBack_RegFilePlugin_regFileWrite_payload_address = _zz_52[11 : 7];
  assign writeBack_RegFilePlugin_regFileWrite_payload_data = _zz_85;
  always @ (*) begin
    case(execute_ALU_BITWISE_CTRL)
      `AluBitwiseCtrlEnum_binary_sequancial_AND_1 : begin
        execute_IntAluPlugin_bitwise = (execute_SRC1 & execute_SRC2);
      end
      `AluBitwiseCtrlEnum_binary_sequancial_OR_1 : begin
        execute_IntAluPlugin_bitwise = (execute_SRC1 | execute_SRC2);
      end
      `AluBitwiseCtrlEnum_binary_sequancial_XOR_1 : begin
        execute_IntAluPlugin_bitwise = (execute_SRC1 ^ execute_SRC2);
      end
      default : begin
        execute_IntAluPlugin_bitwise = execute_SRC1;
      end
    endcase
  end

  always @ (*) begin
    case(execute_ALU_CTRL)
      `AluCtrlEnum_binary_sequancial_BITWISE : begin
        _zz_181 = execute_IntAluPlugin_bitwise;
      end
      `AluCtrlEnum_binary_sequancial_SLT_SLTU : begin
        _zz_181 = {31'd0, _zz_408};
      end
      default : begin
        _zz_181 = execute_SRC_ADD_SUB;
      end
    endcase
  end

  assign _zz_50 = _zz_181;
  always @ (*) begin
    case(execute_SRC1_CTRL)
      `Src1CtrlEnum_binary_sequancial_RS : begin
        _zz_182 = _zz_46;
      end
      `Src1CtrlEnum_binary_sequancial_FOUR : begin
        _zz_182 = (32'b00000000000000000000000000000100);
      end
      default : begin
        _zz_182 = {execute_INSTRUCTION[31 : 12],(12'b000000000000)};
      end
    endcase
  end

  assign _zz_48 = _zz_182;
  assign _zz_183 = _zz_409[11];
  always @ (*) begin
    _zz_184[19] = _zz_183;
    _zz_184[18] = _zz_183;
    _zz_184[17] = _zz_183;
    _zz_184[16] = _zz_183;
    _zz_184[15] = _zz_183;
    _zz_184[14] = _zz_183;
    _zz_184[13] = _zz_183;
    _zz_184[12] = _zz_183;
    _zz_184[11] = _zz_183;
    _zz_184[10] = _zz_183;
    _zz_184[9] = _zz_183;
    _zz_184[8] = _zz_183;
    _zz_184[7] = _zz_183;
    _zz_184[6] = _zz_183;
    _zz_184[5] = _zz_183;
    _zz_184[4] = _zz_183;
    _zz_184[3] = _zz_183;
    _zz_184[2] = _zz_183;
    _zz_184[1] = _zz_183;
    _zz_184[0] = _zz_183;
  end

  assign _zz_185 = _zz_410[11];
  always @ (*) begin
    _zz_186[19] = _zz_185;
    _zz_186[18] = _zz_185;
    _zz_186[17] = _zz_185;
    _zz_186[16] = _zz_185;
    _zz_186[15] = _zz_185;
    _zz_186[14] = _zz_185;
    _zz_186[13] = _zz_185;
    _zz_186[12] = _zz_185;
    _zz_186[11] = _zz_185;
    _zz_186[10] = _zz_185;
    _zz_186[9] = _zz_185;
    _zz_186[8] = _zz_185;
    _zz_186[7] = _zz_185;
    _zz_186[6] = _zz_185;
    _zz_186[5] = _zz_185;
    _zz_186[4] = _zz_185;
    _zz_186[3] = _zz_185;
    _zz_186[2] = _zz_185;
    _zz_186[1] = _zz_185;
    _zz_186[0] = _zz_185;
  end

  always @ (*) begin
    case(execute_SRC2_CTRL)
      `Src2CtrlEnum_binary_sequancial_RS : begin
        _zz_187 = execute_RS2;
      end
      `Src2CtrlEnum_binary_sequancial_IMI : begin
        _zz_187 = {_zz_184,execute_INSTRUCTION[31 : 20]};
      end
      `Src2CtrlEnum_binary_sequancial_IMS : begin
        _zz_187 = {_zz_186,{execute_INSTRUCTION[31 : 25],execute_INSTRUCTION[11 : 7]}};
      end
      default : begin
        _zz_187 = _zz_43;
      end
    endcase
  end

  assign _zz_45 = _zz_187;
  assign execute_SrcPlugin_addSub = _zz_411;
  assign execute_SrcPlugin_less = ((execute_SRC1[31] == execute_SRC2[31]) ? execute_SrcPlugin_addSub[31] : (execute_SRC_LESS_UNSIGNED ? execute_SRC2[31] : execute_SRC1[31]));
  assign _zz_42 = execute_SrcPlugin_addSub;
  assign _zz_41 = execute_SrcPlugin_addSub;
  assign _zz_40 = execute_SrcPlugin_less;
  assign execute_MulPlugin_a = execute_SRC1;
  assign execute_MulPlugin_b = execute_SRC2;
  always @ (*) begin
    case(_zz_381)
      2'b01 : begin
        execute_MulPlugin_aSigned = 1'b1;
        execute_MulPlugin_bSigned = 1'b1;
      end
      2'b10 : begin
        execute_MulPlugin_aSigned = 1'b1;
        execute_MulPlugin_bSigned = 1'b0;
      end
      default : begin
        execute_MulPlugin_aSigned = 1'b0;
        execute_MulPlugin_bSigned = 1'b0;
      end
    endcase
  end

  assign execute_MulPlugin_aULow = execute_MulPlugin_a[15 : 0];
  assign execute_MulPlugin_bULow = execute_MulPlugin_b[15 : 0];
  assign execute_MulPlugin_aSLow = {1'b0,execute_MulPlugin_a[15 : 0]};
  assign execute_MulPlugin_bSLow = {1'b0,execute_MulPlugin_b[15 : 0]};
  assign execute_MulPlugin_aHigh = {(execute_MulPlugin_aSigned && execute_MulPlugin_a[31]),execute_MulPlugin_a[31 : 16]};
  assign execute_MulPlugin_bHigh = {(execute_MulPlugin_bSigned && execute_MulPlugin_b[31]),execute_MulPlugin_b[31 : 16]};
  assign _zz_39 = (execute_MulPlugin_aULow * execute_MulPlugin_bULow);
  assign _zz_38 = ($signed(execute_MulPlugin_aSLow) * $signed(execute_MulPlugin_bHigh));
  assign _zz_37 = ($signed(execute_MulPlugin_aHigh) * $signed(execute_MulPlugin_bSLow));
  assign _zz_36 = ($signed(execute_MulPlugin_aHigh) * $signed(execute_MulPlugin_bHigh));
  assign _zz_35 = ($signed(_zz_419) + $signed(_zz_427));
  assign writeBack_MulPlugin_result = ($signed(_zz_428) + $signed(_zz_429));
  always @ (*) begin
    memory_DivPlugin_div_counter_willClear = 1'b0;
    if(_zz_376)begin
      memory_DivPlugin_div_counter_willClear = 1'b1;
    end
  end

  assign memory_DivPlugin_div_done = (memory_DivPlugin_div_counter_value == (6'b100001));
  assign memory_DivPlugin_div_counter_willOverflow = (memory_DivPlugin_div_done && memory_DivPlugin_div_counter_willIncrement);
  always @ (*) begin
    if(memory_DivPlugin_div_counter_willOverflow)begin
      memory_DivPlugin_div_counter_valueNext = (6'b000000);
    end else begin
      memory_DivPlugin_div_counter_valueNext = (memory_DivPlugin_div_counter_value + _zz_433);
    end
    if(memory_DivPlugin_div_counter_willClear)begin
      memory_DivPlugin_div_counter_valueNext = (6'b000000);
    end
  end

  assign _zz_188 = memory_DivPlugin_rs1[31 : 0];
  assign _zz_189 = {memory_DivPlugin_accumulator[31 : 0],_zz_188[31]};
  assign _zz_190 = (_zz_189 - _zz_434);
  assign _zz_191 = (memory_INSTRUCTION[13] ? memory_DivPlugin_accumulator[31 : 0] : memory_DivPlugin_rs1[31 : 0]);
  assign _zz_192 = (execute_RS2[31] && execute_IS_RS2_SIGNED);
  assign _zz_193 = (1'b0 || ((execute_IS_DIV && execute_RS1[31]) && execute_IS_RS1_SIGNED));
  always @ (*) begin
    _zz_194[32] = (execute_IS_RS1_SIGNED && execute_RS1[31]);
    _zz_194[31 : 0] = execute_RS1;
  end

  assign execute_FullBarrielShifterPlugin_amplitude = execute_SRC2[4 : 0];
  always @ (*) begin
    _zz_195[0] = execute_SRC1[31];
    _zz_195[1] = execute_SRC1[30];
    _zz_195[2] = execute_SRC1[29];
    _zz_195[3] = execute_SRC1[28];
    _zz_195[4] = execute_SRC1[27];
    _zz_195[5] = execute_SRC1[26];
    _zz_195[6] = execute_SRC1[25];
    _zz_195[7] = execute_SRC1[24];
    _zz_195[8] = execute_SRC1[23];
    _zz_195[9] = execute_SRC1[22];
    _zz_195[10] = execute_SRC1[21];
    _zz_195[11] = execute_SRC1[20];
    _zz_195[12] = execute_SRC1[19];
    _zz_195[13] = execute_SRC1[18];
    _zz_195[14] = execute_SRC1[17];
    _zz_195[15] = execute_SRC1[16];
    _zz_195[16] = execute_SRC1[15];
    _zz_195[17] = execute_SRC1[14];
    _zz_195[18] = execute_SRC1[13];
    _zz_195[19] = execute_SRC1[12];
    _zz_195[20] = execute_SRC1[11];
    _zz_195[21] = execute_SRC1[10];
    _zz_195[22] = execute_SRC1[9];
    _zz_195[23] = execute_SRC1[8];
    _zz_195[24] = execute_SRC1[7];
    _zz_195[25] = execute_SRC1[6];
    _zz_195[26] = execute_SRC1[5];
    _zz_195[27] = execute_SRC1[4];
    _zz_195[28] = execute_SRC1[3];
    _zz_195[29] = execute_SRC1[2];
    _zz_195[30] = execute_SRC1[1];
    _zz_195[31] = execute_SRC1[0];
  end

  assign execute_FullBarrielShifterPlugin_reversed = ((execute_SHIFT_CTRL == `ShiftCtrlEnum_binary_sequancial_SLL_1) ? _zz_195 : execute_SRC1);
  assign _zz_32 = _zz_448;
  always @ (*) begin
    _zz_196[0] = memory_SHIFT_RIGHT[31];
    _zz_196[1] = memory_SHIFT_RIGHT[30];
    _zz_196[2] = memory_SHIFT_RIGHT[29];
    _zz_196[3] = memory_SHIFT_RIGHT[28];
    _zz_196[4] = memory_SHIFT_RIGHT[27];
    _zz_196[5] = memory_SHIFT_RIGHT[26];
    _zz_196[6] = memory_SHIFT_RIGHT[25];
    _zz_196[7] = memory_SHIFT_RIGHT[24];
    _zz_196[8] = memory_SHIFT_RIGHT[23];
    _zz_196[9] = memory_SHIFT_RIGHT[22];
    _zz_196[10] = memory_SHIFT_RIGHT[21];
    _zz_196[11] = memory_SHIFT_RIGHT[20];
    _zz_196[12] = memory_SHIFT_RIGHT[19];
    _zz_196[13] = memory_SHIFT_RIGHT[18];
    _zz_196[14] = memory_SHIFT_RIGHT[17];
    _zz_196[15] = memory_SHIFT_RIGHT[16];
    _zz_196[16] = memory_SHIFT_RIGHT[15];
    _zz_196[17] = memory_SHIFT_RIGHT[14];
    _zz_196[18] = memory_SHIFT_RIGHT[13];
    _zz_196[19] = memory_SHIFT_RIGHT[12];
    _zz_196[20] = memory_SHIFT_RIGHT[11];
    _zz_196[21] = memory_SHIFT_RIGHT[10];
    _zz_196[22] = memory_SHIFT_RIGHT[9];
    _zz_196[23] = memory_SHIFT_RIGHT[8];
    _zz_196[24] = memory_SHIFT_RIGHT[7];
    _zz_196[25] = memory_SHIFT_RIGHT[6];
    _zz_196[26] = memory_SHIFT_RIGHT[5];
    _zz_196[27] = memory_SHIFT_RIGHT[4];
    _zz_196[28] = memory_SHIFT_RIGHT[3];
    _zz_196[29] = memory_SHIFT_RIGHT[2];
    _zz_196[30] = memory_SHIFT_RIGHT[1];
    _zz_196[31] = memory_SHIFT_RIGHT[0];
  end

  always @ (*) begin
    _zz_197 = 1'b0;
    _zz_198 = 1'b0;
    if((writeBack_arbitration_isValid && writeBack_REGFILE_WRITE_VALID))begin
      if((1'b0 || (! _zz_202)))begin
        if(_zz_203)begin
          _zz_197 = 1'b1;
        end
        if(_zz_204)begin
          _zz_198 = 1'b1;
        end
      end
    end
    if((memory_arbitration_isValid && memory_REGFILE_WRITE_VALID))begin
      if((1'b0 || (! memory_BYPASSABLE_MEMORY_STAGE)))begin
        if(_zz_205)begin
          _zz_197 = 1'b1;
        end
        if(_zz_206)begin
          _zz_198 = 1'b1;
        end
      end
    end
    if((execute_arbitration_isValid && execute_REGFILE_WRITE_VALID))begin
      if((1'b0 || (! execute_BYPASSABLE_EXECUTE_STAGE)))begin
        if(_zz_207)begin
          _zz_197 = 1'b1;
        end
        if(_zz_208)begin
          _zz_198 = 1'b1;
        end
      end
    end
    if((! decode_RS1_USE))begin
      _zz_197 = 1'b0;
    end
    if((! decode_RS2_USE))begin
      _zz_198 = 1'b0;
    end
  end

  assign _zz_202 = 1'b1;
  assign _zz_203 = (writeBack_INSTRUCTION[11 : 7] == decode_INSTRUCTION[19 : 15]);
  assign _zz_204 = (writeBack_INSTRUCTION[11 : 7] == decode_INSTRUCTION[24 : 20]);
  assign _zz_205 = (memory_INSTRUCTION[11 : 7] == decode_INSTRUCTION[19 : 15]);
  assign _zz_206 = (memory_INSTRUCTION[11 : 7] == decode_INSTRUCTION[24 : 20]);
  assign _zz_207 = (execute_INSTRUCTION[11 : 7] == decode_INSTRUCTION[19 : 15]);
  assign _zz_208 = (execute_INSTRUCTION[11 : 7] == decode_INSTRUCTION[24 : 20]);
  assign xbaseband_cmd_payload_instruction = writeBack_INSTRUCTION;
  assign xbaseband_cmd_payload_rs1 = writeBack_RS1;
  assign xbaseband_cmd_valid = (writeBack_IS_XBASEBAND && writeBack_arbitration_isValid);
  assign execute_XbbVectorCordic_rs1 = execute_RS1;
  assign execute_XbbVectorCordic_rs2 = execute_RS2;
  assign execute_XbbVectorCordic_theta_0 = (17'b00100000000000000);
  assign execute_XbbVectorCordic_theta_1 = (17'b00010010111001000);
  assign execute_XbbVectorCordic_theta_2 = (17'b00001001111110110);
  assign execute_XbbVectorCordic_theta_3 = (17'b00000101000100010);
  assign execute_XbbVectorCordic_theta_4 = (17'b00000010100010110);
  assign execute_XbbVectorCordic_theta_5 = (17'b00000001010001011);
  assign execute_XbbVectorCordic_theta_6 = (17'b00000000101000101);
  assign execute_XbbVectorCordic_theta_7 = (17'b00000000010100010);
  assign execute_XbbVectorCordic_theta_8 = (17'b00000000001010001);
  assign execute_XbbVectorCordic_theta_9 = (17'b00000000000101000);
  assign execute_XbbVectorCordic_theta_10 = (17'b00000000000010100);
  assign execute_XbbVectorCordic_theta_11 = (17'b00000000000001010);
  assign execute_XbbVectorCordic_theta_12 = (17'b00000000000000101);
  assign execute_XbbVectorCordic_theta_13 = (17'b00000000000000010);
  assign execute_XbbVectorCordic_theta_14 = (17'b00000000000000001);
  assign execute_XbbVectorCordic_theta_15 = (17'b00000000000000000);
  assign execute_XbbVectorCordic_vfsm_wantExit = 1'b0;
  assign execute_XbbVectorCordic_vfsm_isvcordic = execute_IS_VCORDIC;
  assign _zz_209 = _zz_450[11];
  always @ (*) begin
    _zz_210[18] = _zz_209;
    _zz_210[17] = _zz_209;
    _zz_210[16] = _zz_209;
    _zz_210[15] = _zz_209;
    _zz_210[14] = _zz_209;
    _zz_210[13] = _zz_209;
    _zz_210[12] = _zz_209;
    _zz_210[11] = _zz_209;
    _zz_210[10] = _zz_209;
    _zz_210[9] = _zz_209;
    _zz_210[8] = _zz_209;
    _zz_210[7] = _zz_209;
    _zz_210[6] = _zz_209;
    _zz_210[5] = _zz_209;
    _zz_210[4] = _zz_209;
    _zz_210[3] = _zz_209;
    _zz_210[2] = _zz_209;
    _zz_210[1] = _zz_209;
    _zz_210[0] = _zz_209;
  end

  assign decode_BranchPlugin_conditionalBranchPrediction = _zz_451[31];
  assign _zz_30 = ((decode_BRANCH_CTRL == `BranchCtrlEnum_binary_sequancial_JAL) || ((decode_BRANCH_CTRL == `BranchCtrlEnum_binary_sequancial_B) && decode_BranchPlugin_conditionalBranchPrediction));
  assign _zz_107 = (decode_PREDICTION_HAD_BRANCHED2 && decode_arbitration_isFiring);
  assign _zz_211 = _zz_452[19];
  always @ (*) begin
    _zz_212[10] = _zz_211;
    _zz_212[9] = _zz_211;
    _zz_212[8] = _zz_211;
    _zz_212[7] = _zz_211;
    _zz_212[6] = _zz_211;
    _zz_212[5] = _zz_211;
    _zz_212[4] = _zz_211;
    _zz_212[3] = _zz_211;
    _zz_212[2] = _zz_211;
    _zz_212[1] = _zz_211;
    _zz_212[0] = _zz_211;
  end

  assign _zz_213 = _zz_453[11];
  always @ (*) begin
    _zz_214[18] = _zz_213;
    _zz_214[17] = _zz_213;
    _zz_214[16] = _zz_213;
    _zz_214[15] = _zz_213;
    _zz_214[14] = _zz_213;
    _zz_214[13] = _zz_213;
    _zz_214[12] = _zz_213;
    _zz_214[11] = _zz_213;
    _zz_214[10] = _zz_213;
    _zz_214[9] = _zz_213;
    _zz_214[8] = _zz_213;
    _zz_214[7] = _zz_213;
    _zz_214[6] = _zz_213;
    _zz_214[5] = _zz_213;
    _zz_214[4] = _zz_213;
    _zz_214[3] = _zz_213;
    _zz_214[2] = _zz_213;
    _zz_214[1] = _zz_213;
    _zz_214[0] = _zz_213;
  end

  assign _zz_108 = (decode_PC + ((decode_BRANCH_CTRL == `BranchCtrlEnum_binary_sequancial_JAL) ? {{_zz_212,{{{_zz_693,_zz_694},_zz_695},decode_INSTRUCTION[30 : 21]}},1'b0} : {{_zz_214,{{{_zz_696,_zz_697},decode_INSTRUCTION[30 : 25]},decode_INSTRUCTION[11 : 8]}},1'b0}));
  assign _zz_109 = (((decode_INSTRUCTION_READY && decode_PREDICTION_HAD_BRANCHED2) && decode_arbitration_isValid) && (_zz_108[1 : 0] != (2'b00)));
  assign execute_BranchPlugin_eq = (execute_SRC1 == execute_SRC2);
  assign _zz_215 = execute_INSTRUCTION[14 : 12];
  always @ (*) begin
    if((_zz_215 == (3'b000))) begin
        _zz_216 = execute_BranchPlugin_eq;
    end else if((_zz_215 == (3'b001))) begin
        _zz_216 = (! execute_BranchPlugin_eq);
    end else if((((_zz_215 & (3'b101)) == (3'b101)))) begin
        _zz_216 = (! execute_SRC_LESS);
    end else begin
        _zz_216 = execute_SRC_LESS;
    end
  end

  always @ (*) begin
    case(execute_BRANCH_CTRL)
      `BranchCtrlEnum_binary_sequancial_INC : begin
        _zz_217 = 1'b0;
      end
      `BranchCtrlEnum_binary_sequancial_JAL : begin
        _zz_217 = 1'b1;
      end
      `BranchCtrlEnum_binary_sequancial_JALR : begin
        _zz_217 = 1'b1;
      end
      default : begin
        _zz_217 = _zz_216;
      end
    endcase
  end

  assign _zz_27 = (execute_PREDICTION_HAD_BRANCHED2 != _zz_217);
  always @ (*) begin
    case(execute_BRANCH_CTRL)
      `BranchCtrlEnum_binary_sequancial_JALR : begin
        execute_BranchPlugin_branch_src1 = execute_RS1;
        execute_BranchPlugin_branch_src2 = {_zz_219,execute_INSTRUCTION[31 : 20]};
      end
      default : begin
        execute_BranchPlugin_branch_src1 = execute_PC;
        execute_BranchPlugin_branch_src2 = (execute_PREDICTION_HAD_BRANCHED2 ? (32'b00000000000000000000000000000100) : {{_zz_221,{{{execute_INSTRUCTION[31],execute_INSTRUCTION[7]},execute_INSTRUCTION[30 : 25]},execute_INSTRUCTION[11 : 8]}},1'b0});
      end
    endcase
  end

  assign _zz_218 = _zz_454[11];
  always @ (*) begin
    _zz_219[19] = _zz_218;
    _zz_219[18] = _zz_218;
    _zz_219[17] = _zz_218;
    _zz_219[16] = _zz_218;
    _zz_219[15] = _zz_218;
    _zz_219[14] = _zz_218;
    _zz_219[13] = _zz_218;
    _zz_219[12] = _zz_218;
    _zz_219[11] = _zz_218;
    _zz_219[10] = _zz_218;
    _zz_219[9] = _zz_218;
    _zz_219[8] = _zz_218;
    _zz_219[7] = _zz_218;
    _zz_219[6] = _zz_218;
    _zz_219[5] = _zz_218;
    _zz_219[4] = _zz_218;
    _zz_219[3] = _zz_218;
    _zz_219[2] = _zz_218;
    _zz_219[1] = _zz_218;
    _zz_219[0] = _zz_218;
  end

  assign _zz_220 = _zz_455[11];
  always @ (*) begin
    _zz_221[18] = _zz_220;
    _zz_221[17] = _zz_220;
    _zz_221[16] = _zz_220;
    _zz_221[15] = _zz_220;
    _zz_221[14] = _zz_220;
    _zz_221[13] = _zz_220;
    _zz_221[12] = _zz_220;
    _zz_221[11] = _zz_220;
    _zz_221[10] = _zz_220;
    _zz_221[9] = _zz_220;
    _zz_221[8] = _zz_220;
    _zz_221[7] = _zz_220;
    _zz_221[6] = _zz_220;
    _zz_221[5] = _zz_220;
    _zz_221[4] = _zz_220;
    _zz_221[3] = _zz_220;
    _zz_221[2] = _zz_220;
    _zz_221[1] = _zz_220;
    _zz_221[0] = _zz_220;
  end

  assign execute_BranchPlugin_branchAdder = (execute_BranchPlugin_branch_src1 + execute_BranchPlugin_branch_src2);
  assign _zz_26 = {execute_BranchPlugin_branchAdder[31 : 1],((execute_BRANCH_CTRL == `BranchCtrlEnum_binary_sequancial_JALR) ? 1'b0 : execute_BranchPlugin_branchAdder[0])};
  assign _zz_105 = (memory_BRANCH_DO && memory_arbitration_isFiring);
  assign _zz_106 = memory_BRANCH_CALC;
  assign DebugPlugin_isPipBusy = (DebugPlugin_isPipActive || _zz_222);
  always @ (*) begin
    debug_bus_rsp_data = DebugPlugin_busReadDataReg;
    if((! _zz_223))begin
      debug_bus_rsp_data[0] = DebugPlugin_resetIt;
      debug_bus_rsp_data[1] = DebugPlugin_haltIt;
      debug_bus_rsp_data[2] = DebugPlugin_isPipBusy;
      debug_bus_rsp_data[3] = DebugPlugin_haltedByBreak;
      debug_bus_rsp_data[4] = DebugPlugin_stepIt;
    end
  end

  assign debug_resetOut = _zz_224;
  assign _zz_25 = decode_ENV_CTRL;
  assign _zz_22 = execute_ENV_CTRL;
  assign _zz_23 = _zz_64;
  assign _zz_20 = _zz_238;
  assign _zz_84 = _zz_239;
  assign _zz_19 = decode_BRANCH_CTRL;
  assign _zz_29 = _zz_65;
  assign _zz_28 = _zz_243;
  assign _zz_17 = decode_SRC1_CTRL;
  assign _zz_15 = _zz_68;
  assign _zz_47 = _zz_247;
  assign _zz_14 = decode_ALU_BITWISE_CTRL;
  assign _zz_12 = _zz_75;
  assign _zz_51 = _zz_250;
  assign _zz_11 = decode_SHIFT_CTRL;
  assign _zz_8 = execute_SHIFT_CTRL;
  assign _zz_9 = _zz_78;
  assign _zz_33 = _zz_255;
  assign _zz_31 = _zz_256;
  assign _zz_6 = decode_SRC2_CTRL;
  assign _zz_4 = _zz_74;
  assign _zz_44 = _zz_266;
  assign _zz_3 = decode_ALU_CTRL;
  assign _zz_1 = _zz_69;
  assign _zz_49 = _zz_287;
  assign prefetch_arbitration_isFlushed = (((((prefetch_arbitration_flushAll || fetch_arbitration_flushAll) || decode_arbitration_flushAll) || execute_arbitration_flushAll) || memory_arbitration_flushAll) || writeBack_arbitration_flushAll);
  assign fetch_arbitration_isFlushed = ((((fetch_arbitration_flushAll || decode_arbitration_flushAll) || execute_arbitration_flushAll) || memory_arbitration_flushAll) || writeBack_arbitration_flushAll);
  assign decode_arbitration_isFlushed = (((decode_arbitration_flushAll || execute_arbitration_flushAll) || memory_arbitration_flushAll) || writeBack_arbitration_flushAll);
  assign execute_arbitration_isFlushed = ((execute_arbitration_flushAll || memory_arbitration_flushAll) || writeBack_arbitration_flushAll);
  assign memory_arbitration_isFlushed = (memory_arbitration_flushAll || writeBack_arbitration_flushAll);
  assign writeBack_arbitration_isFlushed = writeBack_arbitration_flushAll;
  assign prefetch_arbitration_isStuckByOthers = (prefetch_arbitration_haltByOther || (((((1'b0 || fetch_arbitration_haltItself) || decode_arbitration_haltItself) || execute_arbitration_haltItself) || memory_arbitration_haltItself) || writeBack_arbitration_haltItself));
  assign prefetch_arbitration_isStuck = (prefetch_arbitration_haltItself || prefetch_arbitration_isStuckByOthers);
  assign prefetch_arbitration_isMoving = ((! prefetch_arbitration_isStuck) && (! prefetch_arbitration_removeIt));
  assign prefetch_arbitration_isFiring = ((prefetch_arbitration_isValid && (! prefetch_arbitration_isStuck)) && (! prefetch_arbitration_removeIt));
  assign fetch_arbitration_isStuckByOthers = (fetch_arbitration_haltByOther || ((((1'b0 || decode_arbitration_haltItself) || execute_arbitration_haltItself) || memory_arbitration_haltItself) || writeBack_arbitration_haltItself));
  assign fetch_arbitration_isStuck = (fetch_arbitration_haltItself || fetch_arbitration_isStuckByOthers);
  assign fetch_arbitration_isMoving = ((! fetch_arbitration_isStuck) && (! fetch_arbitration_removeIt));
  assign fetch_arbitration_isFiring = ((fetch_arbitration_isValid && (! fetch_arbitration_isStuck)) && (! fetch_arbitration_removeIt));
  assign decode_arbitration_isStuckByOthers = (decode_arbitration_haltByOther || (((1'b0 || execute_arbitration_haltItself) || memory_arbitration_haltItself) || writeBack_arbitration_haltItself));
  assign decode_arbitration_isStuck = (decode_arbitration_haltItself || decode_arbitration_isStuckByOthers);
  assign decode_arbitration_isMoving = ((! decode_arbitration_isStuck) && (! decode_arbitration_removeIt));
  assign decode_arbitration_isFiring = ((decode_arbitration_isValid && (! decode_arbitration_isStuck)) && (! decode_arbitration_removeIt));
  assign execute_arbitration_isStuckByOthers = (execute_arbitration_haltByOther || ((1'b0 || memory_arbitration_haltItself) || writeBack_arbitration_haltItself));
  assign execute_arbitration_isStuck = (execute_arbitration_haltItself || execute_arbitration_isStuckByOthers);
  assign execute_arbitration_isMoving = ((! execute_arbitration_isStuck) && (! execute_arbitration_removeIt));
  assign execute_arbitration_isFiring = ((execute_arbitration_isValid && (! execute_arbitration_isStuck)) && (! execute_arbitration_removeIt));
  assign memory_arbitration_isStuckByOthers = (memory_arbitration_haltByOther || (1'b0 || writeBack_arbitration_haltItself));
  assign memory_arbitration_isStuck = (memory_arbitration_haltItself || memory_arbitration_isStuckByOthers);
  assign memory_arbitration_isMoving = ((! memory_arbitration_isStuck) && (! memory_arbitration_removeIt));
  assign memory_arbitration_isFiring = ((memory_arbitration_isValid && (! memory_arbitration_isStuck)) && (! memory_arbitration_removeIt));
  assign writeBack_arbitration_isStuckByOthers = (writeBack_arbitration_haltByOther || 1'b0);
  assign writeBack_arbitration_isStuck = (writeBack_arbitration_haltItself || writeBack_arbitration_isStuckByOthers);
  assign writeBack_arbitration_isMoving = ((! writeBack_arbitration_isStuck) && (! writeBack_arbitration_removeIt));
  assign writeBack_arbitration_isFiring = ((writeBack_arbitration_isValid && (! writeBack_arbitration_isStuck)) && (! writeBack_arbitration_removeIt));
  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      prefetch_arbitration_isValid <= 1'b0;
      fetch_arbitration_isValid <= 1'b0;
      decode_arbitration_isValid <= 1'b0;
      execute_arbitration_isValid <= 1'b0;
      memory_arbitration_isValid <= 1'b0;
      writeBack_arbitration_isValid <= 1'b0;
      _zz_101 <= (2'b11);
      prefetch_PcManagerSimplePlugin_pcReg <= (32'b00000000000000000000000000000000);
      prefetch_IBusSimplePlugin_pendingCmd <= 1'b0;
      _zz_114 <= 1'b0;
      CsrPlugin_mstatus_MIE <= 1'b0;
      CsrPlugin_mstatus_MPIE <= 1'b0;
      CsrPlugin_mstatus_MPP <= (2'b11);
      CsrPlugin_mip_MEIP <= (6'b000000);
      CsrPlugin_mip_MTIP <= 1'b0;
      CsrPlugin_mip_MSIP <= 1'b0;
      CsrPlugin_mie_MEIE <= (6'b000000);
      CsrPlugin_mie_MTIE <= 1'b0;
      CsrPlugin_mie_MSIE <= 1'b0;
      CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_2 <= 1'b0;
      CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_3 <= 1'b0;
      CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_4 <= 1'b0;
      CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_5 <= 1'b0;
      DmaCsrPlugin_reverseReg <= 1'b0;
      DmaCsrPlugin_last_or_run_till_lastReg <= 1'b0;
      DmaCsrPlugin_demapper_constellationReg <= (4'b0000);
      DmaCsrPlugin_demapper_two_over_sigma_sqReg <= (16'b0001000000000000);
      DmaCsrPlugin_reverseReg_1 <= 1'b0;
      DmaCsrPlugin_last_or_run_till_lastReg_1 <= 1'b0;
      DmaCsrPlugin_demapper_constellationReg_1 <= (4'b0000);
      DmaCsrPlugin_demapper_two_over_sigma_sqReg_1 <= (16'b0001000000000000);
      DmaCsrPlugin_reverseReg_2 <= 1'b0;
      DmaCsrPlugin_last_or_run_till_lastReg_2 <= 1'b0;
      DmaCsrPlugin_demapper_constellationReg_2 <= (4'b0000);
      DmaCsrPlugin_demapper_two_over_sigma_sqReg_2 <= (16'b0001000000000000);
      MapperMoverCsrPlugin_mover_active_reg1 <= (32'b00000000000000001111111111111111);
      MapperMoverCsrPlugin_trim_start_reg <= (32'b00000000000000000000000000000000);
      MapperMoverCsrPlugin_trim_end_reg <= (32'b00000000000000000000001111111111);
      MapperMoverCsrPlugin_one_value_reg <= (16'b0001011010100001);
      MapperMoverCsrPlugin_zero_value_reg <= (16'b1110100101011111);
      TimerCsrPlugin_timerReg <= (32'b00000000000000000000000000000000);
      DEngineCsrPlugin_resetReg <= 1'b0;
      DEngineCsrPlugin_func0MinThresholdReg <= (32'b00000000000000000000000000000000);
      DEngineCsrPlugin_func0MaxThresholdReg <= (32'b00000000000000000000000000000000);
      DEngineCsrPlugin_func1MinThresholdReg <= (32'b00000000000000000000000000000000);
      DEngineCsrPlugin_func1MaxThresholdReg <= (32'b00000000000000000000000000000000);
      _zz_180 <= 1'b1;
      memory_DivPlugin_div_counter_value <= (6'b000000);
      _zz_199 <= 1'b0;
      execute_XbbVectorCordic_vfsm_x <= (18'b000000000000000000);
      execute_XbbVectorCordic_vfsm_y <= (18'b000000000000000000);
      execute_XbbVectorCordic_vfsm_xtmp <= (18'b000000000000000000);
      execute_XbbVectorCordic_vfsm_ytmp <= (18'b000000000000000000);
      execute_XbbVectorCordic_vfsm_z <= (17'b00000000000000000);
      execute_XbbVectorCordic_vfsm_viter <= (4'b0000);
      execute_XbbVectorCordic_vfsm_sign <= (2'b00);
      _zz_227 <= (32'b00000000000000000000000000000000);
      _zz_260 <= (32'b00000000000000000000000000000000);
      execute_XbbVectorCordic_vfsm_stateReg <= `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_boot;
    end else begin
      prefetch_arbitration_isValid <= 1'b1;
      if(prefetch_arbitration_isFiring)begin
        prefetch_PcManagerSimplePlugin_pcReg <= prefetch_PcManagerSimplePlugin_pcPlus4;
      end
      if(prefetch_PcManagerSimplePlugin_jump_pcLoad_valid)begin
        prefetch_PcManagerSimplePlugin_pcReg <= prefetch_PcManagerSimplePlugin_jump_pcLoad_payload;
      end
      if(iBus_rsp_ready)begin
        prefetch_IBusSimplePlugin_pendingCmd <= 1'b0;
      end
      if((_zz_296 && iBus_cmd_ready))begin
        prefetch_IBusSimplePlugin_pendingCmd <= 1'b1;
      end
      if(iBus_rsp_ready)begin
        _zz_114 <= 1'b1;
      end
      if((! fetch_arbitration_isStuck))begin
        _zz_114 <= 1'b0;
      end
      CsrPlugin_mip_MEIP <= externalInterrupt;
      CsrPlugin_mip_MTIP <= timerInterrupt;
      if((! decode_arbitration_isStuck))begin
        CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_2 <= 1'b0;
      end else begin
        CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_2 <= CsrPlugin_exceptionPortCtrl_exceptionValids_2;
      end
      if((! execute_arbitration_isStuck))begin
        CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_3 <= CsrPlugin_exceptionPortCtrl_exceptionValids_2;
      end else begin
        CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_3 <= CsrPlugin_exceptionPortCtrl_exceptionValids_3;
      end
      if((! memory_arbitration_isStuck))begin
        CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_4 <= CsrPlugin_exceptionPortCtrl_exceptionValids_3;
      end else begin
        CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_4 <= CsrPlugin_exceptionPortCtrl_exceptionValids_4;
      end
      if((! writeBack_arbitration_isStuck))begin
        CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_5 <= CsrPlugin_exceptionPortCtrl_exceptionValids_4;
      end else begin
        CsrPlugin_exceptionPortCtrl_exceptionValidsRegs_5 <= CsrPlugin_exceptionPortCtrl_exceptionValids_5;
      end
      if(_zz_375)begin
        CsrPlugin_mstatus_MIE <= 1'b0;
        CsrPlugin_mstatus_MPIE <= CsrPlugin_mstatus_MIE;
        CsrPlugin_mstatus_MPP <= _zz_101;
      end
      if(_zz_368)begin
        if(memory_arbitration_isFiring)begin
          CsrPlugin_mstatus_MIE <= CsrPlugin_mstatus_MPIE;
          _zz_101 <= CsrPlugin_mstatus_MPP;
        end
      end
      if(_zz_127)begin
        DmaCsrPlugin_last_or_run_till_lastReg <= 1'b0;
      end
      if(_zz_133)begin
        DmaCsrPlugin_last_or_run_till_lastReg_1 <= 1'b0;
      end
      if(_zz_139)begin
        DmaCsrPlugin_last_or_run_till_lastReg_2 <= 1'b0;
      end
      TimerCsrPlugin_timerReg <= (TimerCsrPlugin_timerReg + (32'b00000000000000000000000000000001));
      _zz_180 <= 1'b0;
      memory_DivPlugin_div_counter_value <= memory_DivPlugin_div_counter_valueNext;
      _zz_199 <= (_zz_53 && writeBack_arbitration_isFiring);
      execute_XbbVectorCordic_vfsm_viter <= (execute_XbbVectorCordic_vfsm_viter + (4'b0001));
      if(debug_bus_cmd_valid)begin
        case(_zz_374)
          1'b0 : begin
          end
          default : begin
            if(debug_bus_cmd_payload_wr)begin
              if(DebugPlugin_firstCycle)begin
                decode_arbitration_isValid <= 1'b1;
              end
            end
          end
        endcase
      end
      if((! writeBack_arbitration_isStuck))begin
        _zz_227 <= _zz_34;
      end
      if((! writeBack_arbitration_isStuck))begin
        _zz_260 <= memory_INSTRUCTION;
      end
      if(((! fetch_arbitration_isStuck) || fetch_arbitration_removeIt))begin
        fetch_arbitration_isValid <= 1'b0;
      end
      if(((! prefetch_arbitration_isStuck) && (! prefetch_arbitration_removeIt)))begin
        fetch_arbitration_isValid <= prefetch_arbitration_isValid;
      end
      if(((! decode_arbitration_isStuck) || decode_arbitration_removeIt))begin
        decode_arbitration_isValid <= 1'b0;
      end
      if(((! fetch_arbitration_isStuck) && (! fetch_arbitration_removeIt)))begin
        decode_arbitration_isValid <= fetch_arbitration_isValid;
      end
      if(((! execute_arbitration_isStuck) || execute_arbitration_removeIt))begin
        execute_arbitration_isValid <= 1'b0;
      end
      if(((! decode_arbitration_isStuck) && (! decode_arbitration_removeIt)))begin
        execute_arbitration_isValid <= decode_arbitration_isValid;
      end
      if(((! memory_arbitration_isStuck) || memory_arbitration_removeIt))begin
        memory_arbitration_isValid <= 1'b0;
      end
      if(((! execute_arbitration_isStuck) && (! execute_arbitration_removeIt)))begin
        memory_arbitration_isValid <= execute_arbitration_isValid;
      end
      if(((! writeBack_arbitration_isStuck) || writeBack_arbitration_removeIt))begin
        writeBack_arbitration_isValid <= 1'b0;
      end
      if(((! memory_arbitration_isStuck) && (! memory_arbitration_removeIt)))begin
        writeBack_arbitration_isValid <= memory_arbitration_isValid;
      end
      case(execute_CsrPlugin_csrAddress)
        12'b110000100011 : begin
        end
        12'b111001000110 : begin
        end
        12'b111000100010 : begin
        end
        12'b111000011001 : begin
        end
        12'b110000011010 : begin
        end
        12'b110000001000 : begin
        end
        12'b110000010001 : begin
        end
        12'b111000010000 : begin
        end
        12'b111000000001 : begin
          if(execute_CsrPlugin_writeEnable)begin
            TimerCsrPlugin_timerReg <= (32'b00000000000000000000000000000000);
          end
        end
        12'b111001000000 : begin
        end
        12'b111000010011 : begin
        end
        12'b111000110111 : begin
        end
        12'b001100000000 : begin
          if(execute_CsrPlugin_writeEnable)begin
            CsrPlugin_mstatus_MPP <= execute_CsrPlugin_writeData[12 : 11];
            CsrPlugin_mstatus_MPIE <= _zz_456[0];
            CsrPlugin_mstatus_MIE <= _zz_457[0];
          end
        end
        12'b101100100100 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DmaCsrPlugin_demapper_two_over_sigma_sqReg_1 <= execute_CsrPlugin_writeData[15 : 0];
          end
        end
        12'b111000010110 : begin
        end
        12'b101100011011 : begin
        end
        12'b101100010010 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DmaCsrPlugin_last_or_run_till_lastReg <= _zz_458[0];
          end
        end
        12'b111000111010 : begin
        end
        12'b111000110001 : begin
        end
        12'b101100101101 : begin
        end
        12'b110000100010 : begin
        end
        12'b101100011110 : begin
        end
        12'b110000010000 : begin
        end
        12'b101100110000 : begin
        end
        12'b110000011001 : begin
        end
        12'b101100001100 : begin
        end
        12'b110000000001 : begin
          if(execute_CsrPlugin_writeEnable)begin
            MapperMoverCsrPlugin_mover_active_reg1 <= execute_CsrPlugin_writeData[31 : 0];
          end
        end
        12'b110000011100 : begin
        end
        12'b110000100101 : begin
        end
        12'b101100100001 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DmaCsrPlugin_reverseReg_1 <= _zz_459[0];
          end
        end
        12'b110000001010 : begin
        end
        12'b110000010011 : begin
        end
        12'b101100001111 : begin
        end
        12'b101100011000 : begin
        end
        12'b101100110011 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DmaCsrPlugin_demapper_constellationReg_2 <= execute_CsrPlugin_writeData[3 : 0];
          end
        end
        12'b101100101010 : begin
        end
        12'b001101000001 : begin
        end
        12'b110000011111 : begin
        end
        12'b111001000010 : begin
        end
        12'b110000001101 : begin
        end
        12'b101100001001 : begin
        end
        12'b110000010110 : begin
        end
        12'b111010000001 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DEngineCsrPlugin_func0MinThresholdReg <= execute_CsrPlugin_writeData[31 : 0];
          end
        end
        12'b111000111001 : begin
        end
        12'b111000110000 : begin
        end
        12'b110000000100 : begin
        end
        12'b111000010101 : begin
        end
        12'b111010000100 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DEngineCsrPlugin_func1MaxThresholdReg <= execute_CsrPlugin_writeData[31 : 0];
          end
        end
        12'b111000110011 : begin
        end
        12'b111000100001 : begin
        end
        12'b111000011000 : begin
        end
        12'b111001000101 : begin
        end
        12'b001101000100 : begin
          if(execute_CsrPlugin_writeEnable)begin
            CsrPlugin_mip_MSIP <= _zz_460[0];
          end
        end
        12'b111001100000 : begin
        end
        12'b110000000111 : begin
        end
        12'b111000110110 : begin
        end
        12'b101100101001 : begin
        end
        12'b101100100000 : begin
        end
        12'b111000010010 : begin
        end
        12'b111000000000 : begin
        end
        12'b101100110010 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DmaCsrPlugin_last_or_run_till_lastReg_2 <= _zz_461[0];
          end
        end
        12'b101100100011 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DmaCsrPlugin_demapper_constellationReg_1 <= execute_CsrPlugin_writeData[3 : 0];
          end
        end
        12'b101100101100 : begin
        end
        12'b101100010001 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DmaCsrPlugin_reverseReg <= _zz_462[0];
          end
        end
        12'b101100011010 : begin
        end
        12'b101100001000 : begin
        end
        12'b111010000011 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DEngineCsrPlugin_func1MinThresholdReg <= execute_CsrPlugin_writeData[31 : 0];
          end
        end
        12'b101100010100 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DmaCsrPlugin_demapper_two_over_sigma_sqReg <= execute_CsrPlugin_writeData[15 : 0];
          end
        end
        12'b110000000110 : begin
        end
        12'b111001110001 : begin
        end
        12'b101100011101 : begin
        end
        12'b101100001011 : begin
        end
        12'b110000100001 : begin
          if(execute_CsrPlugin_writeEnable)begin
            MapperMoverCsrPlugin_trim_end_reg <= execute_CsrPlugin_writeData[31 : 0];
          end
        end
        12'b110000001111 : begin
        end
        12'b110000011000 : begin
        end
        12'b001101000011 : begin
        end
        12'b101100101111 : begin
        end
        12'b110000100100 : begin
        end
        12'b110000011011 : begin
        end
        12'b101100001110 : begin
        end
        12'b110000010010 : begin
        end
        12'b111001010000 : begin
        end
        12'b111000110101 : begin
        end
        12'b110000000000 : begin
        end
        12'b110000001001 : begin
        end
        12'b111000111000 : begin
        end
        12'b110000000011 : begin
        end
        12'b110000011110 : begin
        end
        12'b111001000001 : begin
        end
        12'b110000010101 : begin
        end
        12'b110000001100 : begin
        end
        12'b111010000000 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DEngineCsrPlugin_resetReg <= _zz_463[0];
          end
        end
        12'b001100000100 : begin
          if(execute_CsrPlugin_writeEnable)begin
            CsrPlugin_mie_MEIE[5] <= _zz_464[0];
            CsrPlugin_mie_MEIE[4] <= _zz_465[0];
            CsrPlugin_mie_MEIE[3] <= _zz_466[0];
            CsrPlugin_mie_MEIE[2] <= _zz_467[0];
            CsrPlugin_mie_MEIE[1] <= _zz_468[0];
            CsrPlugin_mie_MEIE[0] <= _zz_469[0];
            CsrPlugin_mie_MTIE <= _zz_470[0];
            CsrPlugin_mie_MSIE <= _zz_471[0];
          end
        end
        12'b111000110010 : begin
        end
        12'b111001000100 : begin
        end
        12'b111000100000 : begin
        end
        12'b111000010111 : begin
        end
        12'b101100011111 : begin
        end
        12'b111000010001 : begin
        end
        12'b111000011010 : begin
        end
        12'b101100110001 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DmaCsrPlugin_reverseReg_2 <= _zz_472[0];
          end
        end
        12'b101100101000 : begin
        end
        12'b101100001101 : begin
        end
        12'b110000000010 : begin
        end
        12'b101100011001 : begin
        end
        12'b110000001011 : begin
        end
        12'b110000100110 : begin
          if(execute_CsrPlugin_writeEnable)begin
            MapperMoverCsrPlugin_one_value_reg <= execute_CsrPlugin_writeData[15 : 0];
            MapperMoverCsrPlugin_zero_value_reg <= execute_CsrPlugin_writeData[15 : 0];
          end
        end
        12'b101100100010 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DmaCsrPlugin_last_or_run_till_lastReg_1 <= _zz_473[0];
          end
        end
        12'b110000010100 : begin
        end
        12'b110000011101 : begin
        end
        12'b101100010000 : begin
        end
        12'b101100101011 : begin
        end
        12'b101100110100 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DmaCsrPlugin_demapper_two_over_sigma_sqReg_2 <= execute_CsrPlugin_writeData[15 : 0];
          end
        end
        12'b001101000010 : begin
        end
        12'b101100101110 : begin
        end
        12'b110000010111 : begin
        end
        12'b110000100000 : begin
          if(execute_CsrPlugin_writeEnable)begin
            MapperMoverCsrPlugin_trim_start_reg <= execute_CsrPlugin_writeData[31 : 0];
          end
        end
        12'b111001000011 : begin
        end
        12'b101100011100 : begin
        end
        12'b110000001110 : begin
        end
        12'b101100010011 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DmaCsrPlugin_demapper_constellationReg <= execute_CsrPlugin_writeData[3 : 0];
          end
        end
        12'b101100001010 : begin
        end
        12'b111010000010 : begin
          if(execute_CsrPlugin_writeEnable)begin
            DEngineCsrPlugin_func0MaxThresholdReg <= execute_CsrPlugin_writeData[31 : 0];
          end
        end
        12'b111001110000 : begin
        end
        12'b110000000101 : begin
        end
        default : begin
        end
      endcase
      execute_XbbVectorCordic_vfsm_stateReg <= execute_XbbVectorCordic_vfsm_stateNext;
      case(execute_XbbVectorCordic_vfsm_stateReg)
        `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateInit : begin
          if(_zz_377)begin
            if(execute_XbbVectorCordic_rs1[15])begin
              execute_XbbVectorCordic_vfsm_x <= {(2'b00),(~ execute_XbbVectorCordic_rs1[15 : 0])};
              execute_XbbVectorCordic_vfsm_xtmp <= {(2'b00),(~ execute_XbbVectorCordic_rs1[15 : 0])};
            end else begin
              execute_XbbVectorCordic_vfsm_x <= {(2'b00),execute_XbbVectorCordic_rs1[15 : 0]};
              execute_XbbVectorCordic_vfsm_xtmp <= {(2'b00),execute_XbbVectorCordic_rs1[15 : 0]};
            end
            execute_XbbVectorCordic_vfsm_y <= {{{execute_XbbVectorCordic_rs1[31],execute_XbbVectorCordic_rs1[31]},execute_XbbVectorCordic_rs1[31]},execute_XbbVectorCordic_rs1[30 : 16]};
            execute_XbbVectorCordic_vfsm_ytmp <= {{{execute_XbbVectorCordic_rs1[31],execute_XbbVectorCordic_rs1[31]},execute_XbbVectorCordic_rs1[31]},execute_XbbVectorCordic_rs1[30 : 16]};
            execute_XbbVectorCordic_vfsm_z <= (17'b00000000000000000);
            execute_XbbVectorCordic_vfsm_sign <= {execute_XbbVectorCordic_rs1[31],execute_XbbVectorCordic_rs1[15]};
          end
          execute_XbbVectorCordic_vfsm_viter <= (4'b0000);
        end
        `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateCompute : begin
          execute_XbbVectorCordic_vfsm_x <= execute_XbbVectorCordic_vfsm_stateCompute_xval;
          execute_XbbVectorCordic_vfsm_y <= execute_XbbVectorCordic_vfsm_stateCompute_yval;
          case(execute_XbbVectorCordic_vfsm_viter)
            4'b0000 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_475)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_476));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_477));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (1'b1));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (1'b1));
            end
            4'b0001 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_478)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_479));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_480));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (2'b10));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (2'b10));
            end
            4'b0010 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_481)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_482));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_483));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (2'b11));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (2'b11));
            end
            4'b0011 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_484)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_485));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_486));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (3'b100));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (3'b100));
            end
            4'b0100 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_487)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_488));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_489));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (3'b101));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (3'b101));
            end
            4'b0101 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_490)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_491));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_492));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (3'b110));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (3'b110));
            end
            4'b0110 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_493)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_494));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_495));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (3'b111));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (3'b111));
            end
            4'b0111 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_496)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_497));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_498));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (4'b1000));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (4'b1000));
            end
            4'b1000 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_499)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_500));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_501));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (4'b1001));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (4'b1001));
            end
            4'b1001 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_502)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_503));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_504));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (4'b1010));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (4'b1010));
            end
            4'b1010 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_505)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_506));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_507));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (4'b1011));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (4'b1011));
            end
            4'b1011 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_508)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_509));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_510));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (4'b1100));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (4'b1100));
            end
            4'b1100 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_511)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_512));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_513));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (4'b1101));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (4'b1101));
            end
            4'b1101 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_514)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_515));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_516));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (4'b1110));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (4'b1110));
            end
            4'b1110 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_517)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_518));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_519));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (4'b1111));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (4'b1111));
            end
            4'b1111 : begin
              if(($signed(execute_XbbVectorCordic_vfsm_y) < $signed(_zz_520)))begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) - $signed(_zz_521));
              end else begin
                execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) + $signed(_zz_522));
              end
              execute_XbbVectorCordic_vfsm_xtmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_xval) >>> (5'b10000));
              execute_XbbVectorCordic_vfsm_ytmp <= ($signed(execute_XbbVectorCordic_vfsm_stateCompute_yval) >>> (5'b10000));
            end
            default : begin
            end
          endcase
          if(_zz_372)begin
            execute_XbbVectorCordic_vfsm_z <= execute_XbbVectorCordic_vfsm_z;
            execute_XbbVectorCordic_vfsm_x <= execute_XbbVectorCordic_vfsm_x;
            execute_XbbVectorCordic_vfsm_y <= execute_XbbVectorCordic_vfsm_y;
          end
        end
        `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateSaturate : begin
          if((execute_XbbVectorCordic_vfsm_z[16] != execute_XbbVectorCordic_vfsm_z[15]))begin
            execute_XbbVectorCordic_vfsm_z <= ((! execute_XbbVectorCordic_vfsm_z[16]) ? _zz_523 : _zz_524);
            execute_XbbVectorCordic_vfsm_z[15] <= execute_XbbVectorCordic_vfsm_z[16];
            execute_XbbVectorCordic_vfsm_z[16] <= execute_XbbVectorCordic_vfsm_z[16];
          end
        end
        `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateNormalize : begin
          if((execute_XbbVectorCordic_vfsm_sign[0] && (! execute_XbbVectorCordic_vfsm_z[15])))begin
            execute_XbbVectorCordic_vfsm_z <= ($signed(_zz_525) - $signed(_zz_526));
          end else begin
            if((execute_XbbVectorCordic_vfsm_sign[0] && execute_XbbVectorCordic_vfsm_z[15]))begin
              execute_XbbVectorCordic_vfsm_z <= ($signed(_zz_527) - $signed(_zz_528));
            end else begin
              execute_XbbVectorCordic_vfsm_z <= ($signed(execute_XbbVectorCordic_vfsm_z) >>> (1'b1));
            end
          end
        end
        `execute_XbbVectorCordic_vfsm_enumDefinition_binary_sequancial_execute_XbbVectorCordic_vfsm_stateOutput : begin
        end
        default : begin
        end
      endcase
    end
  end

  always @ (posedge io_mainClk) begin
    if((! _zz_114))begin
      _zz_115 <= iBus_rsp_inst;
    end
    if (!(! (((dBus_rsp_ready && memory_MEMORY_ENABLE) && memory_arbitration_isValid) && memory_arbitration_isStuck))) begin
      $display("ERROR DBusSimplePlugin doesn't allow memory stage stall when read happend");
    end
    if (!(! (((writeBack_arbitration_isValid && writeBack_MEMORY_ENABLE) && (! writeBack_INSTRUCTION[5])) && writeBack_arbitration_isStuck))) begin
      $display("ERROR DBusSimplePlugin doesn't allow memory stage stall when read happend");
    end
    CsrPlugin_mcycle <= (CsrPlugin_mcycle + (64'b0000000000000000000000000000000000000000000000000000000000000001));
    if(writeBack_arbitration_isFiring)begin
      CsrPlugin_minstret <= (CsrPlugin_minstret + (64'b0000000000000000000000000000000000000000000000000000000000000001));
    end
    if(_zz_378)begin
      CsrPlugin_exceptionPortCtrl_exceptionContext_code <= _zz_301;
      CsrPlugin_exceptionPortCtrl_exceptionContext_badAddr <= _zz_302;
    end
    if(_zz_373)begin
      CsrPlugin_exceptionPortCtrl_exceptionContext_code <= (5'b00000);
      CsrPlugin_exceptionPortCtrl_exceptionContext_badAddr <= _zz_106;
    end
    if(_zz_375)begin
      CsrPlugin_mepc <= _zz_125;
      CsrPlugin_mcause_interrupt <= CsrPlugin_interrupt;
      CsrPlugin_mcause_exceptionCode <= ((CsrPlugin_mip_MEIP[5] && CsrPlugin_mie_MEIE[5]) ? (5'b11111) : ((CsrPlugin_mip_MEIP[4] && CsrPlugin_mie_MEIE[4]) ? (5'b11011) : ((CsrPlugin_mip_MEIP[3] && CsrPlugin_mie_MEIE[3]) ? (5'b10111) : ((CsrPlugin_mip_MEIP[2] && CsrPlugin_mie_MEIE[2]) ? (5'b10011) : _zz_387))));
    end
    _zz_126 <= CsrPlugin_exception;
    if(_zz_126)begin
      CsrPlugin_mbadaddr <= CsrPlugin_exceptionPortCtrl_exceptionContext_badAddr;
      CsrPlugin_mcause_exceptionCode <= CsrPlugin_exceptionPortCtrl_exceptionContext_code;
    end
    if(execute_arbitration_isValid)begin
      execute_CsrPlugin_readDataRegValid <= 1'b1;
    end
    if((! execute_arbitration_isStuck))begin
      execute_CsrPlugin_readDataRegValid <= 1'b0;
    end
    _zz_131 <= _zz_130;
    _zz_137 <= _zz_136;
    _zz_143 <= _zz_142;
    MapperMoverCsrPlugin_pilot_ram_we <= _zz_145;
    MapperMoverCsrPlugin_reset <= _zz_146;
    _zz_160 <= _zz_159;
    _zz_161 <= GenericOutCsrPlugin_valueReg;
    SatDetectCsrPlugin_satDetectReg <= _zz_104;
    SatDetectCsrPlugin_satTimeReg <= (SatDetectCsrPlugin_satTimeReg + (16'b0000000000000001));
    SatDetectCsrPlugin_satCountReg <= SatDetectCsrPlugin_satCountReg;
    if((SatDetectCsrPlugin_satTimeReg == (16'b1111111111111111)))begin
      SatDetectCsrPlugin_satCountReg <= (16'b0000000000000000);
    end
    if((SatDetectCsrPlugin_satDetectReg == 1'b1))begin
      SatDetectCsrPlugin_satCountReg <= (SatDetectCsrPlugin_satCountReg + (16'b0000000000000001));
    end
    if(_zz_162)begin
      SatDetectCsrPlugin_satCountReg <= (16'b0000000000000000);
      SatDetectCsrPlugin_satTimeReg <= (16'b0000000000000000);
    end
    if(_zz_370)begin
      if(_zz_371)begin
        memory_DivPlugin_rs1[31 : 0] <= _zz_435[31:0];
        memory_DivPlugin_accumulator[31 : 0] <= ((! _zz_190[32]) ? _zz_436 : _zz_437);
        if((memory_DivPlugin_div_counter_value == (6'b100000)))begin
          memory_DivPlugin_div_result <= _zz_438[31:0];
        end
      end
    end
    if(_zz_376)begin
      memory_DivPlugin_accumulator <= (65'b00000000000000000000000000000000000000000000000000000000000000000);
      memory_DivPlugin_rs1 <= ((_zz_193 ? (~ _zz_194) : _zz_194) + _zz_444);
      memory_DivPlugin_rs2 <= ((_zz_192 ? (~ execute_RS2) : execute_RS2) + _zz_446);
      memory_DivPlugin_div_needRevert <= (_zz_193 ^ (_zz_192 && (! execute_INSTRUCTION[13])));
    end
    _zz_200 <= _zz_52[11 : 7];
    _zz_201 <= _zz_85;
    execute_XbbVectorCordic_iters <= execute_XbbVectorCordic_rs2[3 : 0];
    if((! execute_arbitration_isStuck))begin
      _zz_225 <= decode_IS_EBREAK;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_226 <= _zz_81;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_228 <= decode_RS1;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_229 <= _zz_46;
    end
    if((! writeBack_arbitration_isStuck))begin
      _zz_230 <= memory_RS1;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_231 <= decode_BYPASSABLE_MEMORY_STAGE;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_232 <= execute_BYPASSABLE_MEMORY_STAGE;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_233 <= execute_MUL_HH;
    end
    if((! writeBack_arbitration_isStuck))begin
      _zz_234 <= memory_MUL_HH;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_235 <= decode_PREDICTION_HAD_BRANCHED2;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_236 <= decode_INSTRUCTION_READY;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_237 <= execute_INSTRUCTION_READY;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_238 <= _zz_24;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_239 <= _zz_21;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_240 <= decode_IS_VCORDIC;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_241 <= decode_SRC_LESS_UNSIGNED;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_242 <= decode_RS2;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_243 <= _zz_18;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_244 <= decode_IS_XBASEBAND;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_245 <= execute_IS_XBASEBAND;
    end
    if((! writeBack_arbitration_isStuck))begin
      _zz_246 <= memory_IS_XBASEBAND;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_247 <= _zz_16;
    end
    if((! writeBack_arbitration_isStuck))begin
      _zz_248 <= memory_MEMORY_READ_DATA;
    end
    if((! writeBack_arbitration_isStuck))begin
      _zz_249 <= memory_MUL_LOW;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_250 <= _zz_13;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_251 <= execute_MEMORY_ADDRESS_LOW;
    end
    if((! writeBack_arbitration_isStuck))begin
      _zz_252 <= memory_MEMORY_ADDRESS_LOW;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_253 <= decode_IS_CSR;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_254 <= decode_IS_RS1_SIGNED;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_255 <= _zz_10;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_256 <= _zz_7;
    end
    if((! decode_arbitration_isStuck))begin
      _zz_257 <= _zz_90;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_258 <= decode_INSTRUCTION;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_259 <= execute_INSTRUCTION;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_261 <= execute_BRANCH_DO;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_262 <= decode_CSR_WRITE_OPCODE;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_263 <= decode_IS_MUL;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_264 <= execute_IS_MUL;
    end
    if((! writeBack_arbitration_isStuck))begin
      _zz_265 <= memory_IS_MUL;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_266 <= _zz_5;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_267 <= decode_SRC_USE_SUB_LESS;
    end
    if((! fetch_arbitration_isStuck))begin
      _zz_268 <= _zz_93;
    end
    if((! decode_arbitration_isStuck))begin
      _zz_269 <= fetch_PC;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_270 <= decode_PC;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_271 <= _zz_43;
    end
    if((! writeBack_arbitration_isStuck))begin
      _zz_272 <= memory_PC;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_273 <= decode_IS_DIV;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_274 <= execute_IS_DIV;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_275 <= decode_CSR_READ_OPCODE;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_276 <= execute_MUL_HL;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_277 <= decode_IS_RS2_SIGNED;
    end
    if((! fetch_arbitration_isStuck))begin
      _zz_278 <= prefetch_FORMAL_PC_NEXT;
    end
    if((! decode_arbitration_isStuck))begin
      _zz_279 <= fetch_FORMAL_PC_NEXT;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_280 <= _zz_94;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_281 <= _zz_95;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_282 <= decode_BYPASSABLE_EXECUTE_STAGE;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_283 <= decode_MEMORY_ENABLE;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_284 <= execute_MEMORY_ENABLE;
    end
    if((! writeBack_arbitration_isStuck))begin
      _zz_285 <= memory_MEMORY_ENABLE;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_286 <= execute_MUL_LH;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_287 <= _zz_2;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_288 <= execute_BRANCH_CALC;
    end
    if((! execute_arbitration_isStuck))begin
      _zz_289 <= decode_REGFILE_WRITE_VALID;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_290 <= execute_REGFILE_WRITE_VALID;
    end
    if((! writeBack_arbitration_isStuck))begin
      _zz_291 <= memory_REGFILE_WRITE_VALID;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_292 <= execute_MUL_LL;
    end
    if((! memory_arbitration_isStuck))begin
      _zz_293 <= execute_SHIFT_RIGHT;
    end
    case(execute_CsrPlugin_csrAddress)
      12'b110000100011 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_pilot_ram_wdata <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111001000110 : begin
      end
      12'b111000100010 : begin
      end
      12'b111000011001 : begin
      end
      12'b110000011010 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg26 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000001000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg8 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000010001 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg17 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111000010000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          RingBusCsrPlugin_writeAddrReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111000000001 : begin
      end
      12'b111001000000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          NCOCsrPlugin_startAngleReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111000010011 : begin
      end
      12'b111000110111 : begin
      end
      12'b001100000000 : begin
      end
      12'b101100100100 : begin
      end
      12'b111000010110 : begin
      end
      12'b101100011011 : begin
      end
      12'b101100010010 : begin
      end
      12'b111000111010 : begin
      end
      12'b111000110001 : begin
        if(execute_CsrPlugin_writeEnable)begin
          RingBusCsrPlugin_writeDataReg_1 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100101101 : begin
      end
      12'b110000100010 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_pilot_ram_addr <= execute_CsrPlugin_writeData[9 : 0];
        end
      end
      12'b101100011110 : begin
      end
      12'b110000010000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg16 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100110000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          DmaCsrPlugin_slicerReg_2 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000011001 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg25 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100001100 : begin
      end
      12'b110000000001 : begin
      end
      12'b110000011100 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg28 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000100101 : begin
      end
      12'b101100100001 : begin
      end
      12'b110000001010 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg10 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000010011 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg19 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100001111 : begin
      end
      12'b101100011000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          DmaCsrPlugin_startAddrReg_1 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100110011 : begin
      end
      12'b101100101010 : begin
        if(execute_CsrPlugin_writeEnable)begin
          DmaCsrPlugin_timerInitReg_2 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b001101000001 : begin
        if(execute_CsrPlugin_writeEnable)begin
          CsrPlugin_mepc <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000011111 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg31 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111001000010 : begin
        if(execute_CsrPlugin_writeEnable)begin
          NCOCsrPlugin_deltaReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000001101 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg13 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100001001 : begin
        if(execute_CsrPlugin_writeEnable)begin
          DmaCsrPlugin_lengthReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000010110 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg22 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111010000001 : begin
      end
      12'b111000111001 : begin
      end
      12'b111000110000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          RingBusCsrPlugin_writeAddrReg_1 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000000100 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg4 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111000010101 : begin
      end
      12'b111010000100 : begin
      end
      12'b111000110011 : begin
      end
      12'b111000100001 : begin
        if(execute_CsrPlugin_writeEnable)begin
          GpioCsrPlugin_writeEnableReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111000011000 : begin
      end
      12'b111001000101 : begin
      end
      12'b001101000100 : begin
      end
      12'b111001100000 : begin
      end
      12'b110000000111 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg7 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111000110110 : begin
      end
      12'b101100101001 : begin
        if(execute_CsrPlugin_writeEnable)begin
          DmaCsrPlugin_lengthReg_2 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100100000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          DmaCsrPlugin_slicerReg_1 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111000010010 : begin
      end
      12'b111000000000 : begin
      end
      12'b101100110010 : begin
      end
      12'b101100100011 : begin
      end
      12'b101100101100 : begin
      end
      12'b101100010001 : begin
      end
      12'b101100011010 : begin
        if(execute_CsrPlugin_writeEnable)begin
          DmaCsrPlugin_timerInitReg_1 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100001000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          DmaCsrPlugin_startAddrReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111010000011 : begin
      end
      12'b101100010100 : begin
      end
      12'b110000000110 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg6 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111001110001 : begin
        if(execute_CsrPlugin_writeEnable)begin
          ControlStatusCsrPlugin_controlReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100011101 : begin
      end
      12'b101100001011 : begin
      end
      12'b110000100001 : begin
      end
      12'b110000001111 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg15 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000011000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg24 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b001101000011 : begin
      end
      12'b101100101111 : begin
      end
      12'b110000100100 : begin
      end
      12'b110000011011 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg27 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100001110 : begin
      end
      12'b110000010010 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg18 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111001010000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          GenericOutCsrPlugin_valueReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111000110101 : begin
      end
      12'b110000000000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg0 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000001001 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg9 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111000111000 : begin
      end
      12'b110000000011 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg3 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000011110 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg30 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111001000001 : begin
        if(execute_CsrPlugin_writeEnable)begin
          NCOCsrPlugin_lengthReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000010101 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg21 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000001100 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg12 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111010000000 : begin
      end
      12'b001100000100 : begin
      end
      12'b111000110010 : begin
      end
      12'b111001000100 : begin
      end
      12'b111000100000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          GpioCsrPlugin_writeReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111000010111 : begin
      end
      12'b101100011111 : begin
      end
      12'b111000010001 : begin
        if(execute_CsrPlugin_writeEnable)begin
          RingBusCsrPlugin_writeDataReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111000011010 : begin
      end
      12'b101100110001 : begin
      end
      12'b101100101000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          DmaCsrPlugin_startAddrReg_2 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100001101 : begin
      end
      12'b110000000010 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg2 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100011001 : begin
        if(execute_CsrPlugin_writeEnable)begin
          DmaCsrPlugin_lengthReg_1 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000001011 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg11 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000100110 : begin
      end
      12'b101100100010 : begin
      end
      12'b110000010100 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg20 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000011101 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg29 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100010000 : begin
        if(execute_CsrPlugin_writeEnable)begin
          DmaCsrPlugin_slicerReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100101011 : begin
      end
      12'b101100110100 : begin
      end
      12'b001101000010 : begin
      end
      12'b101100101110 : begin
      end
      12'b110000010111 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg23 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b110000100000 : begin
      end
      12'b111001000011 : begin
      end
      12'b101100011100 : begin
      end
      12'b110000001110 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg14 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b101100010011 : begin
      end
      12'b101100001010 : begin
        if(execute_CsrPlugin_writeEnable)begin
          DmaCsrPlugin_timerInitReg <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      12'b111010000010 : begin
      end
      12'b111001110000 : begin
      end
      12'b110000000101 : begin
        if(execute_CsrPlugin_writeEnable)begin
          MapperMoverCsrPlugin_mover_active_reg5 <= execute_CsrPlugin_writeData[31 : 0];
        end
      end
      default : begin
      end
    endcase
    if(DebugPlugin_insertDecodeInstruction)begin
      _zz_257 <= debug_bus_cmd_payload_data;
    end
  end

  always @ (posedge io_mainClk) begin
    DebugPlugin_firstCycle <= 1'b0;
    if(_zz_299)begin
      DebugPlugin_firstCycle <= 1'b1;
    end
    DebugPlugin_secondCycle <= DebugPlugin_firstCycle;
    DebugPlugin_isPipActive <= ((((fetch_arbitration_isValid || decode_arbitration_isValid) || execute_arbitration_isValid) || memory_arbitration_isValid) || writeBack_arbitration_isValid);
    _zz_222 <= DebugPlugin_isPipActive;
    if(writeBack_arbitration_isValid)begin
      DebugPlugin_busReadDataReg <= _zz_85;
    end
    _zz_223 <= debug_bus_cmd_payload_address[2];
    _zz_224 <= DebugPlugin_resetIt;
  end

  always @ (posedge io_mainClk or posedge resetCtrl_mainClkReset) begin
    if (resetCtrl_mainClkReset) begin
      DebugPlugin_resetIt <= 1'b0;
      DebugPlugin_haltIt <= 1'b0;
      DebugPlugin_stepIt <= 1'b0;
      DebugPlugin_haltedByBreak <= 1'b0;
    end else begin
      if(debug_bus_cmd_valid)begin
        case(_zz_374)
          1'b0 : begin
            if(debug_bus_cmd_payload_wr)begin
              DebugPlugin_stepIt <= debug_bus_cmd_payload_data[4];
              if(debug_bus_cmd_payload_data[16])begin
                DebugPlugin_resetIt <= 1'b1;
              end
              if(debug_bus_cmd_payload_data[24])begin
                DebugPlugin_resetIt <= 1'b0;
              end
              if(debug_bus_cmd_payload_data[17])begin
                DebugPlugin_haltIt <= 1'b1;
              end
              if(debug_bus_cmd_payload_data[25])begin
                DebugPlugin_haltIt <= 1'b0;
              end
              if(debug_bus_cmd_payload_data[25])begin
                DebugPlugin_haltedByBreak <= 1'b0;
              end
            end
          end
          default : begin
          end
        endcase
      end
      if(_zz_369)begin
        DebugPlugin_haltIt <= 1'b1;
        DebugPlugin_haltedByBreak <= 1'b1;
      end
      if((DebugPlugin_stepIt && prefetch_arbitration_isFiring))begin
        DebugPlugin_haltIt <= 1'b1;
      end
      if((DebugPlugin_stepIt && ({writeBack_arbitration_redoIt,{memory_arbitration_redoIt,{execute_arbitration_redoIt,{decode_arbitration_redoIt,{fetch_arbitration_redoIt,prefetch_arbitration_redoIt}}}}} != (6'b000000))))begin
        DebugPlugin_haltIt <= 1'b0;
      end
    end
  end

endmodule

module JtagBridge (
      input   io_jtag_tms,
      input   io_jtag_tdi,
      output reg  io_jtag_tdo,
      input   io_jtag_tck,
      output  io_remote_cmd_valid,
      input   io_remote_cmd_ready,
      output  io_remote_cmd_payload_last,
      output [0:0] io_remote_cmd_payload_fragment,
      input   io_remote_rsp_valid,
      output  io_remote_rsp_ready,
      input   io_remote_rsp_payload_error,
      input  [31:0] io_remote_rsp_payload_data,
      input   io_mainClk,
      input   resetCtrl_mainClkReset);
  wire  _zz_2;
  wire  _zz_3;
  wire  _zz_4;
  wire  _zz_5;
  wire [0:0] _zz_6;
  wire  _zz_7;
  wire  _zz_8;
  wire [3:0] _zz_9;
  wire [3:0] _zz_10;
  wire [3:0] _zz_11;
  wire  system_cmd_valid;
  wire  system_cmd_payload_last;
  wire [0:0] system_cmd_payload_fragment;
  reg  system_rsp_valid;
  reg  system_rsp_payload_error;
  reg [31:0] system_rsp_payload_data;
  wire `JtagState_binary_sequancial_type jtag_tap_fsm_stateNext;
  reg `JtagState_binary_sequancial_type jtag_tap_fsm_state = `JtagState_binary_sequancial_IR_CAPTURE;
  reg `JtagState_binary_sequancial_type _zz_1;
  reg [3:0] jtag_tap_instruction;
  reg [3:0] jtag_tap_instructionShift;
  reg  jtag_tap_bypass;
  wire [0:0] jtag_idcodeArea_instructionId;
  wire  jtag_idcodeArea_instructionHit;
  reg [31:0] jtag_idcodeArea_shifter;
  wire [1:0] jtag_writeArea_instructionId;
  wire  jtag_writeArea_instructionHit;
  reg  jtag_writeArea_source_valid;
  wire  jtag_writeArea_source_payload_last;
  wire [0:0] jtag_writeArea_source_payload_fragment;
  wire [1:0] jtag_readArea_instructionId;
  wire  jtag_readArea_instructionHit;
  reg [33:0] jtag_readArea_shifter;
  assign io_remote_cmd_valid = _zz_2;
  assign io_remote_rsp_ready = _zz_3;
  assign _zz_7 = (jtag_tap_fsm_state == `JtagState_binary_sequancial_DR_SHIFT);
  assign _zz_8 = (jtag_tap_fsm_state == `JtagState_binary_sequancial_DR_SHIFT);
  assign _zz_9 = {3'd0, jtag_idcodeArea_instructionId};
  assign _zz_10 = {2'd0, jtag_writeArea_instructionId};
  assign _zz_11 = {2'd0, jtag_readArea_instructionId};
  FlowCCByToggle flowCCByToggle_1 ( 
    .io_input_valid(jtag_writeArea_source_valid),
    .io_input_payload_last(jtag_writeArea_source_payload_last),
    .io_input_payload_fragment(jtag_writeArea_source_payload_fragment),
    .io_output_valid(_zz_4),
    .io_output_payload_last(_zz_5),
    .io_output_payload_fragment(_zz_6),
    .io_jtag_tck(io_jtag_tck),
    .io_mainClk(io_mainClk),
    .resetCtrl_mainClkReset(resetCtrl_mainClkReset) 
  );
  assign _zz_2 = system_cmd_valid;
  assign io_remote_cmd_payload_last = system_cmd_payload_last;
  assign io_remote_cmd_payload_fragment = system_cmd_payload_fragment;
  assign _zz_3 = 1'b1;
  always @ (*) begin
    case(jtag_tap_fsm_state)
      `JtagState_binary_sequancial_IDLE : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_DR_SELECT : `JtagState_binary_sequancial_IDLE);
      end
      `JtagState_binary_sequancial_IR_SELECT : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_RESET : `JtagState_binary_sequancial_IR_CAPTURE);
      end
      `JtagState_binary_sequancial_IR_CAPTURE : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_IR_EXIT1 : `JtagState_binary_sequancial_IR_SHIFT);
      end
      `JtagState_binary_sequancial_IR_SHIFT : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_IR_EXIT1 : `JtagState_binary_sequancial_IR_SHIFT);
      end
      `JtagState_binary_sequancial_IR_EXIT1 : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_IR_UPDATE : `JtagState_binary_sequancial_IR_PAUSE);
      end
      `JtagState_binary_sequancial_IR_PAUSE : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_IR_EXIT2 : `JtagState_binary_sequancial_IR_PAUSE);
      end
      `JtagState_binary_sequancial_IR_EXIT2 : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_IR_UPDATE : `JtagState_binary_sequancial_IR_SHIFT);
      end
      `JtagState_binary_sequancial_IR_UPDATE : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_DR_SELECT : `JtagState_binary_sequancial_IDLE);
      end
      `JtagState_binary_sequancial_DR_SELECT : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_IR_SELECT : `JtagState_binary_sequancial_DR_CAPTURE);
      end
      `JtagState_binary_sequancial_DR_CAPTURE : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_DR_EXIT1 : `JtagState_binary_sequancial_DR_SHIFT);
      end
      `JtagState_binary_sequancial_DR_SHIFT : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_DR_EXIT1 : `JtagState_binary_sequancial_DR_SHIFT);
      end
      `JtagState_binary_sequancial_DR_EXIT1 : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_DR_UPDATE : `JtagState_binary_sequancial_DR_PAUSE);
      end
      `JtagState_binary_sequancial_DR_PAUSE : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_DR_EXIT2 : `JtagState_binary_sequancial_DR_PAUSE);
      end
      `JtagState_binary_sequancial_DR_EXIT2 : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_DR_UPDATE : `JtagState_binary_sequancial_DR_SHIFT);
      end
      `JtagState_binary_sequancial_DR_UPDATE : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_DR_SELECT : `JtagState_binary_sequancial_IDLE);
      end
      default : begin
        _zz_1 = (io_jtag_tms ? `JtagState_binary_sequancial_RESET : `JtagState_binary_sequancial_IDLE);
      end
    endcase
  end

  assign jtag_tap_fsm_stateNext = _zz_1;
  always @ (*) begin
    io_jtag_tdo = jtag_tap_bypass;
    case(jtag_tap_fsm_state)
      `JtagState_binary_sequancial_IR_CAPTURE : begin
      end
      `JtagState_binary_sequancial_IR_SHIFT : begin
        io_jtag_tdo = jtag_tap_instructionShift[0];
      end
      `JtagState_binary_sequancial_IR_UPDATE : begin
      end
      `JtagState_binary_sequancial_DR_SHIFT : begin
      end
      default : begin
      end
    endcase
    if(jtag_idcodeArea_instructionHit)begin
      if(_zz_8)begin
        io_jtag_tdo = jtag_idcodeArea_shifter[0];
      end
    end
    if(jtag_readArea_instructionHit)begin
      if(_zz_7)begin
        io_jtag_tdo = jtag_readArea_shifter[0];
      end
    end
  end

  assign jtag_idcodeArea_instructionId = (1'b1);
  assign jtag_idcodeArea_instructionHit = (jtag_tap_instruction == _zz_9);
  assign jtag_writeArea_instructionId = (2'b10);
  assign jtag_writeArea_instructionHit = (jtag_tap_instruction == _zz_10);
  always @ (*) begin
    jtag_writeArea_source_valid = 1'b0;
    if(jtag_writeArea_instructionHit)begin
      if((jtag_tap_fsm_state == `JtagState_binary_sequancial_DR_SHIFT))begin
        jtag_writeArea_source_valid = 1'b1;
      end
    end
  end

  assign jtag_writeArea_source_payload_last = io_jtag_tms;
  assign jtag_writeArea_source_payload_fragment[0] = io_jtag_tdi;
  assign system_cmd_valid = _zz_4;
  assign system_cmd_payload_last = _zz_5;
  assign system_cmd_payload_fragment = _zz_6;
  assign jtag_readArea_instructionId = (2'b11);
  assign jtag_readArea_instructionHit = (jtag_tap_instruction == _zz_11);
  always @ (posedge io_mainClk) begin
    if(_zz_2)begin
      system_rsp_valid <= 1'b0;
    end
    if((io_remote_rsp_valid && _zz_3))begin
      system_rsp_valid <= 1'b1;
      system_rsp_payload_error <= io_remote_rsp_payload_error;
      system_rsp_payload_data <= io_remote_rsp_payload_data;
    end
  end

  always @ (posedge io_jtag_tck) begin
    jtag_tap_fsm_state <= jtag_tap_fsm_stateNext;
    case(jtag_tap_fsm_state)
      `JtagState_binary_sequancial_IR_CAPTURE : begin
        jtag_tap_instructionShift <= jtag_tap_instruction;
      end
      `JtagState_binary_sequancial_IR_SHIFT : begin
        jtag_tap_instructionShift <= ({io_jtag_tdi,jtag_tap_instructionShift} >>> 1);
      end
      `JtagState_binary_sequancial_IR_UPDATE : begin
        jtag_tap_instruction <= jtag_tap_instructionShift;
      end
      `JtagState_binary_sequancial_DR_SHIFT : begin
        jtag_tap_bypass <= io_jtag_tdi;
      end
      default : begin
      end
    endcase
    if(jtag_idcodeArea_instructionHit)begin
      if(_zz_8)begin
        jtag_idcodeArea_shifter <= ({io_jtag_tdi,jtag_idcodeArea_shifter} >>> 1);
      end
    end
    if((jtag_tap_fsm_state == `JtagState_binary_sequancial_RESET))begin
      jtag_idcodeArea_shifter <= (32'b00010000000000000001111111111111);
      jtag_tap_instruction <= {3'd0, jtag_idcodeArea_instructionId};
    end
    if(jtag_readArea_instructionHit)begin
      if((jtag_tap_fsm_state == `JtagState_binary_sequancial_DR_CAPTURE))begin
        jtag_readArea_shifter <= {{system_rsp_payload_data,system_rsp_payload_error},system_rsp_valid};
      end
      if(_zz_7)begin
        jtag_readArea_shifter <= ({io_jtag_tdi,jtag_readArea_shifter} >>> 1);
      end
    end
  end

endmodule

module SystemDebugger (
      input   io_remote_cmd_valid,
      output  io_remote_cmd_ready,
      input   io_remote_cmd_payload_last,
      input  [0:0] io_remote_cmd_payload_fragment,
      output  io_remote_rsp_valid,
      input   io_remote_rsp_ready,
      output  io_remote_rsp_payload_error,
      output [31:0] io_remote_rsp_payload_data,
      output  io_mem_cmd_valid,
      input   io_mem_cmd_ready,
      output [31:0] io_mem_cmd_payload_address,
      output [31:0] io_mem_cmd_payload_data,
      output  io_mem_cmd_payload_wr,
      output [1:0] io_mem_cmd_payload_size,
      input   io_mem_rsp_valid,
      input  [31:0] io_mem_rsp_payload,
      input   io_mainClk,
      input   resetCtrl_mainClkReset);
  wire  _zz_2;
  wire  _zz_3;
  wire [0:0] _zz_4;
  reg [66:0] dispatcher_dataShifter;
  reg  dispatcher_dataLoaded;
  reg [7:0] dispatcher_headerShifter;
  wire [7:0] dispatcher_header;
  reg  dispatcher_headerLoaded;
  reg [2:0] dispatcher_counter;
  wire [66:0] _zz_1;
  assign io_mem_cmd_valid = _zz_2;
  assign _zz_3 = (dispatcher_headerLoaded == 1'b0);
  assign _zz_4 = _zz_1[64 : 64];
  assign dispatcher_header = dispatcher_headerShifter[7 : 0];
  assign io_remote_cmd_ready = (! dispatcher_dataLoaded);
  assign _zz_1 = dispatcher_dataShifter[66 : 0];
  assign io_mem_cmd_payload_address = _zz_1[31 : 0];
  assign io_mem_cmd_payload_data = _zz_1[63 : 32];
  assign io_mem_cmd_payload_wr = _zz_4[0];
  assign io_mem_cmd_payload_size = _zz_1[66 : 65];
  assign _zz_2 = (dispatcher_dataLoaded && (dispatcher_header == (8'b00000000)));
  assign io_remote_rsp_valid = io_mem_rsp_valid;
  assign io_remote_rsp_payload_error = 1'b0;
  assign io_remote_rsp_payload_data = io_mem_rsp_payload;
  always @ (posedge io_mainClk or posedge resetCtrl_mainClkReset) begin
    if (resetCtrl_mainClkReset) begin
      dispatcher_dataLoaded <= 1'b0;
      dispatcher_headerLoaded <= 1'b0;
      dispatcher_counter <= (3'b000);
    end else begin
      if(io_remote_cmd_valid)begin
        if(_zz_3)begin
          dispatcher_counter <= (dispatcher_counter + (3'b001));
          if((dispatcher_counter == (3'b111)))begin
            dispatcher_headerLoaded <= 1'b1;
          end
        end
        if(io_remote_cmd_payload_last)begin
          dispatcher_headerLoaded <= 1'b1;
          dispatcher_dataLoaded <= 1'b1;
          dispatcher_counter <= (3'b000);
        end
      end
      if((_zz_2 && io_mem_cmd_ready))begin
        dispatcher_headerLoaded <= 1'b0;
        dispatcher_dataLoaded <= 1'b0;
      end
    end
  end

  always @ (posedge io_mainClk) begin
    if(io_remote_cmd_valid)begin
      if(_zz_3)begin
        dispatcher_headerShifter <= ({io_remote_cmd_payload_fragment,dispatcher_headerShifter} >>> 1);
      end else begin
        dispatcher_dataShifter <= ({io_remote_cmd_payload_fragment,dispatcher_dataShifter} >>> 1);
      end
    end
  end

endmodule

module XbbRiscvSimpleBusToApbBridge (
      input   io_simpleBus_cmd_valid,
      output  io_simpleBus_cmd_ready,
      input   io_simpleBus_cmd_payload_wr,
      input  [31:0] io_simpleBus_cmd_payload_address,
      input  [31:0] io_simpleBus_cmd_payload_data,
      input  [3:0] io_simpleBus_cmd_payload_mask,
      output  io_simpleBus_rsp_valid,
      output [31:0] io_simpleBus_rsp_payload_data,
      output [19:0] io_apb_PADDR,
      output [0:0] io_apb_PSEL,
      output  io_apb_PENABLE,
      input   io_apb_PREADY,
      output  io_apb_PWRITE,
      output [31:0] io_apb_PWDATA,
      input  [31:0] io_apb_PRDATA,
      input   io_apb_PSLVERROR,
      input   io_mainClk,
      input   resetCtrl_systemReset);
  wire  _zz_10;
  wire  _zz_11;
  wire  simpleBusStage_cmd_valid;
  reg  simpleBusStage_cmd_ready;
  wire  simpleBusStage_cmd_payload_wr;
  wire [31:0] simpleBusStage_cmd_payload_address;
  wire [31:0] simpleBusStage_cmd_payload_data;
  wire [3:0] simpleBusStage_cmd_payload_mask;
  reg  simpleBusStage_rsp_valid;
  wire [31:0] simpleBusStage_rsp_payload_data;
  wire  _zz_1;
  reg  _zz_2;
  reg  _zz_3;
  reg  _zz_4;
  reg [31:0] _zz_5;
  reg [31:0] _zz_6;
  reg [3:0] _zz_7;
  reg  _zz_8;
  reg [31:0] _zz_9;
  reg  state;
  assign _zz_10 = (! _zz_2);
  assign _zz_11 = (! state);
  assign io_simpleBus_cmd_ready = _zz_3;
  assign simpleBusStage_cmd_valid = _zz_2;
  assign _zz_1 = simpleBusStage_cmd_ready;
  assign simpleBusStage_cmd_payload_wr = _zz_4;
  assign simpleBusStage_cmd_payload_address = _zz_5;
  assign simpleBusStage_cmd_payload_data = _zz_6;
  assign simpleBusStage_cmd_payload_mask = _zz_7;
  assign io_simpleBus_rsp_valid = _zz_8;
  assign io_simpleBus_rsp_payload_data = _zz_9;
  always @ (*) begin
    simpleBusStage_cmd_ready = 1'b0;
    simpleBusStage_rsp_valid = 1'b0;
    if(! _zz_11) begin
      if(io_apb_PREADY)begin
        simpleBusStage_rsp_valid = (! simpleBusStage_cmd_payload_wr);
        simpleBusStage_cmd_ready = 1'b1;
      end
    end
  end

  assign io_apb_PSEL[0] = simpleBusStage_cmd_valid;
  assign io_apb_PENABLE = state;
  assign io_apb_PWRITE = simpleBusStage_cmd_payload_wr;
  assign io_apb_PADDR = simpleBusStage_cmd_payload_address[19:0];
  assign io_apb_PWDATA = simpleBusStage_cmd_payload_data;
  assign simpleBusStage_rsp_payload_data = io_apb_PRDATA;
  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      _zz_2 <= 1'b0;
      _zz_3 <= 1'b1;
      _zz_8 <= 1'b0;
      state <= 1'b0;
    end else begin
      if(_zz_10)begin
        _zz_2 <= io_simpleBus_cmd_valid;
        _zz_3 <= (! io_simpleBus_cmd_valid);
      end else begin
        _zz_2 <= (! _zz_1);
        _zz_3 <= _zz_1;
      end
      _zz_8 <= simpleBusStage_rsp_valid;
      if(_zz_11)begin
        state <= simpleBusStage_cmd_valid;
      end else begin
        if(io_apb_PREADY)begin
          state <= 1'b0;
        end
      end
    end
  end

  always @ (posedge io_mainClk) begin
    if(_zz_10)begin
      _zz_4 <= io_simpleBus_cmd_payload_wr;
      _zz_5 <= io_simpleBus_cmd_payload_address;
      _zz_6 <= io_simpleBus_cmd_payload_data;
      _zz_7 <= io_simpleBus_cmd_payload_mask;
    end
    _zz_9 <= simpleBusStage_rsp_payload_data;
  end

endmodule

module Apb3UartCtrl (
      input  [3:0] io_apb_PADDR,
      input  [0:0] io_apb_PSEL,
      input   io_apb_PENABLE,
      output  io_apb_PREADY,
      input   io_apb_PWRITE,
      input  [31:0] io_apb_PWDATA,
      output reg [31:0] io_apb_PRDATA,
      output  io_uart_txd,
      input   io_uart_rxd,
      output  io_interrupt,
      input   io_mainClk,
      input   resetCtrl_systemReset);
  wire  _zz_5;
  reg  _zz_6;
  wire  _zz_7;
  wire  _zz_8;
  wire  _zz_9;
  wire  _zz_10;
  wire [7:0] _zz_11;
  wire  _zz_12;
  wire  _zz_13;
  wire  _zz_14;
  wire [7:0] _zz_15;
  wire [4:0] _zz_16;
  wire [4:0] _zz_17;
  wire  _zz_18;
  wire  _zz_19;
  wire [7:0] _zz_20;
  wire [4:0] _zz_21;
  wire [4:0] _zz_22;
  wire [19:0] _zz_23;
  wire [19:0] _zz_24;
  wire [0:0] _zz_25;
  wire [0:0] _zz_26;
  wire [4:0] _zz_27;
  wire  busCtrl_askWrite;
  wire  busCtrl_askRead;
  wire  busCtrl_doWrite;
  wire  busCtrl_doRead;
  reg [2:0] bridge_uartConfigReg_frame_dataLength;
  reg `UartStopType_binary_sequancial_type bridge_uartConfigReg_frame_stop;
  reg `UartParityType_binary_sequancial_type bridge_uartConfigReg_frame_parity;
  reg [19:0] bridge_uartConfigReg_clockDivider;
  reg  _zz_1;
  wire  bridge_write_streamUnbuffered_valid;
  wire  bridge_write_streamUnbuffered_ready;
  wire [7:0] bridge_write_streamUnbuffered_payload;
  reg  bridge_interruptCtrl_writeIntEnable;
  reg  bridge_interruptCtrl_readIntEnable;
  wire  bridge_interruptCtrl_readInt;
  wire  bridge_interruptCtrl_writeInt;
  wire  bridge_interruptCtrl_interrupt;
  wire [7:0] _zz_2;
  wire `UartParityType_binary_sequancial_type _zz_3;
  wire `UartStopType_binary_sequancial_type _zz_4;
  assign io_apb_PREADY = _zz_8;
  assign _zz_23 = io_apb_PWDATA[19 : 0];
  assign _zz_24 = _zz_23;
  assign _zz_25 = io_apb_PWDATA[0 : 0];
  assign _zz_26 = io_apb_PWDATA[1 : 1];
  assign _zz_27 = ((5'b10000) - _zz_16);
  UartCtrl uartCtrl_1 ( 
    .io_config_frame_dataLength(bridge_uartConfigReg_frame_dataLength),
    .io_config_frame_stop(bridge_uartConfigReg_frame_stop),
    .io_config_frame_parity(bridge_uartConfigReg_frame_parity),
    .io_config_clockDivider(bridge_uartConfigReg_clockDivider),
    .io_write_valid(_zz_14),
    .io_write_ready(_zz_9),
    .io_write_payload(_zz_15),
    .io_read_valid(_zz_10),
    .io_read_payload(_zz_11),
    .io_uart_txd(_zz_12),
    .io_uart_rxd(io_uart_rxd),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  StreamFifo_8 streamFifo_10 ( 
    .io_push_valid(bridge_write_streamUnbuffered_valid),
    .io_push_ready(_zz_13),
    .io_push_payload(bridge_write_streamUnbuffered_payload),
    .io_pop_valid(_zz_14),
    .io_pop_ready(_zz_9),
    .io_pop_payload(_zz_15),
    .io_flush(_zz_5),
    .io_occupancy(_zz_16),
    .io_availability(_zz_17),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  StreamFifo_8 streamFifo_11 ( 
    .io_push_valid(_zz_10),
    .io_push_ready(_zz_18),
    .io_push_payload(_zz_11),
    .io_pop_valid(_zz_19),
    .io_pop_ready(_zz_6),
    .io_pop_payload(_zz_20),
    .io_flush(_zz_7),
    .io_occupancy(_zz_21),
    .io_availability(_zz_22),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  assign io_uart_txd = _zz_12;
  assign _zz_8 = 1'b1;
  always @ (*) begin
    io_apb_PRDATA = (32'b00000000000000000000000000000000);
    _zz_1 = 1'b0;
    _zz_6 = 1'b0;
    case(io_apb_PADDR)
      4'b1000 : begin
      end
      4'b1100 : begin
      end
      4'b0000 : begin
        if(busCtrl_doWrite)begin
          _zz_1 = 1'b1;
        end
        if(busCtrl_doRead)begin
          _zz_6 = 1'b1;
        end
        io_apb_PRDATA[16 : 16] = _zz_19;
        io_apb_PRDATA[7 : 0] = _zz_20;
      end
      4'b0100 : begin
        io_apb_PRDATA[20 : 16] = _zz_27;
        io_apb_PRDATA[28 : 24] = _zz_21;
        io_apb_PRDATA[0 : 0] = bridge_interruptCtrl_writeIntEnable;
        io_apb_PRDATA[1 : 1] = bridge_interruptCtrl_readIntEnable;
        io_apb_PRDATA[8 : 8] = bridge_interruptCtrl_writeInt;
        io_apb_PRDATA[9 : 9] = bridge_interruptCtrl_readInt;
      end
      default : begin
      end
    endcase
  end

  assign busCtrl_askWrite = ((io_apb_PSEL[0] && io_apb_PENABLE) && io_apb_PWRITE);
  assign busCtrl_askRead = ((io_apb_PSEL[0] && io_apb_PENABLE) && (! io_apb_PWRITE));
  assign busCtrl_doWrite = (((io_apb_PSEL[0] && io_apb_PENABLE) && _zz_8) && io_apb_PWRITE);
  assign busCtrl_doRead = (((io_apb_PSEL[0] && io_apb_PENABLE) && _zz_8) && (! io_apb_PWRITE));
  assign bridge_write_streamUnbuffered_valid = _zz_1;
  assign bridge_write_streamUnbuffered_payload = _zz_2;
  assign bridge_write_streamUnbuffered_ready = _zz_13;
  assign bridge_interruptCtrl_readInt = (bridge_interruptCtrl_readIntEnable && _zz_19);
  assign bridge_interruptCtrl_writeInt = (bridge_interruptCtrl_writeIntEnable && (! _zz_14));
  assign bridge_interruptCtrl_interrupt = (bridge_interruptCtrl_readInt || bridge_interruptCtrl_writeInt);
  assign io_interrupt = bridge_interruptCtrl_interrupt;
  assign _zz_2 = io_apb_PWDATA[7 : 0];
  assign _zz_3 = io_apb_PWDATA[9 : 8];
  assign _zz_4 = io_apb_PWDATA[16 : 16];
  assign _zz_5 = 1'b0;
  assign _zz_7 = 1'b0;
  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      bridge_uartConfigReg_clockDivider <= (20'b00000000000000000000);
      bridge_uartConfigReg_clockDivider <= (20'b00000000000011011000);
      bridge_uartConfigReg_frame_dataLength <= (3'b111);
      bridge_uartConfigReg_frame_parity <= `UartParityType_binary_sequancial_NONE;
      bridge_uartConfigReg_frame_stop <= `UartStopType_binary_sequancial_ONE;
      bridge_interruptCtrl_writeIntEnable <= 1'b0;
      bridge_interruptCtrl_readIntEnable <= 1'b0;
    end else begin
      case(io_apb_PADDR)
        4'b1000 : begin
          if(busCtrl_doWrite)begin
            bridge_uartConfigReg_clockDivider[19 : 0] <= _zz_24;
          end
        end
        4'b1100 : begin
          if(busCtrl_doWrite)begin
            bridge_uartConfigReg_frame_dataLength <= io_apb_PWDATA[2 : 0];
            bridge_uartConfigReg_frame_parity <= _zz_3;
            bridge_uartConfigReg_frame_stop <= _zz_4;
          end
        end
        4'b0000 : begin
        end
        4'b0100 : begin
          if(busCtrl_doWrite)begin
            bridge_interruptCtrl_writeIntEnable <= _zz_25[0];
            bridge_interruptCtrl_readIntEnable <= _zz_26[0];
          end
        end
        default : begin
        end
      endcase
    end
  end

endmodule

module Apb3Decoder (
      input  [19:0] io_input_PADDR,
      input  [0:0] io_input_PSEL,
      input   io_input_PENABLE,
      output  io_input_PREADY,
      input   io_input_PWRITE,
      input  [31:0] io_input_PWDATA,
      output [31:0] io_input_PRDATA,
      output  io_input_PSLVERROR,
      output [19:0] io_output_PADDR,
      output [0:0] io_output_PSEL,
      output  io_output_PENABLE,
      input   io_output_PREADY,
      output  io_output_PWRITE,
      output [31:0] io_output_PWDATA,
      input  [31:0] io_output_PRDATA,
      input   io_output_PSLVERROR);
  wire [19:0] _zz_1;
  assign _zz_1 = (20'b11111111000000000000);
  assign io_output_PADDR = io_input_PADDR;
  assign io_output_PENABLE = io_input_PENABLE;
  assign io_output_PWRITE = io_input_PWRITE;
  assign io_output_PWDATA = io_input_PWDATA;
  assign io_output_PSEL[0] = (((io_input_PADDR & _zz_1) == (20'b00000000000000000000)) && io_input_PSEL[0]);
  assign io_input_PREADY = io_output_PREADY;
  assign io_input_PRDATA = io_output_PRDATA;
  assign io_input_PSLVERROR = io_output_PSLVERROR;
endmodule

module Apb3Router (
      input  [19:0] io_input_PADDR,
      input  [0:0] io_input_PSEL,
      input   io_input_PENABLE,
      output  io_input_PREADY,
      input   io_input_PWRITE,
      input  [31:0] io_input_PWDATA,
      output [31:0] io_input_PRDATA,
      output  io_input_PSLVERROR,
      output [19:0] io_outputs_0_PADDR,
      output [0:0] io_outputs_0_PSEL,
      output  io_outputs_0_PENABLE,
      input   io_outputs_0_PREADY,
      output  io_outputs_0_PWRITE,
      output [31:0] io_outputs_0_PWDATA,
      input  [31:0] io_outputs_0_PRDATA,
      input   io_outputs_0_PSLVERROR,
      input   io_mainClk,
      input   resetCtrl_systemReset);
  assign io_outputs_0_PADDR = io_input_PADDR;
  assign io_outputs_0_PENABLE = io_input_PENABLE;
  assign io_outputs_0_PSEL[0] = io_input_PSEL[0];
  assign io_outputs_0_PWRITE = io_input_PWRITE;
  assign io_outputs_0_PWDATA = io_input_PWDATA;
  assign io_input_PREADY = io_outputs_0_PREADY;
  assign io_input_PRDATA = io_outputs_0_PRDATA;
  assign io_input_PSLVERROR = io_outputs_0_PSLVERROR;
endmodule

module DBus2Simple (
      input   io_dbus_cmd_valid,
      output  io_dbus_cmd_ready,
      input   io_dbus_cmd_payload_wr,
      input  [31:0] io_dbus_cmd_payload_address,
      input  [31:0] io_dbus_cmd_payload_data,
      input  [1:0] io_dbus_cmd_payload_size,
      output  io_dbus_rsp_ready,
      output  io_dbus_rsp_error,
      output [31:0] io_dbus_rsp_data,
      output  io_bus_cmd_valid,
      input   io_bus_cmd_ready,
      output  io_bus_cmd_payload_wr,
      output [31:0] io_bus_cmd_payload_address,
      output [31:0] io_bus_cmd_payload_data,
      output [3:0] io_bus_cmd_payload_mask,
      input   io_bus_rsp_valid,
      input  [31:0] io_bus_rsp_payload_data);
  reg [3:0] _zz_1;
  assign io_bus_cmd_valid = io_dbus_cmd_valid;
  assign io_bus_cmd_payload_wr = io_dbus_cmd_payload_wr;
  assign io_bus_cmd_payload_address = io_dbus_cmd_payload_address;
  assign io_bus_cmd_payload_data = io_dbus_cmd_payload_data;
  always @ (*) begin
    case(io_dbus_cmd_payload_size)
      2'b00 : begin
        _zz_1 = (4'b0001);
      end
      2'b01 : begin
        _zz_1 = (4'b0011);
      end
      default : begin
        _zz_1 = (4'b1111);
      end
    endcase
  end

  assign io_bus_cmd_payload_mask = (_zz_1 <<< io_dbus_cmd_payload_address[1 : 0]);
  assign io_dbus_cmd_ready = io_bus_cmd_ready;
  assign io_dbus_rsp_ready = io_bus_rsp_valid;
  assign io_dbus_rsp_data = io_bus_rsp_payload_data;
  assign io_dbus_rsp_error = 1'b0;
endmodule

module XbbRiscv (
      input   io_asyncReset,
      input   io_mainClk,
      output  iBus_cmd_valid,
      input   iBus_cmd_ready,
      output [31:0] iBus_cmd_payload_pc,
      input   iBus_rsp_ready,
      input   iBus_rsp_error,
      input  [31:0] iBus_rsp_inst,
      input  [5:0] io_externalInterrupt,
      input   jtag_tms,
      input   jtag_tdi,
      output  jtag_tdo,
      input   jtag_tck,
      output  io_uart_txd,
      input   io_uart_rxd,
      output reg  scalarMemBus_cmd_valid,
      input   scalarMemBus_cmd_ready,
      output  scalarMemBus_cmd_payload_wr,
      output [31:0] scalarMemBus_cmd_payload_address,
      output [31:0] scalarMemBus_cmd_payload_data,
      output [3:0] scalarMemBus_cmd_payload_mask,
      input   scalarMemBus_rsp_valid,
      input  [31:0] scalarMemBus_rsp_payload_data,
      output reg  io_vmemBus_cmd_valid,
      input   io_vmemBus_cmd_ready,
      output  io_vmemBus_cmd_payload_wr,
      output [31:0] io_vmemBus_cmd_payload_address,
      output [31:0] io_vmemBus_cmd_payload_data,
      output [3:0] io_vmemBus_cmd_payload_mask,
      input   io_vmemBus_rsp_valid,
      input  [31:0] io_vmemBus_rsp_payload_data,
      output  xbaseband_cmd_valid,
      input   xbaseband_cmd_ready,
      output [31:0] xbaseband_cmd_payload_instruction,
      output [31:0] xbaseband_cmd_payload_rs1,
      output  dma_0_dmaReset,
      input  [31:0] dma_0_status,
      output  dma_0_interrupt_clear,
      output  dma_0_config_valid,
      input   dma_0_config_ready,
      output [31:0] dma_0_config_payload_startAddr,
      output [31:0] dma_0_config_payload_length,
      output [31:0] dma_0_config_payload_timerInit,
      output [31:0] dma_0_config_payload_slicer,
      output  dma_0_config_payload_reverse,
      output  dma_0_config_payload_last_or_run_till_last,
      output [3:0] dma_0_config_payload_demapper_constellation,
      output [15:0] dma_0_config_payload_demapper_two_over_sigma_sq,
      output  dma_1_dmaReset,
      input  [31:0] dma_1_status,
      output  dma_1_interrupt_clear,
      output  dma_1_config_valid,
      input   dma_1_config_ready,
      output [31:0] dma_1_config_payload_startAddr,
      output [31:0] dma_1_config_payload_length,
      output [31:0] dma_1_config_payload_timerInit,
      output [31:0] dma_1_config_payload_slicer,
      output  dma_1_config_payload_reverse,
      output  dma_1_config_payload_last_or_run_till_last,
      output [3:0] dma_1_config_payload_demapper_constellation,
      output [15:0] dma_1_config_payload_demapper_two_over_sigma_sq,
      output  dma_2_dmaReset,
      input  [31:0] dma_2_status,
      output  dma_2_interrupt_clear,
      output  dma_2_config_valid,
      input   dma_2_config_ready,
      output [31:0] dma_2_config_payload_startAddr,
      output [31:0] dma_2_config_payload_length,
      output [31:0] dma_2_config_payload_timerInit,
      output [31:0] dma_2_config_payload_slicer,
      output  dma_2_config_payload_reverse,
      output  dma_2_config_payload_last_or_run_till_last,
      output [3:0] dma_2_config_payload_demapper_constellation,
      output [15:0] dma_2_config_payload_demapper_two_over_sigma_sq,
      output [1023:0] mapmov_mover_active,
      output [31:0] mapmov_trim_start,
      output [31:0] mapmov_trim_end,
      output [9:0] mapmov_pilot_ram_addr,
      output [31:0] mapmov_pilot_ram_wdata,
      output  mapmov_pilot_ram_we,
      output  mapmov_reset,
      output [15:0] mapmov_one_value,
      output [15:0] mapmov_zero_value,
      output [31:0] io_timerStatus_gtimer,
      output  ringbus_0_interrupt_clear,
      output  ringbus_0_config_valid,
      input   ringbus_0_config_ready,
      output [31:0] ringbus_0_config_payload_write_data,
      output [31:0] ringbus_0_config_payload_write_addr,
      input   ringbus_0_read_valid,
      output  ringbus_0_read_ready,
      input  [31:0] ringbus_0_read_payload_read_data,
      input   ringbus_0_write_done,
      output  ringbus_1_interrupt_clear,
      output  ringbus_1_config_valid,
      input   ringbus_1_config_ready,
      output [31:0] ringbus_1_config_payload_write_data,
      output [31:0] ringbus_1_config_payload_write_addr,
      input   ringbus_1_read_valid,
      output  ringbus_1_read_ready,
      input  [31:0] ringbus_1_read_payload_read_data,
      input   ringbus_1_write_done,
      output  nco_ncoReset,
      input   nco_busy,
      output  nco_config_valid,
      input   nco_config_ready,
      output [31:0] nco_config_payload_startAngle,
      output [31:0] nco_config_payload_length,
      output [31:0] nco_config_payload_delta,
      output [31:0] slicer_value,
      input   satDetect_satDetect,
      input  [31:0] status_status,
      output [31:0] control_control,
      output  dengine_reset,
      output [31:0] dengine_func0MinThreshold,
      output [31:0] dengine_func0MaxThreshold,
      output [31:0] dengine_func1MinThreshold,
      output [31:0] dengine_func1MaxThreshold,
      inout [31:0] io_gpio);
  wire [7:0] _zz_68;
  reg  _zz_69;
  wire [3:0] _zz_70;
  wire  _zz_71;
  reg [31:0] _zz_72;
  wire  _zz_73;
  wire  _zz_74;
  wire [31:0] _zz_75;
  wire [31:0] _zz_76;
  wire [31:0] _zz_77;
  wire [31:0] _zz_78;
  wire  _zz_79;
  wire  _zz_80;
  wire [3:0] _zz_81;
  wire [15:0] _zz_82;
  wire  _zz_83;
  wire  _zz_84;
  wire  _zz_85;
  wire [31:0] _zz_86;
  wire [31:0] _zz_87;
  wire [31:0] _zz_88;
  wire [31:0] _zz_89;
  wire  _zz_90;
  wire  _zz_91;
  wire [3:0] _zz_92;
  wire [15:0] _zz_93;
  wire  _zz_94;
  wire  _zz_95;
  wire  _zz_96;
  wire [31:0] _zz_97;
  wire [31:0] _zz_98;
  wire [31:0] _zz_99;
  wire [31:0] _zz_100;
  wire  _zz_101;
  wire  _zz_102;
  wire [3:0] _zz_103;
  wire [15:0] _zz_104;
  wire  _zz_105;
  wire  _zz_106;
  wire [1023:0] _zz_107;
  wire [31:0] _zz_108;
  wire [31:0] _zz_109;
  wire [9:0] _zz_110;
  wire [31:0] _zz_111;
  wire  _zz_112;
  wire  _zz_113;
  wire [15:0] _zz_114;
  wire [15:0] _zz_115;
  wire [31:0] _zz_116;
  wire  _zz_117;
  wire  _zz_118;
  wire [31:0] _zz_119;
  wire [31:0] _zz_120;
  wire  _zz_121;
  wire [31:0] _zz_122;
  wire [31:0] _zz_123;
  wire  _zz_124;
  wire  _zz_125;
  wire [31:0] _zz_126;
  wire [31:0] _zz_127;
  wire  _zz_128;
  wire  _zz_129;
  wire [31:0] _zz_130;
  wire [31:0] _zz_131;
  wire [31:0] _zz_132;
  wire  _zz_133;
  wire [31:0] _zz_134;
  wire [31:0] _zz_135;
  wire  _zz_136;
  wire [31:0] _zz_137;
  wire [31:0] _zz_138;
  wire [31:0] _zz_139;
  wire [31:0] _zz_140;
  wire  _zz_141;
  wire [31:0] _zz_142;
  wire  _zz_143;
  wire  _zz_144;
  wire [31:0] _zz_145;
  wire  _zz_146;
  wire  _zz_147;
  wire [31:0] _zz_148;
  wire [31:0] _zz_149;
  wire [1:0] _zz_150;
  wire  _zz_151;
  wire [31:0] _zz_152;
  wire [31:0] _zz_153;
  wire  _zz_154;
  wire  _zz_155;
  wire  _zz_156;
  wire [0:0] _zz_157;
  wire  _zz_158;
  wire  _zz_159;
  wire  _zz_160;
  wire  _zz_161;
  wire [31:0] _zz_162;
  wire  _zz_163;
  wire [31:0] _zz_164;
  wire [31:0] _zz_165;
  wire  _zz_166;
  wire [1:0] _zz_167;
  wire  _zz_168;
  wire  _zz_169;
  wire [31:0] _zz_170;
  wire [19:0] _zz_171;
  wire [0:0] _zz_172;
  wire  _zz_173;
  wire  _zz_174;
  wire [31:0] _zz_175;
  wire  _zz_176;
  wire [31:0] _zz_177;
  wire  _zz_178;
  wire  _zz_179;
  wire  _zz_180;
  wire [31:0] _zz_181;
  wire  _zz_182;
  wire [19:0] _zz_183;
  wire [0:0] _zz_184;
  wire  _zz_185;
  wire  _zz_186;
  wire [31:0] _zz_187;
  wire  _zz_188;
  wire [31:0] _zz_189;
  wire  _zz_190;
  wire [19:0] _zz_191;
  wire [0:0] _zz_192;
  wire  _zz_193;
  wire  _zz_194;
  wire [31:0] _zz_195;
  wire  _zz_196;
  wire  _zz_197;
  wire  _zz_198;
  wire [31:0] _zz_199;
  wire  _zz_200;
  wire  _zz_201;
  wire [31:0] _zz_202;
  wire [31:0] _zz_203;
  wire [3:0] _zz_204;
  wire  _zz_205;
  wire  _zz_206;
  wire [31:0] _zz_207;
  wire [31:0] _zz_208;
  reg  _zz_1;
  reg  _zz_2;
  reg  _zz_3;
  reg  _zz_4;
  reg  _zz_5;
  reg  _zz_6;
  reg  _zz_7;
  reg  _zz_8;
  reg  _zz_9;
  reg  _zz_10;
  reg  _zz_11;
  reg  _zz_12;
  reg  _zz_13;
  reg  _zz_14;
  reg  _zz_15;
  reg  _zz_16;
  reg  _zz_17;
  reg  _zz_18;
  reg  _zz_19;
  reg  _zz_20;
  reg  _zz_21;
  reg  _zz_22;
  reg  _zz_23;
  reg  _zz_24;
  reg  _zz_25;
  reg  _zz_26;
  reg  _zz_27;
  reg  _zz_28;
  reg  _zz_29;
  reg  _zz_30;
  reg  _zz_31;
  reg  _zz_32;
  wire [31:0] _zz_33;
  wire [31:0] _zz_34;
  wire [31:0] _zz_35;
  reg  resetCtrl_mainClkResetUnbuffered;
  reg [5:0] resetCtrl_systemClkResetCounter = (6'b000000);
  wire [5:0] _zz_36;
  reg  resetCtrl_mainClkReset;
  reg  resetCtrl_systemReset;
  wire  system_dBus_cmd_valid;
  wire  system_dBus_cmd_ready;
  wire  system_dBus_cmd_payload_wr;
  wire [31:0] system_dBus_cmd_payload_address;
  wire [31:0] system_dBus_cmd_payload_data;
  wire [1:0] system_dBus_cmd_payload_size;
  wire  system_dBus_rsp_ready;
  wire  system_dBus_rsp_error;
  wire [31:0] system_dBus_rsp_data;
  wire  system_sbus_cmd_valid;
  wire  system_sbus_cmd_ready;
  wire  system_sbus_cmd_payload_wr;
  wire [31:0] system_sbus_cmd_payload_address;
  wire [31:0] system_sbus_cmd_payload_data;
  wire [3:0] system_sbus_cmd_payload_mask;
  wire  system_sbus_rsp_valid;
  wire [31:0] system_sbus_rsp_payload_data;
  wire  system_timerInterrupt;
  wire [5:0] system_externalInterrupt;
  wire  _zz_37;
  reg  _zz_38;
  reg  _zz_39;
  reg  _zz_40;
  reg [31:0] _zz_41;
  reg [31:0] _zz_42;
  reg [1:0] _zz_43;
  reg  _zz_44;
  reg  _zz_45;
  wire  _zz_46;
  wire  _zz_47;
  reg  _zz_48;
  wire  _zz_49;
  wire [31:0] _zz_50;
  wire [31:0] _zz_51;
  wire [3:0] _zz_52;
  wire  _zz_53;
  wire [31:0] _zz_54;
  wire  _zz_55;
  reg  _zz_56;
  reg  _zz_57;
  reg [31:0] _zz_58;
  reg [31:0] _zz_59;
  reg [3:0] _zz_60;
  wire  _zz_61;
  wire  _zz_62;
  wire  _zz_63;
  wire  _zz_64;
  reg  _zz_65;
  reg  _zz_66;
  reg [1:0] _zz_67;
  assign _zz_205 = (resetCtrl_systemClkResetCounter != _zz_36);
  assign _zz_206 = (! _zz_38);
  assign _zz_207 = (32'b11111111111111000000000000000000);
  assign _zz_208 = (32'b11111111111100000000000000000000);
  BufferCC_2 bufferCC_3 ( 
    .io_dataIn(io_asyncReset),
    .io_dataOut(_zz_73),
    .io_mainClk(io_mainClk) 
  );
  VexRiscv system_cpu ( 
    .timerInterrupt(system_timerInterrupt),
    .externalInterrupt(io_externalInterrupt),
    .dma_0_config_valid(_zz_74),
    .dma_0_config_ready(dma_0_config_ready),
    .dma_0_config_payload_startAddr(_zz_75),
    .dma_0_config_payload_length(_zz_76),
    .dma_0_config_payload_timerInit(_zz_77),
    .dma_0_config_payload_slicer(_zz_78),
    .dma_0_config_payload_reverse(_zz_79),
    .dma_0_config_payload_last_or_run_till_last(_zz_80),
    .dma_0_config_payload_demapper_constellation(_zz_81),
    .dma_0_config_payload_demapper_two_over_sigma_sq(_zz_82),
    .dma_0_status(dma_0_status),
    .dma_0_interrupt_clear(_zz_83),
    .dma_0_dmaReset(_zz_84),
    .dma_1_config_valid(_zz_85),
    .dma_1_config_ready(dma_1_config_ready),
    .dma_1_config_payload_startAddr(_zz_86),
    .dma_1_config_payload_length(_zz_87),
    .dma_1_config_payload_timerInit(_zz_88),
    .dma_1_config_payload_slicer(_zz_89),
    .dma_1_config_payload_reverse(_zz_90),
    .dma_1_config_payload_last_or_run_till_last(_zz_91),
    .dma_1_config_payload_demapper_constellation(_zz_92),
    .dma_1_config_payload_demapper_two_over_sigma_sq(_zz_93),
    .dma_1_status(dma_1_status),
    .dma_1_interrupt_clear(_zz_94),
    .dma_1_dmaReset(_zz_95),
    .dma_2_config_valid(_zz_96),
    .dma_2_config_ready(dma_2_config_ready),
    .dma_2_config_payload_startAddr(_zz_97),
    .dma_2_config_payload_length(_zz_98),
    .dma_2_config_payload_timerInit(_zz_99),
    .dma_2_config_payload_slicer(_zz_100),
    .dma_2_config_payload_reverse(_zz_101),
    .dma_2_config_payload_last_or_run_till_last(_zz_102),
    .dma_2_config_payload_demapper_constellation(_zz_103),
    .dma_2_config_payload_demapper_two_over_sigma_sq(_zz_104),
    .dma_2_status(dma_2_status),
    .dma_2_interrupt_clear(_zz_105),
    .dma_2_dmaReset(_zz_106),
    .mapmovCsr_mover_active(_zz_107),
    .mapmovCsr_trim_start(_zz_108),
    .mapmovCsr_trim_end(_zz_109),
    .mapmovCsr_pilot_ram_addr(_zz_110),
    .mapmovCsr_pilot_ram_wdata(_zz_111),
    .mapmovCsr_pilot_ram_we(_zz_112),
    .mapmovCsr_reset(_zz_113),
    .mapmovCsr_one_value(_zz_114),
    .mapmovCsr_zero_value(_zz_115),
    .timerCsr_gtimer(_zz_116),
    .ringbus_0_interrupt_clear(_zz_117),
    .ringbus_0_config_valid(_zz_118),
    .ringbus_0_config_ready(ringbus_0_config_ready),
    .ringbus_0_config_payload_write_data(_zz_119),
    .ringbus_0_config_payload_write_addr(_zz_120),
    .ringbus_0_read_valid(ringbus_0_read_valid),
    .ringbus_0_read_ready(_zz_121),
    .ringbus_0_read_payload_read_data(ringbus_0_read_payload_read_data),
    .ringbus_0_write_done(ringbus_0_write_done),
    .gpio_read(_zz_33),
    .gpio_write(_zz_122),
    .gpio_writeEnable(_zz_123),
    .ringbus_1_interrupt_clear(_zz_124),
    .ringbus_1_config_valid(_zz_125),
    .ringbus_1_config_ready(ringbus_1_config_ready),
    .ringbus_1_config_payload_write_data(_zz_126),
    .ringbus_1_config_payload_write_addr(_zz_127),
    .ringbus_1_read_valid(ringbus_1_read_valid),
    .ringbus_1_read_ready(_zz_128),
    .ringbus_1_read_payload_read_data(ringbus_1_read_payload_read_data),
    .ringbus_1_write_done(ringbus_1_write_done),
    .nco_0_config_valid(_zz_129),
    .nco_0_config_ready(nco_config_ready),
    .nco_0_config_payload_startAngle(_zz_130),
    .nco_0_config_payload_length(_zz_131),
    .nco_0_config_payload_delta(_zz_132),
    .nco_0_busy(nco_busy),
    .nco_0_ncoReset(_zz_133),
    .slicer_value(_zz_134),
    ._zz_104(satDetect_satDetect),
    .status_status(status_status),
    .control_control(_zz_135),
    .dengine_reset(_zz_136),
    .dengine_func0MinThreshold(_zz_137),
    .dengine_func0MaxThreshold(_zz_138),
    .dengine_func1MinThreshold(_zz_139),
    .dengine_func1MaxThreshold(_zz_140),
    .debug_bus_cmd_valid(_zz_163),
    .debug_bus_cmd_ready(_zz_141),
    .debug_bus_cmd_payload_wr(_zz_166),
    .debug_bus_cmd_payload_address(_zz_68),
    .debug_bus_cmd_payload_data(_zz_165),
    .debug_bus_rsp_data(_zz_142),
    .debug_resetOut(_zz_143),
    .iBus_cmd_valid(_zz_144),
    .iBus_cmd_ready(iBus_cmd_ready),
    .iBus_cmd_payload_pc(_zz_145),
    .iBus_rsp_ready(iBus_rsp_ready),
    .iBus_rsp_error(iBus_rsp_error),
    .iBus_rsp_inst(iBus_rsp_inst),
    .dBus_cmd_valid(_zz_146),
    .dBus_cmd_ready(_zz_39),
    .dBus_cmd_payload_wr(_zz_147),
    .dBus_cmd_payload_address(_zz_148),
    .dBus_cmd_payload_data(_zz_149),
    .dBus_cmd_payload_size(_zz_150),
    .dBus_rsp_ready(system_dBus_rsp_ready),
    .dBus_rsp_error(system_dBus_rsp_error),
    .dBus_rsp_data(system_dBus_rsp_data),
    .xbaseband_cmd_valid(_zz_151),
    .xbaseband_cmd_ready(xbaseband_cmd_ready),
    .xbaseband_cmd_payload_instruction(_zz_152),
    .xbaseband_cmd_payload_rs1(_zz_153),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset),
    .resetCtrl_mainClkReset(resetCtrl_mainClkReset) 
  );
  JtagBridge jtagBridge_1 ( 
    .io_jtag_tms(jtag_tms),
    .io_jtag_tdi(jtag_tdi),
    .io_jtag_tdo(_zz_154),
    .io_jtag_tck(jtag_tck),
    .io_remote_cmd_valid(_zz_155),
    .io_remote_cmd_ready(_zz_159),
    .io_remote_cmd_payload_last(_zz_156),
    .io_remote_cmd_payload_fragment(_zz_157),
    .io_remote_rsp_valid(_zz_160),
    .io_remote_rsp_ready(_zz_158),
    .io_remote_rsp_payload_error(_zz_161),
    .io_remote_rsp_payload_data(_zz_162),
    .io_mainClk(io_mainClk),
    .resetCtrl_mainClkReset(resetCtrl_mainClkReset) 
  );
  SystemDebugger systemDebugger_1 ( 
    .io_remote_cmd_valid(_zz_155),
    .io_remote_cmd_ready(_zz_159),
    .io_remote_cmd_payload_last(_zz_156),
    .io_remote_cmd_payload_fragment(_zz_157),
    .io_remote_rsp_valid(_zz_160),
    .io_remote_rsp_ready(_zz_158),
    .io_remote_rsp_payload_error(_zz_161),
    .io_remote_rsp_payload_data(_zz_162),
    .io_mem_cmd_valid(_zz_163),
    .io_mem_cmd_ready(_zz_141),
    .io_mem_cmd_payload_address(_zz_164),
    .io_mem_cmd_payload_data(_zz_165),
    .io_mem_cmd_payload_wr(_zz_166),
    .io_mem_cmd_payload_size(_zz_167),
    .io_mem_rsp_valid(_zz_45),
    .io_mem_rsp_payload(_zz_142),
    .io_mainClk(io_mainClk),
    .resetCtrl_mainClkReset(resetCtrl_mainClkReset) 
  );
  XbbRiscvSimpleBusToApbBridge system_apbBridge ( 
    .io_simpleBus_cmd_valid(_zz_69),
    .io_simpleBus_cmd_ready(_zz_168),
    .io_simpleBus_cmd_payload_wr(_zz_49),
    .io_simpleBus_cmd_payload_address(_zz_50),
    .io_simpleBus_cmd_payload_data(_zz_51),
    .io_simpleBus_cmd_payload_mask(_zz_52),
    .io_simpleBus_rsp_valid(_zz_169),
    .io_simpleBus_rsp_payload_data(_zz_170),
    .io_apb_PADDR(_zz_171),
    .io_apb_PSEL(_zz_172),
    .io_apb_PENABLE(_zz_173),
    .io_apb_PREADY(_zz_180),
    .io_apb_PWRITE(_zz_174),
    .io_apb_PWDATA(_zz_175),
    .io_apb_PRDATA(_zz_181),
    .io_apb_PSLVERROR(_zz_182),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  Apb3UartCtrl system_uartCtrl ( 
    .io_apb_PADDR(_zz_70),
    .io_apb_PSEL(_zz_192),
    .io_apb_PENABLE(_zz_193),
    .io_apb_PREADY(_zz_176),
    .io_apb_PWRITE(_zz_194),
    .io_apb_PWDATA(_zz_195),
    .io_apb_PRDATA(_zz_177),
    .io_uart_txd(_zz_178),
    .io_uart_rxd(io_uart_rxd),
    .io_interrupt(_zz_179),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  Apb3Decoder io_apb_decoder ( 
    .io_input_PADDR(_zz_171),
    .io_input_PSEL(_zz_172),
    .io_input_PENABLE(_zz_173),
    .io_input_PREADY(_zz_180),
    .io_input_PWRITE(_zz_174),
    .io_input_PWDATA(_zz_175),
    .io_input_PRDATA(_zz_181),
    .io_input_PSLVERROR(_zz_182),
    .io_output_PADDR(_zz_183),
    .io_output_PSEL(_zz_184),
    .io_output_PENABLE(_zz_185),
    .io_output_PREADY(_zz_188),
    .io_output_PWRITE(_zz_186),
    .io_output_PWDATA(_zz_187),
    .io_output_PRDATA(_zz_189),
    .io_output_PSLVERROR(_zz_190) 
  );
  Apb3Router apb3Router_1 ( 
    .io_input_PADDR(_zz_183),
    .io_input_PSEL(_zz_184),
    .io_input_PENABLE(_zz_185),
    .io_input_PREADY(_zz_188),
    .io_input_PWRITE(_zz_186),
    .io_input_PWDATA(_zz_187),
    .io_input_PRDATA(_zz_189),
    .io_input_PSLVERROR(_zz_190),
    .io_outputs_0_PADDR(_zz_191),
    .io_outputs_0_PSEL(_zz_192),
    .io_outputs_0_PENABLE(_zz_193),
    .io_outputs_0_PREADY(_zz_176),
    .io_outputs_0_PWRITE(_zz_194),
    .io_outputs_0_PWDATA(_zz_195),
    .io_outputs_0_PRDATA(_zz_177),
    .io_outputs_0_PSLVERROR(_zz_71),
    .io_mainClk(io_mainClk),
    .resetCtrl_systemReset(resetCtrl_systemReset) 
  );
  DBus2Simple dBus2Simple_1 ( 
    .io_dbus_cmd_valid(system_dBus_cmd_valid),
    .io_dbus_cmd_ready(_zz_196),
    .io_dbus_cmd_payload_wr(system_dBus_cmd_payload_wr),
    .io_dbus_cmd_payload_address(system_dBus_cmd_payload_address),
    .io_dbus_cmd_payload_data(system_dBus_cmd_payload_data),
    .io_dbus_cmd_payload_size(system_dBus_cmd_payload_size),
    .io_dbus_rsp_ready(_zz_197),
    .io_dbus_rsp_error(_zz_198),
    .io_dbus_rsp_data(_zz_199),
    .io_bus_cmd_valid(_zz_200),
    .io_bus_cmd_ready(_zz_46),
    .io_bus_cmd_payload_wr(_zz_201),
    .io_bus_cmd_payload_address(_zz_202),
    .io_bus_cmd_payload_data(_zz_203),
    .io_bus_cmd_payload_mask(_zz_204),
    .io_bus_rsp_valid(_zz_53),
    .io_bus_rsp_payload_data(_zz_54) 
  );
  assign io_gpio[0] = _zz_32 ? _zz_34[0] : 1'bz;
  assign io_gpio[1] = _zz_31 ? _zz_34[1] : 1'bz;
  assign io_gpio[2] = _zz_30 ? _zz_34[2] : 1'bz;
  assign io_gpio[3] = _zz_29 ? _zz_34[3] : 1'bz;
  assign io_gpio[4] = _zz_28 ? _zz_34[4] : 1'bz;
  assign io_gpio[5] = _zz_27 ? _zz_34[5] : 1'bz;
  assign io_gpio[6] = _zz_26 ? _zz_34[6] : 1'bz;
  assign io_gpio[7] = _zz_25 ? _zz_34[7] : 1'bz;
  assign io_gpio[8] = _zz_24 ? _zz_34[8] : 1'bz;
  assign io_gpio[9] = _zz_23 ? _zz_34[9] : 1'bz;
  assign io_gpio[10] = _zz_22 ? _zz_34[10] : 1'bz;
  assign io_gpio[11] = _zz_21 ? _zz_34[11] : 1'bz;
  assign io_gpio[12] = _zz_20 ? _zz_34[12] : 1'bz;
  assign io_gpio[13] = _zz_19 ? _zz_34[13] : 1'bz;
  assign io_gpio[14] = _zz_18 ? _zz_34[14] : 1'bz;
  assign io_gpio[15] = _zz_17 ? _zz_34[15] : 1'bz;
  assign io_gpio[16] = _zz_16 ? _zz_34[16] : 1'bz;
  assign io_gpio[17] = _zz_15 ? _zz_34[17] : 1'bz;
  assign io_gpio[18] = _zz_14 ? _zz_34[18] : 1'bz;
  assign io_gpio[19] = _zz_13 ? _zz_34[19] : 1'bz;
  assign io_gpio[20] = _zz_12 ? _zz_34[20] : 1'bz;
  assign io_gpio[21] = _zz_11 ? _zz_34[21] : 1'bz;
  assign io_gpio[22] = _zz_10 ? _zz_34[22] : 1'bz;
  assign io_gpio[23] = _zz_9 ? _zz_34[23] : 1'bz;
  assign io_gpio[24] = _zz_8 ? _zz_34[24] : 1'bz;
  assign io_gpio[25] = _zz_7 ? _zz_34[25] : 1'bz;
  assign io_gpio[26] = _zz_6 ? _zz_34[26] : 1'bz;
  assign io_gpio[27] = _zz_5 ? _zz_34[27] : 1'bz;
  assign io_gpio[28] = _zz_4 ? _zz_34[28] : 1'bz;
  assign io_gpio[29] = _zz_3 ? _zz_34[29] : 1'bz;
  assign io_gpio[30] = _zz_2 ? _zz_34[30] : 1'bz;
  assign io_gpio[31] = _zz_1 ? _zz_34[31] : 1'bz;
  always @(*) begin
    case(_zz_67)
      2'b00 : begin
        _zz_72 = scalarMemBus_rsp_payload_data;
      end
      2'b01 : begin
        _zz_72 = io_vmemBus_rsp_payload_data;
      end
      default : begin
        _zz_72 = _zz_170;
      end
    endcase
  end

  always @ (*) begin
    _zz_1 = 1'b0;
    if(_zz_35[31])begin
      _zz_1 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_2 = 1'b0;
    if(_zz_35[30])begin
      _zz_2 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_3 = 1'b0;
    if(_zz_35[29])begin
      _zz_3 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_4 = 1'b0;
    if(_zz_35[28])begin
      _zz_4 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_5 = 1'b0;
    if(_zz_35[27])begin
      _zz_5 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_6 = 1'b0;
    if(_zz_35[26])begin
      _zz_6 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_7 = 1'b0;
    if(_zz_35[25])begin
      _zz_7 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_8 = 1'b0;
    if(_zz_35[24])begin
      _zz_8 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_9 = 1'b0;
    if(_zz_35[23])begin
      _zz_9 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_10 = 1'b0;
    if(_zz_35[22])begin
      _zz_10 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_11 = 1'b0;
    if(_zz_35[21])begin
      _zz_11 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_12 = 1'b0;
    if(_zz_35[20])begin
      _zz_12 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_13 = 1'b0;
    if(_zz_35[19])begin
      _zz_13 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_14 = 1'b0;
    if(_zz_35[18])begin
      _zz_14 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_15 = 1'b0;
    if(_zz_35[17])begin
      _zz_15 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_16 = 1'b0;
    if(_zz_35[16])begin
      _zz_16 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_17 = 1'b0;
    if(_zz_35[15])begin
      _zz_17 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_18 = 1'b0;
    if(_zz_35[14])begin
      _zz_18 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_19 = 1'b0;
    if(_zz_35[13])begin
      _zz_19 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_20 = 1'b0;
    if(_zz_35[12])begin
      _zz_20 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_21 = 1'b0;
    if(_zz_35[11])begin
      _zz_21 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_22 = 1'b0;
    if(_zz_35[10])begin
      _zz_22 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_23 = 1'b0;
    if(_zz_35[9])begin
      _zz_23 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_24 = 1'b0;
    if(_zz_35[8])begin
      _zz_24 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_25 = 1'b0;
    if(_zz_35[7])begin
      _zz_25 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_26 = 1'b0;
    if(_zz_35[6])begin
      _zz_26 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_27 = 1'b0;
    if(_zz_35[5])begin
      _zz_27 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_28 = 1'b0;
    if(_zz_35[4])begin
      _zz_28 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_29 = 1'b0;
    if(_zz_35[3])begin
      _zz_29 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_30 = 1'b0;
    if(_zz_35[2])begin
      _zz_30 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_31 = 1'b0;
    if(_zz_35[1])begin
      _zz_31 = 1'b1;
    end
  end

  always @ (*) begin
    _zz_32 = 1'b0;
    if(_zz_35[0])begin
      _zz_32 = 1'b1;
    end
  end

  always @ (*) begin
    resetCtrl_mainClkResetUnbuffered = 1'b0;
    if(_zz_205)begin
      resetCtrl_mainClkResetUnbuffered = 1'b1;
    end
  end

  assign _zz_36[5 : 0] = (6'b111111);
  assign system_timerInterrupt = 1'b0;
  assign iBus_cmd_valid = _zz_144;
  assign iBus_cmd_payload_pc = _zz_145;
  assign system_dBus_cmd_valid = _zz_38;
  assign _zz_37 = system_dBus_cmd_ready;
  assign system_dBus_cmd_payload_wr = _zz_40;
  assign system_dBus_cmd_payload_address = _zz_41;
  assign system_dBus_cmd_payload_data = _zz_42;
  assign system_dBus_cmd_payload_size = _zz_43;
  assign dma_0_config_valid = _zz_74;
  assign dma_0_config_payload_startAddr = _zz_75;
  assign dma_0_config_payload_length = _zz_76;
  assign dma_0_config_payload_timerInit = _zz_77;
  assign dma_0_config_payload_slicer = _zz_78;
  assign dma_0_config_payload_reverse = _zz_79;
  assign dma_0_config_payload_last_or_run_till_last = _zz_80;
  assign dma_0_config_payload_demapper_constellation = _zz_81;
  assign dma_0_config_payload_demapper_two_over_sigma_sq = _zz_82;
  assign dma_0_interrupt_clear = _zz_83;
  assign dma_0_dmaReset = _zz_84;
  assign dma_1_config_valid = _zz_85;
  assign dma_1_config_payload_startAddr = _zz_86;
  assign dma_1_config_payload_length = _zz_87;
  assign dma_1_config_payload_timerInit = _zz_88;
  assign dma_1_config_payload_slicer = _zz_89;
  assign dma_1_config_payload_reverse = _zz_90;
  assign dma_1_config_payload_last_or_run_till_last = _zz_91;
  assign dma_1_config_payload_demapper_constellation = _zz_92;
  assign dma_1_config_payload_demapper_two_over_sigma_sq = _zz_93;
  assign dma_1_interrupt_clear = _zz_94;
  assign dma_1_dmaReset = _zz_95;
  assign dma_2_config_valid = _zz_96;
  assign dma_2_config_payload_startAddr = _zz_97;
  assign dma_2_config_payload_length = _zz_98;
  assign dma_2_config_payload_timerInit = _zz_99;
  assign dma_2_config_payload_slicer = _zz_100;
  assign dma_2_config_payload_reverse = _zz_101;
  assign dma_2_config_payload_last_or_run_till_last = _zz_102;
  assign dma_2_config_payload_demapper_constellation = _zz_103;
  assign dma_2_config_payload_demapper_two_over_sigma_sq = _zz_104;
  assign dma_2_interrupt_clear = _zz_105;
  assign dma_2_dmaReset = _zz_106;
  assign mapmov_mover_active = _zz_107;
  assign mapmov_trim_start = _zz_108;
  assign mapmov_trim_end = _zz_109;
  assign mapmov_pilot_ram_addr = _zz_110;
  assign mapmov_pilot_ram_wdata = _zz_111;
  assign mapmov_pilot_ram_we = _zz_112;
  assign mapmov_reset = _zz_113;
  assign mapmov_one_value = _zz_114;
  assign mapmov_zero_value = _zz_115;
  assign io_timerStatus_gtimer = _zz_116;
  assign ringbus_0_interrupt_clear = _zz_117;
  assign ringbus_0_config_valid = _zz_118;
  assign ringbus_0_config_payload_write_data = _zz_119;
  assign ringbus_0_config_payload_write_addr = _zz_120;
  assign ringbus_0_read_ready = _zz_121;
  assign _zz_34 = _zz_122;
  assign _zz_35 = _zz_123;
  assign ringbus_1_interrupt_clear = _zz_124;
  assign ringbus_1_config_valid = _zz_125;
  assign ringbus_1_config_payload_write_data = _zz_126;
  assign ringbus_1_config_payload_write_addr = _zz_127;
  assign ringbus_1_read_ready = _zz_128;
  assign nco_ncoReset = _zz_133;
  assign nco_config_valid = _zz_129;
  assign nco_config_payload_startAngle = _zz_130;
  assign nco_config_payload_length = _zz_131;
  assign nco_config_payload_delta = _zz_132;
  assign slicer_value = _zz_134;
  assign control_control = _zz_135;
  assign dengine_reset = _zz_136;
  assign dengine_func0MinThreshold = _zz_137;
  assign dengine_func0MaxThreshold = _zz_138;
  assign dengine_func1MinThreshold = _zz_139;
  assign dengine_func1MaxThreshold = _zz_140;
  assign xbaseband_cmd_valid = _zz_151;
  assign xbaseband_cmd_payload_instruction = _zz_152;
  assign xbaseband_cmd_payload_rs1 = _zz_153;
  assign _zz_68 = _zz_164[7:0];
  assign jtag_tdo = _zz_154;
  assign io_uart_txd = _zz_178;
  assign _zz_70 = _zz_191[3:0];
  assign _zz_71 = 1'b0;
  assign system_dBus_cmd_ready = _zz_196;
  assign system_dBus_rsp_ready = _zz_197;
  assign system_dBus_rsp_error = _zz_198;
  assign system_dBus_rsp_data = _zz_199;
  assign _zz_46 = ((1'b1 && (! _zz_55)) || _zz_48);
  assign _zz_55 = _zz_56;
  assign _zz_47 = _zz_55;
  assign _zz_49 = _zz_57;
  assign _zz_50 = _zz_58;
  assign _zz_51 = _zz_59;
  assign _zz_52 = _zz_60;
  assign _zz_61 = ((_zz_50 & _zz_207) == (32'b00000000000000000000000000000000));
  always @ (*) begin
    scalarMemBus_cmd_valid = (_zz_47 && _zz_61);
    io_vmemBus_cmd_valid = (_zz_47 && _zz_62);
    _zz_69 = (_zz_47 && _zz_63);
    _zz_48 = ((((_zz_61 && scalarMemBus_cmd_ready) || (_zz_62 && io_vmemBus_cmd_ready)) || (_zz_63 && _zz_168)) || _zz_64);
    if((_zz_65 && (! _zz_53)))begin
      _zz_48 = 1'b0;
      scalarMemBus_cmd_valid = 1'b0;
      io_vmemBus_cmd_valid = 1'b0;
      _zz_69 = 1'b0;
    end
  end

  assign scalarMemBus_cmd_payload_wr = _zz_49;
  assign scalarMemBus_cmd_payload_address = _zz_50;
  assign scalarMemBus_cmd_payload_data = _zz_51;
  assign scalarMemBus_cmd_payload_mask = _zz_52;
  assign _zz_62 = (((32'b00000000000001000000000000000000) <= _zz_50) && (_zz_50 < (32'b00000000000101000000000000000000)));
  assign io_vmemBus_cmd_payload_wr = _zz_49;
  assign io_vmemBus_cmd_payload_address = _zz_50;
  assign io_vmemBus_cmd_payload_data = _zz_51;
  assign io_vmemBus_cmd_payload_mask = _zz_52;
  assign _zz_63 = ((_zz_50 & _zz_208) == (32'b11110000000000000000000000000000));
  assign _zz_64 = ((! ((_zz_61 || _zz_62) || _zz_63)) && _zz_47);
  assign _zz_53 = (((scalarMemBus_rsp_valid || io_vmemBus_rsp_valid) || _zz_169) || (_zz_65 && _zz_66));
  assign _zz_54 = _zz_72;
  assign _zz_33 = io_gpio;
  always @ (posedge io_mainClk) begin
    if(_zz_205)begin
      resetCtrl_systemClkResetCounter <= (resetCtrl_systemClkResetCounter + (6'b000001));
    end
    if(_zz_73)begin
      resetCtrl_systemClkResetCounter <= (6'b000000);
    end
  end

  always @ (posedge io_mainClk) begin
    resetCtrl_mainClkReset <= resetCtrl_mainClkResetUnbuffered;
    resetCtrl_systemReset <= resetCtrl_mainClkResetUnbuffered;
    if(_zz_44)begin
      resetCtrl_systemReset <= 1'b1;
    end
  end

  always @ (posedge io_mainClk or posedge resetCtrl_systemReset) begin
    if (resetCtrl_systemReset) begin
      _zz_38 <= 1'b0;
      _zz_39 <= 1'b1;
      _zz_56 <= 1'b0;
      _zz_65 <= 1'b0;
      _zz_66 <= 1'b0;
    end else begin
      if(_zz_206)begin
        _zz_38 <= _zz_146;
        _zz_39 <= (! _zz_146);
      end else begin
        _zz_38 <= (! _zz_37);
        _zz_39 <= _zz_37;
      end
      if(_zz_46)begin
        _zz_56 <= _zz_200;
      end
      if(_zz_53)begin
        _zz_65 <= 1'b0;
      end
      if(((_zz_47 && _zz_48) && (! _zz_49)))begin
        _zz_65 <= 1'b1;
      end
      _zz_66 <= 1'b0;
      if(_zz_64)begin
        _zz_66 <= 1'b1;
      end
    end
  end

  always @ (posedge io_mainClk) begin
    if(_zz_206)begin
      _zz_40 <= _zz_147;
      _zz_41 <= _zz_148;
      _zz_42 <= _zz_149;
      _zz_43 <= _zz_150;
    end
    if(_zz_46)begin
      _zz_57 <= _zz_201;
      _zz_58 <= _zz_202;
      _zz_59 <= _zz_203;
      _zz_60 <= _zz_204;
    end
    if((_zz_47 && _zz_48))begin
      _zz_67 <= {_zz_63,_zz_62};
    end
  end

  always @ (posedge io_mainClk) begin
    _zz_44 <= _zz_143;
  end

  always @ (posedge io_mainClk or posedge resetCtrl_mainClkReset) begin
    if (resetCtrl_mainClkReset) begin
      _zz_45 <= 1'b0;
    end else begin
      _zz_45 <= (_zz_163 && _zz_141);
    end
  end

endmodule

