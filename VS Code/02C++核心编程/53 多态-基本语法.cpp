#include <iostream>
using namespace std;

// 多态是C++面向对象三大特性之一

// 多态分为两类
// ·静态多态：函数重载和运算符重载属于静态多态，复用函数名
// ·动态多态：派生类和虚函数实现运行时多态

// 静态多态和动态多态区别：
// ·静态多态的函数地址早绑定－编译阶段确定函数地址
// ·动态多态的函数地址晚绑定－运行阶段确定函数地址

// 下面通过案例进行讲解多态

// 多态基本语法

// 动物类
class Animal
{
public:
	// 虚函数
	virtual void speak()
	{
		cout << "动物在说话" << endl;
	}
};

// 猫类
class Cat : public Animal
{
public:
	// 重写  函数返回值类型 函数名 参数列表 完全相同
	virtual void speak() // virtual可以不写
	{
		cout << "小猫在说话" << endl;
	}
};

// 狗类
class Dog : public Animal
{
public:
	void speak()
	{
		cout << "小狗在说话" << endl;
	}
};

// 执行说话的函数
// 地址早绑定  在编译阶段确定函数地址
// 如果想执行让猫说话，那么这个函数地址就不能提前绑定  需要在运行阶段绑定，地址晚绑定

// 动态多态满足条件
// 1、有继承关系
// 2、子类重写父类虚函数

// 动态多态使用
// 父类的指针或引用 指向子类的对象

void doSpeak(Animal &animal) // Animal & animal = cat;
{
	animal.speak(); // 由传入的子类类型确定调用子类的speak函数
}

void test01()
{
	Cat cat;
	doSpeak(cat);

	Dog dog;
	doSpeak(dog);
}

int main()
{
	test01();

	system("pause");

	return 0;
}

// 总结：
// 多态满足条件
// ·有继承关系
// ·子类重写父类中的虚函数

// 多态使用条件
// ·父类指针或引用指向子类对象
// 重写：函数返回值类型函数名参数列表完全一致称为重写