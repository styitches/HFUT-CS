module cla_adder32(A,B,cin,result,cout);

input [31:0] A;
input [31:0] B;
input cin;
output[31:0] result;
output cout;


wire[31:0] TAG,TAP;
wire[32:1] TAC;
wire[15:0] TAG_0,TAP_0;
wire[3:0] TAG_1,TAP_1;
wire[8:1] TAC_1;
wire[4:1] TAC_2;
 
assign result = A ^ B ^ {TAC[31:1],cin};  
assign TAG = A&B;
assign TAP = A|B;

cla_4 cla_0_0( .p(TAP[3:0]),  .g(TAG[3:0]),  .c_in(cin), .c(TAC[4:1]),  .gx(TAG_0[0]),.px(TAP_0[0]));
cla_4 cla_0_1( .p(TAP[7:4]),  .g(TAG[7:4]),  .c_in(TAC_1[1]),.c(TAC[8:5]),  .gx(TAG_0[1]),.px(TAP_0[1]));
cla_4 cla_0_2( .p(TAP[11:8]), .g(TAG[11:8]), .c_in(TAC_1[2]),.c(TAC[12:9]), .gx(TAG_0[2]),.px(TAP_0[2]));
cla_4 cla_0_3( .p(TAP[15:12]),.g(TAG[15:12]),.c_in(TAC_1[3]),.c(TAC[16:13]),.gx(TAG_0[3]),.px(TAP_0[3]));
cla_4 cla_0_4( .p(TAP[19:16]),.g(TAG[19:16]),.c_in(TAC_1[4]),.c(TAC[20:17]),.gx(TAG_0[4]),.px(TAP_0[4]));
cla_4 cla_0_5( .p(TAP[23:20]),.g(TAG[23:20]),.c_in(TAC_1[5]),.c(TAC[24:21]),.gx(TAG_0[5]),.px(TAP_0[5]));
cla_4 cla_0_6( .p(TAP[27:24]),.g(TAG[27:24]),.c_in(TAC_1[6]),.c(TAC[28:25]),.gx(TAG_0[6]),.px(TAP_0[6]));
cla_4 cla_0_7( .p(TAP[31:28]),.g(TAG[31:28]),.c_in(TAC_1[7]),.c(TAC[32:29]),.gx(TAG_0[7]),.px(TAP_0[7]));


////////////////////////
cla_4 cla_1_0(.p(TAP_0[3:0]),  .g(TAG_0[3:0]),  .c_in(cin),.c(TAC_1[4:1]),  .gx(TAG_1[0]),.px(TAP_1[0]));


cla_4 cla_1_1(.p(TAP_0[7:4]),  .g(TAG_0[7:4]),  .c_in(TAC_1[4]),.c(TAC_1[8:5]),  .gx(TAG_1[1]),.px(TAP_1[1]));

assign TAG_1[3:2] = 2'b00;
assign TAP_1[3:2] = 2'b00;

cla_4 cla_2_0(.p(TAP_1[3:0]),   .g(TAG_1[3:0]),    .c_in(1'b0), .c(TAC_2[4:1]),  .gx(),.px());

assign cout = TAC_2[2];

endmodule