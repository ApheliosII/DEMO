#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

// 二元谓词
class MyCompare
{
public:
	bool operator()(int num1, int num2)
	{
		return num1 > num2;
	}
};


// 普通函数作为谓词：
bool MyCompare2(int num1, int num2)
{
	return num1 > num2;
}

void test01()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(40);
	v.push_back(20);
	v.push_back(30);
	v.push_back(50);

	sort(v.begin(), v.end());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	// 使用函数对象改变算法策略，排序从大到小
	// sort(v.begin(), v.end(), MyCompare()); //
	sort(v.begin(), v.end(), MyCompare2);
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

int main()
{
	test01();

	// system("pause");

	return 0;
}
/* 
默认排序行为：
	sort(v.begin(), v.end())默认按升序排列元素（从小到大）。

自定义排序规则：
	仿函数（Function Object）：通过重载operator()的类实现，例如MyCompare。
			使用时需创建类的实例（如MyCompare()），适合需要保持状态的场景。
	函数指针：直接传递普通函数（如MyCompare2），代码更简洁，但无法保存状态。 

总结：
	仿函数：通过类重载operator()实现，适合复杂逻辑或需要保存状态的场景。
	普通函数：直接传递函数指针，适合简单逻辑。
*/

/*
在 C++ 中，仿函数（Function Object） 和 函数指针 都可以用来定制算法（如排序）的行为，
但它们在功能和使用场景上有本质区别，尤其是“保持状态”的能力。以下是详细解释：

1. 仿函数（Function Object）
定义：仿函数是一个重载了 operator() 的类对象，可以像函数一样被调用。
保持状态的含义：
仿函数是对象，可以拥有成员变量。这意味着它可以在多次调用之间保留数据（状态）。
例如：记录调用次数、缓存中间结果、动态调整比较逻辑等。

class Counter {
private:
    int count = 0;  // 成员变量（状态）
public:
    void operator()() {
        count++;
        cout << "调用了 " << count << " 次" << endl;
    }
};

int main() {
    Counter c;
    c();  // 输出：调用了 1 次
    c();  // 输出：调用了 2 次（状态被保留）
    return 0;
}

2. 函数指针
定义：函数指针直接指向一个普通函数，没有关联的数据。
无法保持状态：
普通函数没有成员变量，无法存储任何状态。
每次调用函数时，只能依赖参数和全局变量（但全局变量会破坏封装性）。

void printCount() {
    static int count = 0; // 使用静态变量模拟状态（不推荐！）
    count++;
    cout << "调用了 " << count << " 次" << endl;
}

int main() {
    printCount(); // 输出：调用了 1 次
    printCount(); // 输出：调用了 2 次
    return 0;
}

虽然通过 static 变量模拟了状态，但这会引发线程安全问题，且破坏了函数的独立性。

3. 关键区别总结
特性	仿函数	函数指针
本质	类对象（可以包含成员变量）	指向函数的指针（无关联数据）
保持状态	✅ 通过成员变量保留状态	❌ 只能依赖参数或全局变量
灵活性	高（可通过构造函数初始化不同状态）	低（逻辑固定）
性能	可能被编译器内联优化	通常无法内联
使用场景	需要状态或复杂逻辑（如动态比较器）	简单逻辑（如纯比较或操作）

5. 现代 C++ 的替代方案
在 C++11 之后，lambda 表达式结合捕获列表可以更简洁地实现状态保存：
int threshold = 30;
sort(v.begin(), v.end(), [threshold](int a, int b) {
    // 根据 threshold 动态比较
    return (a > threshold) > (b > threshold);
});

Lambda 可以捕获外部变量（如 threshold），本质上是通过生成匿名仿函数实现的。

总结
保持状态：仿函数通过成员变量保存数据，适用于需要记录多次调用间信息的场景。
函数指针：简单、无状态，适合一次性操作。
优先选择：需要状态或复杂逻辑时用仿函数或 lambda；简单逻辑用函数指针。
*/