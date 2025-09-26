#include <iostream>
using namespace std;
#include <string>

// 类模板与函数模板区别

// 1.类模板没有自动类型推导的使用方式
// 2.举模板在模板参数列表中可以有默认参数

template <class NameType, class AgeType = int>
class Person
{
public:
	Person(NameType name, AgeType age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	void showPerson()
	{
		cout << " name: " << this->m_Name << " age: " << this->m_Age << endl;
	}

	// 姓名
	NameType m_Name;
	// 年龄
	AgeType m_Age;
};

// 1、类模板没有自动类型推导使用方式
void test01()
{
	// Person p("孙悟空", 999);  错误，无法用自动类型推导
	Person<string, int> p("孙悟空", 999); // 正确，只能用显式指定类型
	p.showPerson();
}

// 2、类模板在模板参数列表中可以有默认参数列表
void test02()
{
	Person<string> p("猪八戒", 999);
	p.showPerson();
}

int main()
{
	test01();
	test02();

	system("pause");

	return 0;
}