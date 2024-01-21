`timescale 1ns / 1ps

module sim_cpu;
    reg clk, rst;
    
    initial 
    begin 
      clk = 1;
      rst = 1;
      #5 rst = 0;
      #80 $stop;
    end

    always #5 clk = ~clk;

    cpu_10 cpu_10(
        .clk(clk), .rst(rst)
    );

endmodule
