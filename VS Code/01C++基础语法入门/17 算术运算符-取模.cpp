#include<iostream>
using namespace std;

int main()
{
	//取模运算本质求余数
	int a1 = 10;
	int b1 = -3;

	cout << a1 % b1 << endl; //1 符号取决于a1

	int a2 = 10;
	int b2 = 20;

	cout << a2 % b2 << endl; //10

	int a3 = 10;
	int b3 = 0;
	//取模运算除数不能为0
	// cout << a3 % b3 << endl; 

	//两个小数不能取模运算
	double d1 = 3.14;
	double d2 = 1.1;
	//cout << d1 % d2 << endl;

	system("pause");

	return 0;
}