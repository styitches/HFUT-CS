`timescale 1ns / 1ps
module mux3_1(
	input [31:0]din1,
	input [31:0]din2,
	input [31:0]din3,
	input [1:0]sel,
	output [31:0]dout
    );
	
	assign dout=sel[1] ? din1 : sel[0] ? din2 : din3 ;

endmodule
