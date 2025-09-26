#include<iostream>
using namespace std;
#include<stack>

//栈stack容器

//stack是一种先进后出(First In Last Out, FILO)的数据结构，它只有一个出口
//栈中只有顶端的元素才可以被外界使用，因此栈不允许有遍历行为
//栈中进入数据称为 — 入栈 push
//栈中弹出数据称为 — 出栈 pop

/* 
功能描述：栈容器常用的对外接口
构造函数：
	stack<T> stk;     			//stack采用模板类实现，stack对象的默认构造形式
	stack(const stack &stk); 	//拷贝构造函数
赋值操作：
	stack& operator=(const stack &stk); //重载等号操作符
数据存取：
	push(elem); //向栈顶添加元素
	pop(); 		//从栈顶移除第一个元素
	top();  	//返回栈顶元素
大小操作：
	empty(); 	//判断堆栈是否为空
	size();  	//返回栈的大小 
*/

void test01()
{
	//特点：符合先进后出数据结构
	stack<int>s;

	//入栈
	s.push(10);
	s.push(20);
	s.push(30);
	s.push(40);

	cout << "栈的大小： " << s.size() << endl;

	//只要栈不为空，查看栈顶，并且执行出栈操作
	while (!s.empty())  //不是遍历
	{
		//查看栈顶元素
		cout << "栈顶元素为： " << s.top() << endl;

		//出栈
		s.pop();
	}
	cout << "栈的大小： " << s.size() << endl;
}

int main()
{
	test01();

	system("pause");

	return 0;
}

// 总结：
// ·入栈 --- push
// ·出栈 --- pop
// ·返回栈顶 --- top
// ·判断栈是否为空 --- empty
// ·返回栈大小 --- size