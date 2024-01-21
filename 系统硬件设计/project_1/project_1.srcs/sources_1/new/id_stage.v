
module id_stage(
	input clk,
	input rst_n,
	input RegWrite_id_i,
	input [4:0]Rd_id_i,
	input [31:0]Wr_reg_data_id_i,
	input [31:0] instr_id_i,
	output [6:0] opcode_id_o,
	output [2:0] func3_id_o,
	output func7_id_o,
	output [31:0] imme_id_o,
	output [31:0] Rd_data1_id_o,
	output [31:0] Rd_data2_id_o,
	output [4:0]Rd_id_o,
	output  [4:0]Rs1_id_o,
	output  [4:0]Rs2_id_o
    );

	

	
	instr_decode instr_decode_inst (
    .instr(instr_id_i), 
    .opcode(opcode_id_o), 
    .func3(func3_id_o), 
    .func7(func7_id_o), 
    .Rs1(Rs1_id_o), 
    .Rs2(Rs2_id_o), 
    .Rd(Rd_id_o), 
    .imme(imme_id_o)
    );
	
    registers registers_inst (
    .clk(clk), 
	.rst_n(rst_n), 
    .W_en(RegWrite_id_i), 
    .Rs1(Rs1_id_o), 
    .Rs2(Rs2_id_o), 
    .Rd(Rd_id_i), 
    .Wr_data(Wr_reg_data_id_i), 
    .Rd_data1(Rd_data1_id_o), 
    .Rd_data2(Rd_data2_id_o)
    );
endmodule
