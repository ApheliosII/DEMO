#include<iostream>
using namespace std;

//程序运行后：

int* func()  
{
	//利用new关键字   可以将数据开辟到堆区
	//指针 本质也是局部变量，放在栈上,指针保存到数据是放在堆区
	int* a = new int(10);
	return a;  //返回局部变量的地址
}

int main()
{
	//在堆区开辟数据
	int* p = func();

	cout << *p << endl;
	cout << *p << endl;

	system("pause");

	return 0;
}

//10
//10

//栈区：p 0x0010 ->  堆区：10 0x0010