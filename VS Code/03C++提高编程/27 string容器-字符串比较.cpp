#include <iostream>
using namespace std;
#include <string>

// 字符串比较

// 比较方式：
// ·字符串比较是按字符的ASCII码进行对比
// =返回 0
// >返回 1
// <返回 -1

// 函数原型：
// int compare(const string&s)const;/与字符串s比较
// int compare(const char *s) const; //与字符串s比较

void test01()
{
	string str1 = "hello";
	string str2 = "xello";
	if (str1.compare(str2) == 0)
	{
		cout << "str1 = str2" << endl;
	}
	else if (str1.compare(str2) > 0) // 1
	{
		cout << "str1 > str2" << endl;
	}
	else //-1 a-97,e-101,h-104,x-120,l-108,o-111
	{
		cout << "str1 < str2" << endl;
	}
}
// 总结：字符串对比主要是用于比较两个字符串是否相等，判断谁大谁小的意义并不是很大

int main()
{
	test01();

	system("pause");

	return 0;
}