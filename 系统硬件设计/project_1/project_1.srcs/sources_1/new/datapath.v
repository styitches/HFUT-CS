module datapath(
	input 	clk,
	input   rst_n,
	input   [31:0]instr,


	input   MemtoReg, //写回寄存器的数据选择控制信号
	input   ALUSrc,   //ALU的数据来源的数据选择器控制信号
	input   RegWrite, //寄存器的写使能控制信号
	input   lui,
	input   U_type,
	input   jal,
	input   jalr,
	input   beq,
	input   bne,
	input   blt,
	input   bge,
	input   bltu,
	input   bgeu,
	input   [3:0]ALUctl,  //ALU的控制信号，决定ALU进行什么运算
	input  [2:0]RW_type,
	input   MemRead,
	input   MemWrite,
	
	input [31:0]loaddata,
	
	
	output  MemRead_ex_mem_o,
	output  MemWrite_ex_mem_o,
	output [2:0] RW_type_ex_mem_o,
	
	output  [7:0]rom_addr,  //指令地址
	output [31:0]Wr_mem_data,  //数据存储的写数据
	output [31:0]ALU_result_ex_mem_o,
	output [6:0]opcode,
	output [2:0]func3,
	output func7
	
);

	wire [31:0]pc_if_i;
	wire [31:0]pc_if_o;

	wire [31:0]pc_if_id_o;
	wire [31:0]instr_if_id_o;

	
	wire [31:0]imme_id_o;
	wire [31:0]Rd_data1_id_o;
	wire [31:0]Rd_data2_id_o;
	wire [4:0]Rd_id_o;
	wire [4:0]Rs1_id_o;
	wire [4:0]Rs2_id_o;
	
///////////////////////////////////////////////////	
	wire [31:0]pc_id_ex_o;
	wire [31:0]imme_id_ex_o;
	wire [31:0]Rd_data1_id_ex_o;
	wire [31:0]Rd_data2_id_ex_o;
	wire [4:0]Rd_id_ex_o;
	wire [4:0]Rs1_id_ex_o;
	wire [4:0]Rs2_id_ex_o;
	
	
	
	wire ALUSrc_id_ex_o;
	wire [3:0]ALUctl_id_ex_o;
	wire beq_id_ex_o;
	wire bne_id_ex_o;
	wire blt_id_ex_o;
	wire bge_id_ex_o;
	wire bltu_id_ex_o;
	wire bgeu_id_ex_o;
	wire jal_id_ex_o;
	wire jalr_id_ex_o;
	wire MemRead_id_ex_o;
	wire MemWrite_id_ex_o;
	wire [2:0]RW_type_id_ex_o;
	wire lui_id_ex_o;
	wire U_type_id_ex_o;
	wire MemtoReg_id_ex_o;
	wire RegWrite_id_ex_o;
/////////////////////////////////////////////////////	
	
	
	
	wire [31:0] ALU_result_ex_o;
	wire [31:0] pc_jump_o;
	wire [31:0] imme_ex_o;
	wire [31:0] pc_order_ex_o;
	
	wire forwardC_ex_o;
	wire [31:0]B;
	
///////////////////////////////////////////////////////	
	//wire [31:0] ALU_result_ex_mem_o;
	wire [31:0] pc_jump_ex_mem_o;
	wire [31:0] Rd_data2_ex_mem_o;
	wire [31:0] imme_ex_mem_o;
	wire [31:0] pc_order_ex_mem_o;
	wire [4:0]Rd_ex_mem_o;
	wire forwardC_ex_mem_o;

	wire  jal_ex_mem_o;
	wire  jalr_ex_mem_o;
//	wire  MemRead_ex_mem_o;
//	wire  MemWrite_ex_mem_o;
//	wire [2:0] RW_type_ex_mem_o;
	wire  lui_ex_mem_o;
	wire  U_type_ex_mem_o;
	wire  MemtoReg_ex_mem_o;
	wire  RegWrite_ex_mem_o;
////////////////////////////////////////////////////////////	



///////////////////////////////////////////////////////////	
	wire [31:0] ALU_result_mem_wb_o;
	wire [31:0] pc_jump_mem_wb_o;
	wire [31:0] loaddata_mem_wb_o;
	wire [31:0] imme_mem_wb_o;
	wire [31:0] pc_order_mem_wb_o;
	wire [4:0] Rd_mem_wb_o;
	
	wire  jal_mem_wb_o;
	wire  jalr_mem_wb_o;
	wire  lui_mem_wb_o;
	wire  U_type_mem_wb_o;
	wire  MemtoReg_mem_wb_o;
	wire  RegWrite_mem_wb_o;
