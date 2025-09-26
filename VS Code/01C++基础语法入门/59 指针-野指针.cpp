#include<iostream>
using namespace std;

int main()
{

	//野指针：指向非法的内存空间的指针，称为野指针。

	//在程序中，尽量避免出现野指针
	int* p = (int*)0x1100;  //指向地址为0x1100的内存空间，该地址并不存在，因此称为野指针

	//报错
	cout << *p << endl;

	system("pause");

	return 0;
}
//总结：空指针和野指针都不是我们申请的内存空间因此不要访问它们，否则会导致程序崩溃。