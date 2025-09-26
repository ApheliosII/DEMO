#include <iostream>
using namespace std;
#include <vector>

// vector容器 预留空间

/*
功能描述：
	·减少vector在动态扩展容量时的扩展次数
函数原型：
	reserve(int len); //容器预留len个元素长度，预留位置不初始化，元素不可访问。
 */

void test01()
{
	vector<int> v;

	// 利用reserve预留空间
	v.reserve(100000);

	int num = 0; // 统计开辟次数
	int *p = NULL;
	for (int i = 0; i < 100000; i++) // 动态分配
	{
		v.push_back(i);

		if (p != &v[0]) // 开辟新空间首地址不一样
		{
			p = &v[0];
			num++;
		}
	}
	cout << "num = " << num << endl; // 不预留18次开辟空间，预留空间后，开辟次数为1
}

int main()
{
	test01();

	system("pause");

	return 0;
}

// 总结：如果数据量较大，可以一开始利用rserve预留空间