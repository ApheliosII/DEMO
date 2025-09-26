#include <iostream>
using namespace std;

// 函数默认参数

// 如果我们自己传入数据，就用自己的数据，如果没有，就用默认值
// 语法：返回值类型 函数名 （形参 = 默认值）{}
int func(int a, int b = 20, int c = 30)
{
	return a + b + c;
}

// 注意
// 1. 如果某个位置参数有默认值，那么从这个位置往后，从左向右，必须都要有默认值
// 以下代码错误：
// int func2(int a = 10, int b, int c )
//{
//	return a + b + c;
// }

// 2. 如果函数声明有默认值，函数实现的时候就不能有默认参数
// 声明和实现只能一个有默认参数
int func2(int a = 10, int b = 10);

/* int func2(int a, int b)
{
	return a + b;
} */

int main()
{
	cout << func(10, 30) << endl;

	cout << func2() << endl;

	system("pause");

	return 0;
}

int func2(int a, int b)
{
	return a + b;
}
//
// 输出：
// 70
// 20
