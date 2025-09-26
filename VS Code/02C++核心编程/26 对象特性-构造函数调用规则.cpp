#include<iostream>
using namespace std;

//构造函数调用规则
//1、创建一个类，C++编译器至少给每个类添加3个函数
//默认构造 (空实现)
//默认析构函数 (空实现)
//默认拷贝构造（值拷贝）

//2、
//如果我们写了有参构造函数，编译器不再提供默认/无参构造，依然提供拷贝构造
//如果我们写了拷贝构造函数，编译器不会再提供其他普通构造函数

class Person
{
public:

	// Person()
	// {
	// 	cout << "Person的默认构造函数的调用" << endl;
	// }

	Person(int age)
	{
		m_Age = age;
		cout << "Person的有参构造函数的调用" << endl;
	}

	//Person(const Person& p)
	//{
	//	m_Age = p.m_Age;
	//	cout << "Person的拷贝构造函数的调用" << endl;
	//}

	//析构函数
	~Person()
	{
		cout << "Person的析构函数的调用" << endl;
	}

	int m_Age;
};

// void test01()
// {
// 	Person p;  
// 	p.m_Age = 18;

// 	Person p2(p);

// 	cout << "p2的年龄为： " << p2.m_Age << endl;
// }

void test02()
{
	//Person p;  
	Person p(28);

	Person p2(p);

	cout << "p2的年龄为： " << p2.m_Age << endl;
}

int main()
{
	//test01(); 
	test02();

	system("pause");

	return 0;
}

//输出：

//test02();
// Person的有参构造函数的调用
// p2的年龄为： 28
// Person的析构函数的调用
// Person的析构函数的调用