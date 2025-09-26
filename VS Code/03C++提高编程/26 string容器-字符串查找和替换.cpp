#include <iostream>
using namespace std;
#include <string>

// string查找和替换

// 功能描述：
// ·查找：查找指定字符串是否存在
// ·替换：在指定的位置替换字符串

/* 函数原型
int find(const string& str, int pos = 0) const;      //查找str第一次出现位置,从pos开始查找
int find(const char* s, int pos = 0) const;          //查找s第一次出现位置,从pos开始查找
int find(const char* s, int pos, int n) const;       //从pos位置查找s的前n个字符第一次位置
int find(const char c, int pos = 0) const;           //查找字符c第一次出现位置
int rfind(const string& str, int pos = npos) const;  //查找str最后一次位置,从pos开始查找
int rfind(const char* s, int pos = npos) const;      //查找s最后一次出现位置,从pos开始查找
int rfind(const char* s, int pos, int n) const;      //从pos查找s的前n个字符最后一次位置
int rfind(const char c, int pos = 0) const;          //查找字符c最后一次出现位置
string& replace(int pos, int n, const string& str);  //替换从pos开始n个字符为字符串str
string& replace(int pos, int n,const char* s);       //替换从pos开始的n个字符为字符串s
*/

// 1、查找
void test01()
{
	string str1 = "abcdefgde";
	int pos = str1.find("de");
	if (pos == -1)
	{
		cout << "未找到字符串" << endl;
	}
	else
	{
		cout << "找到字符串，pos = " << pos << endl; // 3
	}

	string str2 = "我爱你";
	pos = str2.find("爱");
	cout << "找到字符串，pos = " << pos << endl; // 2
	// 字符串内存布局分析（GBK编码为例）：
	// "我"    "爱"    "你"  
	// 0 1    2 3    4 5    // 每个汉字占2个字节的索引位置

	// 代码解释：
	// "我爱你"每个汉字在GBK编码下占2字节
	// "爱"从第3个字节开始（即索引2）
	// find()返回的是字节级别的偏移量
	

	// rfind 和find区别
	// rfind从右往左查找 find从左往右查找
	pos = str1.rfind("de");
	if (pos == -1)
	{
		cout << "未找到字符串" << endl;
	}
	else
	{
		cout << "pos = " << pos << endl; // 7
	}
}

// 2、替换
void test02()
{
	string str1 = "abcdefg";

	// 从1号位置起3个字符替换为"1111"
	str1.replace(1, 3, "1111");

	cout << "str1 = " << str1 << endl; // a1111efg
}

int main()
{
	test01();
	test02();

	system("pause");

	return 0;
}
// 输出：
// 找到字符串，pos = 3
// 找到字符串，pos = 2
// pos = 7
// str1 = a1111efg

// 总结：
// ·find查找是从左往后，rfind从右往左
// ·find找到字符串后返回查找的第一个字符位置，找不到返回-1
// ·replace在替换时，要指定从哪个位置起，多少个字符，替换成什么样的字符串