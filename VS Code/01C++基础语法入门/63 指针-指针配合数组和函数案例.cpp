#include<iostream>
using namespace std;


//案例：冒泡排序
//封装一个函数，利用冒泡排序，实现对整型数组的升序排序
//int arr[10] = { 4,3,6,9,1,2,10,8,7,5 };

//冒泡排序函数  参数1  数组首地址  参数2  数组长度
void bubbleSort(int* arr, int len)  //int * arr 也可以写为int arr[]
{
	// int len = sizeof(arr) / sizeof(int); //数组长度 在函数bubbleSort中计算不出来？
	// 上述代码的问题在于 bubbleSort 函数中计算数组长度的方式不正确。
	// 具体来说，sizeof(a) / sizeof(a[0]) 这种方式在函数内部无法正确获取数组的长度。
	// 当数组作为参数传递给函数时，它会退化为指向其第一个元素的指针，因此 sizeof(a) 实际上返回的是指针的大小，而不是数组的大小。
	// 为了修正这个问题，可以在 main 函数中将数组的长度作为参数传递给 bubbleSort 函数。

	for (int i = 0; i < len - 1; i++) //排序轮数
	{
		for (int j = 0; j < len - 1 - i; j++) //每轮内比较次数
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//打印数组函数
void printArray(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << endl;
	}
}

int main() {

	//1、创建数组
	int arr[10] = { 4,3,6,9,1,2,10,8,7,5 };
	int len = sizeof(arr) / sizeof(arr[0]); //数组长度 在函数bubbleSort中计算不出来？

	//2、创建函数，实现冒泡排序
	bubbleSort(arr, len);

	//3、打印排序后数组
	printArray(arr, len);

	system("pause");

	return 0;
}