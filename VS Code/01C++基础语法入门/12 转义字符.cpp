#include<iostream>
using namespace std;

int main()
{
	//转义字符
	//作用：用于表示一些不能显示出来的ASCII字符，如\n、\t、\\等。

	//换行符 \n 010
	
	cout << "hello world\n";
	
	//反斜杆 \\ 092

	cout << "\\" << endl;
	
	//水平制表符 \t 009 作用:整齐输出数据 

	cout << "aaaa\thello world" << endl;
	cout << "aa\thello world" << endl;
	cout << "aaa\thello world" << endl;

	cout << "aaaa hello world" << endl;
	cout << "aa hello world" << endl;
	cout << "aaa hello world" << endl;
	
	system("pause");

	return 0;
}