#include <iostream>
using namespace std;

int And(int a,int b) {
    int res = a * b;
    return res;
}

int Or (int a, int b) {
    int res = a + b;
    res = res > 0 ? 1 : res;
    return res;
}
int Not(int a) {
    int res = a == 1 ? 0 : 1;
    return res;
}

int If(int a, int b) { //条件
    int res = (b == 1 && a == 0) ? 0 : 1;
    return res;
}

int Iif(int a, int b) {//双条件
    int res = (b == a) ? 1 : 0;
    return res;
}
int main() {
    int a, b, c;
    cout << "请输入两个命题变元的真值：" << endl;
    cin >> a >> b;
    cout << "合取运算结果：" << And(a, b) << endl;
    cout << "析取运算结果：" << Or(a, b) <<endl;
    cout << "单条件运算结果：" << If(a, b) <<endl;
    cout << "双条件运算结果：" << Iif(a, b) <<endl;

    cout << "请输入取非命题变元的真值：" << endl;
    cin >> c;
    cout << "取非运算结果：" << Not(c) << endl;
}
