#include<iostream>
using namespace std;

//利用指针作函数参数，可以修改实参的值

//值传递
void swap1(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
	cout << "swap1 a = " << a << endl;
	cout << "swap1 b = " << b << endl;
}

//地址传递
void swap2(int* p1, int* p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

int main() {

	//指针和函数

	//1、值传递
	int a = 10;
	int b = 20;
	swap1(a, b);  //值传递不会改变实参

	cout << "swap1 a = " << a << endl;
	cout << "swap1 b = " << b << endl;

	//2、地址传递：传的是地址，而不是值
	//如果是地址传递，可以修饰实参
	swap2(&a, &b);  //地址传递会改变实参

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	system("pause");

	return 0;
}