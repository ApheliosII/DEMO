#include<iostream>
using namespace std;

int main() {

	//空指针：指向内存地址编号为0的空间

	//1、空指针用于给指针变量进行初始化
	int* p = NULL;  //指针变量p指向内存地址编号为0的空间 

	//NULL 和 nullptr 都是宏定义，作用是定义一个指针变量，指向内存地址编号为0的空间
	int* p1 = nullptr;  //指针变量p1指向内存地址编号为0的空间 
	//区别：nullptr 是C++11新标准引入的，可以避免一些潜在的错误

	//2、空指针不能进行访问
	// 0~255之间的内存编号是系统占用的，因此不可以访问
	//访问空指针报错 
	//cout << *p << endl;

	system("pause");

	return 0;
}