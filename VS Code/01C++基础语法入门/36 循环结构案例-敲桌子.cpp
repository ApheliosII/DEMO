#include<iostream>
using namespace std;

int main() {

	//敲桌子案例
	//1、打印数字1~100
	for (int i = 1; i <= 100; i++)
	{
		//2、找到特殊数字打印“敲桌子”
		//如果是7的倍数、个位有7、十位有7
		if (i % 7 == 0 || i % 10 == 7 || i / 10 == 7)
		{
			cout << "Knock on the table" << endl;
		}
		else
		{
			cout << i << endl;
		}
	}

	system("pause");

	return 0;
}