#include<iostream>
using namespace std;

//函数重载注意事项
//1、引用作为重载条件
void func15(int& a)  // int& a = 10; 不合法
{
	cout << "func15(int &a) 调用 " << endl;
}

void func15(const int& a) // const int& a = 10; 合法
{
	cout << "func15(const int &a) 调用 " << endl;
}


//2、函数重载碰到函数默认参数
void func16(int a, int b = 10)
{
	cout << "func16(int a, int b = 10) 调用" << endl;
}

void func16(int a)
{
	cout << "func16(int a) 调用" << endl;
}


int main()
{
	int a = 10;
	func15(a); //调用无const
	func15(10);//调用有const

	//func16(10); //碰到默认参数产生歧义，需要避免

	system("pause");

	return 0;
}