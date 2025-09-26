/* 
堆（Heap）数据结构介绍（C++实现）

堆是一种特殊的完全二叉树，满足以下性质：
    最大堆：每个父节点的值都 ≥ 其子节点的值（根节点最大）
    最小堆：每个父节点的值都 ≤ 其子节点的值（根节点最小）

核心特性
    完全二叉树结构：可以用数组紧凑存储
    快速访问极值：O(1)时间获取最大值/最小值
    高效插入删除：O(log n)时间插入/删除元素 
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    // 获取父节点索引
    int parent(int i) { return (i - 1) / 2; }
    
    // 获取左子节点索引
    int left(int i) { return 2 * i + 1; }
    
    // 获取右子节点索引
    int right(int i) { return 2 * i + 2; }

    // 上浮操作（插入时使用）
    void siftUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    // 下沉操作（删除时使用）
    void siftDown(int i) {
        int maxIndex = i;
        int l = left(i);
        
        if (l < heap.size() && heap[l] > heap[maxIndex])
            maxIndex = l;
            
        int r = right(i);
        if (r < heap.size() && heap[r] > heap[maxIndex])
            maxIndex = r;
            
        if (i != maxIndex) {
            swap(heap[i], heap[maxIndex]);
            siftDown(maxIndex);
        }
    }

public:
    // 插入新元素
    void insert(int value) {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }

    // 提取最大值
    int extractMax() {
        if (heap.empty()) {
            cerr << "Heap is empty!" << endl;
            return -1;
        }
        
        int max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);
        return max;
    }

    // 查看最大值
    int getMax() {
        if (heap.empty()) {
            cerr << "Heap is empty!" << endl;
            return -1;
        }
        return heap[0];
    }

    // 打印堆内容（调试用）
    void print() {
        for (int val : heap) 
            cout << val << " ";
        cout << endl;
    }
};

int main() {
    MaxHeap heap;
    
    heap.insert(10);
    heap.insert(5);
    heap.insert(20);
    heap.insert(3);
    
    cout << "当前堆内容: ";
    heap.print();  // 输出: 20 10 5 3 
    
    cout << "最大值: " << heap.getMax() << endl;  // 20
    
    cout << "提取最大值: " << heap.extractMax() << endl;  // 20
    cout << "提取后最大值: " << heap.getMax() << endl;    // 10
    
    return 0;
}

/*
输出关键操作说明
插入元素：
    将新元素添加到数组末尾
    执行上浮操作：与父节点比较，如果更大则交换位置
    时间复杂度：O(log n)
删除最大值：
    取出根节点（最大值）
    将最后一个元素移到根位置
    执行下沉操作：与子节点比较，与较大的子节点交换
    时间复杂度：O(log n)
数组索引计算（核心技巧）：
    父节点：(i-1)/2
    左子节点：2*i + 1
    右子节点：2*i + 2

堆的常见用途
    优先队列（系统调度、任务处理）
    堆排序（O(n log n) 原地排序）
    求Top K问题（如：最大的K个元素）
    图算法（Dijkstra最短路径、Prim最小生成树）
   
实际开发中建议使用STL的priority_queue：
*/

#include <queue>
priority_queue<int> maxHeap; // 最大堆
priority_queue<int, vector<int>, greater<int>> minHeap; // 最小堆

// 通过这个实现，新手可以清晰理解堆的核心操作机制，建议尝试添加heapify()方法（将无序数组转为堆）作为练习！