//////////////////////////////////////////////////////////
	
	
	wire [31:0]Wr_reg_data_wb_o;
	
	wire load_use_flag;
	wire jump_flag;
	
if_stage if_stage_inst (
    .clk(clk), 
    .rst_n(rst_n), 
    .pc_if_i(pc_if_i), 
    .pc_if_o(pc_if_o), 
    .rom_addr(rom_addr),
    .load_use_flag(load_use_flag)
    );

if_id_regs  if_id_regs_inst(
    .clk(clk), 
    .rst_n(rst_n), 
    .pc_if_id_i(pc_if_o), 
    .instr_if_id_i(instr), 
    .pc_if_id_o(pc_if_id_o), 
    .instr_if_id_o(instr_if_id_o),
    .load_use_flag(load_use_flag),
    .jump_flag(jump_flag)
    );

id_stage id_stage_inst (
    .clk(clk), 
    .rst_n(rst_n), 
    .RegWrite_id_i(RegWrite_mem_wb_o), //////////////////////////WB stage singal
	.Rd_id_i(Rd_mem_wb_o),
    .Wr_reg_data_id_i(Wr_reg_data_wb_o), 
    .instr_id_i(instr_if_id_o), 
    .opcode_id_o(opcode), 
    .func3_id_o(func3), 
    .func7_id_o(func7), 
    .imme_id_o(imme_id_o), 
    .Rd_data1_id_o(Rd_data1_id_o), 
    .Rd_data2_id_o(Rd_data2_id_o),
	.Rd_id_o(Rd_id_o),
	.Rs1_id_o(Rs1_id_o),
	.Rs2_id_o(Rs2_id_o)
    );

id_ex_regs id_ex_regs_inst (
    .clk(clk), 
    .rst_n(rst_n), 
    .pc_id_ex_i(pc_if_id_o), 
    .imme_id_ex_i(imme_id_o), 
    .Rd_data1_id_ex_i(Rd_data1_id_o), 
    .Rd_data2_id_ex_i(Rd_data2_id_o), 
	.Rd_id_ex_i(Rd_id_o),
	.Rs1_id_ex_i(Rs1_id_o),
	.Rs2_id_ex_i(Rs2_id_o),
    .pc_id_ex_o(pc_id_ex_o), 
    .imme_id_ex_o(imme_id_ex_o), 
    .Rd_data1_id_ex_o(Rd_data1_id_ex_o), 
    .Rd_data2_id_ex_o(Rd_data2_id_ex_o),
	.Rd_id_ex_o(Rd_id_ex_o),
	.Rs1_id_ex_o(Rs1_id_ex_o),
	.Rs2_id_ex_o(Rs2_id_ex_o),
	////////////////////////////////////////////control signals
	.ALUSrc_id_ex_i(ALUSrc), 
    .ALUctl_id_ex_i(ALUctl), 
    .beq_id_ex_i(beq), 
    .bne_id_ex_i(bne), 
    .blt_id_ex_i(blt), 
    .bge_id_ex_i(bge), 
    .bltu_id_ex_i(bltu), 
    .bgeu_id_ex_i(bgeu), 
    .jal_id_ex_i(jal), 
    .jalr_id_ex_i(jalr), 
    .MemRead_id_ex_i(MemRead), 
    .MemWrite_id_ex_i(MemWrite), 
    .RW_type_id_ex_i(RW_type), 
    .lui_id_ex_i(lui), 
    .U_type_id_ex_i(U_type), 
    .MemtoReg_id_ex_i(MemtoReg), 
    .RegWrite_id_ex_i(RegWrite), 
    .ALUSrc_id_ex_o(ALUSrc_id_ex_o), 
    .ALUctl_id_ex_o(ALUctl_id_ex_o), 
    .beq_id_ex_o(beq_id_ex_o), 
    .bne_id_ex_o(bne_id_ex_o), 
    .blt_id_ex_o(blt_id_ex_o), 
    .bge_id_ex_o(bge_id_ex_o), 
    .bltu_id_ex_o(bltu_id_ex_o), 
    .bgeu_id_ex_o(bgeu_id_ex_o), 
    .jal_id_ex_o(jal_id_ex_o), 
    .jalr_id_ex_o(jalr_id_ex_o), 
    .MemRead_id_ex_o(MemRead_id_ex_o), 
    .MemWrite_id_ex_o(MemWrite_id_ex_o), 
    .RW_type_id_ex_o(RW_type_id_ex_o), 
    .lui_id_ex_o(lui_id_ex_o), 
    .U_type_id_ex_o(U_type_id_ex_o), 
    .MemtoReg_id_ex_o(MemtoReg_id_ex_o), 
    .RegWrite_id_ex_o(RegWrite_id_ex_o),
    .load_use_flag(load_use_flag),
    .jump_flag(jump_flag)
    );

