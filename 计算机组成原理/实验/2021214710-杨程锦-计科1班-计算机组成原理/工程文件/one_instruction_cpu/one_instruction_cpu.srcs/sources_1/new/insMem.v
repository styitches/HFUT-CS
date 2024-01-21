`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/15 01:57:04
// Design Name: 
// Module Name: insMem
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module insMem(
    input wire [7:0] addr,  //8位指令地址
    output reg [15:0] ins   //16位指令
    );
    
    reg [15:0] units [7:0];  //unit用来存放指令，每个指令16位，一共可以放8个指令
    
    initial
    begin
        units[0] = 16'b0000000_000_001_010;
        units[1] = 16'b0000000_001_010_011;
    end
    
    always @(addr)
    begin
        ins <= units[addr];
    end
    
endmodule
