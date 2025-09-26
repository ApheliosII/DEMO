#include<iostream>
using namespace std;

int main() {

	//利用嵌套循环打印星图
	
	//外层循环执行1次，内层循环执行1轮
	//外层循环
	for (int i = 0; i < 10; i++)
	{
		//内层循环
		for (int j = 0; j < 10; j++)
		{
			cout << "*" << " ";
		}
		cout << endl;
	}

	system("pause");

	return 0;
}