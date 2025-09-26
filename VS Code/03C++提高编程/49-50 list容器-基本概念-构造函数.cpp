#include <iostream>
using namespace std;
#include <list>

// 链表list容器

/*
功能：将数据进行链式存储
	链表（list）是一种物理存储单元上非连续的存储结构，数据元素的逻辑顺序是通过链表中的指针链接实现的
	链表的组成：链表由一系列结点组成
	结点的组成：一个是存储数据元素的数据域，另一个是存储下一个结点地址的指针域
	STL中的链表是一个双向循环链表
	由于链表的存储方式并不是连续的内存空间，因此链表list中的迭代器只支持前移和后移，属于双向迭代器

list的优点：
	采用动态存储分配，不会造成内存浪费和溢出
	链表执行插入和删除操作十分方便，修改指针即可，不需要移动大量元素

list的缺点：
	链表灵活，但是空间(指针域) 和 时间（遍历）额外耗费较大
	list有一个重要的性质，插入操作和删除操作都不会造成原有list迭代器的失效，这在vector是不成立的。

总结：STL中list和vector是两个最常被使用的容器，各有优缺点
 */

void printList(const list<int> &L)
{
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
/* 
功能描述：         
	创建list容器        
函数原型：
	list<T> lst;   	 		//list采用采用模板类实现，对象的默认构造形式：
	list(beg,end);   		//构造函数将[beg,end)区间中的元素拷贝给本身。
	1ist(n,elem);    		//构造函数将n个elem拷贝给本身。
	list(const list & lst); //拷贝构造函数。 
*/

void test01()
{
	// 创建list容器
	list<int> L1; // 默认构造 无参构造
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);

	// 遍历容器
	printList(L1);

	// 通过区间方式进行构造
	list<int> L2(L1.begin(), L1.end());
	printList(L2);

	// 拷贝构造
	list<int> L3(L2);
	printList(L3);

	// n个elem方式构造
	list<int> L4(10, 100);
	printList(L4);
}
// 总结：list构造方式同其他几个STL常用容器，熟练掌握即可

/*     ************************自己写链表************************     */
template <typename T>
class ListNode
{
public:
	T val;
	ListNode *next;
	ListNode(T x) : val(x), next(NULL) {} // 建议使用初始化列表提升效率。

	// ListNode(T x)
	// {
	// 	val = x;
	// 	next = NULL;
	// }
};

// 输出
void printListNode(const ListNode<int> *L)
{
	for (const ListNode<int> *it = L; it != NULL; it = it->next)
	{
		cout << it->val << " ";
	}
	cout << endl;
}

void test02()
{
	ListNode<int> *l1 = new ListNode<int>(1);
	ListNode<int> *l2 = new ListNode<int>(2);
	l1->next = l2;
	l1->next->next = new ListNode<int>(3);
	printListNode(l1);

	// 插入temp节点
	ListNode<int> *temp = new ListNode<int>(100);
	l1->next = temp;
	// l1->next->next = l2;
	temp->next = l2;
	printListNode(l1);	 // 1 100 2 3
	printListNode(temp); // 100 2 3

	// 删除temp节点
	l1->next = l2;
	printListNode(l1); // 1 2 3

	// 释放内存
	ListNode<int> *current = l1;
	while (current != NULL)
	{
		ListNode<int> *next = current->next;
		delete current;
		current = next;
	}
}

int main()
{
	// test01();
	test02();

	system("pause");

	return 0;
}