`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/15 02:33:58
// Design Name: 
// Module Name: sim_cpu
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


module sim_cpu();
    reg clk, rst;
    initial
    begin
        clk = 1;
        rst = 1;
        #10 rst = 0;
    end
    
    always
    begin
        #5 clk = ~clk;
        if ($time >= 50) $stop;
    end
    
    cpu cpu(
        .clk(clk),
        .rst(rst)
    );
endmodule
