`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/08/2021 03:06:35 PM
// Design Name: 
// Module Name: tb_mux
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_mux();
    reg i1, i2, i3, i4;
    reg [1:0]s;
    wire out;
    
    fourone_mux test(i1, i2, i3, i4, s, out);
    initial
    begin
    i1 = 0;
    i2 = 0;
    i3 = 1;
    i4 = 1;
    //test case one
    s = 2'b00;
    #50;
    //test case two
    s = 2'b01;
    #50;
    //test case three
    s = 2'b10;
    #50;
    //test case four
    s = 2'b11;
    #50;
    
    $finish;
    end
endmodule
