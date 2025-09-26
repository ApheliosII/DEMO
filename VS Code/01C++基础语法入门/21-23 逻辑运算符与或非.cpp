#include<iostream>
using namespace std;

int main()
{
	//逻辑运算符 非 ！
	//C++中除了0都为真
	int a = 10;
	int b = 10;

	cout << !a << endl; // 0

	cout << !!a << endl; // 1
	

	//逻辑运算符 与 &&
	 a = 10;
	 b = 10;
	
	cout << (a && b) << endl;// 1

	a = 0;
	b = 10;

	cout << (a && b) << endl; // 0

	a = 0;
	b = 0;

	cout << (a && b) << endl; // 0
	//逻辑与：同真为真，其余为假


	//逻辑运算符 或 ||
	a = 10;
	b = 10;

	cout << (a || b) << endl; // 1

	a = 0;
	b = 10;

	cout << (a || b) << endl; // 1

	a = 0;
	b = 0;

	cout << (a || b) << endl; // 0
	//逻辑或：同假为假，其余为真

	system("pause");

	return 0;
}