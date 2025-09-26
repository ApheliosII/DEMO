#include<iostream>
using namespace std;

//函数的声明
//比较函数，实现两个整型数比较，返回较大值

//提前告诉编译器函数的存在，可以利用函数的声明
//函数的声明
//声明可以多次，定义只能一次
int max(int a, int b);
int max(int a, int b);

//定义
//前面有声明，可以在main函数后面定义函数。 2025好像不用声明也可以。
int max(int a, int b)
{
	return a > b ? a : b;
}

int main() {

	int a = 100;
	int b = 200;

	cout << max(a, b) << endl;

	system("pause");

	return 0;
}