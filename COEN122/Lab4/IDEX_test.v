module IDEX_test();
    reg clock;
    reg [31:0] rsout;
    reg [31:0] rtout;
    reg [5:0] rdout;
    reg [31:0] addout;
    reg [31:0] immgenout;
    
    wire [31:0] rs;
    wire [31:0] rt;
    wire [5:0] rd;
    wire [31:0] add;
    wire [31:0] immgen;
    
    ID_EX ID_EX(clock, rsout, rtout, rdout, addout, immgenout, rs, rt, rd, add ,immgen);
    
    initial
    begin
        clock = 0;
        forever #5 clock = ~clock;
    end
    
    initial begin
    rsout = 1;
    rtout = 2;
    rdout = 3;
    addout = 4;
    immgenout = 5;
    #50;
    
    rsout = 6;
    rtout = 7;
    rdout = 8;
    addout = 9;
    immgenout = 10;
    #50;
    $finish;
    end
    
endmodule