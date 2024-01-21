
module mux(data1,data2,sel,dout
    );
	input [31:0]data1;
	input [31:0]data2;
	input sel;
	output [31:0]dout;
	
	assign dout = sel ? data1 : data2 ;

endmodule
