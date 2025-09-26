#include <iostream>
#include <queue>
#include <vector>
using namespace std;
/*
C++中的priority_queue是一种容器适配器，它基于堆数据结构实现，允许以优先级顺序处理元素。以下是其主要特性的详细介绍：

1. 基本特性
定义：位于头文件 <queue> 中，默认情况下，元素按降序排列（最大堆，队首为最大元素）。
底层容器：默认使用 vector，但也可选择 deque 等其他支持随机访问迭代器的容器。
操作复杂度：
插入（push）和删除（pop）操作：O(log n)
访问队首元素（top）：O(1)

2. 声明方式
 */
// 默认声明（最大堆）
// priority_queue<int> pq;

// 最小堆声明
// priority_queue<int, vector<int>, greater<int>> min_pq;

// 自定义类型与比较器
struct MyStruct
{
    int value;
};
struct Compare
{
    bool operator()(const MyStruct &a, const MyStruct &b)
    {
        return a.value < b.value; // 最大堆；若改为 '>' 则为最小堆 (个人理解：子节点<父节点)
    }
};

// priority_queue<MyStruct, vector<MyStruct>, Compare> custom_pq;
/* 3. 常用成员函数
push(const T& val): 插入元素。
pop(): 移除队首元素（最高优先级）。
top(): 返回队首元素的引用。
empty(): 判断队列是否为空。
size(): 返回元素个数。 */

int main()
{
    priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.push(2);

    while (!pq.empty())
    {
        cout << pq.top() << " "; // 输出：4 3 2 1
        pq.pop();
    }

    vector<int> vec = {3, 1, 4, 2, 5};
    priority_queue<int> q(vec.begin(), vec.end());
    while (!q.empty())
    {
        cout << q.top() << " "; // 输出：5 4 3 2 1
        q.pop();
    }

    return 0;
}