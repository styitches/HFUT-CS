`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/14 14:50:07
// Design Name: 
// Module Name: RAM
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


module RAM(
    input wire clk,
    input wire we,
    input wire [9:0] addr,
    input wire [15:0] data_in,
    output reg [15:0] data_out
    );
    
    reg [15:0] ram[511:0]; //16λword 512words
    
    always @(posedge clk)
    begin
        if (we)
        begin
            ram[addr] <= data_in;
        end
        else
        begin
            data_out <= ram[addr];
        end
    end
endmodule
