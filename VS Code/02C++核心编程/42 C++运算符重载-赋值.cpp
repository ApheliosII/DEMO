#include <iostream>
using namespace std;
// #include<string>

// c++编译器至少给一个类添加4个函数：
// 1.默认构造函数(无参，函数体为空)
// 2.默认析构函数(无参，函数体为空)
// 3.默认拷贝构造函数，对属性进行值拷贝
// 4.赋值运算符operator=，对属性进行值拷贝

// 如果类中有属性指向堆区，做赋值操作时也会出现深浅拷贝问题

// 赋值运算符重载

class Person
{
public:
	Person(int age)
	{
		m_Age = new int(age);
	}

	~Person()
	{
		if (m_Age != NULL)
		{
			delete m_Age;
			m_Age = NULL;
		}
	}
	// 堆区内存重复释放

	// 重载  赋值运算符
	Person &operator=(Person &p)
	{
		// 编译器提供的是浅拷贝
		// m_Age = p.m_Age;  // 地址相同，指向堆区同一个数据，析构时会重复释放堆区内存

		// 应该先判断是否有属性在堆区，如果有先释放干净，再深拷贝
		if (m_Age != NULL)
		{
			delete m_Age;
			m_Age = NULL;
		}

		// 深拷贝
		m_Age = new int(*p.m_Age);

		// 返回对象本身 引用 支持链式编程
		return *this;
	}

	int *m_Age;
};

void test01()
{
	Person p1(18);

	Person p2(20);

	Person p3(30);

	p3 = p2 = p1; // 赋值操作

	cout << "p1的年龄为： " << *p1.m_Age << endl;

	cout << "p2的年龄为： " << *p2.m_Age << endl;

	cout << "p3的年龄为： " << *p3.m_Age << endl;
}

int main()
{
	test01();

	// int a = 10;
	// int b = 20;
	// int c = 30;

	// c = b = a;

	// cout << "a = " << a << endl;
	// cout << "b = " << b << endl;
	// cout << "c = " << c << endl;

	system("pause");

	return 0;
}

/*
Person &operator=(Person &p)

参数是引用
1.避免不必要的拷贝：
如果参数不是引用而是按值传递（即 Person p），那么每次调用赋值运算符时，都会创建一个 Person 对象的副本。这会导致不必要的内存分配和释放操作，降低效率。
使用引用（即 Person &p）可以避免这种不必要的拷贝，直接操作传入的对象。
2.常量引用：
更好的做法是使用常量引用（即 const Person &p），这样可以确保赋值运算符不会修改传入的对象，并且可以接受常量对象作为参数。
这是一种良好的编程实践，可以提高代码的健壮性和灵活性。

返回值是引用
1.支持链式赋值：
如果返回值不是引用（即 Person operator=(const Person &p)），那么赋值运算符将返回一个副本。
这会破坏链式赋值的能力，例如 p1 = p2 = p3; 将无法正常工作，因为 p2 = p3 返回的将是 p2 的副本，而不是 p2 本身。
使用引用（即 Person &operator=(const Person &p)）可以允许链式赋值，使得 p1 = p2 = p3; 这样的语句能够正常工作。

2.返回当前对象：
返回引用允许赋值运算符返回当前对象的引用，这样可以支持链式操作，并且返回的对象可以用于其他操作。
例如，在函数中使用赋值运算符后，可以继续调用其他成员函数：(p1 = p2).someMemberFunction();
*/