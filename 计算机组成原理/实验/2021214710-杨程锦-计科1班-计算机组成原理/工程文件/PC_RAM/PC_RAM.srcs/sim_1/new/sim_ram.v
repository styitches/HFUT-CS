`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/14 16:01:06
// Design Name: 
// Module Name: sim_ram
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


module sim_ram();
    reg clk;
    reg we;
    reg [9:0] addr;
    reg [15:0] data_in;
    wire [15:0] data_out;
    
    RAM RAM(
        .clk(clk),
        .we(we),
        .addr(addr),
        .data_in(data_in),
        .data_out(data_out)
    );
    
    initial
    begin
        clk = 1;
        we = 0;
        addr = 0;
        data_in = 0;
        #10;
        we = 1;
        addr = 0;
        data_in = 16'h4710;
        #10;
        we = 0;
        addr = 0;
        #10;
        $display("Data out =  %h", data_out);
        #10;
        $finish;
    end
    
    always #5 clk = ~clk;
endmodule
