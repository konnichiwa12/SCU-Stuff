module tb_alu();
    reg [31:0] A;
    reg [31:0] B;
    reg [3:0] opcode;
    wire [31:0] out;
    wire negative, zero;
    
    ALU test(A, B, opcode, out, zero, negative);
    
    initial
    begin
    //A+B
        A = 0;
        B = 1;
        opcode = 4'b0000;
        #50
        A = 1;
        B = 0;
        opcode = 4'b0000;
        #50
        A = 1;
        B = 1;
        opcode = 4'b0000;
        #50
    //B + 1
        A = 0;
        B = 1;
        opcode = 4'b0001;
        #50
        A = 1;
        B = 0;
        opcode = 4'b0001;
        #50
        A = 1;
        B = 1;
        opcode = 4'b0001;
        #50
    //-A
        A = 0;
        B = 1;
        opcode = 4'b0010;
        #50
        A = 1;
        B = 0;
        opcode = 4'b0010;
        #50
        A = 1;
        B = 1;
        opcode = 4'b0010;
        #50
    //B-A
        A = 0;
        B = 1;
        opcode = 4'b0011;
        #50
        A = 1;
        B = 0;
        opcode = 4'b0011;
        #50
        A = 1;
        B = 1;
        opcode = 4'b0011;
        #50
    //0 + A
        A = 0;
        B = 1;
        opcode = 4'b0100;
        #50
        A = 1;
        B = 0;
        opcode = 4'b0100;
        #50
        A = 1;
        B = 1;
        opcode = 4'b0100;
        #50
    $finish;
    end
endmodule