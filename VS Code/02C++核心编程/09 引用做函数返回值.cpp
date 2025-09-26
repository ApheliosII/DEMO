#include<iostream>
using namespace std;
	
//引用做函数的返回值

//1、不要返回局部变量的引用
int& test01()
{
	int a = 10;  //局部变量，存放在四区中的栈区
	return a;
}

//2、函数的调用可以作为左值
int& test02()
{
	static int a = 10;  //静态变量，存放在全局区，由全局区数据在程序结束后系统释放
	return a;
}

int main()
{
	int& ref = test01();

	cout << "ref = " << ref << endl;   //第一次可以打印正确的数字，是因为编译器做了保留
	cout << "ref = " << ref << endl;   //第二次这个数据就不再保留，a的内存已经释放（vs 2019）

	int& ref2 = test02(); 

	cout << "ref2 = " << ref2 << endl;
	cout << "ref2 = " << ref2 << endl;

	test02() = 1000;   //如果函数返回值是引用，这个函数调用可以作为左值，相当于 ref2 = 1000, 或者 a = 1000;

	cout << "ref2 = " << ref2 << endl;
	cout << "ref2 = " << ref2 << endl;

	system("pause");

	return 0;
}
//输出：
//ref = -858993460
//ref = -858993460 //vs 2022
//(vs 可以运行 vs code不行)

//ref2 = 10
//ref2 = 10
//ref2 = 1000
//ref2 = 1000