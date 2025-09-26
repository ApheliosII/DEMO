#include<iostream>
using namespace std;

int main()
{
	//加减乘除运算
	int a1 = 10;
	int b1 = 3;

	cout << a1 + b1 << endl;
	cout << a1 - b1 << endl;
	cout << a1 * b1 << endl;
	cout << a1 / b1 << endl; //3 两个整数相除，结果仍然是整数，将小数部分去除

	int a2 = 10;
	int b2 = 20;

	cout << a2 / b2 << endl; //0 两个整数相除，结果为0.5，返回0

	int a3 = 10;
	int b3 = 0;

	// cout << a3 / b3 << endl; //错误！除数不能为0

	//两小数可以相除 
	double d1 = 0.5;
	double d2 = 0.22;
	cout << d1 / d2 << endl; //运算结果也可以是小数, 6个有效数字

	system("pause");

	return 0;
}