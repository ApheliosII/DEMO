#include <iostream>
using namespace std;
#include <fstream> //头文件包含

// 二进制文件 写文件 ios::binary
class Person
{
public:
	char m_Name[64]; // 姓名  不要用string
	int m_Age;		 // 年龄
};

void test01()
{
	// 1、包含头文件 fstream

	// 2、创建流对象
	ofstream ofs("person.txt", ios::out | ios::binary); // output file

	// 3、指定打开方式
	// ofs.open("person.txt", ios::out | ios::binary);

	// 4、写文件
	Person p = {"zhangsan", 18};
	ofs.write((const char *)&p, sizeof(Person));

	// 5、关闭文件
	ofs.close();
}

int main()
{
	test01();

	system("pause");

	return 0;
}
// 总结：
// ·文件输出流对象可以通过write函数，以二进制方式写数据