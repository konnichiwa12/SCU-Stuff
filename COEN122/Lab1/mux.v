module fourone_mux(i1, i2, i3, i4, s, out);
input i1, i2, i3, i4;
input [1:0]s;
output reg out;
    
always@(s) begin
    if (s == 2'b00) begin
        out = i1;
    end else if (s == 2'b01) begin
        out = i2;
    end else if (s == 2'b10) begin
        out = i3;
    end else begin
        out = i4;
    end
 
end

endmodule