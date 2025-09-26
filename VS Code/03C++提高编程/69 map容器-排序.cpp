#include <iostream>
using namespace std;
#include <map>

// map容器 排序
/*
学习目标：
	map容器默认排序规则为按照key值进行从小到大排序，掌握如何改变排序规则
主要技术点：
	利用仿函数，可以改变排序规则
*/

class Person
{
	// friend ostream &operator<<(ostream &out, const Person &p); // 私有属性需要友元函数
	
public:
	Person(const string &name, const int &age)
	{
		this->m_name = name;
		this->m_age = age;
	}

	string m_name;
	int m_age;
};

class MyCompare
{
public:
	bool operator()(const int &v1, const int &v2) const // const
	{
		// 降序
		return v1 > v2;
	}
};

// 利用仿函数实现Person类按照age从大到小排序
class MyCompare2
{
public:
	bool operator()(const Person &p1, const Person &p2) const // const
	{
		// 降序
		return p1.m_age > p2.m_age;
	}
};

void test01()
{
	// 默认从小到大排序
	// 利用仿函数实现从大到小排序
	map<int, int, MyCompare> m;

	m.insert(make_pair(1, 10));
	m.insert(make_pair(2, 20));
	m.insert(make_pair(5, 50));
	m.insert(make_pair(3, 30));
	m.insert(make_pair(4, 40));

	for (map<int, int, MyCompare>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key:" << it->first << " value:" << it->second << endl;
	}
}

ostream &operator<<(ostream &out, const Person &p); // 声明

void test02()
{
	// 利用仿函数实现Person类按照age从大到小排序
	map<Person, int, MyCompare2> m2;
	Person p1("A", 1);
	Person p2("B", 2);
	Person p3("C", 3);
	Person p4("D", 4);
	Person p5("E", 5);
	m2.insert(make_pair(p1, 10));
	m2.insert(make_pair(p2, 20));
	m2.insert(make_pair(p5, 50));
	m2.insert(make_pair(p3, 30));
	m2.insert(make_pair(p4, 40));

	for (map<Person, int, MyCompare2>::iterator it = m2.begin(); it != m2.end(); it++)
	{
		cout << "key:" << it->first << " value:" << it->second << endl;
	}
}

// 重载<<
ostream &operator<<(ostream &out, const Person &p) // 本质  operator<<(cout, p)  简化  cout<<p
{
	out << "Name = " << p.m_name << " Age = " << p.m_age;
	return out;
}

int main()
{
	test01();
	test02();

	system("pause");

	return 0;
}

// 总结：
// ·利用仿函数可以指定map容器的排序规则
// ·对于自定义数据类型，map必须要指定排序规则，同set容器