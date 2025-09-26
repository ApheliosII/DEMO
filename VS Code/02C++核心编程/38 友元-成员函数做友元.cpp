#include <iostream>
using namespace std;
// #include<string>

// 成员函数做友元

class Building;

class GoodGay
{
public:
	GoodGay();

	void visit();  // 让visit函数可以访问Building中的私有成员
	void visit2(); // 让visit2函数不可以访问Building中的私有成员

	Building *building;
};

class Building
{
	// 告诉编译器  GoodGay类下的visit成员函数作为本类的好朋友，可以访问私有成员
	friend void GoodGay::visit();

public:
	Building();

public:
	string m_SittingRoom; // 客厅

private:
	string m_BedRoom; // 卧室
};

// 类外写成员函数
Building::Building() // Building::   作用域
{
	m_SittingRoom = "客厅";
	m_BedRoom = "卧室";
}

GoodGay::GoodGay()
{
	// 创建建筑物对象
	building = new Building;
}

void GoodGay::visit()
{
	cout << "visit 函数正在访问：" << building->m_SittingRoom << endl;

	cout << "visit 函数正在访问：" << building->m_BedRoom << endl;
}

void GoodGay::visit2()
{
	cout << "visit2 函数正在访问：" << building->m_SittingRoom << endl;

	// cout << "visit2 函数正在访问：" << building->m_BedRoom << endl;  xxx 不能访问私有成员
}

void test01()
{
	GoodGay gg;
	gg.visit();
	gg.visit2();
}

int main()
{
	test01();

	system("pause");

	return 0;
}