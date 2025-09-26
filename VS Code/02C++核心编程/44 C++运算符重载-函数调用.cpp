#include <iostream>
using namespace std;
// #include<string>

// ·函数调用运算符()也可以重载
// ·由于重载后使用的方式非常像函数的调用，因此称为仿函数
// ·仿函数没有固定写法，非常灵活

// STL中的函数对象也属于仿函数

// 函数调用运算符重载

class MyPrint
{
public:
	// 重载函数调用运算符
	void operator()(string test)
	{
		cout << test << endl;
	}
};

void MyPrint02(string test)
{
	cout << test << endl;
}

void test01()
{
	MyPrint myPrint;

	myPrint("hello world"); // 由于使用起来非常像函数调用，因此称为仿函数

	MyPrint02("hello world");
}

// 仿函数非常灵活，没用固定写法
// 加法类
class MyAdd
{
public:
	int operator()(int num1, int num2)
	{
		return num1 + num2;
	}
};

void test02()
{
	MyAdd myadd;

	int ret = myadd(100, 100);

	cout << "ret = " << ret << endl;

	// 匿名函数对象: 不创建具体对象，直接调用重载的函数
	cout << MyAdd()(100, 100) << endl;
	/*
	MyAdd() 是创建了一个 MyAdd 类的匿名对象。匿名对象是指没有名字的对象，通常在创建后立即使用或销毁。
	MyAdd()(100, 100) 这部分代码首先创建了一个 MyAdd 类的匿名对象，然后立即调用了该对象的重载 operator(), 传入参数 100 和 100。
	由于 operator() 返回的是两个整数的和，所以 cout << MyAdd()(100, 100) << endl; 输出的是 200
	*/
}

int main()
{
	test01();
	test02();

	system("pause");

	return 0;
}
// 输出：
// hello world
// hello world
// ret = 200
// 200