#include<iostream>
using namespace std;
#include<string>

//string求子串

/* 
功能描述：
	从字符串中获取想的子串
函数原型：
	string substr(int pos = 0，int n = npos) const; //返回由pos开始的n个字符组成的字符串
 */

void test01()
{
	string str = "abcdefg";

	string subStr = str.substr(1, 3);

	cout << "subStr = " << subStr << endl;  //bcd
}

//实用操作
void test02()
{
	string email = "zhangsan@sina.com";

	//从邮件地址中 获取 用户名信息
	
	//int pos = 0;
	//for (int i = 0; i < email.size(); i++)
	//{
	//	if (email[i]=='@')
	//	{
	//		pos = i;
	//	}
	//}

	int pos = email.find("@");  
	cout << pos << endl;  //8

	string usrName = email.substr(0, pos);
	cout << "usrName = " << usrName << endl;
}
int main()
{
	test01();

	test02();

	system("pause");

	return 0;
}

// 总结：灵活的运用求子串功能，可以在实际开发中获取有效的信息