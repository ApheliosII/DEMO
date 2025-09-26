#include <iostream>
using namespace std;
#include <string>
#include <list>
#include <algorithm>

// list容器 排序案例 对于自定义数据类型

// 案例描述：将Person自定义数据类型进行排序，Person中属性有姓名、年龄、身高
// 排序规则：按照年龄进行升序，如果年龄相同按照身高进行降序

class Person
{
public:
	Person(string name, int age, int height)
	{
		this->m_Name = name;
		this->m_Age = age;
		this->m_Height = height;
	}

	string m_Name; // 姓名
	int m_Age;	   // 年龄
	int m_Height;  // 身高
};

// 指定排序规则
bool comparePerson(Person &p1, Person &p2)
{
	if (p1.m_Age == p2.m_Age)
	{
		// 年龄相同 按照身高排序
		return p1.m_Height > p2.m_Height;
	}
	else
	{
		// 按照年龄 升序
		return p1.m_Age < p2.m_Age;
	}
}

void test01()
{
	list<Person> L; // 创建容器

	// 准备数据
	Person p1("刘备", 35, 175);
	Person p2("曹操", 45, 180);
	Person p3("孙权", 40, 170);
	Person p4("赵云", 25, 190);
	Person p5("张飞", 35, 160);
	Person p6("关羽", 35, 200);

	// 插入数据
	L.push_back(p1);
	L.push_back(p2);
	L.push_back(p3);
	L.push_back(p4);
	L.push_back(p5);
	L.push_back(p6);

	for (list<Person>::iterator it = L.begin(); it != L.end(); it++)
	{
		// cout << "姓名： " << (*it).m_Name << "\t年龄： " << (*it).m_Age << "\t身高： " << (*it).m_Height << endl;
		cout << "姓名： " << it->m_Name << "\t年龄： " << it->m_Age << "\t身高： " << it->m_Height << endl;
	}

	// 排序
	cout << "---------------------------------" << endl;
	L.sort(comparePerson);

	cout << "排序后： " << endl;
	for (list<Person>::iterator it = L.begin(); it != L.end(); it++)
	{
		cout << "姓名： " << it->m_Name << "\t年龄： " << it->m_Age << "\t身高： " << it->m_Height << endl;
	}
}

// 总结：
// ·对于自定义数据类型，必须要指定排序规则，否则编译器不知道如何进行排序
// ·高级排序只是在排序规则上再进行一次逻辑规则制定，并不复杂

int main()
{
	test01();

	system("pause");

	return 0;
}

/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// list容器 排序案例 对于自定义数据类型

// 案例描述：将Person自定义数据类型进行排序，Person中属性有姓名、年龄、身高
// 排序规则：按照年龄进行升序，如果年龄相同按照身高进行降序

class Person
{
public:
	Person(const string &name, const int &age, const int &height)
	{
		this->name = name;
		this->age = age;
		this->height = height;
	}

	string name;
	int age;
	int height;
};

void myPrint(const vector<Person> &p)
{
	for (vector<Person>::const_iterator it = p.begin(); it != p.end(); it++)
	{
		cout << "name: " << it->name
			 << "\tage: " << it->age
			 << "\theight: " << it->height << endl;
	}
}

// *****自定义排序规则*****
bool myCompare(const Person &p1, const Person &p2)
{
	if (p1.age != p2.age)
		return p1.age < p2.age;
	else
		return p1.height > p2.height;
}

int main()
{
	vector<Person> p;
	Person p1("A", 21, 208);
	Person p2("B", 15, 168);
	Person p3("C", 31, 198);
	Person p4("D", 15, 188);
	Person p5("E", 29, 188);

	p.push_back(p1);
	p.push_back(p2);
	p.push_back(p3);
	p.push_back(p4);
	p.push_back(p5);

	myPrint(p);

	sort(p.begin(), p.end(), myCompare); // myCompare 没有括号
	cout << "---------------------------------" << endl;
	cout << "after sort : " << endl;
	myPrint(p);

	system("pause");
	return 0;
}
	*/