#include <iostream>
using namespace std;
#include <vector>
/*
功能描述：
	·给vector容器进行赋值
函数原型：
	vector&operator=(constvector&vec)：//重载等号操作符
	assign(beg,end); //将[beg,end)区间中的数据拷贝赋值给本身。
	assign(n, elem); //将n个elem拷贝赋值给本身。
 */

void printVector(vector<int> &v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void printVector2(vector<int> &v)
{
	for (const auto &it : v)
	{
		cout << it << " ";
	}
	cout << endl;
}

// vector赋值

void test01()
{
	vector<int> v1; // 默认构造 无参构造

	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	printVector2(v1);

	// 赋值 operator=
	vector<int> v2;
	v2 = v1;
	printVector2(v2);

	// assign
	vector<int> v3;
	v3.assign(v1.begin(), v1.end());
	printVector2(v3);

	// n个elem方式赋值
	vector<int> v4;
	v4.assign(10, 100);
	printVector2(v4);
}

int main()
{
	test01();

	system("pause");

	return 0;
}

// 总结：vector赋值方式比较简单，使用operator=，或者assign都可以