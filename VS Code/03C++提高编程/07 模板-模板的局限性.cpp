#include <iostream>
using namespace std;
#include <string>

// 模板局限性
// 模板并不是万能的，有些特定数据类型，需要用具体化方法做特殊实现

class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	// 1.==运算符重载
	// bool operator==(const Person &p)
	// {
	// 	if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
	// 	{
	// 		return true;
	// 	}
	// 	else
	// 	{
	// 		return false;
	// 	}
	// }

	// 姓名
	string m_Name;
	// 年龄
	int m_Age;
};

// 对比两个数是否相等函数
template <class T>
bool myCompare(T &a, T &b)
{
	if (a == b)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 1.==运算符重载

// 2.利用具体化Person的版本实现代码，具体化优先使用
template <>
bool myCompare(Person &a, Person &b)
{
	if (a.m_Name == b.m_Name && a.m_Age == b.m_Age)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void test01()
{
	int a = 10;
	int b = 20;

	bool ret = myCompare(a, b);

	if (ret)
	{
		cout << "a == b" << endl;
	}
	else
	{
		cout << "a != b" << endl;
	}
}

void test02()
{
	Person p1("Tom", 10);
	Person p2("Tom", 10);

	bool ret = myCompare(p1, p2);

	if (ret)
	{
		cout << "p1 == p2" << endl;
	}
	else
	{
		cout << "p1 != p2" << endl;
	}
}

int main()
{
	test01();
	test02();

	system("pause");

	return 0;
}
// a != b
// p1 == p2

// 总结：
// ·利用具体化的模板，可以解决自定义类型的通用化
// ·学习模板并不是为了写模板，而是在STL能够运用系统提供的模板