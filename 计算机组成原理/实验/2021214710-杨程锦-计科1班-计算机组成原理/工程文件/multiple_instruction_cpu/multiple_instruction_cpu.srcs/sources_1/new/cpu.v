`timescale 1ns / 1ps
module cpu_10(
    input wire clk, rst,
    output a
);
    wire stop, ct, uct, acc_wr, dataMem_wr;
    wire [11:0] pc_addr;
    wire [3:0] alu_op;
    wire [15:0] ins, in1, in2, Z;

    //pc实例化
    pc pc(
      .clk(clk), .rst(rst), .stop(stop), .ct(ct), .uct(uct),
      .offset(ins[11:0]),
      .pc(pc_addr)
    );
    //指令存储器实例化
    insMem insMem(
      .addr(pc_addr),
      .Ins(ins)
    );
    //acc实例化
    acc acc(
      .clk(clk), .acc_wr(acc_wr),
      .data_in(Z), 
      .data_out(in1)
    );
    //数据存储器实例化
    dataMem dataMem(
      .dataMem_wr(dataMem_wr), .clk(clk),
      .addr(ins[11:0]),
      .data_in(Z),
      .data_out(in2)
    );
    //cu实例化
    cu cu(
      .operate(ins[15:12]),
      .stop(stop), .uct(uct), .acc_wr(acc_wr), .dataMem_wr(dataMem_wr),
      .alu_op(alu_op)
    );
    //alu实例化
    alu alu(
      .in1(in1), .in2(in2),
      .alu_op(alu_op),
      .ct(ct),
      .Z(Z)
    );

endmodule

