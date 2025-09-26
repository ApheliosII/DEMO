#include <iostream>
using namespace std;
#include <string>

// 类模板与继承

// 当类模板碰到继承时，需要注意一下几点：
// ·当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类中T的类型
// ·如果不指定，编译器无法给子类分配内存
// ·如果想灵活指定出父类中T的类型，子类也需变为类模板

template <class T>
class Base
{
	T m;
};

// class Son :public Base  //错误，必须要知道父类中的T类型，才能继承给子类
class Son : public Base<int>
{
};

void test01()
{
	Son s1;
}

// 如果想灵活指定父类中的T类型，子类也需要变类板
template <class T1, class T2>
class Son2 : public Base<T2>
{
public:
	Son2()
	{
		cout << "T1的类型为：" << typeid(T1).name() << endl;
		cout << "T2的类型为：" << typeid(T2).name() << endl;
	}
	T1 obj;
};

void test02()
{ 
	Son2<int, char> s2;
}

int main()
{
	// test01();
	test02();

	system("pause");

	return 0;
}
// 输出：
// T1的类型为：i
// T2的类型为：c