#include<iostream>
using namespace std;
//#include<string>

//用const防止误操作

//学生结构体定义
struct student
{
	//成员列表
	string name;  //姓名
	int age;      //年龄
	int score;    //分数
};

//const使用场景
//值传递会复制一个副本出来，修改副本不会影响原值
//将函数中的形参改为指针，可以减少内存空间，而且不会复制新的副本出来
void printStudent(const struct student* p) 
{
	//p->age = 100;  //加了const之后，一旦修改就会报错，可以防止函数体中的误操作
	cout << "姓名：" << p->name << " 年龄：" << p->age << " 分数：" << p->score << endl;
}

int main() 
{
	//创建结构体变量
	student s = { "张三",15,70 };

	printStudent(&s);

	cout << "main中张三的年龄：" << s.age << endl;

	system("pause");

	return 0;
}