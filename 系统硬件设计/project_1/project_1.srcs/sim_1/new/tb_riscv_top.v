`timescale 1ns / 1ps



module tb_riscv_top;

	// Inputs
	reg clk;
	reg rst_n;

	// Outputs
	wire [7:0] rom_addr;

	// Instantiate the Unit Under Test (UUT)
	riscv_top uut (
		.clk(clk), 
		.rst_n(rst_n), 
		.rom_addr(rom_addr)
	);
always #10 clk= ~clk;
	initial begin
		// Initialize Inputs
		clk = 0;
		rst_n = 0;

		// Wait 100 ns for global reset to finish
		#100;
		rst_n=1;
        
		// Add stimulus here

	end
      
endmodule

