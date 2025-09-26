#include <iostream>
using namespace std;
#include <map>

/*
简介：
	map中所有元素都是pair
	pair中第一个元素为key（键值），起到索引作用，第二个元素为value（实值）
	所有元素都会根据元素的键值自动排序

本质：
	map / multimap属于关联式容器，底层结构是用二叉树实现。

优点：
	可以根据key值快速找到value值

map和multimap区别：
	map不允许容器中有重复key值元素
	multimap允许容器中有重复key值元素
*/

// map容器 构造和赋值

/*
构造：
	map<T1, T2> mp;   	//map默认构造函数：
	map(const map& mp); //拷贝构造函数
赋值：
	map& operator=(const map& mp);//重载等号操作符
*/

void printMap(map<int, int> &m)
{
	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key = " << it->first << " value = " << it->second << endl; //(*it).first
	}
	cout << endl;
}

void printMap2(const map<int, int> &m)
{
	for (const auto& it : m)
	{
		cout << "key = " << it.first << " value = " << it.second << endl; //(*it).first
	}
	cout << endl;
}


void test01()
{
	// 创建map容器
	map<int, int> m; // 默认构造
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(3, 30));
	m.insert(pair<int, int>(4, 40));
	printMap(m);

	// 拷贝构造
	map<int, int> m2(m);
	printMap2(m2);

	// 赋值
	map<int, int> m3;
	m3 = m2;
	printMap2(m3);
}

// 总结：map中所有元素都是成对出现，插入数据时候要使用对组

int main()
{
	test01();

	system("pause");

	return 0;
}