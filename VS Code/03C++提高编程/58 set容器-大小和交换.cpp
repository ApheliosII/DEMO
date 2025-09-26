#include<iostream>
using namespace std;
#include <set>

//set容器  大小和交换

/* 
功能描述：
	统计set容器大小以及交换set容器
函数原型：
	size(); 	//返回容器中元素的数目
	empty();) 	//判断容器是否为空
	swap(st); 	//交换两个集合容器 
*/

void printSet(const set<int>& s)
{
	for (set<int>::const_iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//大小
void test01()
{
	set<int> s1;

	s1.insert(10);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);

	printSet(s1);

	if (s1.empty())
	{
		cout << "s1 is empty" << endl;
	}
	else
	{
		cout << "s1 is not empty" << endl;
		cout << "s1 size is : " << s1.size() << endl;
	}
}

//交换
void test02()
{
	set<int> s1;

	s1.insert(10);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);

	set<int> s2;

	s2.insert(100);
	s2.insert(300);
	s2.insert(200);
	s2.insert(400);

	cout << "before swap : " << endl;
	printSet(s1);
	printSet(s2);
	cout << endl;

	cout << "after swap : " << endl;
	s1.swap(s2);  //交换
	printSet(s1);
	printSet(s2);
}

// 总结：
// ·统计大小---size
// ·判断是否为空---empty
// ·交换容器---swap

int main() 
{
	test01();

	test02();

	system("pause");

	return 0;
}