#include<iostream>

// #include<cstdint>  //uintptr_t 作用：获取指针的实际地址，

using namespace std;

int main() {

	//二维数组名称用途

	//1.可以查看占用内存空间大小
	int arr[2][3] =
	{
		{1,2,3},
		{4,5,6}
	};
	cout << "二维数组占用内存大小： " << sizeof(arr) << endl;
	cout << "二维数组一行大小： " << sizeof(arr[0]) << endl;
	cout << "二维数组元素大小： " << sizeof(arr[0][0]) << endl;

	cout << "二维数组行数： " << sizeof(arr) / sizeof(arr[0]) << endl;
	cout << "二维数组列数： " << sizeof(arr[0]) / sizeof(arr[0][0]) << endl;

	//2.可以查看二维数组首地址
	//十六进制
	cout << "二维数组首地址：" << arr << endl;
	cout << "二维数组第一行地址：" << arr[0] << endl;
	cout << "二维数组第二行地址：" << arr[1] << endl;

	cout << "二维数组第一个元素地址：" << &arr[0][0] << endl;
	cout << "二维数组第二个元素地址：" << &arr[0][1] << endl;

	//十进制
	cout << "二维数组首地址：" <<(uintptr_t)arr << endl;
	cout << "二维数组第一行地址：" << (uintptr_t)arr[0] << endl;
	cout << "二维数组第二行地址：" << (uintptr_t)arr[1] << endl;

	cout << "二维数组第一个元素地址：" << (uintptr_t)&arr[0][0] << endl;
	cout << "二维数组第二个元素地址：" << (uintptr_t)&arr[0][1] << endl;

	system("pause");

	return 0;
}
//输出：
// 二维数组占用内存大小： 24
// 二维数组一行大小： 12
// 二维数组元素大小： 4
// 二维数组行数： 2
// 二维数组列数： 3
// 二维数组首地址：0x62fe30
// 二维数组第一行地址：0x62fe30
// 二维数组第二行地址：0x62fe3c
// 二维数组第一个元素地址：0x62fe30
// 二维数组第二个元素地址：0x62fe34
// 二维数组首地址：6487600
// 二维数组第一行地址：6487600
// 二维数组第二行地址：6487612
// 二维数组第一个元素地址：6487600
// 二维数组第二个元素地址：6487604