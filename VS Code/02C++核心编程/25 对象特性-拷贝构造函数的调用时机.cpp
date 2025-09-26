#include <iostream>
using namespace std;

// 拷贝构造函数的调用时机

class Person
{
public:
	Person()
	{
		cout << "Person的默认构造函数的调用" << endl;
	}

	Person(int age)
	{
		m_Age = age;
		cout << "Person的有参构造函数的调用" << endl;
	}

	Person(const Person &p)
	{
		m_Age = p.m_Age;
		cout << "Person的拷贝构造函数的调用" << endl;
	}

	// 析构函数
	~Person()
	{
		cout << "Person的析构函数的调用" << endl;
	}

	int m_Age;
};

// 1、使用一个已经创建完毕的对象来初始化一个新对象
void test01()
{
	Person p1(20); // 有参构造
	Person p2(p1); // 拷贝构造函数

	cout << "p2的年龄为： " << p2.m_Age << endl;
}

// 2、值传递的方式给函数参数传值
void doWork(Person q)
{
}

void test02()
{
	Person p;
	doWork(p);
}

// 3、以值方式返回局部对象
Person doWork2()
{
	Person p1;
	cout << (int *)&p1 << endl;
	return p1;
}

void test03()
{
	Person p = doWork2();
	cout << (int *)&p << endl;
}

int main()
{
	test01();
	test02();
	test03();

	system("pause");

	return 0;
}

// 输出：
// Person的有参构造函数的调用
// Person的拷贝构造函数的调用
// p2的年龄为： 20
// Person的析构函数的调用
// Person的析构函数的调用

// Person的默认构造函数的调用
// Person的拷贝构造函数的调用
// Person的析构函数的调用
// Person的析构函数的调用

// Person的默认构造函数的调用
// 0x62fe0c
// 0x62fe0c
// Person的析构函数的调用

// 这里为什么没有调用拷贝构造函数？？
/*
对象返回机制:

关键在于 return p1 这一行。
根据 C++ 的对象返回机制，当一个对象从函数返回时，通常会调用拷贝构造函数来创建一个新的对象，这个新的对象是返回值的副本。
然而，在现代 C++ 编译器中，通常会使用一种优化技术称为返回值优化（Return Value Optimization, RVO）或命名返回值优化（Named Return Value Optimization, NRVO），
这些优化技术可以避免不必要的拷贝构造函数调用，直接将 p1 的数据复制到 test03 函数中的 p 对象中。
接收返回值 Person p = doWork2();:

Person p = doWork2(); 这一行代码接收了 doWork2 函数的返回值。
在这个过程中，通常情况下会调用拷贝构造函数来创建 p 对象并初始化它为 doWork2 返回的对象 p1 的副本。
但是，由于返回值优化的存在，p1 的数据可能会直接被复制到 p 中，而不会调用拷贝构造函数。
输出 p 的地址:

cout << (int *)&p << endl; 这一行代码输出了 p 对象的地址。
这个地址与 doWork2 函数中输出的 p1 的地址相同，这表明返回值优化可能已经生效，p 和 p1 实际上是同一个对象。
*/
