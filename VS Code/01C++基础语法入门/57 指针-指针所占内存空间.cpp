#include<iostream>
using namespace std;

int main() {

	//指针所占内存空间大小
	int a = 10;

	//指针指向数据a的地址
	//int* p;
	//p = &a; 
	int* p = &a;

	//32位操作系统：4字节；64位操作系统：8字节
	cout << *p << endl; //* 解引用
	cout << "sizeof(int*) = " << sizeof(p) << endl;
	cout << "sizeof(char*) = " << sizeof(char*) << endl;
	cout << "sizeof(float*) = " << sizeof(float*) << endl;
	cout << "sizeof(double*) = " << sizeof(double*) << endl;

	system("pause");

	return 0;
}
//输出：
//10
//sizeof(int*) = 8
//sizeof(char*) = 8
//sizeof(float*) = 8
//sizeof(double*) = 8