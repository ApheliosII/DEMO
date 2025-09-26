#include <iostream>
using namespace std;
#include <list>

// list容器 数据存取

/*
3.7.6list数据存取
功能描述：
	对list容器中数据进行存取
函数原型：
	front();	//返回第一个元素。
	back(); 	//返回最后一个元素。
*/

void test01()
{
	list<int> L1;
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);

	// L[0]  不可以用[]方式访问list容器中元素

	// L.at[0]  不可以用at方式访问list容器中元素

	// 原因list本质是链表，不是用连续空间存储的数据，迭代器也是不支持随机访问

	cout << "The first element is: " << L1.front() << endl;
	cout << "The last element is: " << L1.back() << endl;

	// 验证迭代器是不支持随机访问的
	list<int>::iterator it = L1.begin();
	it++; // 支持双向
	it--;
	// it = it + 3;  // 不支持随机访问
}

int main()
{
	test01();

	system("pause");

	return 0;
}

// 总结：
// ·list容器中不可以通过[]或者at方式访问数据
// ·返回第一个元素---front
// ·返回最后一个元素I---back