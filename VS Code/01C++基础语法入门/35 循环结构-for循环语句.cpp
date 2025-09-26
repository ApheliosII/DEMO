#include<iostream>
using namespace std;

//for循环语句
//语法：for (初始化表达式; 循环条件表达式; 循环后操作表达式) {循环体语句}

int main() {

	//for循环
	//打印数字0`9

	for (int i = 0; i < 10; i++) 
	{
		cout << i << endl;
	}

	/*int i = 0;
	for ( ; ; )
	{
		if (i >= 10) 
		{
			break;
		}
		cout << i << endl;
		i++;
	}*/

	system("pause");

	return 0;
}