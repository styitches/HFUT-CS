`include "define.vh"
module instr_decode(
	input [31:0]instr,
	output [6:0]opcode,
	output [2:0]func3,
	output func7,
	output [4:0]Rs1,
	output [4:0]Rs2,
	output [4:0]Rd,
	output [31:0]imme
	 );
	 
	wire I_type;
	wire U_type;
	wire J_type;
	wire B_type;
	wire S_type;
	
	wire [31:0]I_imme;
	wire [31:0]U_imme;
	wire [31:0]J_imme;
	wire [31:0]B_imme;
	wire [31:0]S_imme;
	
	
	assign opcode=instr[6:0];
	assign func3=instr[14:12];
	assign func7=instr[30];
	assign Rs1=instr[19:15];
	assign Rs2=instr[24:20];
	assign Rd =instr[11:7];
	
	assign I_type=(instr[6:0]==`jalr) | (instr[6:0]==`load) | (instr[6:0]==`I_type);
	assign U_type=(instr[6:0]==`lui) | (instr[6:0]==`auipc);
	assign J_type=(instr[6:0]==`jal);
	assign B_type=(instr[6:0]==`B_type);
	assign S_type=(instr[6:0]==`store);
	
	
	assign I_imme={{20{instr[31]}},instr[31:20]}; 
	assign U_imme={instr[31:12],{12{1'b0}}};
	assign J_imme={{12{instr[31]}},instr[19:12],instr[20],instr[30:21],1'b0};   
	assign B_imme={{20{instr[31]}},instr[7],instr[30:25],instr[11:8],1'b0};
	assign S_imme={{20{instr[31]}},instr[31:25],instr[11:7]}; 
	
	assign imme= I_type?I_imme :
				 U_type?U_imme :
				 J_type?J_imme :
				 B_type?B_imme :
				 S_type?S_imme : 32'd0;


endmodule