ex_stage ex_stage_inst (
    .ALUctl_ex_i(ALUctl_id_ex_o), 
    .beq_ex_i(beq_id_ex_o), 
    .bne_ex_i(bne_id_ex_o), 
    .blt_ex_i(blt_id_ex_o), 
    .bge_ex_i(bge_id_ex_o), 
    .bltu_ex_i(bltu_id_ex_o), 
    .bgeu_ex_i(bgeu_id_ex_o), 
    .jal_ex_i(jal_id_ex_o), 
    .jalr_ex_i(jalr_id_ex_o), 
    .ALUSrc_ex_i(ALUSrc_id_ex_o), 
	.pc_if_o(pc_if_o),
    .pc_ex_i(pc_id_ex_o), 
    .imme_ex_i(imme_id_ex_o), 
    .Rd_data1_ex_i(Rd_data1_id_ex_o), 
    .Rd_data2_ex_i(Rd_data2_id_ex_o), 
    .ALU_result_ex_o(ALU_result_ex_o), 
    .pc_new_ex_o(pc_if_i), 
    .pc_jump_o(pc_jump_o), 
    .imme_ex_o(imme_ex_o), 
    .pc_order_ex_o(pc_order_ex_o),
	.Rs1_ex_i(Rs1_id_ex_o), 
    .Rs2_ex_i(Rs2_id_ex_o), 
    .Rd_ex_mem_o(Rd_ex_mem_o), 
    .Rd_mem_wb_o(Rd_mem_wb_o), 
    .RegWrite_ex_mem_o(RegWrite_ex_mem_o), 
    .RegWrite_mem_wb_o(RegWrite_mem_wb_o), 
    .MemRead_ex_mem_o(MemRead_ex_mem_o), 
    .MemWrite_id_ex_o(MemWrite_id_ex_o), 
    .ALU_result_ex_mem_o(ALU_result_ex_mem_o), 
    .ALU_result_mem_wb_o(ALU_result_mem_wb_o), 
    .forwardC(forwardC_ex_o),
	.B(B),
	.jump_flag(jump_flag),
	.load_use_flag(load_use_flag),
	 .Rs1_id_ex_i(Rs1_id_o),
	.Rs2_id_ex_i(Rs2_id_o),
	.Rd_id_ex_o(Rd_id_ex_o),
	.MemRead_id_ex_o(MemRead_id_ex_o),
	.MemWrite_id_ex_i(MemWrite),
    .RegWrite_id_ex_o(RegWrite_id_ex_o)
    );
	
