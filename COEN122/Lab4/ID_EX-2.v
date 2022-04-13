module ID_EX(clock, rsout, rtout, rdout, addout, immgenout, rs, rt, rd, add ,immgen);
    input clock;
    input [31:0] rsout;
    input [31:0] rtout;
    input [5:0] rdout;
    input [31:0] addout;
    input [31:0] immgenout;
    
    output reg [31:0] rs;
    output reg [31:0] rt;
    output reg [5:0] rd;
    output reg [31:0] add;
    output reg [31:0] immgen;
    
    always@(posedge clock)begin
        rs = rsout;
        rt = rtout;
        rd = rdout;
        add = addout;
        immgen = immgenout;
    end
    
endmodule