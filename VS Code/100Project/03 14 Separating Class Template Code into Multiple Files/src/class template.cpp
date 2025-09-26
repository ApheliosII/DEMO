#include <iostream>
using namespace std;
#include <string>

// 类模板分文件编写问题及解决

// 问题：

// #include"person.h"
// 类模板中成员函数创建时机是在调用阶段，导致分文件编写时链接不到

// 第一种解决方式，直接包含 源文件
// #include"person.cpp"

// 第二种解决方式，将.h和.cpp中的内容写到同一个文件中，将后缀名改为.hpp文件,hpp是约定的名称，并不是强制
#include "person.hpp" //主流

// template<class T1, class T2>
// class Person
//{
// public:
//	Person(T1 name, T2 age);
//
//	void showPerson();
//
//	T1 m_Name;
//	T2 m_Age;
// };

////构造函数类外实现
// template<class T1, class T2>
// Person<T1, T2>::Person(T1 name, T2 age)
//{
//	this->m_Name = name;
//	this->m_Age = age;
// }
//
////成员函数类外实现
// template<class T1, class T2>
// void Person<T1, T2>::showPerson()
//{
//	cout << "姓名： " << this->m_Name << "\t年龄： " << this->m_Age << endl;
// }

void test01()
{
	Person<string, int> p("Tom", 20);
	p.showPerson();
}

int main()
{
	test01();

	system("pause");

	return 0;
}