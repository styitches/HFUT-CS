`include "define.vh"

module registers(
	clk,
	rst_n,
	W_en,
	Rs1,
	Rs2,
	Rd,
	Wr_data,
	Rd_data1,
	Rd_data2
    );
	input clk;
	input rst_n;
	input W_en;
	input [4:0]Rs1;
	input [4:0]Rs2;
	input [4:0]Rd;
	input [31:0]Wr_data;
	
	output [31:0]Rd_data1;
	output [31:0]Rd_data2;
	
	reg [31:0] regs [31:0];
	
	
///////////////////////////////////////////////write
	
	always@(negedge clk )
		begin
			if(!rst_n)
				begin
					regs[0]<=`zeroword;
					regs[1]<=`zeroword;
					regs[2]<=`zeroword;
					regs[3]<=`zeroword;
					regs[4]<=`zeroword;
					regs[5]<=`zeroword;
					regs[6]<=`zeroword;
					regs[7]<=`zeroword;
					regs[8]<=`zeroword;
					regs[9]<=`zeroword;
					regs[10]<=`zeroword;
					regs[11]<=`zeroword;
					regs[12]<=`zeroword;
					regs[13]<=`zeroword;
					regs[14]<=`zeroword;
					regs[15]<=`zeroword;
					regs[16]<=`zeroword;
					regs[17]<=`zeroword;
					regs[18]<=`zeroword;
					regs[19]<=`zeroword;
					regs[20]<=`zeroword;
					regs[21]<=`zeroword;
					regs[22]<=`zeroword;
					regs[23]<=`zeroword;
					regs[24]<=`zeroword;
					regs[25]<=`zeroword;
					regs[26]<=`zeroword;
					regs[27]<=`zeroword;
					regs[28]<=`zeroword;
					regs[29]<=`zeroword;
					regs[30]<=`zeroword;
					regs[31]<=`zeroword;
				end
			else if(W_en & (Rd!=0))
					regs[Rd]<=Wr_data;	
		end

//////////////////////////////////////////////read

	assign Rd_data1=(Rs1==5'd0)?`zeroword: regs[Rs1];
	assign Rd_data2=(Rs2==5'd0)?`zeroword: regs[Rs2];
	

endmodule
