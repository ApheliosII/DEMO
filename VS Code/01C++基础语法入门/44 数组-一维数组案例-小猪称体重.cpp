#include<iostream>
using namespace std;

int main()
{
	//1.创建数组
	int arr[5] = { 300,350,200,400,250 };

	//2.数组中找到最大值
	int max = 0;  //先认定一个最大值
	for (int i = 0; i < 5; i++) 
	{
		//cout << arr[i] << endl;
		
		//max = arr[i] > max ? arr[i] : max;  //访问数组每个元素，如果数组元素大于最大值，更新最大值
	
		if(arr[i] > max)
		{
			max = arr[i];
		}
	}
	
	//3.打印最大值
	cout <<"最重的小猪体重为："<< max << endl;

	system("pause");

	return 0;
}