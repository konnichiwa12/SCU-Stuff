module EX_MEM(clock, sum, zero, alu, idex, sum_out, zero_out, alu_out, idex_out);
    input [31:0] sum;
    input [31:0] zero;
    input [31:0] alu;
    input [31:0] idex;
    input clock;

    output reg [31:0] sum_out;
    output reg [31:0] zero_out;
    output reg [31:0] alu_out;
    output reg [31:0] idex_out;
    
    always@(posedge clock)begin
        sum_out = sum;
        zero_out = zero;
        alu_out = alu;
        idex_out = idex;
    end

endmodule
