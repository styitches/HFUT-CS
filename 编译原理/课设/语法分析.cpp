#include "data.h"

/*
○1  标识符：1-id
○2  整数：2
○3  小数：3
○4  保留字：41-program 42-if 43-else 44-while 45-integer 46-float 47-input 48-output
○5  单运算符：  51-＋ 52-－ 53-*  54-/  55-=  56-<  57->
○6  双运算符：  61-<=  62->=  63-<>  64-==
○7  布尔运算符：71-and  72-or
○8  界符：81-{  82-}  83-(  84-)  85-,  86-;
*/

//1.	<程序>->program  id  <语句块>
void program()
{
	if (Next.type == 41) // 41-program
	{
		Next = getNextToken();
		if (Next.type == 1) // 1-id
		{
			Next = getNextToken();
			Statementblock();//语句块
		}
		else
		{
			cout << "Line:" << row << "  ";
			cout << "Wrong in program! There should be a name for the function!" << endl;
			wrong = 1;
			exit(0);
		}
	}
	else
	{
		cout << "Line:" << row << "  ";
		cout << "Wrong in program! There should begin with keyword “program”!" << endl;
		wrong = 1;
		exit(0);
	}
}
//2.	<语句块>->  {  语句  [ 语句 ]  }
void Statementblock()
{
	if (Next.type == 81) // 81-{
	{
		Next = getNextToken();
		Statement(); // 语句
		while (Next.type == 1 || Next.type == 42 || Next.type == 44 || Next.type == 45 || Next.type == 46 || Next.type == 47 || Next.type == 48)
		{
			Statement(); // 语句
		}
		if (Next.type == 82) // 82-}
		{
			Next = getNextToken();
		}
		else
		{
			cout << "Line:" << row << "  ";
			cout << "Loose a }." << endl;
			wrong = 1;
		}
	}
	else
	{
		cout << "Line:" << row << "  ";
		cout << "Statementblock should begin with a {!\n";
		wrong = 1;
	}
}
//3.	<语句>-><分支语句>|<赋值语句>|<循环语句>|<输入语句>|<输出语句>|<变量定义语句>
void Statement()
{
	bool flag;
	if (Next.type == 45 || Next.type == 46) // 45-integer 46-float
	{
		Vardefstatement(); // 变量定义语句
	}
	else if (Next.type == 1) // 1-id
	{
		flag = Check(Next.varname, 0);
		if (flag == 0)
		{
			cout << "Line:" << row << "  ";
			cout << "The var '" << Next.varname << "' haven't defined." << endl;
			wrong = 1;
		}
		Assignstatement(); // 赋值语句
	}
	else if (Next.type == 47) // 47-input
	{
		Inputstatement(); // 输入语句
	}
	else if (Next.type == 48) // 48-output
	{
		Outputstatement(); // 输出语句
	}
	else if (Next.type == 42) // 42-if 43-else
	{
		Branchstatement(); // 分支语句
	}
	else if (Next.type == 44) // 44-while
	{
		Loopstatement(); // 循环语句
	}
	else
	{
		cout << "Line:" << row << "  ";
		cout << "Wrong!" << endl;
		wrong = 1;
	}
}
//4.	<变量定义语句>-> <数据类型>  id  [  ,  id ] ；
void Vardefstatement()
{
	bool flag;
	flag = Datatype(); // 数据类型
	if (Next.type == 1) // 1-id
	{
		AddSymbol(Next.varname, flag);
		Next = getNextToken();
		while (Next.type == 85) // 85-,
		{
			Next = getNextToken();
			if (Next.type == 1) // 1-id
			{
				AddSymbol(Next.varname, flag);
				Next = getNextToken();
			}
			else
			{
				cout << "Line:" << row << "  ";
				cout << "There should be an varname." << endl;
				wrong = 1;
			}
		}
		if (Next.type == 86) // 86-;
		{
			Next = getNextToken();
		}
		else
		{
			cout << "Line:" << row << "  ";
			cout << "Loose a ;" << endl;
			wrong = 1;
		}
	}
	else
	{
		cout << "Line:" << row << "  ";
		cout << "Wrong!" << endl;
		wrong = 1;
	}

}
//5.	<数据类型>-> integer | float
bool Datatype()
{
	// 45-integer 46-float
	if (Next.type == 45)
	{
		Next = getNextToken();
		return 1;
	}
	else if (Next.type == 46)
	{
		Next = getNextToken();
		return 0;
	}
	else
	{
		cout << "Line:" << row << "  ";
		cout << "Wrong Datatype." << endl;
		wrong = 1;
		exit(0);
	}
}
//6.	<输入语句>-> input  id  [  ,  id ] ；
void Inputstatement()
{
	bool flag;
	Next = getNextToken();
	if (Next.type == 1) // 1=id
	{
		flag = Check(Next.varname, 0);
		if (flag == 0)
		{
			cout << "Line:" << row << "  ";
			cout << "The var '" << Next.varname << "' haven't defined." << endl;
			wrong = 1;
		}
		Next = getNextToken();
		while (Next.type == 85) // 85-,   id,
		{
			Next = getNextToken();
			if (Next.type == 1) // 1-id   id,id
			{
				flag = Check(Next.varname, 0);
				if (flag == 0)
				{
					cout << "Line:" << row << "  ";
					cout << "The var '" << Next.varname << "' haven't defined." << endl;
					wrong = 1;
				}
				Next = getNextToken();
			}
			else  //id, 
			{
				cout << "Line:" << row << "  ";
				cout << "There should be an varname." << endl;
				wrong = 1;
			}
		}
		if (Next.type == 86) // 86-; id;
		{
			Next = getNextToken();
		}
		else
		{
			cout << "Line:" << row << "  ";
			cout << "Loose a ;" << endl;
			wrong = 1;
		}
	}
	else
	{
		cout << "Line:" << row << "  ";
		cout << "Wrong!" << endl;
		wrong = 1;
	}
}
//7.	<输出语句>-> output  <表达式>  [  ,  <表达式> ] ；
void Outputstatement()
{
	Next = getNextToken();
	expression(); // 表达式
	while (Next.type == 85) // 85-,
	{
		Next = getNextToken();
		expression(); // 表达式
	}
	if (Next.type == 86) // 86-;
	{
		Next = getNextToken();
	}
	else
	{
		cout << "Line:" << row << "  ";
		cout << "Loose a ;" << endl;
		wrong = 1;
	}
}
//8.	<赋值语句>-> id  =  <表达式> ；
void Assignstatement()
{
	Push(&Var, Next.varname);
	Next = getNextToken();
	if (Next.type == 55) // 55-=
	{
		Push(&Sign, "=");
		Next = getNextToken();
		expression();
		if (Next.type == 86) // 86-;
		{
			Next = getNextToken();
		}
		else
		{
			cout << "Line:" << row << "  ";
			cout << "Loose a ; ." << endl;
			wrong = 1;
		}
	}
	Pop(&Sign, &op1);
	Pop(&Var, &op2);
	Pop(&Var, &op4);
	strcpy(op3, "-");
	MakeFour(op1, op2, op3, op4);
	sysnum++;
}
//9.	<分支语句>-> if <布尔表达式> <语句块> { else <语句块> }
void Branchstatement()
{
	Next = getNextToken();
	Boolexpression();
	grade++;
	Statementblock();
	grade--;
	if (Next.type == 43) // 43-else
	{
		cp_Ture->x = cp_FourList;
		cp_Ture->grade = grade;
		Ture = (Link*)malloc(sizeof(Link));
		Ture->Next = cp_Ture;
		cp_Ture = Ture;
		MakeFour("J", "-", "-", "0");//cout<<grade<<"/"<<cp_Ture->Next->x->num<<endl;
		sysnum++;
		Back(False);
		Next = getNextToken();
		grade++;
		Statementblock();
		grade--;
		Back(Ture);
	}
	Back(False);
}
//10.	<循环语句>-> while  <布尔表达式> <语句块>
void Loopstatement()
{
	char Return[10];
	Next = getNextToken();
	itoa(sysnum, Return, 10);
	Boolexpression();
	grade++;
	Statementblock();
	grade--;
	MakeFour("J", "-", "-", Return);
	sysnum++;
	Back(False);
}
//11.	<表达式>-> <项> [  +|－ <项> ]
void expression()
{
	item(); //项()必须保证函数结束时下一个项已取出来了
	while (Next.type == 51 || Next.type == 52) // 51-＋ 52-－
	{
		if (Next.type == 51) { Push(&Sign, "+"); }
		else { Push(&Sign, "-"); }
		Next = getNextToken();
		item();
		Pop(&Sign, &op1);
		Pop(&Var, &op3);
		Pop(&Var, &op2);
		op4[0] = 'T';
		char* cop4 = op4 + 1;
		itoa(var_count, cop4, 10);
		var_count++;
		wrong = Push(&Var, op4);
		MakeFour(op1, op2, op3, op4);
		sysnum++;
	}
}
//12.	<项>-> <因子> [ *|/  <因子> ]
void item()
{
	factor();
	while (Next.type == 53 || Next.type == 54) // 53-*  54-/
	{
		if (Next.type == 53) { wrong = Push(&Sign, "*"); }
		else { wrong = Push(&Sign, "/"); }
		Next = getNextToken();
		factor();
		Pop(&Sign, &op1);
		Pop(&Var, &op3);
		Pop(&Var, &op2);
		op4[0] = 'T';
		char* cop4 = op4 + 1;
		itoa(var_count, cop4, 10);
		var_count++;
		wrong = Push(&Var, op4);
		MakeFour(op1, op2, op3, op4);
		sysnum++;
	}
}
//13.	<因子>-> id | con | deci |  (  <表达式>  )
void factor()
{
	bool flag;
	if (Next.type == 1) // 1-id
	{
		Push(&Var, Next.varname);
		flag = Check(Next.varname, 0);
		if (flag == 0)
		{
			cout << "Line:" << row << "  ";
			cout << "The var '" << Next.varname << "' haven't defined." << endl;
			wrong = 1;
		}
		Next = getNextToken();
	}
	else if (Next.type == 2) // 2-整数
	{
		char temp[10];
		itoa(Next.integer, temp, 10);  //数字转换成字符串
		Push(&Var, temp);
		Next = getNextToken();
	}
	else if (Next.type == 3) // 3-小数
	{
		char temp[10];
		itoa(Next.decimal, temp, 10);
		wrong = Push(&Var, temp);
		Next = getNextToken();
	}
	else if (Next.type == 83) // 83-(  84-)
	{
		Next = getNextToken();
		expression();
		if (Next.type == 84)
		{
			Next = getNextToken();
		}
		else
		{
			cout << "Line:" << row << "  ";
			cout << "loose an )" << endl;
			wrong = 1;
		}
	}
	else
	{
		cout << "Line:" << row << "  ";
		cout << "wrong\n" << endl;
		wrong = 1;
	}
}
//14. <布尔表达式>-> <关系表达式> [ and | or  <布尔表达式> ]
void Boolexpression()
{
	bool flag = 1;
	Relatexpression();
	while (Next.type == 71 || Next.type == 72) // 71-and  72-or
	{
		if (Next.type == 72)//or
		{
			Back(False);
		}
		else
		{
			Back(Ture);
		}
		Next = getNextToken();
		Relatexpression();
		flag = 0;
	}
	Back(Ture);
}
//15. <关系表达式>-> <表达式> <关系> <表达式>
void Relatexpression()
{
	expression();
	relation();
	expression();

	Pop(&Sign, &op1);
	Pop(&Var, &op3);
	Pop(&Var, &op2);

	op1[1] = op1[0];
	op1[0] = 'J';
	op1[2] = '\0';

	cp_Ture->x = cp_FourList;
	cp_Ture->grade = grade;
	Ture = (Link*)malloc(sizeof(Link));
	Ture->Next = cp_Ture;
	cp_Ture = Ture;

	MakeFour(op1, op2, op3, "0");//cout<<grade<<"/"<<cp_Ture->Next->x->num<<endl;
	sysnum++;

	cp_False->x = cp_FourList;
	cp_False->grade = grade;
	False = (Link*)malloc(sizeof(Link));
	False->Next = cp_False;
	cp_False = False;
	op1[1] = '\0';

	MakeFour(op1, "-", "-", "0");//cout<<grade<<"/"<<cp_Ture->Next->x->num<<endl;
	sysnum++;
}
//16. <关系>-> < | <= | > | >= | == | <>
void relation()
{
	if (Next.type == 56) // 56-<
	{
		Next = getNextToken();
		wrong = Push(&Sign, "<");
	}
	else if (Next.type == 61) // 61-<=
	{
		Next = getNextToken();
		wrong = Push(&Sign, "<=");
	}
	else if (Next.type == 57) // 57->
	{
		Next = getNextToken();
		wrong = Push(&Sign, ">");
	}
	else if (Next.type == 62) // 62->=
	{
		Next = getNextToken();
		wrong = Push(&Sign, ">=");
	}
	else if (Next.type == 64) // 64-==
	{
		Next = getNextToken();
		wrong = Push(&Sign, "==");
	}
	else if (Next.type == 63) // 63-<>
	{
		Next = getNextToken();
		wrong = Push(&Sign, "<>");
	}
	else
	{
		cout << "Line:" << row << "  ";
		cout << "There should be an relation" << endl;
		wrong = 1;
	}
}