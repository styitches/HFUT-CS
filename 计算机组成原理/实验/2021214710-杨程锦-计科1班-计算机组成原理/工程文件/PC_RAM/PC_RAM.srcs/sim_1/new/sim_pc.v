`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/14 16:01:06
// Design Name: 
// Module Name: sim_pc
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


module sim_pc();
    reg clk;
    reg rst;
    wire [7:0] pc;
    
    initial
    begin
        clk = 1;
        
        forever
        begin
            if ($time == 0 || $time == 80)
                rst = 1;
            else
                rst = 0;
            if ($time >= 160) $stop;
            #5 clk = ~clk;
        end
    end
    
    PC PC(
        .clk(clk),
        .rst(rst),
        .pc(pc)
    );
endmodule
