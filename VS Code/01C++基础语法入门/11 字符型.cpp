#include<iostream>
using namespace std;

int main()
{
	//1.字符型变量创建方式
	//语法：char 变量名 = '字符';
	char ch = 'A';
	cout << ch << endl;

	//2.所占内存大小
	cout << "char字符型变量所占内存空间:" << sizeof(char) << endl; //1字节

	//3.常见错误
	//char ch2 = "b"; //创建字符型变量要用单引号
	//char ch2 = 'abcdef'; //单引号内只能有一个字符
	
	char ch2 = 'abcd';
	cout << "ch2=" << ch2 << endl; //ch2 = d
	
	//4.对应ASCII编码
	//a - 97
	//A - 65
	//大写字母ASCII + 32 = 小写字母ASCII
	cout << "ASCII = " << (int)ch << endl; //查看A的ASCII码为65

	//5.字符型变量的赋值
	ch = 98; //将ASCII码为98的字符赋值给ch
	cout << ch << endl; //b

	system("pause");

	return 0;
}