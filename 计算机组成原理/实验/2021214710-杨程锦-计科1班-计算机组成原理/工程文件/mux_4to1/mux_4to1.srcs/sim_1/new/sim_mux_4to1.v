`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/01 13:34:13
// Design Name: 
// Module Name: sim_mux_4to1
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


module sim_mux_4to1;
    reg [3:0] a, b, c, d;
    reg [1:0] sel;
    wire [3:0] out;
    mux_4to1 mux_4to1(
        .in0(a),
        .in1(b),
        .in2(c),
        .in3(d),
        .sel(sel),
        .out(out)
    );
    
    initial
        begin
            sel <= 00;
            a <= 4'b0100; b <= 4'b0001; c <= 4'b0010; d <= 4'b0011;
            
            #200
            sel <= 01;
            a <= 4'b0100; b <= 4'b0111; c <= 4'b0110; d <= 4'b0111;
            
            #200
            sel <= 10;
            a <= 4'b1000; b <= 4'b1001; c <= 4'b0001; d <= 4'b1011;
            
            #200
            sel <= 11;
            a <= 4'b1100; b <= 4'b1101; c <= 4'b1110; d <= 4'b0000;
        end
endmodule
