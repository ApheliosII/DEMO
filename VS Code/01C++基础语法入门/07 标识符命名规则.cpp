#include<iostream>
using namespace std;

int main()
{
	//1.不能是关键字
	//int int = 10;

	//2.字母数字下划线构成
	int abc = 10;
	int _abc = 20;
	int _123abc = 30;
	
	//3.第一个不能是数字
	//int 123abc = 40;

	//4.区分大小写
	int aaa = 100;
	//cout <<AAA << endl;

	//建议:见名知意
	int num1 = 20;
	int num2 = 30;
	int sum = num1 + num2;
	cout << sum  << endl;

	system("pause");

	return 0;
}