`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/14 02:14:36
// Design Name: 
// Module Name: sim_alu
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


module sim_alu();
    reg [15:0] in0, in1;
    reg [2:0] alu_op;
    wire [15:0] result;
    ALU ALU(
        .in0(in0),
        .in1(in1),
        .alu_op(alu_op),
        .result(result)
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
    initial
    begin
        in0 = 16'h4710;
        in1 = 16'h0001;
        
        alu_op = ADD;
        #10 $display("in0 + in1 = %b",result);
        
        alu_op = SUB;
        #10 $display("in0 - in1 = %b",result);
        
        alu_op = AND;
        #10 $display("in0 && in1 = %b",result);
        
        alu_op = OR;
        #10 $display("in0 || in1 = %b",result);
        
        alu_op = SLL;
        #10 $display("in0 << in1 = %b",result);
        
        alu_op = SRL;
        #10 $display("in0 >> in1 = %b",result);
        
        alu_op = SLA;
        #10 $display("in0 <<< in1 = %b",result);
        
        alu_op = SRA;
        #10 $display("in0 >>> in1 = %b",result);
        
        $finish;
    end
endmodule
