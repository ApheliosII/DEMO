#include<iostream>
using namespace std;
//#include<string>

//学生结构体定义
struct student
{
	//成员列表
	string name;  //姓名
	int age;      //年龄
	int score;    //分数
};

//打印学生信息函数
//1、值传递
void printStudent1(student s)
{
	s.age = 200;
	cout << "子函数中 姓名：" << s.name << " 年龄： " << s.age << " 分数：" << s.score << endl;
}

//2、地址传递
void printStudent2(student* p)
{
	p->age = 200;
	cout << "子函数中 姓名：" << p->name << " 年龄： " << p->age << " 分数：" << p->score << endl;
}

int main() 
{
	//结构体做函数参数 
	//将学生传入到一个参数中，打印学生身上所有信息

	student s = { "张三",18,80 };
	
	//1.值传递：不修改主函数数据
	printStudent1(s);
	cout << "主函数中 姓名：" << s.name << " 年龄： " << s.age << " 分数：" << s.score << endl;

	cout << endl;

	//2.地址传递：修改主函数数据
	printStudent2(&s);
	cout << "主函数中 姓名：" << s.name << " 年龄： " << s.age << " 分数：" << s.score << endl;

	system("pause");

	return 0;
}