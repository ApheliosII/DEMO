#include <iostream>
#include <vector>
#include <set>
#include <cassert>
using namespace std;

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Helper function to create a linked list from a vector
ListNode *createLinkedList(const vector<int> &values)
{
    if (values.empty())
        return nullptr;
    ListNode *head = new ListNode(values[0]);
    ListNode *current = head;
    for (size_t i = 1; i < values.size(); ++i)
    {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

// Helper function to convert a linked list to a vector
vector<int> linkedListToVector(ListNode *head)
{
    vector<int> values;
    while (head)
    {
        values.push_back(head->val);
        head = head->next;
    }
    return values;
}

void deleteList(ListNode *head)
{
	while (head)
	{
		ListNode *temp = head;
		head = head->next;
		delete temp;
	}
}

class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        multiset<int> s;
        for (auto it = lists.begin(); it != lists.end(); it++)
        {
            while (*it)
            {
                s.insert((*it)->val);
                *it = (*it)->next;
            }
        }
        ListNode *dummy = new ListNode();
        ListNode *res = dummy;
        for (auto it = s.begin(); it != s.end(); it++)
        {
            ListNode *t = new ListNode(*it);
            res->next = t;
            res = res->next;
        }
        return dummy->next;
    }
};
/* 问题分析
原链表指针被修改：在遍历链表时，*it = (*it)->next 会修改 vector 中存储的链表头指针，使其最终指向 nullptr。虽然不影响结果，但会破坏原链表结构，可能导致潜在问题（如内存泄漏）。
效率低下：使用 multiset 的插入操作时间复杂度为 O(N log N)，而更优的方法是使用优先队列（O(N log K)）或分治合并。
空间复杂度高：需要额外存储所有节点的值，而非直接复用原链表节点。 */

int main()
{
    // Solution s;
    // vector<ListNode *> lists;
    // ListNode *l1 = new ListNode(1);
    // l1->next = new ListNode(4);
    // l1->next->next = new ListNode(5);
    // lists.push_back(l1);
    // ListNode *l2 = new ListNode(1);
    // l2->next = new ListNode(3);
    // l2->next->next = new ListNode(4);
    // lists.push_back(l2);
    // ListNode *l3 = new ListNode(2);
    // l3->next = new ListNode(6);
    // lists.push_back(l3);
    // ListNode *res = s.mergeKLists(lists);
    // while (res)
    // {
    //     cout << res->val << " ";
    //     res = res->next;
    // }

    Solution s;

    // Test case 1: Happy path with multiple lists
    vector<ListNode *> lists1 = {
        createLinkedList({1, 4, 5}),
        createLinkedList({1, 3, 4}),
        createLinkedList({2, 6})};
    ListNode *result1 = s.mergeKLists(lists1);
    assert(linkedListToVector(result1) == vector<int>({1, 1, 2, 3, 4, 4, 5, 6}));
    while (result1)
    {
        cout << result1->val << " ";
        result1 = result1->next;
    }

    for (auto &list : lists1) {
        deleteList(list);
    }

    return 0;
}


// ListNode *ans = nullptr;
// 代码	是否调用构造函数？	说明
// ListNode *ans = nullptr;	❌ 否	指针为空，未创建对象
// ListNode ans;	✅ 是	栈上创建对象，调用默认构造函数
// ListNode *p = new ListNode;	✅ 是	堆上创建对象，调用默认构造函数