#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

// 常用拷贝和替换算法  replace
/*
功能描述：
	将容器内指定范围的旧元素修改为新元素
函数原型：
	replace(iterator beg, iterator end, oldvalue, newvalue);
	//将区间内旧元素替换成新元素
	//beg开始迭代器
	//end结束迭代器
	//oldvalue旧元素
	//newvalue新元素
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

	// 将容器中的20 替换成 2000
	cout << "替换后：" << endl;
	replace(v.begin(), v.end(), 20, 2000);
	for_each(v.begin(), v.end(), myPrint());
	// for_each(v.begin(), v.end(), myPrint);
	cout << endl;
}

// 总结：replace会替换区间内满足条件的所有元素

int main()
{
	test01();

	// system("pause");

	return 0;
}