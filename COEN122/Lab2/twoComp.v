module twoComp(A, out);
input [31:0] A;
output reg [31:0] out;
integer i;

always@ (A)
begin
  out = (~A) + 1;
end
endmodule