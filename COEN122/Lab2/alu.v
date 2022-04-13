module ALU(A, B, opcode, out, Z, N);
input [31:0] A;
input [31:0] B;
input [3:0] opcode;
output reg Z;
output reg N;
wire [31:0] tcA;
wire [31:0] Bn;
wire [31:0] An;
wire [31:0] temp;
output wire [31:0] out;
reg [2:0] three_one;
reg two_one;

    always@(A, B, opcode)
        begin
        if (opcode == 4'b0000)begin //B + A
             three_one = 2'b00;//A
             two_one = 0;//B
        end else if (opcode == 4'b0001)begin //B + 1
            three_one = 2'b01;//1
            two_one = 0;//B
        end else if (opcode == 4'b0010)begin //0 + (-A)
            three_one = 2'b10;//-A
            two_one = 1;//0
        end else if (opcode == 4'b0011)begin //B + (-A)
            three_one = 2'b10;//-A
            two_one = 0;//B
        end else if (opcode == 4'b0100)begin //0 + A
            three_one = 2'b00;//A
            two_one = 1;//0
        end
        
    end
     
        twoComp twoComp(A, tcA);
        two_onemux twoToOne(B, 0, two_one, Bn);
        three_onemux threeToOne(A, 1, tcA, three_one, An);
        adder32Bit adder32(An, Bn, out);
        
        
    always@(out)begin
        if (out == 0)begin
            Z = 1;
        end else begin
            Z = 0;
        end
        
        if (out[31] == 1)begin
            N = 1;
        end else begin
            N = 0;
        end
    end
endmodule