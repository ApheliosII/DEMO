#include<iostream>
using namespace std;

int main() {

	int num = 0;
	
	//while 循环语句 
	//while(循环条件) {循环体}
	//while( ) 中填入循环条件 只要循环条件为真，循环体就会一直执行 
	//注：避免死循环出现  while (1)
	while (num < 10)   
	{
		cout << "num = " << num << endl;
		num++;
		//cout << "num = " << num++ << endl;
	}

	system("pause");

	return 0;
}
