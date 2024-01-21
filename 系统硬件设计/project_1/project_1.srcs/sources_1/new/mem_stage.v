
module mem_stage(
	input [31:0]Rd_data2_mem_i,
	input [31:0]loaddata_mem_wb_o,
	input forwardC_mem_i,
	output [31:0]Wr_mem_data
	
    );

	mux mem_mux (
    .data1(loaddata_mem_wb_o), 
    .data2(Rd_data2_mem_i), 
    .sel(forwardC_mem_i), 
    .dout(Wr_mem_data)
    );

endmodule
