#include<iostream>
using namespace std;
#include<string>

//作用：用于从键盘获取数据
//数据输入格式：cin >> 变量名;

int main()
{
	//1.整型
	int a = 0;
	cout << "请给整型变量a赋值:" << endl;
	cin >> a;
	cout << "a = " << a << endl;

	//2.浮点型
	float f = 3.14f;
	cout << "请给浮点型变量f赋值:" << endl;
	cin >> f;
	cout << "f = " << f << endl;

	//3.字符型
	char ch = 'a';
	cout << "请给字符型变量ch赋值:" << endl;
	cin >> ch;
	cout << "ch = " << ch << endl;
	cout << "ASCII = " << int(ch) << endl;

	//4.字符串型
	string str = "hello";
	cout << "请给字符串型变量str赋值:" << endl;
	cin >> str;
	cout << "str = " << str << endl;
	 
	//5.布尔类型
	bool flag = false;
	cout << "请给布尔类型flag赋值:" << endl;
	cin >> flag; //输入true或0.1,falg = 0; 输入100,flag = 1
	//bool类型 只要是非0的数值，都表示true
	cout << "flag = " << flag << endl; 

	system("pause");

	return 0;
}