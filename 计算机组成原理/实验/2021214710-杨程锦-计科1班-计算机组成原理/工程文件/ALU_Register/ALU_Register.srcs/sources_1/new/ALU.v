`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/01 21:59:08
// Design Name: 
// Module Name: ALU
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


module ALU(
    input wire [15:0] in0, //输入数据
    input wire [15:0] in1, //输入数据
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
            ADD: result = in0 + in1;
            SUB: result = in0 - in1;
            AND: result = in0 && in1;
            OR: result = in0 || in1;
            SLL: result = in0 << in1;
            SRL: result = in0 >> in1;
            SLA: result = in0 <<< in1;
            SRA: result = in0 >>> in1;
            default: result = 4710;
        endcase
    end
endmodule
