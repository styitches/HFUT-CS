`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/15 02:16:42
// Design Name: 
// Module Name: pc
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


module pc(clk, rst, pc);
    input wire clk;
    input wire rst; //÷ÿ÷√–≈∫≈
    output reg[7:0] pc;
    
    always @(posedge clk)
    begin
        if (rst)
            pc = 0;
        else
            pc = pc + 1;
    end
endmodule
