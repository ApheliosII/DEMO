#include <iostream>
using namespace std;
#include <string>

// 类模板对象做函数参数

// 学习目标：
// ·类模板实例化出的对象，向函数传参的方式
// 一共有三种传入方式：
// 1.指定传入的类型-直接显示对象的数据类型
// 2.参数模板化 将对象中的参数变为模板进行传递
// 3.整个类模板化 予-将这个对象类型模板化进行传递

template <class T1, class T2>
class Person
{
public:
	Person(T1 name, T2 age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	void showPerson()
	{
		cout << "姓名： " << this->m_Name << "\t年龄： " << this->m_Age << endl;
	}

	T1 m_Name;
	T2 m_Age;
};

// 1、指定传入类型  常用
void printPerson1(Person<string, int> &a)
{
	a.showPerson();
}

void test01()
{
	Person<string, int> p1("孙悟空", 100);
	printPerson1(p1);
}

// 2、参数模板化
template <class T1, class T2>
void printPerson2(Person<T1, T2> &a)
{
	a.showPerson();
	cout << "T1 的类型为：" << typeid(T1).name() << endl;
	cout << "T2 的类型为：" << typeid(T2).name() << endl;
}

void test02()
{
	Person<string, int> p2("猪八戒", 90);
	printPerson2(p2);
}

// 3、整个类模板化
template <class T>
void printPerson3(T &a)
{
	a.showPerson();
	cout << "T 的类型为：" << typeid(T).name() << endl;
}

void test03()
{
	Person<string, int> p3("唐僧", 30);
	printPerson3(p3);
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
// 姓名： 孙悟空   年龄： 100
// 姓名： 猪八戒   年龄： 90
// T1 的类型为：NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
// T2 的类型为：i
// 姓名： 唐僧     年龄： 30
// T 的类型为：6PersonINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEiE  

// 总结：
// ·通过类模板创建的对象，可以有三种方式向函数中进行传参
// ·使用比较广泛是第一种：脂定传入的类型