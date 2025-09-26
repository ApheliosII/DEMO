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

// deque容器赋值操作

void test01()
{
	deque<int> d1; // 默认构造 无参构造

	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i);
	}
	printDeque2(d1);

	// 赋值 operator=
	deque<int> d2;
	d2 = d1;
	printDeque2(d2);

	// assign
	deque<int> d3;
	d3.assign(d1.begin(), d1.end());
	printDeque2(d3);

	// n个elem方式赋值
	deque<int> d4;
	d4.assign(10, 100);
	printDeque2(d4);
}
// 总结：deque赋值操作也与vector相同，需熟练掌握

int main()
{
	test01();

	system("pause");

	return 0;
}