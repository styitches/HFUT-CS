`timescale 1ns / 1ps
module alu(
    input wire [15:0] in1, in2,   //操作数in1和in2
    input wire [3:0] alu_op,  //操作选择信号alu_op
    output reg ct, //条件转移ct
    output reg [15:0] Z   //Z
);
    initial 
    begin
      ct = 0;
      Z = 0;  //初始化结果Z为0
    end
    
    always @(*) 
    begin
      case (alu_op)
          4'b0000: Z = 0;   //清除累加器指令CLA
          4'b0001: Z = ~in1;    //累加器取反指令COM    
          4'b0010: Z = in1[15] == 1 ? {1'b1, in1[15:1]} : {1'b0, in1[15:1]};    //算术右移一位指令SHR
          4'b0011: Z = {in1[14:0], in1[15]};    //循环左移一位指令CSL
          4'b0100: Z = in1 + in2;   //加法指令ADD
          4'b0101: Z = in1;    //存数指令STA
          4'b0110: Z = in2;   //取数指令LDA
          4'b1000: ct = in1[15]==1?1:0;   //有条件转移BAN
          4'b1001: ;    //停机指令
      endcase
    end

endmodule