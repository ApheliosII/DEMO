#include<iostream>
using namespace std;
#include<fstream>  //头文件包含

//二进制文件 读文件
class Person
{
public:

	char m_Name[64];  //姓名
	int m_Age;  //年龄
};

void test01()
{
	//1、包含头文件 fstream

	//2、创建流对象
	ifstream ifs;   //input file

	//3、打开文件  判断文件是否打开成功
	ifs.open("person.txt", ios::in | ios::binary);

	if (!ifs.is_open())
	{
		cout << "file open failed" << endl;
	}

	//4、读文件
	Person p;
	ifs.read((char*)&p, sizeof(Person));

	cout << "name: " << p.m_Name << " age: " << p.m_Age << endl;

	//5、关闭文件
	ifs.close();
}

int main()
{
	test01();

	system("pause");

	return 0;
}