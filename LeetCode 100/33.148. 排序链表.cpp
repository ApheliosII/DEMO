#include <iostream>
#include <algorithm>
using namespace std;

#include <vector>

//21. 合并两个有序链表-资料.cpp

struct ListNode
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//stable_sort  //Onlogn;On
class Solution
{
public:
	ListNode *sortList(ListNode *head)
	{
		if (!head || !head->next)
			return head;

		vector<ListNode *> nodes;
		ListNode *t = head;
		while (t)
		{
			nodes.push_back(t);
			t = t->next;
		}

		stable_sort(nodes.begin(), nodes.end(), [](ListNode *a, ListNode *b)
					{ return a->val < b->val; });

		for (size_t i = 1; i < nodes.size(); ++i)
		{
			nodes[i - 1]->next = nodes[i];
		}
		nodes.back()->next = nullptr;

		return nodes.front();
	}
};

ListNode *createList(const vector<int> &values)
{
	ListNode *head = nullptr;
	ListNode *current = nullptr;
	for (int val : values)
	{
		if (!head)
		{
			head = new ListNode(val);
			current = head;
		}
		else
		{
			current->next = new ListNode(val);
			current = current->next;
		}
	}
	return head;
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

int main()
{
	ListNode *head1 = createList({4, 2, 1, 3});
	for (ListNode *t = head1; t != nullptr; t = t->next)
	{
		cout << t->val << " ";
	}
    cout << endl;
	ListNode *sortedHead1 = Solution().sortList(head1);
	for (ListNode *t = sortedHead1; t != nullptr; t = t->next)
	{
		cout << t->val << " ";
	}

	deleteList(sortedHead1);

	// system("pause");
	return 0;
}
