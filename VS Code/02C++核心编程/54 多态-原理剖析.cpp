#include <iostream>
using namespace std;

// 多态原理剖析

// 动物类
class Animal
{
public:
	// 虚函数
	virtual void speak()
	{
		cout << "动物在说话" << endl;
	}

	// vfptr  虚函数（表）指针   ->   虚函数表 vftable
	// v-virtual
	// f-function
	// ptr-pointer

	// vftable  虚函数表  表内记录虚函数地址
	// v-virtual
	// f-function

	// &Animal::speak

	// 当子类重写父类的虚函数
	// 子类中的虚函数表  内部会替换成  子类的虚函数地址

	// 父类的指针或引用 指向子类的对象  发生多态
	// Animal & animal = cat;
	// animal.speak();
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

	// 当子类重写父类的虚函数
	// 子类中的虚函数表  内部会替换成  子类的虚函数地址
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
	animal.speak();
}

void test01()
{
	Cat cat;
	doSpeak(cat);

	Dog dog;
	doSpeak(dog);
}

void test02()
{
	cout << "sizeof Animal = " << sizeof(Animal) << endl;
	// virtual void 4  在大多数现代64位系统上，指针的大小是8字节。
	// void         1
}

// 在C++中，当一个类包含虚函数时，编译器会在该类的对象中添加一个指针（vfptr），
// 指向该类的虚函数表（vftable）。虚函数表记录了类中虚函数的地址，以便在运行时能够动态地调用正确的函数实现。
// 因此，sizeof(Animal) 的结果不仅包括类中数据成员的大小，还包括这个额外的虚函数指针的大小。

int main()
{
	// test01();

	test02();

	system("pause");

	return 0;
}

// cl /d1 reportSingleClassLayout类名 文件名
/* 
class Animal    size(4):
        +---
 0      | {vfptr}
        +---

Animal::$vftable@:
        | &Animal_meta
        |  0
 0      | &Animal::speak 
 */

//子类未重写虚函数：
/*  class Cat       size(4):
        +---
 0      | +--- (base class Animal)
 0      | | {vfptr}
        | +---
        +---

Cat::$vftable@:
        | &Cat_meta
        |  0
 0      | &Animal::speak 
 */

 //子类重写虚函数：
/*  class Cat       size(4):
        +---
 0      | +--- (base class Animal)
 0      | | {vfptr}
        | +---
        +---

Cat::$vftable@:
        | &Cat_meta
        |  0
 0      | &Cat::speak 
 */