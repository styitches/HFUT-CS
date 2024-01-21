
module wb_stage(
	input MemtoReg,
	input jal,
	input jalr,
	input lui,
	input U_type,
	input [31:0]ALU_result_wb_i,   
	input [31:0]pc_jump_wb_i,
	input [31:0]loaddata_wb_i,    
	input [31:0]imme_wb_i,
	input [31:0]pc_order_wb_i,
	output [31:0]Wr_reg_data_wb_o

    );
	
	wire [31:0]WB_data;
	wire reg_sel;
	wire [31:0]Wr_reg_data1;
	wire [31:0]Wr_reg_data2;
	
	assign reg_sel=jal | jalr ;
	
	/////////////////////////////////////ALU_result or datamem	
	mux wb_data_mux (
    .data1(loaddata_wb_i), 
    .data2(ALU_result_wb_i), 
    .sel(MemtoReg), 
    .dout(WB_data)
    );
	
	
////////////////////////////////////Wr_data_sel
	mux jalr_mux (
    .data1(pc_order_wb_i), 
    .data2(WB_data), 
    .sel(reg_sel), 
    .dout(Wr_reg_data2)
    );
	
	mux lui_mux (
    .data1(imme_wb_i), 
    .data2(pc_jump_wb_i), 
    .sel(lui), 
    .dout(Wr_reg_data1)
    );
	
	mux wr_reg_mux (
    .data1(Wr_reg_data1), 
    .data2(Wr_reg_data2), 
    .sel(U_type), 
    .dout(Wr_reg_data_wb_o)
    );
	
	
	
	

endmodule
