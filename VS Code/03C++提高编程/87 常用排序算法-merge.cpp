#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

// 常用排序算法  merge  有序
/*
功能描述：
	两个容器元素合并，并存储到另一容器中
函数原型：
	merge(iterator beg1, iterator end1,iterator beg2, iterator end2, iterator dest);
	//容器元素合并，并存储到另一容器中
	//注意：两个容器必须是有序的
	//beg1容器1开始迭代器
	//end1容器1结束迭代器
	//beg2容器2开始迭代器
	//end2容器2结束迭代器
	//dest目标容器开始迭代器
*/

class myPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

// void myPrint(int val)
//{
//	cout << val << " ";
// }

void test01()
{
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 1);
	}

	vector<int> vtarget;
	// 目标容器需要提前开辟空间
	vtarget.resize(v1.size() + v2.size());
	// 合并  需要两个有序序列
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vtarget.begin());
	for_each(vtarget.begin(), vtarget.end(), myPrint());
	// for_each(vtarget.begin(), vtarget.end(), myPrint);
	cout << endl;
}

// 总结：merge合并的两个容器必须的有序序列

int main()
{
	test01();

	// system("pause");

	return 0;
}