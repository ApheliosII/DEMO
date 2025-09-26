#include<iostream>
using namespace std;

//占位参数
//返回值类型 函数名 （数据类型） {}

//后面会用到
//占位参数 还可以有默认参数
void func(int a, int)
{
	cout << "this is func" << endl;
}

void func2(int a, int = 10)
{
	cout << "this is func2" << endl;
}

int main()
{
	func(10,10);
	
	func2(10);

	system("pause");

	return 0;
}