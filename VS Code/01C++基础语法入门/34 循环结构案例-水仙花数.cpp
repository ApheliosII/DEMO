#include<iostream>
using namespace std;

//每个位数的数字之和等于它本身，即a^3 + b^3 + c^3 = num 即水仙花数

int main() {
	
	//1、先打印所有的三位数
	int num = 100;
	
	do
	{	
		int a = 0;//个位
		int b = 0;//十位
		int c = 0;//百位
		
		a = num % 10;  //获取数字的个位
	    b = num / 10 % 10;  //获取数字的十位
	    c = num / 100;  //获取数字的百位
		
		//2、找到水仙花数
		if (a*a*a + b*b*b + c*c*c == num)//如果是水仙花数，才打印
		{
			cout << num << endl;
		}
		num++;
	} while (num < 1000);

	system("pause");

	return 0;
}