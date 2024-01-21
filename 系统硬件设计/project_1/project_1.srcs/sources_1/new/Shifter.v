//********************************************************
//*************************shifter************************
module Shifter(input [31:0] ALU_DA,
               input [4:0] ALU_SHIFT,
			   input [1:0] Shiftctr,
			   output reg [31:0] shift_result);
			   
    reg[31:0] SLL_M,SRL_M,SRA_M;
    always@(*)//SRLÂß¼­ÓÒÒÆ
    begin
      case(ALU_SHIFT)
         5'b00000:SRL_M[31:0]=ALU_DA[31:0]; 
         5'b00001:SRL_M[31:0]={1'd0 ,ALU_DA[31:1]};
         5'b00010:SRL_M[31:0]={2'd0 ,ALU_DA[31:2]};
         5'b00011:SRL_M[31:0]={3'd0 ,ALU_DA[31:3]}; 		 
         5'b00100:SRL_M[31:0]={4'd0 ,ALU_DA[31:4]}; 	
		 5'b00101:SRL_M[31:0]={5'd0 ,ALU_DA[31:5]}; 	
		 5'b00110:SRL_M[31:0]={6'd0 ,ALU_DA[31:6]}; 	
		 5'b00111:SRL_M[31:0]={7'd0 ,ALU_DA[31:7]}; 	
		 5'b01000:SRL_M[31:0]={8'd0 ,ALU_DA[31:8]}; 	
		 5'b01001:SRL_M[31:0]={9'd0 ,ALU_DA[31:9]}; 	
		 5'b01010:SRL_M[31:0]={10'd0,ALU_DA[31:10]}; 	
		 5'b01011:SRL_M[31:0]={11'd0,ALU_DA[31:11]}; 	
		 5'b01100:SRL_M[31:0]={12'd0,ALU_DA[31:12]}; 	
		 5'b01101:SRL_M[31:0]={13'd0,ALU_DA[31:13]}; 	
		 5'b01110:SRL_M[31:0]={14'd0,ALU_DA[31:14]}; 	
		 5'b01111:SRL_M[31:0]={15'd0,ALU_DA[31:15]}; 	
		 5'b10000:SRL_M[31:0]={16'd0,ALU_DA[31:16]}; 	
		 5'b10001:SRL_M[31:0]={17'd0,ALU_DA[31:17]}; 	
		 5'b10010:SRL_M[31:0]={18'd0,ALU_DA[31:18]}; 	
		 5'b10011:SRL_M[31:0]={19'd0,ALU_DA[31:19]}; 	
		 5'b10100:SRL_M[31:0]={20'd0,ALU_DA[31:20]}; 	
		 5'b10101:SRL_M[31:0]={21'd0,ALU_DA[31:21]}; 	
		 5'b10110:SRL_M[31:0]={22'd0,ALU_DA[31:22]}; 	
		 5'b10111:SRL_M[31:0]={23'd0,ALU_DA[31:23]}; 	
		 5'b11000:SRL_M[31:0]={24'd0,ALU_DA[31:24]}; 	
		 5'b11001:SRL_M[31:0]={25'd0,ALU_DA[31:25]}; 
		 5'b11010:SRL_M[31:0]={26'd0,ALU_DA[31:26]}; 
		 5'b11011:SRL_M[31:0]={27'd0,ALU_DA[31:27]}; 
		 5'b11100:SRL_M[31:0]={28'd0,ALU_DA[31:28]}; 
		 5'b11101:SRL_M[31:0]={29'd0,ALU_DA[31:29]}; 
		 5'b11110:SRL_M[31:0]={30'd0,ALU_DA[31:30]};  
         5'b11111:SRL_M[31:0]={31'd0,ALU_DA[31]}; 
         default: SRL_M[31:0]=ALU_DA[31:0]; 
      endcase
    end
    
    always@(*) //SLLÂß¼­×óÒÆ
    begin
      case(ALU_SHIFT)
         5'b00000:SLL_M[31:0]=ALU_DA[31:0]; 
         5'b00001:SLL_M[31:0]={ALU_DA[30:0],1'd0};
         5'b00010:SLL_M[31:0]={ALU_DA[29:0],2'd0}; 
         5'b00011:SLL_M[31:0]={ALU_DA[28:0],3'd0};
		 5'b00100:SLL_M[31:0]={ALU_DA[27:0],4'd0};
		 5'b00101:SLL_M[31:0]={ALU_DA[26:0],5'd0};
		 5'b00110:SLL_M[31:0]={ALU_DA[25:0],6'd0};
		 5'b00111:SLL_M[31:0]={ALU_DA[24:0],7'd0};
		 5'b01000:SLL_M[31:0]={ALU_DA[23:0],8'd0};
		 5'b01001:SLL_M[31:0]={ALU_DA[22:0],9'd0};
		 5'b01010:SLL_M[31:0]={ALU_DA[21:0],10'd0};
		 5'b01011:SLL_M[31:0]={ALU_DA[20:0],11'd0};
		 5'b01100:SLL_M[31:0]={ALU_DA[19:0],12'd0};
		 5'b01101:SLL_M[31:0]={ALU_DA[18:0],13'd0};
		 5'b01110:SLL_M[31:0]={ALU_DA[17:0],14'd0};
		 5'b01111:SLL_M[31:0]={ALU_DA[16:0],15'd0};
		 5'b10000:SLL_M[31:0]={ALU_DA[15:0],16'd0};
		 5'b10001:SLL_M[31:0]={ALU_DA[14:0],17'd0};
		 5'b10010:SLL_M[31:0]={ALU_DA[13:0],18'd0};
		 5'b10011:SLL_M[31:0]={ALU_DA[12:0],19'd0};
		 5'b10100:SLL_M[31:0]={ALU_DA[11:0],20'd0};
		 5'b10101:SLL_M[31:0]={ALU_DA[10:0],21'd0};
		 5'b10110:SLL_M[31:0]={ALU_DA[9:0] ,22'd0};
		 5'b10111:SLL_M[31:0]={ALU_DA[8:0] ,23'd0};
		 5'b11000:SLL_M[31:0]={ALU_DA[7:0] ,24'd0};
		 5'b11001:SLL_M[31:0]={ALU_DA[6:0] ,25'd0};
		 5'b11010:SLL_M[31:0]={ALU_DA[5:0] ,26'd0};
		 5'b11011:SLL_M[31:0]={ALU_DA[4:0] ,27'd0};
		 5'b11100:SLL_M[31:0]={ALU_DA[3:0] ,28'd0};
		 5'b11101:SLL_M[31:0]={ALU_DA[2:0] ,29'd0};
		 5'b11110:SLL_M[31:0]={ALU_DA[1:0] ,30'd0};
		 5'b11111:SLL_M[31:0]={ALU_DA[0],31'd0}; 
         default: SLL_M[31:0]=ALU_DA[31:0]; 
      endcase
    end
    
    always@(*) //SRAËãÊýÓÒÒÆ
    begin
      case(ALU_SHIFT)
         5'b00000:SRA_M[31:0]=ALU_DA[31:0]; 
         5'b00001:SRA_M[31:0]={{1{ALU_DA[31]}},ALU_DA[31:1]};
         5'b00010:SRA_M[31:0]={{2{ALU_DA[31]}},ALU_DA[31:2]}; 
         5'b00011:SRA_M[31:0]={{3{ALU_DA[31]}},ALU_DA[31:3]};
		 5'b00100:SRA_M[31:0]={{4{ALU_DA[31]}},ALU_DA[31:4]}; 
		 5'b00101:SRA_M[31:0]={{5{ALU_DA[31]}},ALU_DA[31:5]};
		 5'b00110:SRA_M[31:0]={{6{ALU_DA[31]}},ALU_DA[31:6]};
		 5'b00111:SRA_M[31:0]={{7{ALU_DA[31]}},ALU_DA[31:7]};
		 5'b01000:SRA_M[31:0]={{8{ALU_DA[31]}},ALU_DA[31:8]};
		 5'b01001:SRA_M[31:0]={{9{ALU_DA[31]}},ALU_DA[31:9]};
		 5'b01010:SRA_M[31:0]={{10{ALU_DA[31]}},ALU_DA[31:10]};
		 5'b01011:SRA_M[31:0]={{11{ALU_DA[31]}},ALU_DA[31:11]};
		 5'b01100:SRA_M[31:0]={{12{ALU_DA[31]}},ALU_DA[31:12]};
		 5'b01101:SRA_M[31:0]={{13{ALU_DA[31]}},ALU_DA[31:13]};
		 5'b01110:SRA_M[31:0]={{14{ALU_DA[31]}},ALU_DA[31:14]};
		 5'b01111:SRA_M[31:0]={{15{ALU_DA[31]}},ALU_DA[31:15]};
		 5'b10000:SRA_M[31:0]={{16{ALU_DA[31]}},ALU_DA[31:16]};
		 5'b10001:SRA_M[31:0]={{17{ALU_DA[31]}},ALU_DA[31:17]};
		 5'b10010:SRA_M[31:0]={{18{ALU_DA[31]}},ALU_DA[31:18]};
		 5'b10011:SRA_M[31:0]={{19{ALU_DA[31]}},ALU_DA[31:19]};
		 5'b10100:SRA_M[31:0]={{20{ALU_DA[31]}},ALU_DA[31:20]};
		 5'b10101:SRA_M[31:0]={{21{ALU_DA[31]}},ALU_DA[31:21]};
		 5'b10110:SRA_M[31:0]={{22{ALU_DA[31]}},ALU_DA[31:22]};
		 5'b10111:SRA_M[31:0]={{23{ALU_DA[31]}},ALU_DA[31:23]};
		 5'b11000:SRA_M[31:0]={{24{ALU_DA[31]}},ALU_DA[31:24]};
		 5'b11001:SRA_M[31:0]={{25{ALU_DA[31]}},ALU_DA[31:25]};
		 5'b11010:SRA_M[31:0]={{26{ALU_DA[31]}},ALU_DA[31:26]};
		 5'b11011:SRA_M[31:0]={{27{ALU_DA[31]}},ALU_DA[31:27]};
		 5'b11100:SRA_M[31:0]={{28{ALU_DA[31]}},ALU_DA[31:28]};
		 5'b11101:SRA_M[31:0]={{29{ALU_DA[31]}},ALU_DA[31:29]};
		 5'b11110:SRA_M[31:0]={{30{ALU_DA[31]}},ALU_DA[31:30]};
		 5'b11111:SRA_M[31:0]={{31{ALU_DA[31]}},ALU_DA[31]}; 
         default: SRA_M[31:0]=ALU_DA[31:0]; 
      endcase
    end
    
    always@(*) //SHIFT
    begin
      case(Shiftctr)
         2'b00:shift_result=SLL_M;
         2'b01:shift_result=SRL_M;
         2'b10:shift_result=SRA_M;
         default: shift_result=ALU_DA; 
      endcase
    end
endmodule