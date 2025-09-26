#include<iostream>
using namespace std;

//可以通过指针来保存变量的地址，通过解引用的方式找到指针指向的内存	

int main() {

	//1、指针的定义
	int a = 10; //定义整型变量a

	//指针定义语法： 数据类型 * 变量名；
	int* p;

	//指针变量赋值
	p = &a; //指针指向变量a的地址
	cout << "a的地址为：" << &a << endl; //打印数据a的地址
	cout << "指针p为：" << p << endl;  //打印指针变量p

	//2、指针的使用
	//可以通过解引用的方式找到指针指向的内存
	//通过*操作指针变量指向的内存
	*p = 1000;
	cout << "a = " << a << endl;
	cout << "*p = " << *p << endl;

	system("pause");

	return 0;
}
//输出：
//a的地址为：0x62fe44
//指针p为：0x62fe44
//a = 1000
//*p = 1000
