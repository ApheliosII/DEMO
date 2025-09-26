#include <iostream>
using namespace std;
#include <string>
#include <cstring>

// 字符存取

// string中单个字符存取方式有两种
// char& operator[](int n); //通过[]方式取字符
// char& at(int n);   //通过at方法获取字符

void test01()
{
	string str = "hello";
	cout << "str = " << str << endl;
	cout << "str.size() = " << str.size() << endl;		   // 5
	cout << "str.capacity() = " << str.capacity() << endl; // 预分配内存大小（通常 ≥6） 15

	// 遍历整个字符串（C++17范围循环）
	for (auto &ch : str)
	{
		cout << ch << " ";
	}
	cout << endl;

	// 1、通过[]方式取字符  //char& operator[](int n);
	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i] << " ";
	}
	cout << endl;

	// 2、通过at方法获取字符  //char& at(int n);
	for (int i = 0; i < str.size(); i++)
	{
		cout << str.at(i) << " ";
	}
	cout << endl;

	// 修改单个字符
	str[0] = 'x';
	cout << "str = " << str << endl; // xello

	str.at(1) = 'x';
	cout << "str = " << str << endl; // xxllo
}

void test02()
{
	// 测试：包含 \0 的字符串
	string s1 = "hel\0lo";					   // 字面值中含 \0
	cout << "s1.size() = " << s1.size() << endl; // 输出 3 因为 \0 被当作终止符
	cout << "s1 = " << s1 << endl;			   // 输出 "hel"（遇到第一个 \0 终止，但 s1的实际内容未变））

	//string s2 = "hel\\0lo";  // 输出 "hel\0lo"  // 输出 7 因为 "\\"==  "\"
	string s2("hel\0lo",6);	
	cout << "s2.size() = " << s2.size() << endl; // 输出 6 
	cout << "s2 = " << s2 << endl;			   // 输出 "hello" 

	// 结论：std::string 不依赖 \0 作为终止符，可以自由存储 \0 字符，
	// 但需注意初始化时的隐式截断问题。若需操作含 \0 的字符串，应显式指定长度或使用 append/push_back 等方法。

	string str = "hello";
	// 验证 C 风格字符串的结尾符
	cout << "strlen(str.c_str()) = " << strlen(str.c_str()) << endl; // 输出 5(与 size() 一致)
	cout << "sizeof(str) = " << sizeof(str) << endl;				//	sizeof(str) = 32 字节
	cout << "sizeof(hello) = " << sizeof("hello") << endl;			 // 输出 6(包含 \0 的字面值大小)
	/*关键点解析
	1. strlen(str.c_str()) 的输出逻辑：
		str.c_str() 返回 C 风格字符串（以 \0 结尾的 const char*）。
		strlen 从起始位置开始扫描，直到遇到第一个 \0 终止符，统计 \0 之前的字符数量。
		对于 str = "hello"，c_str() 返回 {'h','e','l','l','o','\0'}，因此 strlen 结果为 5。
		与 str.size() 一致，因为 std::string 的 size() 不包含终止符 \0。
	2. sizeof(str) 的输出逻辑：
	2. sizeof("hello") 的输出逻辑：
		sizeof 是编译时运算符，计算 对象或类型的内存占用字节数。
		字符串字面值 "hello" 的类型是 const char[6]（包含隐含的终止符 \0），因此 sizeof("hello") 结果为 6（每个 char 占 1 字节，共 6 字节）。
	*/

	/* 对比总结
	操作	结果	原因
		strlen(str.c_str())	5	统计 \0 前的字符数，与 str.size() 一致。
		sizeof("hello")	6	计算整个字符数组的内存大小（含隐含的 \0）。
	关键差异
		strlen vs size() vs sizeof：
		strlen：运行时函数，依赖 \0 终止符计算 C 字符串长度。
		size()：std::string 的成员函数，返回实际存储的字符数（不含 \0）。
		sizeof：编译时运算符，计算对象/类型的内存占用（含隐含的 \0）。 
	*/

// 结论：strlen 和 size() 统计逻辑一致，而 sizeof 关注内存布局（含隐含 \0）
}

int main()
{
	test01();
	test02();

	system("pause");

	return 0;
}

// 总结：string字符串中单个字符存取有两种方式，利用	[] 或 at