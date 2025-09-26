#include<iostream>
using namespace std;

//实现通用 对不同类型的数组进行排序的函数
//规则 从大到小
//算法 选择排序
//测试 char数组 int数组

//交换模板
template<typename T>
void mySwap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

//排序算法
template<class T>
void mySort(T arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		int max = i;  //认定最大值下标
		for (int j = i + 1; j < len; j++)
		{
			//认定的最大值 比 遍历出的数值 小
			if (arr[max] < arr[j])
			{
				max = j;  //更新最大值下标
			}
		}
		if (max != i)
		{
			//交换max和i元素
			mySwap(arr[max], arr[i]);
		}
	}
}

//提供打印数组模板
template<class T>
void printArr(T arr[], int len)
{
	for (int i = 0; i < len; i++) 
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void test01()
{
	//测试char数组
	char charArr[] = "badcfe";
	int num = sizeof(charArr) / sizeof(char);
	mySort(charArr, num);
	printArr(charArr, num);
}

void test02()
{
	//测试int数组
	int intArr[] = { 7,5,1,3,9,2,4,6,8 };
	int num = sizeof(intArr) / sizeof(int);
	mySort(intArr, num);
	printArr(intArr, num);
}

void test03()
{
	//测试double数组
	double doubleArr[] = { 3.1,2.2,1.3,4.4,5.5,6.6 };
	int num = sizeof(doubleArr) / sizeof(double);
	mySort(doubleArr, num);
	printArr(doubleArr, num);
}

int main() 
{
	test01();
	test02();
	test03();

	system("pause");

	return 0;
}