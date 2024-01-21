
module riscv_top(
	input clk,
	input rst_n,
	output [7:0]rom_addr
    );

	wire [31:0]ram_addr;
	wire [31:0]instr;
	wire [31:0]Rd_mem_data;
	wire [31:0]Wr_mem_data;
	wire W_en;
	wire R_en;
	wire [2:0]RW_type;
	
	instr_memory instr_memory_inst (
    .addr(rom_addr), 
    .instr(instr)
    );

	riscv riscv_inst (
    .clk(clk), 
    .rst_n(rst_n), 
    .instr(instr), 
    .Rd_mem_data(Rd_mem_data), 
    .rom_addr(rom_addr), 
    .Wr_mem_data(Wr_mem_data), 
    .W_en(W_en), 
    .R_en(R_en), 
    .ram_addr(ram_addr), 
    .RW_type(RW_type)
    );

	
	
	
	data_memory data_memory_inst (
    .clk(clk), 
    .rst_n(rst_n), 
    .W_en(W_en), 
    .R_en(R_en), 
    .addr(ram_addr), 
    .RW_type(RW_type), 
    .din(Wr_mem_data), 
    .dout(Rd_mem_data)
    );

	
	
	
	

endmodule
