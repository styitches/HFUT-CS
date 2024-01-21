`timescale 1ns / 1ps
module acc(
    input wire clk, acc_wr, //时钟、acc读写控制
    input wire [15:0] data_in,  //16位输入数据
    output wire [15:0] data_out //16位输出数据
);
    reg [15:0] acc; //16位acc

    initial 
    begin
        acc = 1;  //acc初始化1
    end

    assign data_out = acc; 

    always@(negedge clk) 
    begin
      if(acc_wr == 1)
        acc = data_in;
    end

endmodule