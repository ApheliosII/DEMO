#include <iostream>
using namespace std;
// #include<string>

// 结构体指针

// 定义学生结构体
struct student
{
	// 成员列表
	string name; // 姓名
	int age;	 // 年龄
	int score;	 // 分数
};

int main()
{

	// 1、创建结构体变量
	student s = {"张三", 18, 80}; // struct省略

	// 2、通过指针指向结构体变量
	struct student *p = &s; // stuct可省略

	// 3、通过指针访问结构体变量中的数据
	// 通过结构体指针访问结构体变量中的属性，利用"->"
	cout << "姓名：" << p->name << " 年龄：" << p->age << " 分数：" << p->score << endl;

	cout << "姓名：" << s.name << " 年龄：" << s.age << " 分数：" << s.score << endl;

	system("pause");

	return 0;
}
//总结：通过结构体指针访问结构体变量中的属性，利用"->"