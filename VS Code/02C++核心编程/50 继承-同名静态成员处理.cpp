#include <iostream>
using namespace std;

// 问题：继承中同名的静态成员在子类对象上如何进行访问？
// 静态成员和非静态成员出现同名，处理方式一致
// ·访问子类同名成员直接访问即可
// ·访问父类同名成员需要加作用域

// 继承中同名静态成员处理

class Base
{
public:
	static int m_A; 
	static void func()
	{
		cout << "Base - static void func()调用 " << endl;
	}

	static void func(int a)
	{
		cout << "Base - static void func(int a)调用 " << endl;
	}
};
int Base::m_A = 100;  //编译时分配内存，类内声明，类外初始化

class Son : public Base
{
public:
	static int m_A;

	static void func()
	{
		cout << "Son - static void func()调用 " << endl;
	}
};
int Son::m_A = 200;

// 同名静态成员属性
void test01()
{
	// 1、通过对象访问 
	cout << "通过对象访问: " << endl;
	Son s;
	cout << "Son下 m_A = " << s.m_A << endl;
	cout << "Base下 m_A = " << s.Base::m_A << endl;

	// 2、通过类名访问
	cout << "通过类名访问: " << endl;
	cout << "Son下 m_A = " << Son::m_A << endl;
	// 第一个::代表通过类名访问  第二个::代表访问父类作用于下
	cout << "Base下 m_A = " << Son::Base::m_A << endl;
	cout << "Base下 m_A = " << Base::m_A << endl;
	// 选择建议：
	// 如果代码逻辑需要体现继承关系（如子类可能重写父类成员），用 Son::Base::m_A。
	// 如果直接操作父类成员且无歧义，用 Base::m_A（更简洁）。
}

// 同名成员函数处理
void test02()
{
	// 1、通过对象访问
	cout << "通过对象访问: " << endl;
	Son s;
	s.func();
	s.Base::func();

	// 2、通过类名访问
	cout << "通过类名访问: " << endl;
	Son::func();
	Son::Base::func();
	Base::func();

	// Son::func(100);
	// 如果子类中出现和父类同名静态成员函数，也会隐藏掉父类中所有同名成员函数
	// 如果想访问父类中被隐藏的同名成员，加作用域
	Son::Base::func(100);
	Base::func(100);
}

// 总结：同名静态成员处理方式和非静态处理方式一样，只不过有两种访问的方式（通过对象 和 通过类名）

int main()
{
	test01();

	test02();

	system("pause");

	return 0;
}
