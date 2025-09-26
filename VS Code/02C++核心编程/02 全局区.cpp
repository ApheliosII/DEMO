#include<iostream>
using namespace std;

//*全局变量
int g_a = 10;
int g_b = 10;

//*全局常量
const int c_g_a = 10;
const int c_g_b = 10;

int main()
{
	//全局区
	 
	//全局变量、静态变量、常量

	//创建普通局部变量
	int a = 10;
	int b = 10;
	
	//(int)&a ->(uintptr_t)&a  前者在vs code 报错 , 在 64 位系统中，指针通常是 64 位的，而 int 通常是 32 位的，因此地址信息会被截断。
	cout << "局部变量a的地址：" << (uintptr_t)&a << endl;
	cout << "局部变量b的地址：" << (uintptr_t)&b << endl;
 
	cout << "全局变量g_a的地址：" << (uintptr_t)&g_a << endl;
	cout << "全局变量g_b的地址：" << (uintptr_t)&g_b << endl;

	//*静态变量  在普通变量前面加static,属于静态变量
	static int s_a = 10;
	static int s_b = 10;

	cout << "静态变量s_a的地址：" << (uintptr_t)&s_a << endl;
	cout << "静态变量s_b的地址：" << (uintptr_t)&s_b << endl;

	//*常量
	//*字符串常量
	cout << "字符串常量地址为：" << (uintptr_t)&"hello world" << endl;
	cout << "字符串常量地址为：" << (uintptr_t)&"hello world1" << endl;

	//const修饰的变量
	//const修饰的全局变量，const修饰的局部变量

	//*全局常量
	cout << "全局常量c_g_a地址为：" << (uintptr_t)&c_g_a << endl;
	cout << "全局常量c_g_b地址为：" << (uintptr_t)&c_g_b << endl;

	//局部常量
	const int c_l_a = 10;
	const int c_l_b = 10;  //c-const  l-local  g-global

	cout << "局部常量c_l_a地址为：" << (uintptr_t)&c_l_a << endl;
	cout << "局部常量c_l_b地址为：" << (uintptr_t)&c_l_b << endl;

	system("pause");

	return 0;
}

// 局部变量a的地址：6487628
// 局部变量b的地址：6487624
// 全局变量g_a的地址：4206608
// 全局变量g_b的地址：4206612
// 静态变量s_a的地址：4206616
// 静态变量s_b的地址：4206620
// 字符串常量地址为：4210835
// 字符串常量地址为：4210847
// 全局常量c_g_a地址为：4210692
// 全局常量c_g_b地址为：4210696
// 局部常量c_l_a地址为：6487620
// 局部常量c_l_b地址为：6487616

//不在全局区：局部变量、const修饰的局部变量（局部常量）
//在全局区：全局变量、静态变量static、常量(字符串常量，const修饰的全局变量：全局常量)。