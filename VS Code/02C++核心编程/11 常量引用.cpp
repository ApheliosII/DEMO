#include<iostream>
using namespace std;

//打印数据函数
//vvoid showValue(int& val)
void showValue(const int& val) {
	
	//val = 1000;
	cout << val << endl;
}

int main()
{
	//常量引用
	//使用的场景，通常用来修饰形参，防止误操作
	
	//int& ref = 10;  引用本身需要一个合法的内存空间，因此这行错误
	
	//加入const就可以了，编译器优化代码，int temp = 10; const int& ref = temp;
	const int& ref = 10;

	//ref = 100;  //加入const后变为只读，不可以修改
	cout << ref << endl;

	//函数中利用常量引用防止误操作修改实参
	int a = 100;
	showValue(a);

	system("pause");

	return 0;
}
//输出：
//10
//100