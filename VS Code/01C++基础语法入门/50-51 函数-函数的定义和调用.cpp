#include<iostream>
using namespace std;

//函数定义

//返回值类型 函数名 (参数列表) { 函数体语句 return表达式 }

//定义一个加法函数，实现两个整型数相加,返回结果
int add(int num1, int num2)  //num1和num2称为形式参数,即形参
{
	int sum = num1 + num2;
	return sum;
}

int main()
{
	//main函数中调用add函数
	int a = 10;
	int b = 20;

	//函数调用语法: 函数名称 (参数)
	//调用函数时，实参的值传给形参
	int c = add(a, b);  //a和b称为实际参数,即实参

	cout << "c = " << c << endl;

	system("pause");

	return 0;
}