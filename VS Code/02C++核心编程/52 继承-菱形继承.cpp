#include <iostream>
using namespace std;

// 菱形继承概念：
// 两个派生类继承同一个基类
// 又有某个类同时继承者两个派生类
// 这种继承被称为菱形继承，或者钻石继承

// 菱形继承问题：
// 1.羊继承了动物的数据，驼同样继承了动物的数据，当草泥马使用数据时，就会产生二义性。
// 2.草泥马继承自动物的数据继承了两份，其实我们应该清楚，这份数据我们只需要一份就可以。

// 动物类
class Animal
{
public:
	int m_Age;
};

// 利用虚继承  解决菱形继承的问题
// 在继承之前  加上关键字  virtual  变为虚继承
// Animal类称为  虚基类

// 羊类
class Sheep : virtual public Animal
{
};

// 驼类
class Tuo : virtual public Animal
{
};

// 羊驼类
class SheepTuo : public Sheep, public Tuo
{
};

// cl /d1 reportSingleClassLayout类名 文件名

/*
class SheepTuo  size(8):
		+---
 0      | +--- (base class Sheep)
 0      | | +--- (base class Animal)
 0      | | | m_Age
		| | +---
		| +---
 4      | +--- (base class Tuo)
 4      | | +--- (base class Animal)
 4      | | | m_Age
		| | +---
		| +---
		+---
*/

/*
class SheepTuo  size(12):
		+---
 0      | +--- (base class Sheep)
 0      | | {vbptr}
		| +---
 4      | +--- (base class Tuo)
 4      | | {vbptr}
		| +---
		+---
		+--- (virtual base Animal)
 8      | m_Age
		+---

SheepTuo::$vbtable@Sheep@:
 0      | 0
 1      | 8 (SheepTuod(Sheep+0)Animal)

SheepTuo::$vbtable@Tuo@:
 0      | 0
 1      | 4 (SheepTuod(Tuo+0)Animal)
vbi:       class  offset o.vbptr  o.vbte fVtorDisp
          Animal       8       0       4 0
*/

// vbptr------>vbtable 虚基类表格
// v-virtual
// b-base
// ptr-pointer

void test01()
{
	SheepTuo st;

	st.Sheep::m_Age = 18;
	st.Tuo::m_Age = 28;

	// 当菱形继承，两个父类拥有相同数据，需要加作用域区分
	cout << "st.Sheep::m_Age = " << st.Sheep::m_Age << endl;
	cout << "st.Tuo::m_Age = " << st.Tuo::m_Age << endl;
	cout << "st.m_Age = " << st.m_Age << endl;

	// 这份数据我们知道 只有一份就可以，菱形继承导致数据有两份，资源浪费
}

int main()
{
	test01();

	system("pause");

	return 0;
}
// st.Sheep::m_Age = 28
// st.Tuo::m_Age = 28
// st.m_Age = 28

// 总结：
// ·菱形继承带来的主要问题是子类继承两份相同的数据，导致资源浪费以及毫无意义
// ·利用虚继承可以解决菱形继承问题