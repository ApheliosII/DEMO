#include <iostream>
using namespace std;
#include <list>

// list容器插入和删除

/* 
	push_back(elem);	   // 在容器尾部加入一个元素
	pop_back();			   // 删除容器中最后一个元素
	push_front(elem);	   // 在容器开头插入一个元素
	pop_front();		   // 从容器开头移除第一个元素
	insert(pos, elem);	   // 在pos位置插elem元素的拷贝，返回新数据的位置。
	insert(pos, n, elem);  // 在pos位置插入n个elem数据，无返回值。
	insert(pos, beg, end); // 在pos位置插入[beg,end)区间的数据，无返回值。
	clear();			   // 移除容器的所有数据
	erase(beg, end);	   // 删除[beg,end)区间的数据，返回下一个数据的位置。
	erase(pos);			   // 删除pos位置的数据，返回下一个数据的位置。
	remove(elem);		   // 删除容器中所有与elem值匹配的元素。
*/

void printList(const list<int> &L)
{
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01()
{
	list<int> L;

	// 尾插
	L.push_back(10);
	L.push_back(20);
	L.push_back(30);

	// 头插
	L.push_front(100);
	L.push_front(200);
	L.push_front(300);

	// 遍历
	printList(L); // 300 200 100 10 20 30

	// 尾删
	L.pop_back();
	printList(L); // 300 200 100 10 20

	// 头删
	L.pop_front();
	printList(L); // 200 100 10 20

	// insert插入
	list<int>::iterator it = L.begin();
	L.insert(++it, 1000);
	cout << "it -> = " << *it << endl; // it -> 100
	printList(L); // 200 1000 100 10 20

	// 删除
	L.erase(it);
	printList(L); // 200 1000 10 20
	
	// 插入操作和删除操作都不会造成原有list迭代器的失效
	it = L.begin(); 
	L.erase(++it);
	printList(L); // 200 10 20

	// 移除
	L.push_back(10000);
	L.push_back(10000);
	L.push_back(10000);
	L.push_back(10000);
	printList(L); // 200 10 20 10000 10000 10000 10000
	L.remove(10000);
	printList(L); // 200 10 20

	// 清空
	L.clear();
	printList(L);
}

int main()
{
	test01();

	system("pause");

	return 0;
}

// 总结：
// ·尾插 --- puph_back
// ·尾删 --- pop_back
// ·头插 --- push_front
// ·头删 --- pop_front
// ·插入 --- insert
// ·删除 --- erase
// ·移除 --- remove
// ·清空 --- clear