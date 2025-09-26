#include<iostream>
using namespace std;

#include<string>  //用C++风格字符串时要包含这个头文件       Visual Studio 2019 好像不需要加  自己配置的Visual Studio code 也不需要加

int main()
{
	//1. C风格字符串
	//注1:   char 字符串名 []
	//注2:   等号后面用双引号
	char str[] = "hello world";
	cout << str << endl;

	//2. C++风格字符串
	//包含一个头文件: #include<string> 
	string str2 = "hello world";
	cout << str2 << endl;

	system("pause");

	return 0;
}