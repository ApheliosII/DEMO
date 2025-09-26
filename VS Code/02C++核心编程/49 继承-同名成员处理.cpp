#include <iostream>
using namespace std;

// 继承中同名成员处理

// 问题：当子类与父类出现同名的成员，如何通过子类对象，访问到子类或父类中同名的数据呢？
// ·访问子类同名成员 直接访问即可
// ·访问父类同名成员需要加作用域

class Base
{
public:
	Base()
	{
		m_A = 100;
	}

	void func()
	{
		cout << "Base - func()调用 " << endl;
	}

	void func(int a)
	{
		cout << "Base - func(int a)调用 " << endl;
	}

	int m_A;
};

class Son : public Base
{
public:
	Son()
	{
		m_A = 200;
	}

	void func()
	{
		cout << "Son - func()调用 " << endl;
	}

	int m_A;
};

// 同名成员属性处理
void test01()
{
	Son s;
	cout << "Son下 m_A = " << s.m_A << endl;

	// 如果通过子类对象 访问父类中同名成员，需要加作用域
	cout << "Base下 m_A = " << s.Base::m_A << endl;
}

// 同名成员函数处理
void test02()
{
	Son s;

	s.func(); // 直接调用 调用的是子类中的同名成员

	// 如何调用到父类中同名成员函数
	s.Base::func();

	// 如果子类中出现和父类同名的成员函数，子类的同名成员函数会隐藏掉父类中所有同名成员函数
	// 如果想访问父类中被隐藏的同名成员函数，加作用域
	// s.func(100); // 错误，子类中没有同名成员函数, 也不是调用父类中同名成员函数
	s.Base::func(100);
}

// 1、子类对象可以直接访问到子类中同名成员
// 2、子类对象加作用域可以访问到父类同名成员
// 3、当子类与父类拥有同名的成员函数，子类会隐藏父类中同名成员函数，加作用域可以访问到父类中同名函数

int main()
{
	test01();

	test02();

	system("pause");

	return 0;
}
// 输出
// Son下 m_A = 200
// Base下 m_A = 100
// Son - func()调用
// Base - func()调用
// Base - func(int a)调用

//总结：
// 1.子类对象可以直接访问到子类中同名成员
// 2.子类对象加作用域可以访问到父类同名成员
// 3.当子类与父类拥有同名的成员函数，子类会隐藏父类中同名成员函数，加作用域可以访问到父类中同名函数