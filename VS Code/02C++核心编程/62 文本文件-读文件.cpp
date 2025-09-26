#include <iostream>
using namespace std;
#include <fstream> //头文件包含
#include <string>  //不能省略 vs2019， vscode 可以不需要

// 文本文件 读文件

void test01()
{
	// 1、包含头文件 fstream

	// 2、创建流对象
	ifstream ifs; // input file

	// 3、打开文件  并且判断是否打开成功

	ifs.open("test.txt", ios::in);

	if (!ifs.is_open())
	{
		cout << "file open failed" << endl;
		return;
	}

	// 4、读数据

	// 第一种
	// char buf[1024] = { 0 };
	// while (ifs >> buf)
	//{
	//	cout << buf << endl;
	// }

	// 第二种
	// char buf[1024] = { 0 };
	// while (ifs.getline(buf, sizeof(buf)))
	//{
	//	cout << buf << endl;
	// }

	// 第三种
	string buf;
	while (getline(ifs, buf))
	{
		cout << buf << endl;
	}

	// 第四种
	// char c;
	// while ((c = ifs.get()) != EOF)  //EOF end of file
	//{
	//	cout << c;
	// }

	// 5、关闭文件
	ifs.close();
}

int main()
{
	test01();

	system("pause");

	return 0;
}
// 总结：
// ·读文件可以利用ifstream，或者fstream类
// ·利用is_open函数可以判断文件是否打开成功
// ·close关闭文件
