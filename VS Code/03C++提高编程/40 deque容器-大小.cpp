#include <iostream>
using namespace std;
#include <deque>

void printDeque(const deque<int> &d)
{
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void printDeque2(const deque<int> &d)
{
	for (const auto &it : d)
	{
		cout << it << " ";
	}
	cout << endl;
}

/*
功能描述
	对deque容器的大小进行操作
函数原型：
	deque.empty(); 			//判断容器是否为空
	deque.size();) 			//返回容器中元素的个数
	deque.resize(num);  	//重新指定容器的长度为num,若容器变长，则以默认值填充新位置。
							//如果容器变短，则末尾超出容器长度的元素被删除。
	deque.resize(num,elem); //重新指定容器的长度为num,若容器变长，则以elem值填充新位置。
							//如果容器变短，则末尾超出容器长度的元素被删除。
*/

// deque容器大小操作
void test01()
{
	deque<int> d1;

	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i);
	}
	printDeque(d1);

	if (d1.empty()) // 为真 代表容器为空
	{
		cout << "d1 is empty" << endl;
	}
	else
	{
		cout << "d1 is not empty" << endl;
		cout << "d1 size is : " << d1.size() << endl;
		// deque容器没有容量概念
	}

	// 重新指定大小
	// d1.resize(15);
	d1.resize(15, 100); // 利用重载版本，可以指定默认填充值，参数2
	printDeque(d1);		// 如果重新指定的比原来长，默认用0填充新位置

	d1.resize(5);
	printDeque(d1); // 如果重新指定的比原来短，超出部分会删除掉
}

int main()
{
	test01();

	system("pause");

	return 0;
}

// 总结：
// ·deque没有容量的概念
// ·判断是否为空---empty
// ·返回元素个数---size
// ·重新指定个数---resize