module generic_dpram #(
    parameter AWIDTH = 11,
    parameter DEPTH = 2048
) (
    input                       clk,

    input               t0_valid,
    output logic        t0_ready,
    input               t0_we,
    input         [1:0] t0_size,
    input        [31:0] t0_addr,
    input        [31:0] t0_data,

    output logic        i0_valid,
    input               i0_ready,
    output logic [31:0] i0_data,

    input               t1_valid,
    output logic        t1_ready,
    input               t1_we,
    input         [1:0] t1_size,
    input        [31:0] t1_addr,
    input        [31:0] t1_data,

    output logic        i1_valid,
    input               i1_ready,
    output logic [31:0] i1_data
);

    logic [7:0] mem0 [DEPTH-1:0]  /* synthesis syn_ramstyle = "block_ram */;
    logic [7:0] mem1 [DEPTH-1:0]  /* synthesis syn_ramstyle = "block_ram */;
    logic [7:0] mem2 [DEPTH-1:0]  /* synthesis syn_ramstyle = "block_ram */;
    logic [7:0] mem3 [DEPTH-1:0]  /* synthesis syn_ramstyle = "block_ram */;

initial begin
    $readmemh("scalar0.mif", mem0);
    $readmemh("scalar1.mif", mem1);
    $readmemh("scalar2.mif", mem2);
    $readmemh("scalar3.mif", mem3);
end

// Port 0
    logic [3:0] t0_be;

    assign t0_be = (
        {4{t0_valid & t0_we}} &
        (
            (t0_size == 2'b00) ? {
                (t0_addr[1:0] == 2'b11),
                (t0_addr[1:0] == 2'b10),
                (t0_addr[1:0] == 2'b01),
                (t0_addr[1:0] == 2'b00)
            } :
            (t0_size == 2'b01) ? {
                (t0_addr[1] == 1'b1),
                (t0_addr[1] == 1'b1),
                (t0_addr[1] == 1'b0),
                (t0_addr[1] == 1'b0)
            } :
            4'b1111
        )
    );

    logic [AWIDTH-1:0] t0_addr_word;
    assign t0_ready = 1'b1;
    assign t0_addr_word = t0_addr[AWIDTH+1:2];

    logic [7:0] t0_data0, i0_data0;
    logic [7:0] t0_data1, i0_data1;
    logic [7:0] t0_data2, i0_data2;
    logic [7:0] t0_data3, i0_data3;

    assign t0_data0 = t0_data[7 : 0];
    assign t0_data1 = t0_data[15: 8];
    assign t0_data2 = t0_data[23:16];
    assign t0_data3 = t0_data[31:24];

    always_ff @(posedge clk) begin
        i0_data0 <= mem0[t0_addr_word];
        if (t0_be[0]) begin
            mem0[t0_addr_word] <= t0_data0;
            i0_data0 <= t0_data0;
        end
    end

    always_ff @(posedge clk) begin
        i0_data1 <= mem1[t0_addr_word];
        if (t0_be[1]) begin
            mem1[t0_addr_word] <= t0_data1;
            i0_data1 <= t0_data1;
        end
    end

    always_ff @(posedge clk) begin
        i0_data2 <= mem2[t0_addr_word];
        if (t0_be[2]) begin
            mem2[t0_addr_word] <= t0_data2;
            i0_data2 <= t0_data2;
        end
    end

    always_ff @(posedge clk) begin
        i0_data3 <= mem3[t0_addr_word];
        if (t0_be[3]) begin
            mem3[t0_addr_word] <= t0_data3;
            i0_data3 <= t0_data3;
        end
    end

    always_ff @(posedge clk) i0_valid <= t0_valid;

    assign i0_data = {
        i0_data3,
        i0_data2,
        i0_data1,
        i0_data0
    };

// Port 1
    logic [3:0] t1_be;

    assign t1_be = (
        {4{t1_valid & t1_we}} &
        (
            (t1_size == 2'b00) ? {
                (t1_addr[1:0] == 2'b11),
                (t1_addr[1:0] == 2'b10),
                (t1_addr[1:0] == 2'b01),
                (t1_addr[1:0] == 2'b00)
            } :
            (t1_size == 2'b01) ? {
                (t1_addr[1] == 1'b1),
                (t1_addr[1] == 1'b1),
                (t1_addr[1] == 1'b0),
                (t1_addr[1] == 1'b0)
            } :
            4'b1111
        )
    );

    logic [AWIDTH-1:0] t1_addr_word;
    assign t1_ready = 1'b1;
    assign t1_addr_word = t1_addr[AWIDTH+1:2];

    logic [7:0] t1_data0, i1_data0;
    logic [7:0] t1_data1, i1_data1;
    logic [7:0] t1_data2, i1_data2;
    logic [7:0] t1_data3, i1_data3;

    assign t1_data0 = t1_data[7 : 0];
    assign t1_data1 = t1_data[15: 8];
    assign t1_data2 = t1_data[23:16];
    assign t1_data3 = t1_data[31:24];



    always_ff @(posedge clk) begin
        i1_data0 <= mem0[t1_addr_word];
        if (t1_be[0]) begin
            mem0[t1_addr_word] <= t1_data0;
            i1_data0 <= t1_data0;
        end
    end

    always_ff @(posedge clk) begin
        i1_data1 <= mem1[t1_addr_word];
        if (t1_be[1]) begin
            mem1[t1_addr_word] <= t1_data1;
            i1_data1 <= t1_data1;
        end
    end

    always_ff @(posedge clk) begin
        i1_data2 <= mem2[t1_addr_word];
        if (t1_be[2]) begin
            mem2[t1_addr_word] <= t1_data2;
            i1_data2 <= t1_data2;
        end
    end

    always_ff @(posedge clk) begin
        i1_data3 <= mem3[t1_addr_word];
        if (t1_be[3]) begin
            mem3[t1_addr_word] <= t1_data3;
            i1_data3 <= t1_data3;
        end
    end

    always_ff @(posedge clk) i1_valid <= t1_valid;

    assign i1_data = {
        i1_data3,
        i1_data2,
        i1_data1,
        i1_data0
    };

endmodule
