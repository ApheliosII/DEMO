#include<iostream>
using namespace std;

int main() {

	//goto语句

	//goto 标记; 

	//goto语句的作用是实现无限循环，但是要注意goto语句的使用要慎重。

	cout << "1" << endl;

	goto FLAG;

	cout << "2" << endl;
	cout << "3" << endl;
	cout << "4" << endl;

FLAG:

	cout << "5" << endl;

	system("pause");

	return 0;
}
//输出：
//1
//5