`timescale 1ns / 1ps
module insMem(
    input wire [11:0] addr,  //12位指令地址码
    output wire [15:0] Ins  
);
    reg[15:0] insMem[4096:0];  

    initial 
    begin
        insMem[0] = 16'b0100000000000001 ;   //加法指令ADD
        insMem[1] = 16'b0101000000000000;    //存数指令STA
        insMem[2] = 16'b0110000000000000;    //取数指令LDA
        insMem[3] = 16'b0000000000000000;    //清除累加器指令CLA
        insMem[4] = 16'b0001000000000000;    //累加器取反指令COM
        insMem[5] = 16'b0010000000000000;    //算术右移一位指令SHR
        insMem[6] = 16'b0011000000000000;    //循环左移一位指令CSL
        insMem[7] = 16'b0111000000001001;    //无条件转移指令JMP
        insMem[9] = 16'b1000000000001001;    //有条件转移BAN
        insMem[10] = 16'b100100000000000;    //停机指令STP
    end

    assign Ins = insMem[addr];

endmodule