#include<iostream>
using namespace std;

int main()
{
	//1、前置递增
	int a = 10;
	++a; //让变量+1
	cout << "a = " << a << endl; //输出11

	//2、后置递增
	int b = 10;
	b++; //让变量+1
	cout << "b = " << b << endl; //输出11

	//3、区别
	//前置递增，先让变量+1，再进行表达式运算
	int a2 = 10;
	int b2 = ++a2 * 10;
	cout << "a2 = " << a2 << endl; //输出11
	cout << "b2 = " << b2 << endl; //输出110

	//后置递增，先进行表达式运算，再让变量+1
	int a3 = 10;
	int b3 = a3++ * 10;
	cout << "a3 = " << a3 << endl; //输出11
	cout << "b3 = " << b3 << endl; //输出100

	cout << " hello world" << endl;

	//前置递减，先让变量-1，再进行表达式运算
	int c = 10;
	int d = --c * 10;
	cout << "c = " << c << endl; //输出9
	cout << "d = " << d << endl; //输出90

	//后置递减，先进行表达式运算，再让变量-1
	int e = 10;
	int f = e-- * 10;
	cout << "e = " << e << endl; //输出9
	cout << "f = " << f << endl; //输出100

	system("pause");

	return 0;
}
