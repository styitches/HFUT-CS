`include "define.vh"
module mem_wb_regs(
	input clk,
	input rst_n,
	
	input [31:0]ALU_result_mem_wb_i,   
	input [31:0]pc_jump_mem_wb_i,
	input [31:0]loaddata_mem_wb_i,     //DM
	input [31:0]imme_mem_wb_i,
	input [31:0]pc_order_mem_wb_i,
	input [4:0]Rd_mem_wb_i,
	output reg [31:0]ALU_result_mem_wb_o,   
	output reg [31:0]pc_jump_mem_wb_o,
	output reg [31:0]loaddata_mem_wb_o,     //DM
	output reg [31:0]imme_mem_wb_o,
	output reg [31:0]pc_order_mem_wb_o,
	output reg [4:0]Rd_mem_wb_o,
	//////////////////////////////////////////////control signals
	input jal_mem_wb_i,
	input jalr_mem_wb_i,
	input lui_mem_wb_i,
	input U_type_mem_wb_i,
	input MemtoReg_mem_wb_i,
	input RegWrite_mem_wb_i,
	
	output reg jal_mem_wb_o,
	output reg jalr_mem_wb_o,
	output reg lui_mem_wb_o,
	output reg U_type_mem_wb_o,
	output reg MemtoReg_mem_wb_o,
	output reg RegWrite_mem_wb_o

    );
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			ALU_result_mem_wb_o<=`zeroword;
		else
			ALU_result_mem_wb_o<=ALU_result_mem_wb_i;
	end
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			pc_jump_mem_wb_o<=`zeroword;
		else
			pc_jump_mem_wb_o<=pc_jump_mem_wb_i;
	end
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			loaddata_mem_wb_o<=`zeroword;
		else
			loaddata_mem_wb_o<=loaddata_mem_wb_i;
	end
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			imme_mem_wb_o<=`zeroword;
		else
			imme_mem_wb_o<=imme_mem_wb_i;
	end
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			pc_order_mem_wb_o<=`zeroword;
		else
			pc_order_mem_wb_o<=pc_order_mem_wb_i;
	end
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			Rd_mem_wb_o<=5'd0;
		else
			Rd_mem_wb_o<=Rd_mem_wb_i;
	end
	
	
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			jal_mem_wb_o<=`zero;
		else
			jal_mem_wb_o<=jal_mem_wb_i;
	end
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			jalr_mem_wb_o<=`zero;
		else
			jalr_mem_wb_o<=jalr_mem_wb_i;
	end
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			lui_mem_wb_o<=`zero;
		else
			lui_mem_wb_o<=lui_mem_wb_i;
	end
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			U_type_mem_wb_o<=`zero;
		else
			U_type_mem_wb_o<=U_type_mem_wb_i;
	end
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			MemtoReg_mem_wb_o<=`zero;
		else
			MemtoReg_mem_wb_o<=MemtoReg_mem_wb_i;
	end
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			RegWrite_mem_wb_o<=`zero;
		else
			RegWrite_mem_wb_o<=RegWrite_mem_wb_i;
	end
	
	

endmodule
