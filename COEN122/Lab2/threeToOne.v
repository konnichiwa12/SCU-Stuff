module three_onemux(A1, A2, A3, s, out);
input [31:0] A1;
input [31:0] A2;
input [31:0] A3;
input [1:0]s;
output reg [31:0] out;
    
always@(A1, A2, A3, s) begin
    if (s == 2'b00) begin
        out = A1;
    end else if (s == 2'b01) begin
        out = A2;
    end if (s == 2'b10) begin
        out = A3;
    end
 
end

endmodule
