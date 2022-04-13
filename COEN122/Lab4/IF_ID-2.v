module IF_ID(clock, pc_in, pc_out, instruction_in, instruction_out);

    input clock;
    input [31:0] pc_in;
    input [31:0] instruction_in;
    
    output reg [31:0] pc_out;
    output reg [31:0] instruction_out;
    
    always@(posedge clock) begin
        pc_out = pc_in;
        instruction_out = instruction_in;
    end
    
endmodule