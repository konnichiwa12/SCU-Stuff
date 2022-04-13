module MEM_WB(clock, ALU_in, ALU_out, data_mem_in, data_mem_out);
    
    input clock;
    input [31:0] ALU_in;
    input [31:0] data_mem_in;
    
    output reg [31:0] ALU_out;
    output reg [31:0] data_mem_out;
    
    always@(posedge clock) begin
        ALU_out = ALU_in;
        data_mem_out = data_mem_in;
    end

endmodule