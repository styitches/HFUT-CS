//*************************************************************
//***********************************adder*********************


module Adder(input [31:0] A,
             input [31:0] B,
			 input Cin,
			 input [3:0] ALU_CTL,
			 output ADD_carry,
			 output ADD_OverFlow,
			 output ADD_zero,
			 output [31:0] ADD_result);

    cla_adder32 cla_adder32_inst1(.A(A),
	                        .B(B),
							.cin(Cin),
							.cout(ADD_carry),
							.result(ADD_result));	


   assign ADD_zero = ~(|ADD_result);
   assign ADD_OverFlow=((ALU_CTL==4'b0001) & ~A[31] & ~B[31] & ADD_result[31])  // +(+)+ = -
                      | ((ALU_CTL==4'b0001) & A[31] & B[31] & ~ADD_result[31])  // -(+)- = +
                      | ((ALU_CTL==4'b0011) & A[31] & ~B[31] & ~ADD_result[31]) // +(-)- = -
					  | ((ALU_CTL==4'b0011) & ~A[31] & B[31] & ADD_result[31]); // -(-)+ = +
endmodule
