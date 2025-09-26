#include<iostream>
using namespace std;

int main() {

	//do...while语句

	//do{语句} while(条件表达式);

	//输出0~9
	int num = 0;

	do 
	{
		cout << num << endl;
		num++;
	} 	while (num < 10);
	//do...while和while循环区别在于 do..while 会先执行一次循环语句

	system("pause");

	return 0;
}