#include<iostream>
using namespace std;
//#include<string>

// 这段C++代码的主要目的是创建一个包含英雄信息的数组，并通过冒泡排序算法按照英雄的年龄升序排列这些信息，最后打印出排序前和排序后的英雄列表。

//1、设计英雄结构体
struct Hero
{
	string name;
	int age;
	string sex;
};

//冒泡排序  实现年龄升序排列
void bubbleSort(Hero arr[], int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (arr[j].age > arr[j + 1].age)
			{
				Hero temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//打印数组
void printHeros(Hero arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << "姓名：" << arr[i].name << " 性别：" << arr[i].sex << " 年龄：" << arr[i].age << endl;
	}
}

int main()
{
	//2、创建数组存放5名英雄
	struct Hero heroarr[5] =
	{
		{"刘备",23,"男"},
		{"关羽",22,"男"},
		{"张飞",20,"男"},
		{"赵云",21,"男"},
		{"貂蝉",19,"女"},
	};

	int len = sizeof(heroarr) / sizeof(Hero);  //获取数组元素个数  heroarr[0]

	cout << "排序前：" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << "姓名：" << heroarr[i].name << " 性别：" << heroarr[i].sex << " 年龄：" << heroarr[i].age << endl;
	}

	//3、排序,年龄升序
	bubbleSort(heroarr, len);  
 
	//4、打印
	cout << "排序后：" << endl;
	printHeros(heroarr, len);  

	system("pause");

	return 0;
}