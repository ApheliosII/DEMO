#include<iostream>
using namespace std;

int main() {

	//指针和数组
	//利用指针访问数组中的元素

	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };

	//指向数组的指针
	int* p = arr;  //arr就是数组的首地址

	cout << "第一个元素: " << arr[0] << endl;
	cout << "利用指针访问第一个元素: " << *p << endl;

	cout << "利用指针遍历数组: " << endl;
	for (int i = 0; i < 10; i++)
	{
		//cout << arr[i] << endl;
		
		//利用指针遍历数组
		cout << *p << endl;
		p++;  //让指针向后偏移4个字节 
	}

	system("pause");

	return 0;
}

//输出:
//第一个元素: 1
//利用指针访问第一个元素: 1
//利用指针遍历数组:
//1
//2
//3
//4
//5
//6
//7
//8
//9