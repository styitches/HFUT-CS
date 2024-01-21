#include "data.h"

bool AddSymbol(char* varname, bool type)
{
	bool flag;
	flag = Check(varname, type);
	if (flag == 1)
	{
		cout << "Line:" << row << "  ";
		cout << "Repeat defination : " << varname << endl;
		wrong = 1;
		return 0;
	}
	strcpy(cp_Sym->varname, varname);
	cp_Sym->type = type;
	cp_Sym->Next = (Symbol*)malloc(sizeof(Symbol));
	cp_Sym = cp_Sym->Next;
	cp_Sym->Next = NULL;
	return 1;
}
void PrintSignForm()
{
	Symbol* x = Sym;
	for (; x->Next;)
	{
		cout << x->varname << "  " << x->type << endl;
		x = x->Next;
	}
}
bool Check(char* varname, bool type)  //检查是否被定义过
{
	int flag;
	Symbol* x = Sym;
	while (x)
	{
		flag = strcmp(varname, x->varname);
		if (flag == 0)
		{
			return 1;
		}
		x = x->Next;
	}
	return 0;
}

void MakeFour(char* op1, char* op2, char* op3, char* op4)
{
	strcpy(cp_FourList->op1, op1);
	strcpy(cp_FourList->op2, op2);
	strcpy(cp_FourList->op3, op3);
	strcpy(cp_FourList->op4, op4);
	cp_FourList->num = sysnum;
	cp_FourList->Next = (Four*)malloc(sizeof(Four));
	cp_FourList = cp_FourList->Next;
	cp_FourList->Next = NULL;
}

void PrintFour()
{
	Four* x = &FourList;
	for (int i = 0; x->Next; i++)
	{
		fprintf(fw, "%2d: (%3s, %3s, %3s, %3s)\n",
			x->num, x->op1, x->op2, x->op3, x->op4);
		printf("%2d: (%3s, %3s, %3s, %3s)\n",
			x->num, x->op1, x->op2, x->op3, x->op4);
		x = x->Next;
	}
}

void Back(Link* TF)   //回填跳转语句的目标地址
{
	Link* cp_TF = TF->Next;
	char x[10];
	itoa(sysnum, x, 10);
	int t = grade;
	if (cp_TF)
	{
		while (cp_TF->grade == t)
		{
			strcpy(cp_TF->x->op4, x);
			cp_TF = cp_TF->Next;
			if (cp_TF == NULL)break;
		}
	}
	TF->Next = cp_TF;
}
