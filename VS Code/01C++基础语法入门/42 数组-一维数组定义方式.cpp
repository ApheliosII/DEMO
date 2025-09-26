#include<iostream>
using namespace std;

int main() 
{
	//数组

	//特点：放在一块连续的内存中，可以随机访问元素，元素类型相同，大小固定。0,1,2,...可以通过下标访问数组元素。
	
	/*
	一维数组三种定义方式：
	 1.数据类型 数组名[数组长度];
	 2.数据类型 数组名[数组长度] = { 值1，值2 ... };
	 3.数据类型 数组名[] = { 值1，值2 ... };

	*/

	//1.数据类型 数组名[数组长度];
	int arr[5];
	//元素赋值
	//下标从0开始
	arr[0] = 10;
	arr[1] = 20;
	arr[2] = 30;
	arr[3] = 40;
	arr[4] = 50;

	//访问元素 
	//cout << arr[0] << endl;
	//cout << arr[1] << endl;
	//cout << arr[2] << endl;
	//cout << arr[3] << endl;
	//cout << arr[4] << endl;

	//2.数据类型 数组名[数组长度] = { 值1，值2 ... };
	//如果初始化不完全，用0补
	int arr2[5] = { 10,20,30 };
	
	//逐个
	// cout << arr2[0] << endl;
	// cout << arr2[1] << endl;
	// cout << arr2[2] << endl;
	// cout << arr2[3] << endl;
	// cout << arr2[4] << endl;
	
	//利用循环输出元素
	for (int i = 0; i < 5; i++)
	{
		cout << arr2[i] << endl;
	}

	//3.数据类型 数组名[] = { 值1，值2 ... };
	//定义数组必须有初始长度
	int arr3[] = { 10,20,30,40,50,60,70,80,90 };
	for (int i = 0; i < 9; i++)
	{
		cout << arr3[i] << endl;
	}
	system("pause");

	return 0;
}