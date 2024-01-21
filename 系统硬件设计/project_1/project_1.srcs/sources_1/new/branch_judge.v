
module branch_judge(
  beq,
  bne,
  blt,
  bge,
  bltu,
  bgeu,
  jal,
  jalr,
  zero,
  ALU_result_sig,
  jump_flag

 );
	input beq;
	input bne;
	input blt;
	input bge;
	input bltu;
	input bgeu;
	input jal;
	input jalr;
	
	input zero;
	input ALU_result_sig;
	
	output jump_flag;
	
	assign jump_flag = 	jal |
						jalr |
						(beq && zero)|
						(bne && (!zero))|
						(blt && ALU_result_sig)|
						(bge && (!ALU_result_sig))|
						(bltu && ALU_result_sig)|
						(bgeu && (!ALU_result_sig));

endmodule


