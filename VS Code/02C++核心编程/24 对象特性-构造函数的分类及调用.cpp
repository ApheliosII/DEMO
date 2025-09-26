#include <iostream>
using namespace std;

// 构造函数的分类及调用
// 1、分类
//   按照参数分类     无参构造(默认构造)  和  有参构造
//   按照类型分类     普通构造  拷贝构造
class Person
{
public:
	// 构造函数
	Person()
	{
		cout << "Person的无参构造函数的调用" << endl;
	}
	Person(int a)
	{
		age = a;
		cout << "Person的有参构造函数的调用" << endl;
	}

	// 拷贝构造函数
	Person(const Person &p)
	{
		// 将传入的人身上所有属性，拷贝到我身上
		age = p.age;
		cout << "Person的拷贝构造函数的调用" << endl;
	}

	// 析构函数
	~Person()
	{
		cout << "Persond的析构函数的调用" << endl;
	}

	int age;
};

// 2、调用
void test01()
{
	// 1、括号法
	Person p1;	   // 默认构造函数调用
	Person p2(10); // 有参构造
	Person p3(p2); // 拷贝构造函数
 
	// 注意事项1：
	// 调用默认构造函数时候，不要加()
	// 因为下面这行代码，编译器会认为是一个函数声明,不会认为在创建对象
	// Person p1();

	cout << "p2的年龄为：" << p2.age << endl;
	cout << "p3的年龄为：" << p3.age << endl;

	// 2、显示法
	Person p11;  //默认构造函数调用
	Person p12 = Person(10);  //有参构造
	Person p13 = Person(p2);  //拷贝构造函数

	// Person(10);  //匿名对象  特点：当前执行结束后，系统会立即回收掉匿名对象
	// cout << "aaa" << endl;

	// 注意事项2
	// 不用利用拷贝构造函数  初始化匿名对象  编译器认为Person(p3) == Person p3; 对象声明
	// Person(p3);

	// 3、隐式转换法
	Person p4 = 10; // 相当于 Person p4 = Person(10);  有参构造
	Person p5 = p4; // 拷贝构造
}

int main()
{
	test01();

	system("pause");

	return 0;
}