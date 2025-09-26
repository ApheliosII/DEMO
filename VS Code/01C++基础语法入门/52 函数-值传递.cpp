#include<iostream>
using namespace std;

//值传递
//定义函数，实现两个数字交换

//函数不需要返回值，声明写void
void swap(int num1, int num2)
{
	cout << "交换前：" << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;

	int temp = num1;
	num1 = num2;
	num2 = temp;

	cout << "交换后：" << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;

	//return ; 不需要返回值时，可以不写return
}

int main() {

	int a = 10;
	int b = 20;

	cout << "main中的 a = " << a << endl;
	cout << "main中的 b = " << b << endl;

	swap(a, b);   //值传递时，如果形参发生任何改变，并不会影响实参

	cout << "main中的 a = " << a << endl;
	cout << "main中的 b = " << b << endl;

	system("pause");

	return 0;
}
//输出：
//main中的 a = 10
//main中的 b = 20
//交换前：
//num1 = 10
//num2 = 20
//交换后：
//num1 = 20
//num2 = 10
//main中的 a = 10
//main中的 b = 20

//值传递时，如果形参发生任何改变，并不会影响实参