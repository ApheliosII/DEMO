#include<iostream>
using namespace std;

int main()
{
	//1.单精度 float
	//2.双精度 double
	//默认情况下,输出一个小数显示6位有效数字
	float f1 = 3.1415926f; //最后最好加上f表示float，否则默认double
	cout << " f1 = " << f1 << endl; //输出3.14159
	
	double d1 = 3.1415926;
	cout << " d1 = " << d1 << endl; //输出3.14159

	//统计float和double占用的内存空间
	cout << " f1 占用的内存空间为 " << sizeof(f1) << endl; //float 4字节

	cout << " d1 占用的内存空间为 " << sizeof(d1) << endl; //double 8字节

	//科学计数法
	float f2 = 3e2; //3*10^2;
	cout << "f2 = " << f2 << endl;

	float f3 = 3e-2; //3*0.1^2;
	cout << "f3 = " << f3 << endl;

	system("pause");

	return 0;
}