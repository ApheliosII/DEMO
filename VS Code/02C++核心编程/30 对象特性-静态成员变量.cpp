#include <iostream>
using namespace std;
// #include<string>

// 静态成员变量

class Person
{
public:
	// 1、所有对象都共享同一份数据
	// 2、编译阶段分配内存   全局区
	// 3、类内声明，类外初始化操作
	static int m_A;

	// 静态成员变量也是有访问权限的
private:
	static int m_B;
};

int Person::m_A = 100;
int Person::m_B = 200;

// 上述代码在语法和逻辑上没有明显的问题，但有一个潜在的缺陷与访问权限有关。
// 具体来说，静态成员变量 m_B 被声明为私有成员，这意味着它只能在类的成员函数内部访问。然而，在类外对其进行初始化是正确的，
// 但后续无法通过类的非成员函数或全局作用域直接访问 m_B。如果后续代码需要在类外访问 m_B，将会导致编译错误。

void test01()
{
	Person p;
	// 100
	cout << p.m_A << endl;

	Person p2;
	p2.m_A = 200;

	// 200
	cout << p.m_A << endl;
}

void test02()
{
	// 静态成员变量 不属于某个对象，所有对象都共享同一份数据
	// 因此静态成员变量有两种访问方式

	// 1、通过对象进行访问
	Person p3;
	p3.m_A = 300;
	cout << p3.m_A << endl; // 300

	// 2、通过类名进行访问
	cout << Person::m_A << endl; // 300

	// cout << Person::m_B << endl;  类外访问不到私有静态成员变量
}

int main()
{
	test01();
	test02();

	system("pause");

	return 0;
}