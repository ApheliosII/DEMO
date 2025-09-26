#include <iostream>
using namespace std;
#include <vector>

#include <numeric>
/*
学习目标：
	掌握常用的算术生成算法
注意：
	算术生成算法属于小型算法，使用时包含的头文件为#include<numeric>
算法简介：
	accumulate //计算容器元素累计总和
	fi11  //向容器中添加元素
*/

// 常用算术生成算法  accumulate
/*
5.5.1 accumulate
功能描述：
	计算区间内容器元素累计总和
函数原型：
	accumulate(iterator beg, iterator end, value);
	// 计算容器元素累计总和
	// beg 开始选代器
	// end 结束迭代器
	// value 起始值
*/

void test01()
{
	vector<int> v;
	for (int i = 0; i <= 100; i++)
	{
		v.push_back(i);
	}

	// 参数3  起始累加值
	int total = accumulate(v.begin(), v.end(), 1000);

	cout << "total = " << total << endl; // 6050
}

// 总结：accumulate使用时头文件注意是numeric，这个算法很实用

int main()
{
	test01();

	// system("pause");

	return 0;
}