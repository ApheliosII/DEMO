#include<iostream>
using namespace std;

int main() 
{
	//利用冒泡排序实现升序排列
	int arr[9] = { 4,2,8,0,5,7,1,3,9 };
	cout << "排序前before:" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	//1.比较相邻的元素。如果第一个比第二个大，就交换他们两个。
	//2.对每一对相邻元素作同样的工作，除了最后一个。执行完毕后，找到第一个最大值。
	//3.重复步骤1~2，每次比较次数-1，直到排序完成。

	//总共排序轮数为：元素个数 - 1
	for (int i = 0; i < 9 - 1; i++)
	{
		//内层循环对比  每轮比较次数 = 元素个数 - 1 - 当前论数
		for (int j = 0; j < 9 - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				//如果第一个比第二个大，就交换他们两个。
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	cout << "排序后after:" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	system("pause");

	return 0;
}