#include<iostream>
using namespace std;
//#include<string>
#include <ctime>

//学生结构体定义
struct Student
{
	string sName;
	int score;
};

//老师结构体定义
struct Teacher
{
	string tName;
	Student sArray[5];  //学生数组
};

//给老师和学生赋值的函数
void allocateSpace(Teacher tArray[], int len)
{
	string nameSeed = "ABCDE";

	for (int i = 0; i < len; i++)
	{
		tArray[i].tName = "Teacher";
		tArray[i].tName += nameSeed[i];

		//通过循环给每个老师带的学生赋值
		for (int j = 0; j < 5; j++)
		{
			tArray[i].sArray[j].sName = "Student";
			tArray[i].sArray[j].sName += nameSeed[j];

			tArray[i].sArray[j].score = rand() % 61 + 40;  //40~100随机数
		}
	}
}

void printInfo(Teacher tArray[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << "老师姓名："<<tArray[i].tName << endl;
		for (int j = 0; j < 5; j++)
		{
			cout << "\t学生姓名：" << tArray[i].sArray[j].sName << " 考试分数：" << tArray[i].sArray[j].score << endl;
		}
	}
}

int main() 
{ 
	//随机数种子 头文件 #include <ctime>
	srand((unsigned int)time(NULL));

    //1、创建3名老师的数组
	Teacher tArray[3]; 

	//2、通过函数给3名老师和带的学生的信息赋值
	int len = sizeof(tArray) / sizeof(Teacher);
	allocateSpace(tArray, len);  //创建数据

	//3、打印所有老师和学生信息
	printInfo(tArray, len);  //打印数据

	system("pause");

	return 0;
}