#include<iostream>
using namespace std;
//#include<string>

//1、创建学生数据类型：  学生包括（姓名，年龄，分数）
//自定义数据类型，一些类型集合组成的一个类型

//语法： struct 类型名称 { 成员列表 }
struct Student
{
	//成员列表
	string name;  //姓名
	int age;  //年龄
	int score;  //分数

} s3;//顺便创建结构体变量

//2、通过学生类型创建具体学生 三种方法
int main() {

	//2.1 struct Student s1;
	struct Student s1;  //创建时struct关键字可以省略
	//给s1属性赋值,通过'.'访问结构体变量中的属性
	s1.name = "张三";
	s1.age = 18;
	s1.score = 100;
	cout << "姓名：" << s1.name << " 年龄：" << s1.age << " 分数：" << s1.score << endl;

	//2.2 struct Student s2 = {...};
	struct Student s2 = { "李四" , 19 , 80 };
	cout << "姓名：" << s2.name << " 年龄：" << s2.age << " 分数：" << s2.score << endl;

	//2.3 定义结构体时顺便创建结构体变量
	s3.name = "王五";
	s3.age = 20;
	s3.score = 60;
	cout << "姓名：" << s3.name << " 年龄：" << s3.age << " 分数：" << s3.score << endl;

	system("pause");

	return 0;
}

//总结：
//1.定义结构体：struct 类型名称 { 成员列表 }
//2.创建结构体变量： 类型名称 变量名; struct可以省略
//3.结构体变量利用“.”访问其成员。