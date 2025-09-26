#include<iostream>
using namespace std;

int main() {

	//switch语句

	//请给电影评分 
	//10 ~ 9   经典   
	// 8 ~ 7   非常好
	// 6 ~ 5   一般
	// 5分以下 烂片

	//1、提示
	cout << "请给电影打分" << endl;

	//2、打分
	int score = 0;
	cin >> score;
	cout << "你打的分数为：" << score << endl;

	//3、判断
	switch (score)
	{
	case 10:
	case 9:
		cout << "经典" << endl;
		break;  //退出当前分支
	case 8:
		cout << "非常好" << endl; 
		break;
	case 7:
	case 6:
		cout << "一般" << endl;
		break;
	default:
		cout << "烂片" << endl;
		break;
	}

	// case 里如果没有 break ，那么程序会一直向下执行
	
	//if 和 switch 区别？
	// switch 缺点：语句中表达式类型只能是整型或者字符型，不能是区间
	// switch 优点：结构清晰，执行效率高
	

	system("pause");

	return 0;
}