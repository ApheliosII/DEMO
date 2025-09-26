#include<iostream>
using namespace std;

//程序运行后：栈区，堆区

//栈区注意事项  ——  不要返回局部变量的地址
//栈区的数据由编译器管理开辟和释放

int* func(int b)  //形参数据也会放在栈区
{
	b = 100;
	int a = 10;  //局部变量  存放在栈区，栈区的数据在函数执行完后自动释放
	return &a;  //返回局部变量的地址
}

int main()
{
	//接收func函数返回值
	int b = 0;
	int* p = func(b);

	cout << *p << endl;  //第一次可以打印正确的数字，是因为编译器做了保留(vs code mingw 运行不了)
	cout << *p << endl;  //第二次这个数据就不再保留（vs2019）

	cout << "12" << endl;
	cout << *p << endl;

	system("pause");

	return 0;
} 

//vs 2022输出：
// 10
// 10
// 12
// -858993460