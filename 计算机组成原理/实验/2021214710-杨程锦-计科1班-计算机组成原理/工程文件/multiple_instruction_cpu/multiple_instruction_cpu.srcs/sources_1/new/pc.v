`timescale 1ns / 1ps
module pc(
    input wire clk, rst, stop, ct, uct, //时钟、重置、停机、条件转移、无条件转移
    input wire [11:0] offset,  //12位转移指令偏移量
    output reg [11:0] pc  //12位指令地址码  
);

    assign stop = 0;  //初始化开机状态
    // assign clk = (stop==1)?1'bz:0; //停机则将clk置0

    always@(posedge clk) begin
      if(rst == 1)
        pc = 0;
      else
        pc = pc + 1;
    end

    always@(negedge clk) begin
      if(uct == 1)  //无条件转移
        pc = offset-1;
      if(ct == 1)  //条件转移
        pc = pc+offset-1;
    end

endmodule