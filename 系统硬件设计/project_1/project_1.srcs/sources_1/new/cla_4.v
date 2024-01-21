module cla_4(p,g,c_in,c,gx,px);
input[3:0] p,g;
input c_in;
output[4:1] c;
output gx,px;

assign c[1] = p[0]&c_in | g[0];
assign c[2] = p[1]&p[0]&c_in | p[1]&g[0] | g[1];
assign c[3] = p[2]&p[1]&p[0]&c_in | p[2]&p[1]&g[0] | p[2]&g[1] | g[2];
assign c[4] = gx | px&c_in;

assign px = p[3]&p[2]&p[1]&p[0];
assign gx = g[3] | p[3]&g[2] | p[3]&p[2]&g[1] | p[3]&p[2]&p[1]&g[0];

endmodule