#include <iostream>
using namespace std;
#include <map>

// map容器 查找和统计
/*
功能描述：
	对map容器进行查找数据以及统计数据
函数原型：
	find(key):  //查找key是否存在，若存在，返回该键的元素的迭代器；若不存在，返回set.end();
	count(key); //统计key的元素个数
*/

void test01()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(3, 30));
	m.insert(pair<int, int>(3, 40)); // 插入失败

	m[3] = 50; // 插入成功

	m.emplace(3, 60); // 插入失败

	// 查找
	map<int, int>::iterator pos = m.find(3);

	if (pos != m.end())
	{
		// cout << "找到了元素 key = " << (*pos).first << " value = " << (*pos).second << endl;
		cout << "找到了元素 key = " << pos->first << " value = " << pos->second << endl;
	}
	else
	{
		cout << "未找到元素" << endl;
	}

	// 统计
	// map中不允许插入重复key 元素
	// multimao统计结果可能大于1
	int num = m.count(3); // 结果是0或1
	cout << "num = " << num << endl;
}

// 总结：
// ·查找 --- find （返回的是迭代器）
// ·统计 --- count （对于map，结果为0或者1）

int main()
{
	test01();

	system("pause");

	return 0;
}