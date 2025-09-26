#include <iostream>
using namespace std;
// #include<string>

// 多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码

// 解决方式：将父类中的析构函数改为虚析构或者纯虚析构

// 虚析构和纯虚析构共性：
// ·可以解决父类指针释放子类对象
// ·都需要有具体的函数实现

// 虚析构和纯虚析构区别：
// ·如果是纯虚析构，该类属于抽象类，无法实例化对象

// 语法
// 虚析构语法：
// virtual ~类名(){}

// 纯虚析构语法：
// virtual ~类名()=0;
// 类名::~类名(){}

// 虚析构和纯虚析构
class Animal
{
public:
	Animal()
	{
		cout << "Animal构造函数调用" << endl;
	}

	// 利用虚析构可以解决 父类指针释放子类对象时不干净问题
	// virtual ~Animal()
	//{
	//	cout << "Animal虚析构函数调用" << endl;
	// }

	// 纯虚析构 需要声明也需要实现（类外实现，如果父类有属性开辟到堆区也需要析构函数手动释放delete）
	// 有了纯虚析构之后 ，这个类也属于抽象类，无法实例化对象
	virtual ~Animal() = 0;

	// 纯虚函数
	virtual void speak() = 0;
};

Animal::~Animal()
{
	cout << "Animal纯虚析构函数调用" << endl;
}

class Cat : public Animal
{
public:
	Cat(string name)
	{
		cout << "Cat构造函数调用" << endl;
		m_Name = new string(name);
	}

	virtual void speak()
	{
		cout << *m_Name << "小猫在说话" << endl;
	}

	~Cat()
	{
		if (m_Name != NULL)
		{
			cout << "Cat析构函数调用" << endl;
			delete m_Name;
			m_Name = NULL;
			// 释放内存 delete m_Name;:
			// 使用 delete 关键字释放 m_Name 所指向的堆区内存。这是析构函数的重要职责之一，即确保在对象销毁时释放其占用的所有资源，以避免内存泄漏。
			// 内存泄漏是指程序在运行过程中未能正确释放不再使用的内存，导致可用内存逐渐减少，最终可能耗尽可用内存，引发性能问题或程序崩溃。

			// 将指针置为 NULL, m_Name = NULL;:
			// 在释放了 m_Name 所指向的内存之后，将指针 m_Name 置为 NULL（或 nullptr 在 C++11 及以后的标准中）。
			// 这是一个良好的编程习惯，因为它可以防止悬空指针（即指向已释放内存的指针）的问题。悬空指针可能会导致程序在后续访问该指针时出现未定义行为。
		}
	}

	string *m_Name;
};

void test01()
{
	Animal *animal = new Cat("Tom");
	animal->speak();

	// 父类指针在析构时 不会调用子类中析构函数，导致子类中如果有堆区属性，出现内存泄漏
	delete animal;
}

// 虚析构和纯虚析构共性：
// 可以解决父类指针释放子类对象
// 都需要有具体的函数实现
//
// 虚析构和纯虚析构区别：
// 如果是纯虚析构，该类属于抽象类，无法实例化对象

int main()
{
	test01();

	system("pause");

	return 0;
}
// 输出：
// Animal构造函数调用
// Cat构造函数调用
// Tom小猫在说话
// Cat析构函数调用
// Animal纯虚析构函数调用

// 总结：
// 1.虚析构或纯虚析构就是用来解决通过父类指针释放子类对象
// 2.如果子类中没有堆区数据，可以不写为虚析构或纯虚析构
// 3.拥有纯虚析构函数的类也属于抽象类