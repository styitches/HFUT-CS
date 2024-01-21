#include<iostream>
#include"../Graph.h";
using namespace std;
int main() {
	graph a;
	int x, y;
	a.create();
	a.Enum();
	cout << "边数为：" << a.e << endl;
	a.istree();
	cout << "请输入入口和出口。" << endl;
	cin >> x >> y;
	a.path(x, y);
	/*a.path();*/
}
