#include<iostream>
using namespace std;
//#include<string>

//结构体数组
//语法：struct 结构体名 数组名[元素个数] = { {成员初始值列表},{成员初始值列表},... };

//1、定义结构体
struct Student
{
	//成员列表
	string name;  //姓名
	int age;      //年龄
	int score;    //分数
};

int main65() {

	//2、创建结构体数组
	struct Student stuArray[3] =
	{
		{"张三",18,80 },
		{"李四",19,60 },
		{"王五",20,70 }
	};
	
	//3、给结构体中的元素赋值
	stuArray[2].name = "赵六";
	stuArray[2].age = 80;
	stuArray[2].score = 60;

	//4、遍历结构体数组
	for (int i = 0; i < 3; i++)
	{
		cout << "姓名：" << stuArray[i].name 
		<< " 年龄：" << stuArray[i].age 
		<< " 分数：" << stuArray[i].score << endl;
	}
/* 	
	for (const Student& i : stuArray)
	{
		cout << "姓名：" << i.name << " 年龄：" << i.age << " 分数：" << i.score << endl;
	}
 */

	system("pause");

	return 0;
}      