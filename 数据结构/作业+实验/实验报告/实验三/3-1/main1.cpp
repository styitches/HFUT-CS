#include<stack>
#include<iostream>
#include<string>
using namespace std;


bool isnumber(char x)//扫描数字的函数
{
    if (x >= '0' && x <= '9')
        return true;
    return false;
}

int priority(char x) {//判断运算符优先级的函数
    if (x == '+' || x == '-')
        return 0;
    else if (x == '*' || x == '/')
        return 1;
    else if (x == '(' || x == ')')
        return -1;
    else if (x == '#')
        return -2;
}

int calculate(string s)//计算
{
    stack<int> number;//用于寄存操作数或运算结果
    stack<char> operate;//用于寄存运算符
    char top;
    int a, b;

    for (int i = 0; i < s.size(); ++i)
    {
        if (isnumber(s[i]))
        {
            int Count = 0;
            string temp;//temp用于存放数字字符串，即计算数

            temp += s[i];
            while (isnumber(s[++i]))
                temp += s[i];
            for (int j = 0; j < temp.size(); ++j)
            {
                Count = Count * 10 + temp[j] - 48;//数字字符的ASCII码与数字自身相差48
            }
            number.push(Count);
            temp.clear();
        }//将字符数字转换成整型数字

        if (!isnumber(s[i]))
        {
            if (operate.empty())
            {
                operate.push(s[i]);
            }//入栈第一个符号'#'

            else
            {
                top = operate.top();

                if (priority(s[i]) > priority(top) || s[i] == '(')
                {
                    operate.push(s[i]);
                }//入栈高优先级的运算符
                else {
                    while (priority(s[i]) <= priority(top))
                    {
                        if (top == '#' && s[i] == '#')
                        {
                            int answer;

                            operate.pop();
                            answer = number.top();
                            cout << "\n答案是：" << answer << endl;
                            number.pop();
                            return 0;
                        }//当运算符实现完全后，只剩下'#'

                        else if (top == '(' && s[i] == ')')
                        {
                            ++i;
                        }//当左右括号相遇时，跳过右括号，删除左括号

                        else
                        {
                            a = number.top();
                            number.pop();
                            b = number.top();
                            number.pop();
                        }

                        if (top == '+')
                        {
                            b += a;
                            number.push(b);
                        }

                        else if (top == '-')
                        {
                            b -= a;
                            number.push(b);
                        }

                        else if (top == '*')
                        {
                            b *= a;
                            number.push(b);
                        }

                        else if (top == '/')
                        {
                            b /= a;
                            number.push(b);
                        }

                        operate.pop();
                        top = operate.top();;//取前一个运算符，用于与现在扫描的运算符进行比较
                    }//将优先级高的运算符实现计算
                    operate.push(s[i]);//用于当top=='#'时，将最后一个运算符入栈
                }
            }
        }//扫描运算符，并判断优先级，以及运算
    }//主循环
}

int main()
{
    string s;
    cout << "输入一个用'#'开头和结尾的表达式：" << endl;
    cin >> s;
    calculate(s);
    cin.get();
    return 0;
}
