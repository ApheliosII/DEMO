#include <iostream>
using namespace std;
#include <vector>

// vector容器互换
/*
功能描述：
	·实现两个容器内元素进行互换
函数原型：
	swap(vec); // 将vec与本身的元素互换
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

// 1、基本使用
void test01()
{
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}

	vector<int> v2;
	for (int i = 10; i > 0; i--)
	{
		v2.push_back(i);
	}

	cout << "交换前： " << endl;
	printVector(v1);
	printVector(v2);

	v1.swap(v2);
	cout << "交换后： " << endl;
	printVector(v1);
	printVector(v2);
}

// 2、实际用途
// 巧用swap可以收缩内存空间

void test02()
{
	vector<int> v;
	for (int i = 0; i < 100000; i++)
	{
		v.push_back(i);
	}
	cout << "v的容量为： " << v.capacity() << endl; // v的容量为： 131072
	cout << "v的大小为： " << v.size() << endl;		// v的大小为： 100000

	v.resize(3);									// 重新指定大小
	cout << "v的容量为： " << v.capacity() << endl; // v的容量为： 131072
	cout << "v的大小为： " << v.size() << endl;		// v的大小为： 3

	// 巧用swap收缩内存

	// 原方案（匿名临时对象）
	vector<int>(v).swap(v); // vector<int>(v)  匿名对象: 临时对象在表达式结束时立即析构

	// 你的方案（具名临时对象）
	// vector<int> x(v);  // 创建具名临时对象 x
	// x.swap(v);		  // 交换后，x 会在当前作用域结束时析构

	cout << "v的容量为： " << v.capacity() << endl; // v的容量为： 3
	cout << "v的大小为： " << v.size() << endl;		// v的大小为： 3

	// 推荐原方案：匿名对象更安全，内存立即回收，符合 C++ "资源即时效性"（RAII）的最佳实践。
	// 你的方案适用场景：若需要暂时保留原内存（例如调试时检查旧数据），可具名化临时对象。但需严格确保后续代码不误操作 x。
}

int main()
{
	test01();
	test02();

	system("pause");

	return 0;
}

// 总结：swap可以使两个容器互换，可以达到实用的收缩内存效果