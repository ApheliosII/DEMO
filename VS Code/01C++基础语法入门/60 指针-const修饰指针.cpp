#include<iostream>
using namespace std;

//const修饰指针

int main() {

	int a = 10;
	int b = 10;

	//1、const修饰指针  常量指针
	const int* p1 = &a;
	//指针指向可以改，指针指向的值不可以更改
	p1 = &b; //正确
	//*p1 = 100;  报错

	//2、const修饰常量  指针常量
	int* const p2 = &a;
	//指针指向不可以改，指针指向的值可以更改
	//p2 = &b; //错误
	*p2 = 100; //正确

	//3、const既修饰指针又修饰常量
	const int* const p3 = &a;
	//指针指向和指针指向的值都不可以更改
	//p3 = &b; //错误
	//*p3 = 100; //错误

	system("pause");

	return 0;
}

//技巧：看const右侧紧跟的是指针还是常量，就知道是指针常量还是常量指针。