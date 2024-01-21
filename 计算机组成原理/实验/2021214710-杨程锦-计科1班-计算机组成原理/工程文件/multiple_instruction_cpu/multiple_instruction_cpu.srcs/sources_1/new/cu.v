`timescale 1ns / 1ps
module cu(
    input wire [3:0] operate,    //4位指令操作码
    output reg stop, uct, acc_wr, dataMem_wr, //停机信号、非条件转移uct、acc读写控制、数据存储器读写控制
    output reg [3:0] alu_op //alu操作选择
);
    initial 
    begin
      stop = 0;
      uct = 0;
      acc_wr = 0;
      dataMem_wr = 0;
      alu_op = 4'b1111;
    end

    always @(operate) 
    begin
      case(operate)
        4'b0000: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00100000;   //清除累加器指令CLA
        4'b0001: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00100001;   //累加器取反指令COM    
        4'b0010: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00100010;   //算术右移一位指令SHR
        4'b0011: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00100011;   //循环左移一位指令CSL
        4'b0100: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00100100;   //加法指令ADD
        4'b0101: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00010101;   //存数指令STA
        4'b0110: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00100110;   //取数指令LDA
        4'b0111: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b01000111;   //无条件转移指令JMP
        4'b1000: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00001000;   //有条件转移BAN
        4'b1001: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b10000000;   //停机STOP
        endcase
    end

endmodule