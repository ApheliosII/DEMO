#include <iostream>
using namespace std;

// 学习目标：
// ·掌握类模板配合友元函数的类内和类外实现
// 全局函数类内实现·直接在类内声明友元即可
// 全局函数类外实现·需要提前让编译器知道全局函数的存在

// 通过全局函数 打印Person信息

// 提前让编译器知道Person类存在
template <class T1, class T2>
class Person;

// 类外实现
template <class T1, class T2>
void printPerson2(Person<T1, T2> a);

template <class T1, class T2>
class Person
{
	// 1. 全局函数 类内实现  简单
	friend void printPerson(Person<T1, T2> a)
	{
		cout << "姓名： " << a.m_Name << "\t年龄： " << a.m_Age << endl;
	}

	// 2. 全局函数 类外实现
	// 加空模板参数列表
	// 如果全局函数 是类外实现，需要让编译器提前知道这个函数的存在
	friend void printPerson2<>(Person<T1, T2> a);
	// friend void printPerson2<T1, T2>(Person<T1, T2> a);

public:
	Person(T1 name, T2 age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

private:
	T1 m_Name;
	T2 m_Age;
};

// 类外实现
template <class T1, class T2>
void printPerson2(Person<T1, T2> a)
{
	cout << "类外实现--姓名： " << a.m_Name << "\t年龄： " << a.m_Age << endl;
}

// 1、全局函数在类内实现
void test01()
{
	Person<string, int> p("Tom", 20);

	printPerson(p);
}

// 2、全局函数在类外实现
void test02()
{
	Person<string, int> p("Jerry", 20);

	printPerson2(p);
}

int main()
{
	test01();

	test02();

	system("pause");

	return 0;
}
// 姓名： Tom      年龄： 20
// 类外实现--姓名： Jerry  年龄： 20

// 总结：建议全局函数做类内实现，用法简单，而且编译器可以直接识别