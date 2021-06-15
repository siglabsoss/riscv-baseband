/****************************************************************************
 * vector_alu.sv
 * Daniel Lomeli
 ****************************************************************************/

/**
 * Module: vector_alu
 * 
 * 
 */
module vector_alu#(
        parameter integer DATA_WIDTH   = 10,
        parameter integer OPER_WIDTH   = 10
        ) (
        input  wire [DATA_WIDTH-1:0]             t0_data,  //Target Inputs       
        input  wire [DATA_WIDTH-1:0]             t1_data,  
        input  wire [OPER_WIDTH-1:0]             t_oper,   
        input  wire                              t_valid,
        output wire                              t_ready,
        output logic [DATA_WIDTH-1:0]            i_data,   //Initiator Outputs
        output logic [2:0]                       i_csr,    //carry, overflow, zero
        output logic                             i_valid,
        input  logic                             i_ready,
        input  wire                              clk,
        input  wire                              srst
        );

    localparam MSB_BIT = DATA_WIDTH-1;
    
    logic [DATA_WIDTH:0] immediate;
    
    assign t_ready = i_ready;
    
    // CONTROL LOGIC
    enum {
        ADD=1,
        SUB=2,
        AND=3,
        OR =4,
        XOR=5,
        MV =6,
        ROL=7,
        ROR=8 
    } operation;	
    
    always_ff @(posedge clk) begin
        if (srst)  begin
            i_data <= '0;
            i_csr  <= '0;
            i_valid <= '0;
        end else begin
            i_valid   <= 1'b0;
            i_csr[2] <= 1'b0;
            if (t_valid && i_ready) begin
                // overflow check
                case (t_oper)
                    ADD: begin
                        i_csr[1] <= t0_data[MSB_BIT]&t1_data[MSB_BIT]&~immediate[MSB_BIT]|~t0_data[MSB_BIT]&~t1_data[MSB_BIT]&immediate[MSB_BIT];
                        i_csr[2] <= immediate[DATA_WIDTH]; //carry out
                    end
                    SUB: begin
                        i_csr[1] <= ~t0_data[MSB_BIT]&t1_data[MSB_BIT]&immediate[MSB_BIT]|t0_data[MSB_BIT]&~t1_data[MSB_BIT]&~immediate[MSB_BIT];
                    end
                    default: i_csr[1] <= 1'b0;
                endcase
                // zero check
                if (immediate == '0) begin
                    i_csr[0] <= 1'b1; //zero
                end
                //data out
                i_data <= immediate[MSB_BIT:0];				
                i_valid <= 1'b1;				
            end
        end
    end
    
    always_comb begin
        case (t_oper)
            ADD: immediate = t0_data +  t1_data;
            SUB: immediate = t0_data -  t1_data;
            AND: immediate = {1'b0,t0_data &  t1_data};
            OR : immediate = {1'b0,t0_data |  t1_data};
            XOR: immediate = {1'b0,t0_data ^  t1_data};
            default: immediate = '0;
        endcase
    end

endmodule


