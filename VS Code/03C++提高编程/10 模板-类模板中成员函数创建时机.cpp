#include <iostream>
using namespace std;
#include <string>

// 类模板中成员函数创建时机

// 类模板中成员函数和普通类中成员函数创建时机是有区别的：
// ·普通类中的成员函数一开始就可以创建
// ·类模板中的成员函数在调用时才创建

class Person1
{
public:
	void showPerson1()
	{
		cout << "Person1 show" << endl;
	}
};

class Person2
{
public:
	void showPerson2()
	{
		cout << "Person2 show" << endl;
	}
};

template <class T>
class MyClass
{
public:
	T obj;

	// 类模板中的成员函数
	void func1()
	{
		obj.showPerson1();
	}

	void func2()
	{
		obj.showPerson2();
	}
};

void test01()
{
	MyClass<Person1> m;
	m.func1();
	// m.func2();  出错，函数调用才会去创建成员函数

	MyClass<Person2> n;
	n.func2();
}

int main()
{
	test01();

	system("pause");

	return 0;
}