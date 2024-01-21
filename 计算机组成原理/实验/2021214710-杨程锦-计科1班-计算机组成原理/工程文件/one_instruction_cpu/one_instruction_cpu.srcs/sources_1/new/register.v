`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/15 01:55:45
// Design Name: 
// Module Name: register
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


module register(
     input wire clk,
    //Ð´¶Ë¿Ú
    input wire we,
    input wire[2:0] waddr,
    input wire[15:0] wdata,
    //¶Á¶Ë¿Ú1
    input wire re1,
    input wire[2:0] raddr1,
    output reg[15:0] rdata1,
    //¶Á¶Ë¿Ú2
    input wire re2,
    input wire[2:0] raddr2,
    output reg[15:0] rdata2
    );
    reg[15:0] regs[7:0]; //8¸ö16Î»¼Ä´æÆ÷
    initial
    begin
        regs[0] <= 16'b0010_0000_0010_0001;
        regs[1] <= 16'b0100_0111_0001_0000;
    end
    always @ (posedge clk)  //posedgeÉÏÉýÑØ
    begin
        if (we == 0)
            begin
                regs[waddr] <= wdata;
            end
        if ((raddr1 == waddr) && (re1 == 0))
            begin
                rdata1 <= wdata;
            end
        if ((raddr2 == waddr) && (re2 == 0))
            begin
                rdata2 <= wdata;
            end
    end
    always @ (*)
    begin
        if (re1 == 3'b000)
        begin
            rdata1 = regs[raddr1];
        end
        else
        begin
            rdata1 = 16'h4710;
        end
    end
    always @ (*)
    begin
        if (re2 == 3'b000)
        begin
            rdata2 = regs[raddr2];
        end
        else
        begin
            rdata2 = 16'h4710;
        end
    end
endmodule
