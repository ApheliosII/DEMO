// 案例描述：实现一个通用的数组类，要求如下：
// ·可以对内置数据类型以及自定义数据类型的数据进行存储
// ·将数组中的数据存储到堆区
// ·构造函数中可以传入数组的容量
// ·提供对应的拷贝构造函数以及operator=防止浅拷贝问题
// ·提供尾插法和尾删法对数组中的数据进行增加和删除
// ·可以通过下标的方式访问数组中的元素
// ·可以获取数组中当前元素个数和数组的容量

#include <iostream>
using namespace std;
#include "MyArray.hpp"

void printIntArray(MyArray<int> &arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr[i] << endl;
	}
}

void test01()
{
	MyArray<int> arr1(5);

	for (int i = 0; i < 5; i++)
	{
		// 利用尾插法向数组中插入数据
		arr1.Push_Back(i);
	}
	cout << "arr1的打印输出为： " << endl;
	printIntArray(arr1);

	cout << "arr1的容量为： " << arr1.getCapacity() << endl;
	cout << "arr1的大小为： " << arr1.getSize() << endl;

	MyArray<int> arr2(arr1);
	cout << "arr2的打印输出为： " << endl;
	printIntArray(arr2);

	// 尾删
	arr2.Pop_Back();
	cout << "arr2的尾删后： " << endl;
	cout << "arr2的容量为： " << arr2.getCapacity() << endl;
	cout << "arr2的大小为： " << arr2.getSize() << endl;

	// MyArray <int>arr3(100);
	// arr3 = arr1;
}

// 测试自定义数据类型
class Person
{
public:
	Person() {};

	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

void printPersonArray(MyArray<Person> &arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << "姓名： " << arr[i].m_Name << "\t年龄： " << arr[i].m_Age << endl;
	}
}

void test02()
{
	MyArray<Person> arr(10);

	Person p1("孙悟空", 999);
	Person p2("韩信", 30);
	Person p3("妲己", 20);
	Person p4("赵云", 25);
	Person p5("安琪拉", 27);

	// 将数据插入到数组中
	arr.Push_Back(p1);
	arr.Push_Back(p2);
	arr.Push_Back(p3);
	arr.Push_Back(p4);
	arr.Push_Back(p5);

	// 打印数组
	printPersonArray(arr);

	cout << "arr的容量为： " << arr.getCapacity() << endl;
	cout << "arr的大小为： " << arr.getSize() << endl;
}

int main()
{
	test01();

	test02();

	system("pause");

	return 0;
}

// arr1的打印输出为：
// 0
// 1
// 2
// 3
// 4
// arr1的容量为： 5
// arr1的大小为： 5
// arr2的打印输出为：
// 0
// 1
// 2
// 3
// 4
// arr2的尾删后：
// arr2的容量为： 5
// arr2的大小为： 4
// 姓名： 孙悟空   年龄： 999
// 姓名： 韩信     年龄： 30
// 姓名： 妲己     年龄： 20
// 姓名： 赵云     年龄： 25
// 姓名： 安琪拉   年龄： 27
// arr的容量为： 10
// arr的大小为： 5

// 在const MyArray<Person> &arr参数上使用arr[i]时，出现编译错误的核心原因是：
// 缺少const版本的operator[]重载
// 缺少const版本的getCapacity()和getSize()函数
// 总结
// 当一个对象被声明为const时，它的所有非静态成员函数调用都必须是const成员函数，
// 也就是说，这些函数不能修改对象的状态。例如，如果MyArray类的operator[]没有被声明为const成员函数，
// 那么在一个const对象上调用这个操作符就会导致编译错误。
