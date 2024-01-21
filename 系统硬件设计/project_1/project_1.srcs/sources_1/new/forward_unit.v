
//以上就是我们面临的五种冒险的分析，简单总结如下：
//a.在一个周期开始，EX 阶段要使用上一条处在 EX 阶段指令的执行结果，此时我们将 EX/MEM 寄存器的数据前递。
//b.在一个周期开始，EX 阶段要使用上一条处在 MEM 阶段指令的执行结果，此时我们将 MEM/WB 寄存器的数据前递。
//c.在一个周期开始，EX 阶段要使用上一条处在 WB 阶段指令的执行结果，此时不需要前递（寄存器堆前递机制）
//d.在第一种情况下，如果是上一条是访存指令，即发生加载-使用型冒险。则需要停顿一个周期。
//e.在发生加载--使用型冒险的时候，如果是load后跟着store指令，并且load指令的rd与store指令的rs1 不同而与rs2相同，则不需要停顿，只需要将MEM/WB 寄存器的数据前递到MEM阶段。

module forward_unit(
	input [4:0]Rs1_id_ex_o,
	input [4:0]Rs2_id_ex_o,
	input [4:0]Rd_ex_mem_o,
	input [4:0]Rd_mem_wb_o,
	input RegWrite_ex_mem_o,
	input RegWrite_mem_wb_o,
	input MemWrite_id_ex_o,
	input MemRead_ex_mem_o,
	
	output  [1:0]forwardA,
	output  [1:0]forwardB,
	output forwardC,
	
	
	input [4:0]Rs1_id_ex_i,
	input [4:0]Rs2_id_ex_i,
	input [4:0]Rd_id_ex_o,
	input MemRead_id_ex_o,
	input MemWrite_id_ex_i,
	input RegWrite_id_ex_o,
	
	output load_use_flag
	
    );
	
	assign forwardA[1]=(RegWrite_ex_mem_o &&(Rd_ex_mem_o!=5'd0)&&(Rd_ex_mem_o==Rs1_id_ex_o));
	assign forwardA[0]=(RegWrite_mem_wb_o && (Rd_mem_wb_o !=5'd0) &&(Rd_mem_wb_o==Rs1_id_ex_o));
	
	assign forwardB[1]=(RegWrite_ex_mem_o &&(Rd_ex_mem_o!=5'd0)&&(Rd_ex_mem_o==Rs2_id_ex_o));
	assign forwardB[0]=(RegWrite_mem_wb_o && (Rd_mem_wb_o !=5'd0) &&(Rd_mem_wb_o==Rs2_id_ex_o));
	
	
	//load后紧跟sw但是不需要停顿
	assign forwardC=(RegWrite_ex_mem_o &&(Rd_ex_mem_o!=5'd0)&&(Rd_ex_mem_o!=Rs1_id_ex_o)&& (Rd_ex_mem_o==Rs2_id_ex_o)&& MemWrite_id_ex_o && MemRead_ex_mem_o );
	
	
	//load-use
	assign load_use_flag= 	MemRead_id_ex_o & RegWrite_id_ex_o & (Rd_id_ex_o!=5'd0)   //load
							&(!MemWrite_id_ex_i)     //非store
							& ((Rd_id_ex_o ==Rs1_id_ex_i) | (Rd_id_ex_o ==Rs2_id_ex_i))
							|
							MemRead_id_ex_o & RegWrite_id_ex_o & (Rd_id_ex_o!=5'd0)     //load
							&(MemWrite_id_ex_i)     //store
							& (Rd_id_ex_o ==Rs1_id_ex_i);
							

endmodule




