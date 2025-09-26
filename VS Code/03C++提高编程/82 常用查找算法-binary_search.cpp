#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

// 常用查找算法-binary_search
/*
功能描述：
	查找指定元素是否存在
函数原型：
	bool bihary_search(iterator beg, iterator end, value);
	// 查找指定的元素，查到返回true 否则false
	// 注意：在无序序列中不可用
	// beg 开始选代器
	// end 结束迭代器
	// value 查找的元素
*/
void test01()
{
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	// v.push_back(2);  // 如果是无序序列，结果未知!!
	// 二分查找
	// 注意：容器元素必须是有序序列 默认升序排序
	bool ret = binary_search(v.begin(), v.end(), 9);
	if (ret)
	{
		cout << "找到了" << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}
}

class myCompare
{
public:
	bool operator()(int a, int b)
	{
		return a > b;
	}
};

// 降序容器的二分查找
void test02()
{
	vector<int> v2;
	for (int i = 0; i < 10; i++)
	{
		v2.push_back(9 - i);
	}

	bool ret = binary_search(v2.begin(), v2.end(), 9, myCompare());
	bool ret1 = binary_search(v2.begin(), v2.end(), 9, greater<int>());
	if (ret1)
	{
		cout << "找到了" << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}
}

// 总结：二分查找法查找效率很高，值得注意的是查找的容器中元素必须的有序序列

int main()
{
	test01();
	test02();

	// system("pause");

	return 0;
}