#include<iostream>
using namespace std;

int main()
{
	//整型:short(2)   int(4)   long(4)   long long(8)
	//sizeof算出数据类型占用内存大小
	//语法: sizeof ( 数据类型/变量 )
	short num1 = 10;

	cout << "num1 所占内存空间为： " << sizeof(num1) << endl; //输出结果为2

	cout << "short 类型所占内存空间为： " << sizeof(short) << endl; //2

	cout << "int 类型所占内存空间为： " << sizeof(int) << endl;  //4

	cout << "long 类型所占内存空间为： " << sizeof(long) << endl;  //4

	cout << "long long 类型所占内存空间为： " << sizeof(long long) << endl;  //8

	//整型大小比较
	//short < int <= long <= long long

	system("pause");

	return 0;
}