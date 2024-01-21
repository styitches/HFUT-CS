
`include "define.vh"
module pc_reg(
	clk,
	rst_n,
	pc_new,
	pc_out,
	load_use_flag
    );
	input clk;
	input rst_n;
	input [31:0]pc_new;
	input load_use_flag;
	
	output reg [31:0]pc_out;
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			pc_out<=`zeroword;
		else if(load_use_flag)  //读后写会有冲突，前一个仍然在访存，后一个在执行，需要等前一个拿到数据然后前推，所以pc不变
			pc_out<=pc_out;
		else
			pc_out<=pc_new;
	end	

endmodule


