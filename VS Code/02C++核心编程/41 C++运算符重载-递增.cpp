#include <iostream>
using namespace std;
// #include<string>

// 重载递增运算符

// 作用：通过重载递增运算符，实现自己的整型数据

// 自定义整型
class MyInteger
{
	friend ostream &operator<<(ostream &out, const MyInteger &p); // 友元

public:
	MyInteger()
	{
		m_Num = 0;
	}

	// 重载++运算符

	// 重载前置++运算符  为什么返回引用？ 返回引用是为了一直对一个数据进行递增操作
	MyInteger &operator++()
	{
		// 先进行++运算
		m_Num++;
		// 再将自身做返回
		return *this;
	}

	// 重载后置++运算符
	// void operator++(int)  int代表占位参数，可以用于区分前置和后置递增
	MyInteger operator++(int)
	{
		// 先  记录当时结果
		MyInteger temp = *this;
		// 后  递增
		m_Num++;
		// 最后将记录结果做返回
		return temp;
	}

	// 总结： 前置递增返回引用，后置递增返回值

private:
	int m_Num;
};

// 全局函数重载<<运算符
ostream &operator<<(ostream &out, const MyInteger &p) // 本质  operator<<(cout, p)  简化  cout<<p
{
	out << p.m_Num;
	return out;
}

void test01()
{
	MyInteger myint;

	cout << ++(++myint) << endl;
	cout << myint << endl;
}

void test02()
{
	MyInteger myint02;

	cout << myint02++ << endl;
	cout << myint02 << endl;
}

int main()
{
	test01();
	test02();

	// int a = 0;

	// cout << ++(++a) << endl;
	// cout << a << endl;

	system("pause");

	return 0;
}

// 输出：
// 2
// 2
// 0
// 1

// 递减类似