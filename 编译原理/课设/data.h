#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
/*
○1  标识符：首字符为字母或'_'，其后由字母、数字或'_'组成、长度不超过8个字符；
○2  整数：
○3  小数：
○4  保留字：program  if  else  while  integer  float   input   output
○5  单运算符：  ＋ － *  /  =  <  >
○6  双运算符：  <=  >=  <>  ==
○7  布尔运算符：and  or
○8  界符：      {   }  (  )  ；  ，
*/

typedef struct SNode
{
	char data[10];
	SNode* Next;
}SNode, * StackPtr;

typedef struct
{
	StackPtr top;
	StackPtr base;
}LinkStack;

struct Token
{
	int type;//单词类型:  1:整数  2:变量  3:(   4:)  5:+  6: -  7:*  8: /  -1:错误   0: 输入结束 
	int integer;//如果单词是整数,integer保存该整数之值
	float decimal;//如果单词是小数,decimal保存该整数之值
	char varname[10];//如果单词是变量,var保存变量名
	char key[10];//如果单词是关键字,key保存变量名
};

struct Symbol // 符号表
{
	bool type; //0-小数，1-整数
	char varname[10];
	int integer;
	float decimal;
	Symbol* Next;
};

struct Four //四元式
{
	int num;
	char op1[10];
	char op2[10];
	char op3[10];
	char op4[10];
	Four* Next;
};

struct Link
{
	Four* x;
	int grade;
	Link* Next;
};

extern int sysnum; //当前四元式个数
extern int wrong;  //出错 1-出错 0-未出错
extern char temp;  //
extern Token Next; //
extern FILE* fp;  //读文件指针
extern FILE* fw;  //写文件指针
extern int row;    //当前扫描行数

extern Symbol* Sym;     //变量列表首指针
extern Symbol* cp_Sym;  //变量列表动态指针

extern int var_count;    //四元式中临时变量当前个数
extern char* op1;
extern char* op2;
extern char* op3;
extern char* op4;
extern Four FourList;     //四元式列表首指针   
extern Four* cp_FourList;//四元式列表动态指针
extern Link* Ture;       //真出口
extern Link* False;      //假出口
extern Link* cp_Ture;       //真出口
extern Link* cp_False;      //假出口
extern int grade;

extern LinkStack Sign;    //变量栈
extern LinkStack Var;     //符号栈

void initial();           //初始化

Token getNextToken();     //词法分析

//以下为语法分析程序:

void program();
void Statementblock();
void Statement();
void Vardefstatement();
bool Datatype();
void Inputstatement();

void Outputstatement();
void Assignstatement();
void Branchstatement();
void Loopstatement();
void expression();

void item();
void factor();
void Boolexpression();
void Relatexpression();
void relation();

//以下为栈操作：

int InitStack(LinkStack* S);
int Push(LinkStack* S, char e[]);
int Pop(LinkStack* S, char* e[]);
int IsEmpty(LinkStack* S);

//以下为产生四元式和符号表操做

bool Check(char* varname, bool type);
bool AddSymbol(char* varname, bool type);
void PrintSignForm();
void MakeFour(char* op1, char* op2, char* op3, char* op4);
void PrintFour();
void Back(Link* TF);