ex_mem_regs ex_mem_regs_inst (
    .clk(clk), 
    .rst_n(rst_n), 
    .ALU_result_ex_mem_i(ALU_result_ex_o), 
    .pc_jump_ex_mem_i(pc_jump_o), 
    .Rd_data2_ex_mem_i(B), /////////////////////////
    .imme_ex_mem_i(imme_ex_o), 
    .pc_order_ex_mem_i(pc_order_ex_o), 
	.Rd_ex_mem_i(Rd_id_ex_o),
    .ALU_result_ex_mem_o(ALU_result_ex_mem_o), 
    .pc_jump_ex_mem_o(pc_jump_ex_mem_o), 
    .Rd_data2_ex_mem_o(Rd_data2_ex_mem_o), 
    .imme_ex_mem_o(imme_ex_mem_o), 

    .pc_order_ex_mem_o(pc_order_ex_mem_o),
  
	.Rd_ex_mem_o(Rd_ex_mem_o),
	.forwardC_ex_mem_i(forwardC_ex_o),
	.forwardC_ex_mem_o(forwardC_ex_mem_o),
	
	//////////////////////////////////////////////control signals
	.jal_ex_mem_i(jal_id_ex_o), 
    .jalr_ex_mem_i(jalr_id_ex_o), 
    .MemRead_ex_mem_i(MemRead_id_ex_o), 
    .MemWrite_ex_mem_i(MemWrite_id_ex_o), 
    .RW_type_ex_mem_i(RW_type_id_ex_o), 
    .lui_ex_mem_i(lui_id_ex_o), 
    .U_type_ex_mem_i(U_type_id_ex_o), 
    .MemtoReg_ex_mem_i(MemtoReg_id_ex_o), 
    .RegWrite_ex_mem_i(RegWrite_id_ex_o), 
    .jal_ex_mem_o(jal_ex_mem_o), 
    .jalr_ex_mem_o(jalr_ex_mem_o), 
    .MemRead_ex_mem_o(MemRead_ex_mem_o), /////////////////////////output control
    .MemWrite_ex_mem_o(MemWrite_ex_mem_o), ////////////////////////output control
    .RW_type_ex_mem_o(RW_type_ex_mem_o), ///////////////////////////output control
    .lui_ex_mem_o(lui_ex_mem_o), 
    .U_type_ex_mem_o(U_type_ex_mem_o), 
    .MemtoReg_ex_mem_o(MemtoReg_ex_mem_o), 
    .RegWrite_ex_mem_o(RegWrite_ex_mem_o)
    );
	
	mem_stage mem_stage_inst(
    .Rd_data2_mem_i(Rd_data2_ex_mem_o), 
    .loaddata_mem_wb_o(loaddata_mem_wb_o), 
    .forwardC_mem_i(forwardC_ex_mem_o), 
    .Wr_mem_data(Wr_mem_data)
    );


mem_wb_regs mem_wb_regs_inst (
	.clk(clk),
	.rst_n(rst_n),
    .ALU_result_mem_wb_i(ALU_result_ex_mem_o), 
    .pc_jump_mem_wb_i(pc_jump_ex_mem_o), 
    .loaddata_mem_wb_i(loaddata), 
    .imme_mem_wb_i(imme_ex_mem_o), 
    .pc_order_mem_wb_i(pc_order_ex_mem_o), 
	.Rd_mem_wb_i(Rd_ex_mem_o),
    .ALU_result_mem_wb_o(ALU_result_mem_wb_o), 
    .pc_jump_mem_wb_o(pc_jump_mem_wb_o), 
    .loaddata_mem_wb_o(loaddata_mem_wb_o), 
    .imme_mem_wb_o(imme_mem_wb_o), 
    .pc_order_mem_wb_o(pc_order_mem_wb_o),
	.Rd_mem_wb_o(Rd_mem_wb_o),
	////////////////////////////////////////////////////control signals
	.jal_mem_wb_i(jal_ex_mem_o), 
    .jalr_mem_wb_i(jalr_ex_mem_o), 
    .lui_mem_wb_i(lui_ex_mem_o), 
    .U_type_mem_wb_i(U_type_ex_mem_o), 
    .MemtoReg_mem_wb_i(MemtoReg_ex_mem_o), 
    .RegWrite_mem_wb_i(RegWrite_ex_mem_o), 
    .jal_mem_wb_o(jal_mem_wb_o), 
    .jalr_mem_wb_o(jalr_mem_wb_o), 
    .lui_mem_wb_o(lui_mem_wb_o), 
    .U_type_mem_wb_o(U_type_mem_wb_o), 
    .MemtoReg_mem_wb_o(MemtoReg_mem_wb_o), 
    .RegWrite_mem_wb_o(RegWrite_mem_wb_o)
    );
	
wb_stage wb_stage_inst (
    .MemtoReg(MemtoReg_mem_wb_o), 
    .jal(jal_mem_wb_o), 
    .jalr(jalr_mem_wb_o), 
    .lui(lui_mem_wb_o), 
    .U_type(U_type_mem_wb_o), 
    .ALU_result_wb_i(ALU_result_mem_wb_o), 
    .pc_jump_wb_i(pc_jump_mem_wb_o), 
    .loaddata_wb_i(loaddata_mem_wb_o), 
    .imme_wb_i(imme_mem_wb_o), 
    .pc_order_wb_i(pc_order_mem_wb_o), 
    .Wr_reg_data_wb_o(Wr_reg_data_wb_o)
    );
	
endmodule