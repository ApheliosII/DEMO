#include <iostream>
using namespace std;
// #include<string>

// 运算符重载概念：对已有的运算符重新进行定义，赋予其另一种功能，以适应不同的数据类型
// 4.5.1加号运算符重载
// 作用：实现两个自定义数据类型相加的运算

// 语法：自定义类型 operator+(自定义类型& p)

class Person
{
public:
	// 1、成员函数重载+号
	// Person operator+(Person& p)
	//{
	//	Person temp;
	//	temp.m_A = this->m_A + p.m_A;
	//	temp.m_B = this->m_B + p.m_B;
	//	return temp;
	// }

	int m_A;
	int m_B;
};

// 2、全局函数重载+号
Person operator+(Person &p1, Person &p2)
{
	Person temp;
	temp.m_A = p1.m_A + p2.m_A;
	temp.m_B = p1.m_B + p2.m_B;
	return temp;
}

// 参数传递方式：当前代码通过值传递（Person p1, Person p2）来接收参数，
// 这会导致在每次调用操作符时都会进行对象的拷贝，可能会影响性能。
// 可以考虑使用常量引用（const Person& p1, const Person& p2）来避免不必要的拷贝。

// 函数重载的版本
Person operator+(Person &p1, const int &num)
{
	Person temp;
	temp.m_A = p1.m_A + num;
	temp.m_B = p1.m_B + num;
	return temp;
}

// int num 作为参数传递给运算符重载函数是可行的，
// 但通常情况下，我们更倾向于传递常量引用 const int &num 来避免不必要的拷贝和潜在的修改。
// 不过，这个不一定会导致错误行为，但可以提高代码的效率和安全性。

void test01()
{
	Person p1;
	p1.m_A = 10;
	p1.m_B = 10;
	Person p2;
	p2.m_A = 10;
	p2.m_B = 10;

	// 成员函数重载本质调用
	// Person p3 = p1.operator+(p2);

	// 全局函数重载本质调用
	// Person p3 = operator+(p1,p2);

	// 简化
	Person p3 = p1 + p2;
	// 运算符重载 也可以发生函数重载

	Person p4 = p1 + 100; // Person + int

	cout << "p3.m_A = " << p3.m_A << endl;
	cout << "p3.m_B = " << p3.m_B << endl;

	cout << "p4.m_A = " << p4.m_A << endl;
	cout << "p4.m_B = " << p4.m_B << endl;
}

// 总结1：对于内置的数据类型的表达式的的运算符是不可能改变的

// 总结2：不要滥用运算符重载

int main()
{
	test01();

	system("pause");

	return 0;
}
// 输出：
// p3.m_A = 20
// p3.m_B = 20
// p4.m_A = 110
// p4.m_B = 110

/* 
在C++中，int num 和 const int &num 作为参数传递给函数时，它们之间有一些重要的区别：

1.拷贝 vs 引用：
int num：这里传递的是 int 类型的值，意味着会将 num 的值进行拷贝。每次调用函数时，都会创建一个 num 的副本。
const int &num：这里传递的是 int 类型的常量引用。引用是指向原始变量的别名，不会创建副本，因此传递的是原始变量的地址。

2.性能：
对于基本数据类型（如 int），拷贝的开销通常很小，因此性能差异可能不明显。
对于复杂的数据类型（如类对象、大型数组等），传递引用可以显著提高性能，因为避免了不必要的拷贝操作。

3.内存使用：
传递值（int num）会占用额外的内存来存储副本。
传递引用（const int &num）不会占用额外的内存来存储副本，因为它直接使用原始变量的内存地址。

4.修改原始变量：
int num：由于传递的是副本，原始变量不会被修改。
const int &num：传递常量引用可以确保函数内部不能修改原始变量的值，这提高了代码的安全性和可读性。

5.适用性：
int num：适用于不需要修改原始变量且数据类型较小的情况。
const int &num：适用于需要避免拷贝、原始变量不需要修改、或数据类型较大（如类对象）的情况。
总结来说，const int &num 更安全、更高效，特别是在处理复杂数据类型时。对于基本数据类型，性能差异通常不明显，但使用常量引用仍然是一个良好的编程习惯。 
*/