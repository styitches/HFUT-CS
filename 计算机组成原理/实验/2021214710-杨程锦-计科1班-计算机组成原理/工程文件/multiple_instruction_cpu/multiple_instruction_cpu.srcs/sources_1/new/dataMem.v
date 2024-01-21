`timescale 1ns / 1ps
module dataMem(
    input wire dataMem_wr, clk, //dataMem使能、时钟
    input wire [11:0] addr, //12位指令地址
    input wire [15:0] data_in,  //16位输入数据
    output wire [15:0] data_out //16位输出数据
);
    reg [15:0] dataMem[4096:0]; //2^12个存储单元,每个存储单元16位

    assign data_out = dataMem[addr];

    initial 
    begin
      dataMem[0] = 16'b0010000000100001;    //初始化1
      dataMem[1] = 16'b0100011100010000;    //初始化2
    end

    always @(negedge clk) 
    begin
      if(dataMem_wr == 1)
        dataMem[addr] = data_in;
    end

endmodule