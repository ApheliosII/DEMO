#include <iostream>
using namespace std;
#include <set>

// set容器排序

/*
学习目标：
	set容器默认排序规则为从小到大，掌握如何改变排序规则
主要技术点：
	利用仿函数，可以改变排序规则
*/


// 仿函数  自定义排序规则
class MyCompare
{
public:
	bool operator()(int v1, int v2) const // 重载operator()    加const
	{
		return v1 > v2;
	}
};

void test01()
{
	set<int> s1;
	s1.insert(10);
	s1.insert(40);
	s1.insert(20);
	s1.insert(30);
	s1.insert(50);

	// 默认从小到大
	for (set<int>::iterator it = s1.begin(); it != s1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	// 指定排序规则  从大到小
	set<int, MyCompare> s2;
	s2.insert(10);
	s2.insert(40);
	s2.insert(20);
	s2.insert(30);
	s2.insert(50);

	for (set<int, MyCompare>::iterator it = s2.begin(); it != s2.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

// 总结：利用仿函数可以指定set容器的排序规则

int main()
{
	test01();

	system("pause");

	return 0;
}