// ·本阶段主要针对C++泛型编程和STL技术做详细讲解，探讨C++更深层的使用

// 照片模板：
// PPT模板：

// 模板的特点：
// ·模板不可以直接使用，它只是一个框架
// ·模板的通用并不是万能的

/*
1.2 函数模板
·C++另一种编程思想称为泛型编程，主要利用的技术就是模板
·C++提供两种模板机制 函数模板和类模板
1.2.1函数模板语法
函数模板作用：
建立一个通用函数，其函数返回值类型和形参类型可以不具体制定，用一个虚拟的类型来代表。

语法：
template<typename T>
函数声明或定义

解释：
template --- 声明创建模板
typename --- 表面其后面的符号是一种数据类型，可以用class代替
T --- 通用的数据类型，名称可以替换，通常为大写字母
*/

#include <iostream>
using namespace std;

// 函数模板

// 交换两个整型函数
void swapInt(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

// 交换两个浮点型函数
void swapDouble(double &a, double &b)
{
	double temp = a;
	a = b;
	b = temp;
}

// 函数模板
template <typename T> // 声明一个模板，告诉编译器后面代码中紧跟着的T不要报错，T是一个通用数据类型
void mySwap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

void test01()
{
	int a = 10;
	int b = 20;
	double c = 1.1;
	double d = 2.2;

	swapInt(a, b);
	cout << "a = " << a << "\tb = " << b << endl;

	swapDouble(c, d);
	cout << "c = " << c << "\td = " << d << endl;

	// 利用函数模板交换
	// 两种方式使用函数模板

	// 1、自动类型推导
	mySwap(a, b);
	cout << "a = " << a << "\tb = " << b << endl;

	// 2、显示指定类型
	mySwap<int>(a, b);
	cout << "a = " << a << "\tb = " << b << endl;

	mySwap(c, d);
	mySwap<double>(c, d);
	cout << "c = " << c << "\td = " << d << endl;
}

int main()
{
	test01();

	system("pause");

	return 0;
}
// 总结：
// ·函数模板利用关键字template
// ·使用函数模板有两种方式：自动类型推导、显示指定类型
// ·模板的目的是为了提高复用性，将类型参数化