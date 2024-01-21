`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/15 01:55:45
// Design Name: 
// Module Name: cpu
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


module cpu(
    input wire clk,
    input wire rst
    );
    wire we;
    wire [2:0] alu_op;
    wire [7:0] addr;
    wire re1, re2;
    wire [15:0] result, ins, rdata1, rdata2;
    pc pc(
        .clk(clk),
        .rst(rst),
        .pc(addr)
    ); 
    insMem  insMem(
        .addr(addr),
        .ins(ins)
    );
     cu cu(
        .opcode(ins[15:9]),
        .clk(clk),
        .we(we),
        .re1(re1),
        .re2(re2),
        .alu_op(alu_op)
    );
    register register(
        .clk(clk),
        .we(we),
        .waddr(ins[2:0]),
        .wdata(result),
        .re1(re1),
        .raddr1(ins[8:6]),
        .rdata1(rdata1),
        .re2(re2),
        .raddr2(ins[5:3]),
        .rdata2(rdata2)
    );
    alu alu(
        .in1(rdata1),
        .in2(rdata2),
        .alu_op(alu_op),
        .result(result)
    );
endmodule
