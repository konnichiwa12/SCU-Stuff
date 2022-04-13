module adder32Bit(A,B,sum);

input [31:0]A;
input [31:0]B;
output wire [31:0]sum;

wire c[0:31];

adder1Bit A0(A[0],B[0],1'b0,sum[0],c[0]);
adder1Bit A1(A[1],B[1],c[0],sum[1],c[1]);
adder1Bit A2(A[2],B[2],c[1],sum[2],c[2]);
adder1Bit A3(A[3],B[3],c[2],sum[3],c[3]);
adder1Bit A4(A[4],B[4],c[3],sum[4],c[4]);
adder1Bit A5(A[5],B[5],c[4],sum[5],c[5]);
adder1Bit A6(A[6],B[6],c[5],sum[6],c[6]);
adder1Bit A7(A[7],B[7],c[6],sum[7],c[7]);
adder1Bit A8(A[8],B[8],c[7],sum[8],c[8]);
adder1Bit A9(A[9],B[9],c[8],sum[9],c[9]);
adder1Bit A10(A[10],B[10],c[9],sum[10],c[10]);
adder1Bit A11(A[11],B[11],c[10],sum[11],c[11]);
adder1Bit A12(A[12],B[12],c[11],sum[12],c[12]);
adder1Bit A13(A[13],B[13],c[12],sum[13],c[13]);
adder1Bit A14(A[14],B[14],c[13],sum[14],c[14]);
adder1Bit A15(A[15],B[15],c[14],sum[15],c[15]);
adder1Bit A16(A[16],B[16],c[15],sum[16],c[16]);
adder1Bit A17(A[17],B[17],c[16],sum[17],c[17]);
adder1Bit A18(A[18],B[18],c[17],sum[18],c[18]);
adder1Bit A19(A[19],B[19],c[18],sum[19],c[19]);
adder1Bit A20(A[20],B[20],c[19],sum[20],c[20]);
adder1Bit A21(A[21],B[21],c[20],sum[21],c[21]);
adder1Bit A22(A[22],B[22],c[21],sum[22],c[22]);
adder1Bit A23(A[23],B[23],c[22],sum[23],c[23]);
adder1Bit A24(A[24],B[24],c[23],sum[24],c[24]);
adder1Bit A25(A[25],B[25],c[24],sum[25],c[25]);
adder1Bit A26(A[26],B[26],c[25],sum[26],c[26]);
adder1Bit A27(A[27],B[27],c[26],sum[27],c[27]);
adder1Bit A28(A[28],B[28],c[27],sum[28],c[28]);
adder1Bit A29(A[29],B[29],c[28],sum[29],c[29]);
adder1Bit A30(A[30],B[30],c[29],sum[30],c[30]);
adder1Bit A31(A[31],B[31],c[30],sum[31],c[31]);

endmodule
