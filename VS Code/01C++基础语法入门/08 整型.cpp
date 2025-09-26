// 数据类型存在意义：
// 给变量分配合适的内存空间

#include<iostream>
using namespace std;

int main()
{
	//整型 2字节 -2^15 ~ 2^15-1
	//1.短整型(-32768~32767)
	short num1 = 32768;

	//2.整型 4字节 -2^31 ~ 2^31-1
	int num2 = 32768;

	//3.长整型 windows下为4字节 -2^31 ~ 2^31-1，linux下为4字节（32位），8字节（64位）
	long num3 = 10;

	//4.长长整型 8字节 -2^63 ~ 2^63-1
	long long num4 = 10;

	cout << " num1 = " << num1 << endl; //-32768
	cout << " num2 = " << num2 << endl; //32768
	cout << " num3 = " << num3 << endl; //10
	cout << " num4 = " << num4 << endl; //10 

	system("pause");

	return 0;
}