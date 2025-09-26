// https://leetcode.cn/problems/linked-list-cycle/solutions/175734/yi-wen-gao-ding-chang-jian-de-lian-biao-wen-ti-h-2/

#include <bits/stdc++.h>
using namespace std;

/* 链表节点模板
 * T: 节点存储的数据类型 */
template <typename T>
struct Node
{
    T data;     // 节点存储的数据
    Node *next; // 指向下一个节点的指针

    // 默认构造函数：初始化next为空指针
    Node() : next(nullptr) {}

    // 带参构造函数：初始化数据域，next指针置空
    Node(const T &d) : data(d), next(nullptr) {}
};

/* 链表模板
 * T: 节点存储的数据类型 */
template <typename T>
class ListNode
{
public:
    // 默认构造函数：初始化头节点为空
    ListNode() : next(nullptr) {}

    // 带参构造函数：初始化头节点，并将其next指针指向nullptr
    ListNode(const T &data) : val(data), next(nullptr) {}

    T val;          // 节点存储的数据
    ListNode *next; // 指向下一个节点的指针
};

/* 删除指定节点的后继节点
 * p: 要删除其后继节点的目标节点
 * 安全机制：当p或p->next为空时直接返回 */
template <typename T>
void Remove(Node<T> *p)
{
    if (p == nullptr || p->next == nullptr)
    {
        return; // 防御性编程，防止空指针操作
    }
    auto tmp = p->next->next; // 保存要删除节点的下一个节点地址
    delete p->next;           // 释放要删除节点的内存
    p->next = tmp;            // 将当前节点指向下下个节点
}

/* 在指定节点后插入新节点
 * p: 要插入新节点的目标位置（新节点将位于p之后）
 * data: 要插入的数据 */
template <typename T>
void Insert(Node<T> *p, const T &data)
{
    auto tmp = new Node<T>(data); // 创建新节点
    tmp->next = p->next;          // 新节点指向原后继节点
    p->next = tmp;                // 当前节点指向新节点
}

/* 遍历链表并执行操作
 * p: 起始遍历节点
 * vistor: 函数对象/λ表达式，对每个节点执行操作 */
template <typename T, typename V>
void Walk(Node<T> *p, const V &vistor)
{
    while (p != nullptr)
    {
        vistor(p);   // 对当前节点应用操作
        p = p->next; // 移动到下一个节点
    }
}

/* 寻找链表的倒数第k个节点
 * head: 链表头节点
 * k: 倒数第k个节点的序号（从1开始） */
template <typename T>
class Solution01
{
public:
    ListNode<T> *getKthFromEnd(ListNode<T> *head, int k)
    {
        ListNode<T> *p = head, *q = head; // 初始化
        while (k--)
        { // 将 p指针移动 k 次
            p = p->next;
        }
        while (p != nullptr)
        { // 同时移动，直到 p == nullptr
            p = p->next;
            q = q->next;
        }
        return q;
    }
};

/* 寻找链表的中间节点
 * head: 链表头节点 */
template <typename T>
class Solution02
{
public:
    ListNode<T> *middleNode(ListNode<T> *head)
    {
        ListNode<T> *p = head, *q = head;
        while (q != nullptr && q->next != nullptr)
        {
            p = p->next;
            q = q->next->next;
        }
        return p;
    }
};

/* 判断链表是否有环
 * head: 链表头节点 */
template <typename T>
class Solution03
{
public:
    bool hasCycle(ListNode<T> *head)
    {
        ListNode<T> *slow = head;
        ListNode<T> *fast = head;
        while (fast != nullptr)
        {
            fast = fast->next;
            if (fast != nullptr)
            {
                fast = fast->next;
            }
            if (fast == slow)
            {
                return true;
            }
            slow = slow->next;
        }
        return nullptr;
    }
};

/* 环形链表的长度
 * head: 链表头节点 */
// 未验证
template <typename T>
class Solution04
{
public:
    int cycleLength(ListNode<T> *head)
    {
        ListNode<T> *slow = head;
        ListNode<T> *fast = head;
        while (fast != nullptr)
        {
            fast = fast->next;
            if (fast != nullptr)
            {
                fast = fast->next;
            }
            if (fast == slow)
            {
                break;
            }
            slow = slow->next;
        }
        if (fast == nullptr)
        {
            return nullptr; // 没有环
        }

        // 环的长度
        // 法一
        // int len = 0;
        // slow = head;
        // while (slow != fast)
        // {
        //     slow = slow->next;
        //     fast = fast->next;
        // }
        // while (slow != nullptr)
        // {
        //     ++len;
        //     slow = slow->next;
        // }
        // return len;

        // 法二
        int len = 0;
        do
        {
            fast = fast->next->next;
            slow = slow->next;
            ++len;
        } while (slow != fast);

        return len;
    }
};

/* 环形链表的入口节点
 * head: 链表头节点 */
// 未验证
template <typename T>
class Solution05
{
public:
    ListNode<T> *detectCycle(ListNode<T> *head)
    {
        ListNode<T> *slow = head;
        ListNode<T> *fast = head;
        while (fast != nullptr)
        {
            fast = fast->next;
            if (fast != nullptr)
            {
                fast = fast->next;
            }
            if (fast == slow)
            {
                slow = head;
                while (slow != fast)
                {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
            slow = slow->next;
        }
        return nullptr; // 没有环
    }
};

int main()
{
    // 创建头节点（存储值1）
    auto p = new Node<int>(1); // 链表：1 -> nullptr

    // 在头节点后插入值为2的节点
    Insert(p, 2); // 链表变为：1 -> 2 -> nullptr

    // 第一次遍历求节点值总和
    int sum = 0;
    Walk(p, [&sum](const Node<int> *p) -> void
         {
             sum += p->data; // 累加器：1+2=3
         });
    cout << sum << endl; // 输出3

    // 删除头节点的后继节点（值为2的节点）
    Remove(p); // 链表恢复为：1 -> nullptr

    // 第二次遍历求剩余节点的值
    sum = 0;
    Walk(p, [&sum](const Node<int> *p) -> void
         {
             sum += p->data; // 仅剩头节点值1
         });
    cout << sum << endl; // 输出1

    // 内存泄漏提示：实际开发中需手动释放剩余节点
    delete p;

    return 0;
}
