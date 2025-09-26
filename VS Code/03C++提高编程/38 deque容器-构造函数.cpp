#include <iostream>
using namespace std;
#include <deque>
#include <vector>

// deque容器  双端数组  构造函数

/*
功能：
	双端数组，可以对头端进行插入删除操作
deque与vector区别：
	vector对于头部的插入删除效率低，数据量越大，效率越低
	deque相对而言，对头部的插入删除速度回比vector快
	vector访问元素时的速度会比deque快，这和两者内部实现有关

deque内部工作原理：
	deque内部有 中控器 维护每段缓冲区中的内容，缓冲区中存放真实数据
	中控器维护的是每个缓冲区的地址，使得使用deque时像一片连续的内存空间
	deque容器的迭代器也是 支持随机访问的选代器

功能描述：
	deque容器构造
函数原型：
	deque<T> deqT;     		 //默认构造形式
	deque(beg, end);  `		 //构造函数将[beg,end)区间中的元素拷贝给本身。
	deque(n, elem);   		 //构造函数将n个elem拷贝给本身。
	deque(const deque &deq); //拷贝构造函数
*/

void printDeque(const deque<int> &d)
{
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		// *it = 100; // 容器里中的数据不可以修改了
		cout << *it << " ";
	}
	cout << endl;
}

void printDeque2(const vector<int> &d)
{
	for (const auto &it : d)
	{
		// it = 100; // 容器里中的数据不可以修改了
		cout << it << " ";
	}
	cout << endl;
}

void test01()
{
	deque<int> d1; // 默认构造 无参构造
	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i);
	}
	printDeque(d1);

	// 通过区间方式进行构造
	deque<int> d2(d1.begin(), d1.end());
	printDeque(d2);

	// n个elem方式构造
	deque<int> d3(10, 100);
	printDeque(d3);

	// 拷贝构造
	deque<int> d4(d3);
	printDeque(d4);

	vector<int> v5{1, 2, 3, 4};
	printDeque2(v5);

	deque<int> d5{1, 2, 3};
	printDeque(d5);

	printDeque(deque<int>{1, 2});
	// 如果函数参数 deque<int> &d 此调用不合法，因为临时对象（右值）无法绑定到非 const 左值引用，会导致编译错误。
}
// 总结：deque容器和vector容器的构造方式几乎一致，灵活使用即可

int main()
{
	test01();

	system("pause");

	return 0;
}
/* 
在C++中，当函数的参数类型为非const左值引用（如 deque<int>&）时，尝试传递一个临时对象（右值）会导致编译错误。原因如下：

1. 临时对象的性质
临时对象（例如 deque<int>{1, 2}）是右值（rvalue），它们没有持久的内存地址，生命周期仅限于当前表达式结束时。例如：

2. 非const左值引用的限制
C++规定，非const左值引用（T&）只能绑定到左值（lvalue），即具有明确存储位置的对象
但临时对象（右值）无法绑定到非const左值引用：

3. 为什么禁止这种绑定？
如果允许非const左值引用绑定到右值，会导致以下问题：
	悬空引用风险：临时对象会在表达式结束后立即销毁，但非const引用可能被误认为持有持久对象，后续访问会导致未定义行为。
	逻辑矛盾：非const引用暗示函数可能修改传入的对象，但修改一个即将销毁的临时对象毫无意义。 

4. 解决方案：使用 const 引用
	将参数改为 const 左值引用（const T&）即可接受临时对象：

5. C++11 后的补充：右值引用
	如果确实需要修改临时对象（罕见场景），可以使用右值引用（T&&）：

总结:
	非const左值引用（T&）只能绑定到左值，无法接受临时对象。
	临时对象（右值）必须通过 const T& 或 T&& 传递。
	最佳实践：若函数不修改参数，始终使用 const T&，以提高通用性和安全性。
*/