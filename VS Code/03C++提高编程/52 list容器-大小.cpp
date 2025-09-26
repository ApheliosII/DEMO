#include <iostream>
using namespace std;
#include <list>

// list容器大小操作

/*
功能描述：
	对list容器的大小进行操作
函数原型：
	size();   			//返回容器中元素的个数
	empty();  			//判断容器是否为空
	resize(num);  		//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
						//如果容器变短，则末尾超出容器长度的元素被删除。
	resize(num,elem); 	//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。
						//如果容器变短，则末尾超出容器长度的元素被删除。
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
	list<int> L1;
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);

	printList(L1);

	// 判断容器是否为空
	if (L1.empty()) // 为真 代表容器为空
	{
		cout << "L1 is empty" << endl;
	}
	else
	{
		cout << "L1 is not empty" << endl;
		cout << "size of L1 is : " << L1.size() << endl;
	}

	// 重新指定大小
	// L1.resize(15);
	L1.resize(15, 100); // 利用重载版本，可以指定默认填充值，参数2
	printList(L1);		// 如果重新指定的比原来长，默认用0填充新位置

	L1.resize(2);
	printList(L1); // 如果重新指定的比原来短，超出部分会删除掉
}

int main()
{
	test01();

	system("pause");

	return 0;
}

// 总结：
// ·判断是否为空 --- empty
// ·返回元素个数 --- size
// ·重新指定个数 --- resize