`include "define.vh"
module id_ex_regs(
	input clk,
	input rst_n,
	
	input jump_flag,
	
	input [31:0]pc_id_ex_i,
	input [31:0]imme_id_ex_i,
	input [31:0]Rd_data1_id_ex_i,
	input [31:0]Rd_data2_id_ex_i,
	input [4:0]Rd_id_ex_i,
	input [4:0]Rs1_id_ex_i,
	input [4:0]Rs2_id_ex_i,
	output reg [31:0]pc_id_ex_o,
	output reg [31:0]imme_id_ex_o,
	output reg [31:0]Rd_data1_id_ex_o,
	output reg [31:0]Rd_data2_id_ex_o,
	output reg [4:0]Rd_id_ex_o,
	output reg [4:0]Rs1_id_ex_o,
	output reg [4:0]Rs2_id_ex_o,
	
	//control signals
	input ALUSrc_id_ex_i,
	input [3:0]ALUctl_id_ex_i,
	input beq_id_ex_i,
	input bne_id_ex_i,
	input blt_id_ex_i,
	input bge_id_ex_i,
	input bltu_id_ex_i,
	input bgeu_id_ex_i,
	input jal_id_ex_i,
	input jalr_id_ex_i,
	input MemRead_id_ex_i,
	input MemWrite_id_ex_i,
	input [2:0]RW_type_id_ex_i,
	input lui_id_ex_i,
	input U_type_id_ex_i,
	input MemtoReg_id_ex_i,
	input RegWrite_id_ex_i,
	
	output  reg ALUSrc_id_ex_o,
	output  reg [3:0]ALUctl_id_ex_o,
	output  reg beq_id_ex_o,
	output  reg bne_id_ex_o,
	output  reg blt_id_ex_o,
	output  reg bge_id_ex_o,
	output  reg bltu_id_ex_o,
	output  reg bgeu_id_ex_o,
	output  reg jal_id_ex_o,
	output  reg jalr_id_ex_o,
	output  reg MemRead_id_ex_o,
	output  reg MemWrite_id_ex_o,
	output  reg [2:0]RW_type_id_ex_o,
	output  reg lui_id_ex_o,
	output  reg U_type_id_ex_o,
	output  reg MemtoReg_id_ex_o,
	output  reg RegWrite_id_ex_o,
	input load_use_flag

    );

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			pc_id_ex_o<=`zeroword;
		else
			pc_id_ex_o<=pc_id_ex_i;
	end
	
always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			imme_id_ex_o<=`zeroword;
		else
			imme_id_ex_o<=imme_id_ex_i;
	end
	
always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			Rd_data1_id_ex_o<=`zeroword;
		else
			Rd_data1_id_ex_o<=Rd_data1_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			Rd_data2_id_ex_o<=`zeroword;
		else
			Rd_data2_id_ex_o<=Rd_data2_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			Rd_id_ex_o<=5'd0;
		else
			Rd_id_ex_o<=Rd_id_ex_i;
	end
	
always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			Rs1_id_ex_o<=5'd0;
		else
			Rs1_id_ex_o<=Rs1_id_ex_i;
	end
	
always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			Rs2_id_ex_o<=5'd0;
		else
			Rs2_id_ex_o<=Rs2_id_ex_i;
	end
	
	
	
always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n )
			ALUSrc_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			ALUSrc_id_ex_o<=`zero;
		else
			ALUSrc_id_ex_o<=ALUSrc_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			ALUctl_id_ex_o<=4'b0000;
		else if(jump_flag | load_use_flag)
			ALUctl_id_ex_o<=4'b0000;
		else
			ALUctl_id_ex_o<=ALUctl_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			beq_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			beq_id_ex_o<=`zero;
		else
			beq_id_ex_o<=beq_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			bne_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			bne_id_ex_o<=`zero;
		else
			bne_id_ex_o<=bne_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			blt_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			blt_id_ex_o<=`zero;
		else
			blt_id_ex_o<=blt_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			bge_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			bge_id_ex_o<=`zero;
		else
			bge_id_ex_o<=bge_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			bltu_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			bltu_id_ex_o<=`zero;
		else
			bltu_id_ex_o<=bltu_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			bgeu_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			bgeu_id_ex_o<=`zero;
		else
			bgeu_id_ex_o<=bgeu_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			jal_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			jal_id_ex_o<=`zero;
		else
			jal_id_ex_o<=jal_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			jalr_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			jalr_id_ex_o<=`zero;
		else
			jalr_id_ex_o<=jalr_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			MemRead_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			MemRead_id_ex_o<=`zero;
		else
			MemRead_id_ex_o<=MemRead_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			MemWrite_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			MemWrite_id_ex_o<=`zero;
		else
			MemWrite_id_ex_o<=MemWrite_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			RW_type_id_ex_o<=3'b000;
		else if(jump_flag | load_use_flag)
			RW_type_id_ex_o<=3'b000;
		else
			RW_type_id_ex_o<=RW_type_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			lui_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			lui_id_ex_o<=`zero;
		else
			lui_id_ex_o<=lui_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			U_type_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			U_type_id_ex_o<=`zero;
		else
			U_type_id_ex_o<=U_type_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			MemtoReg_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			MemtoReg_id_ex_o<=`zero;
		else
			MemtoReg_id_ex_o<=MemtoReg_id_ex_i;
	end

always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			RegWrite_id_ex_o<=`zero;
		else if(jump_flag | load_use_flag)
			RegWrite_id_ex_o<=`zero;
		else
			RegWrite_id_ex_o<=RegWrite_id_ex_i;
	end


endmodule



