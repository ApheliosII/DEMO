#include<iostream>
using namespace std;

int main() {

	//选择结构-多行if语句

	//1、输入考试分数
	int score = 0;
	cout << "请输入考试分数：" << endl;
	cin >> score;

	//2、提示用户输入的分数
	cout << "您输入的分数为： " << score << endl;

	//3、判断
	if (score > 600)
	{
		cout << "我考上了一本大学" << endl;
	}
	else
	{
		cout << "我未考上一本大学" << endl;
	}

	system("pause");

	return 0;
}