module alu(
	   ALU_DA,
       ALU_DB,
       ALU_CTL,
       ALU_ZERO,
       ALU_OverFlow,
       ALU_DC   
        );
	input [31:0]    ALU_DA;
    input [31:0]    ALU_DB;
    input [3:0]     ALU_CTL;
    output          ALU_ZERO;
    output          ALU_OverFlow;
    output reg [31:0]   ALU_DC;
		   
//********************generate ctr***********************
wire SUBctr;
wire SIGctr;
wire Ovctr;
wire [1:0] Opctr;
wire [1:0] Logicctr;
wire [1:0] Shiftctr;
//001_ | 10_ _ （减法|比大小）
assign SUBctr = (~ ALU_CTL[3]  & ~ALU_CTL[2]  & ALU_CTL[1]) | ( ALU_CTL[3]  & ~ALU_CTL[2]);  //减法需要进行补码+1，作为cin
assign Opctr = ALU_CTL[3:2];  //ALU_CTL高两位作为运算类型分类 00-加法运算 01-逻辑运算 10-小于置一 11移位
assign Ovctr = ALU_CTL[0] & ~ ALU_CTL[3]  & ~ALU_CTL[2] ;
assign SIGctr = ALU_CTL[0];  //判断小于置一类型0-无符号 1-有符号
assign Logicctr = ALU_CTL[1:0];   //逻辑运算类型  & | ^ ~|
assign Shiftctr = ALU_CTL[1:0];   //判断哪种移位

//********************************************************

//*********************logic op***************************
reg [31:0] logic_result;

always@(*) begin
    case(Logicctr)
	2'b00:logic_result = ALU_DA & ALU_DB;
	2'b01:logic_result = ALU_DA | ALU_DB;
	2'b10:logic_result = ALU_DA ^ ALU_DB;
	2'b11:logic_result = ~(ALU_DA | ALU_DB);
	endcase
end 

//********************************************************
//************************shift op************************
wire [4:0]     ALU_SHIFT;
wire [31:0] shift_result;
assign ALU_SHIFT=ALU_DB[4:0];

Shifter Shifter(.ALU_DA(ALU_DA),
                .ALU_SHIFT(ALU_SHIFT),
				.Shiftctr(Shiftctr),
				.shift_result(shift_result));

//********************************************************
//************************add sub op**********************
wire [31:0] BIT_M,XOR_M;
wire ADD_carry,ADD_OverFlow;
wire [31:0] ADD_result;

assign BIT_M={32{SUBctr}}; //加法为0 减法为1
assign XOR_M=BIT_M^ALU_DB; //加法操作数不变  减法相当于把数字取反

Adder Adder(.A(ALU_DA),
            .B(XOR_M),
			.Cin(SUBctr),
			.ALU_CTL(ALU_CTL),
			.ADD_carry(ADD_carry),
			.ADD_OverFlow(ADD_OverFlow),
			.ADD_zero(ALU_ZERO),
			.ADD_result(ADD_result));

assign ALU_OverFlow = ADD_OverFlow & Ovctr;

//********************************************************
//**************************slt op************************
wire [31:0] SLT_result;
wire LESS_M1,LESS_M2,LESS_S,SLT_M;

assign LESS_M1 = ADD_carry ^ SUBctr;  //无符号 0  ---  加法无进位 减法无借位  1 -- 加法有进位 减法有借位   r1《r2==1
assign LESS_M2 = ADD_OverFlow ^ ADD_result[31];  //有符号da>db = 0 ^ 0 = 0  da<db = 1 ^ 0 = 1 
assign LESS_S = (SIGctr==1'b0)?LESS_M1:LESS_M2;  //SIGctr判断小于置一类型0-无符号 1-有符号
assign SLT_result = (LESS_S)?32'h00000001:32'h00000000;

//********************************************************
//**************************ALU result********************
always @(*) 
begin
  case(Opctr)
     2'b00:ALU_DC<=ADD_result;
     2'b01:ALU_DC<=logic_result;
     2'b10:ALU_DC<=SLT_result;
     2'b11:ALU_DC<=shift_result; 
  endcase
end

endmodule






