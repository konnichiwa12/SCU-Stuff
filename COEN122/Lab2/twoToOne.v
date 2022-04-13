module two_onemux(d0, d1, s, out);
    input [31:0] d0;
    input [31:0] d1;
    input s;
    output reg [31:0] out;
    
    always@(d0, d1, s)
    begin
        if(s) begin
            out = d1;
        end else begin
            out = d0;
        end
    end

endmodule