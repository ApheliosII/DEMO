#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

// 常用拷贝和替换算法  replace_if
/*
功能描述：
	将区间内满足条件的元素，替换成指定元素
函数原型：
	replace_if(iterator beg,iterator end, _pred, newvalue);
	// 按条件替换元素，满足条件的替换成指定元素
	// beg 开始迭代器
	// end 结束迭代器
	// _pred 谓词
	// newvalue 替换的新元素
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

// 1.分开写
class Greater30 // 谓词
{
public:
	bool operator()(int val)
	{
		return val >= 30;
	}
};

class Greater20 // 谓词
{
public:
	bool operator()(int val)
	{
		return val >= 20;
	}
};

// 2.类构造函数实现
class GreaterThan // 谓词
{
public:
	GreaterThan(int t) : threshold(t) {}

	bool operator()(int val)
	{
		return val >= threshold;
	}

private:
	int threshold;
};

// 3.使用模板类实现谓词
template <int Threshold>
class GreaterThan2
{
public:
	bool operator()(int val)
	{
		return val >= Threshold;
	}
};

void test01()
{
	vector<int> v;
	v.push_back(20);
	v.push_back(30);
	v.push_back(20);
	v.push_back(40);
	v.push_back(50);
	v.push_back(10);
	v.push_back(20);

	cout << "替换前：" << endl;
	for_each(v.begin(), v.end(), myPrint());
	// for_each(v.begin(), v.end(), myPrint);
	cout << endl;

	// 将大于等于30 替换成 3000
	cout << "替换后：" << endl;
	// replace_if(v.begin(), v.end(), Greater30(), 3000);
	// replace_if(v.begin(), v.end(), GreaterThan(20), 3000);
	replace_if(v.begin(), v.end(), GreaterThan2<50>(), 3000);

	for_each(v.begin(), v.end(), myPrint());
	// for_each(v.begin(), v.end(), myPrint);
	cout << endl;
}

// 总结：replace_if按条件查找，可以利用仿函数灵活筛选满足的条件

int main()
{
	test01();

	// system("pause");

	return 0;
}