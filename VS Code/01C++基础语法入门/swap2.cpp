//源文件 包含swap2.h
#include"swap2.h"

//函数的定义
void swap2(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;

	cout << "a =" << a << endl;
	cout << "b =" << b << endl;
}