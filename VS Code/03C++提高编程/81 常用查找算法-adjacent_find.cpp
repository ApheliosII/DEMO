#include<iostream>
using namespace std; 
#include <vector>
#include <algorithm>

//常用查找算法-adjacent_find
/* 
功能描述：
	查找相邻重复元素
函数原型：
	adjacent_find(iterator beg,iterator end);
	// 查找相邻重复元素，返回相邻元素的第一个位置的选代器
	// beg开始迭代器
	// end结束迭代器 
*/
void test01()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(5);
	v.push_back(4);
	v.push_back(4);
	v.push_back(2);
	v.push_back(4);
	v.push_back(4);
	v.push_back(3);

	//查找相邻重复元素
	vector<int>::iterator it = adjacent_find(v.begin(), v.end());
	if (it == v.end()) 
	{
		cout << "未找到相邻重复元素" << endl;
	}
	else {
		cout << "找到相邻重复元素为：" << *it << endl;
		cout << "前一个元素为：" << *(it - 1) << endl;
	}
}

int main()
{
	test01();

	// system("pause");

	return 0;
}

// 总结：面试题中如果出现查找相邻重复元素，记得用STL中的adjacent_find算法