#include <iostream>
using namespace std;
#include <set>

/*
set容器：
	所有元素都会在插入时自动被排序
本质：
	set / multiset属于关联式容器，底层结构是用二叉树实现。
set/multiset区别：
	set不允许容器中有重复的元素
	multiset允许容器中有重复的元素

构造：
	set<T> st;    		//默认构造函数：
	set(const set &st);	//拷贝构造函数
赋值： I
	set& operator=(const set &st); //重载等号操作符
*/

void printSet(set<int> &s)
{
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

// set容器构造和赋值
void test01()
{
	set<int> s1;

	// 插入数据  只有insert方式
	s1.insert(10);
	s1.insert(40);
	s1.insert(30);
	s1.insert(20);
	s1.insert(30);

	// 遍历容器
	// set容器特点：所有元素插入时候自动排序
	// set容器不允许插入重复值
	printSet(s1);

	// 拷贝构造
	set<int> s2(s1);
	printSet(s2);

	// 赋值
	set<int> s3;
	s3 = s2;
	printSet(s3);
}

// 总结：
// ·set容器插入数据时用insert
// ·set容器插入数据的数据会自动排序

int main()
{
	test01();

	system("pause");

	return 0;
}