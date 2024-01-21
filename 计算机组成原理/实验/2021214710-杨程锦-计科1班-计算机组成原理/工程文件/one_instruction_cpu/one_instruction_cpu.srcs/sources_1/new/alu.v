`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/15 02:24:14
// Design Name: 
// Module Name: alu
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


module alu(
    input wire [15:0] in1, //输入数据
    input wire [15:0] in2, //输入数据
    input wire [2:0] alu_op, //操作码
    output reg [15:0] result //输出数据
    );
    
    parameter
    ADD = 3'b000,
    SUB = 3'b001,
    AND = 3'b010,
    OR = 3'b011,
    SLL = 3'b100,
    SRL = 3'b101,
    SLA = 3'b110,
    SRA = 3'b111;
    
    always @(*)
    begin
        case(alu_op)
            ADD: result = in1 + in2;
            SUB: result = in1 - in2;
            AND: result = in1 && in2;
            OR: result = in1 || in2;
            SLL: result = in1 << in2;
            SRL: result = in1 >> in2;
            SLA: result = in1 <<< in2;
            SRA: result = in1 >>> in2;
            default: result = 4710;
        endcase
    end
endmodule
