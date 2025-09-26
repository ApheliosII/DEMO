#include <iostream>
using namespace std;

class Person
{
public:
	// Person(int age)
	// {
	// 	age = age;  //系统认为三个age是一样的
	// }

	Person(int age)
	{
		// this指针指向被调用的成员函数所属的对象
		this->age = age;
	}

	void PersonAddAge(Person &p)
	{
		this->age += p.age;
	}

	Person PersonAddAge01(Person &p)
	{
		this->age += p.age;

		// this指向p2的指针，而*p2指向的是p2这个对象本体
		return *this;
	}

	Person &PersonAddAge02(Person &p)
	{
		this->age += p.age;

		// this指向p2的指针，而*p2指向的是p2这个对象本体
		return *this;
	}

	int age;
};

// 1、解决名称冲突
void test01()
{
	Person p1(18);
	cout << "p1的年龄为： " << p1.age << endl;
}

// 2、返回对象本身用 *this
void test02()
{
	Person p1(10);
	Person p2(10);
	Person p3(10);
	Person p4(10);

	p2.PersonAddAge(p1);
	cout << "p2的年龄为： " << p2.age << endl;

	// 链式编程思想
	p3.PersonAddAge02(p1).PersonAddAge02(p1).PersonAddAge02(p1);
	cout << "p3的年龄为： " << p3.age << endl;

	p4.PersonAddAge01(p1).PersonAddAge01(p1).PersonAddAge01(p1);
	cout << "p4的年龄为： " << p4.age << endl;
	// 31行  引用返回  Person&  结果是40
	//        值返回   Person   结果是20
}

int main()
{
	test01();
	test02();

	system("pause");

	return 0;
}
// 输出：
// p1的年龄为： 18
// p2的年龄为： 20
// p3的年龄为： 40
// p4的年龄为： 20

// 解释：
// PersonAddAge02是一个成员函数，它接受一个Person对象的引用作为参数，并将当前对象的age加上传入对象的age。
// this指针指向调用该函数的对象，即p3。
// 函数返回一个Person对象的引用 (return *this;)。
// 由于返回的是对象的引用，可以进行链式调用。即p3.PersonAddAge02(p1)会返回p3的引用，然后可以继续调用PersonAddAge02方法。
// 这里p3的age初始为10，然后分别加上p1的age（10），总共调用了三次该方法，所以p3的最终年龄为40。

// PersonAddAge01也实现了类似的功能，但它返回的是一个Person对象的副本 (return *this;)。
// 由于返回的是对象的副本，每次链式调用实际上都是在副本上操作，而不是在原对象p4上操作。因此，链式调用不会改变p4的age值。
// 这里p4的age初始为10，但在链式调用过程中，每次调用都会返回一个副本并对副本进行操作，最终p4的age值仍然保持为20。

// 总结：
// 1.使用this指针可以明确地区分对象的成员变量和传入的参数，避免了变量名冲突的问题。
// 2.返回对象引用的成员函数（如PersonAddAge02）允许链式调用，因为返回的引用指向的是原始对象本身，后续的调用操作会影响同一个对象。
// 3.而返回对象副本的成员函数（如PersonAddAge01）在链式调用中不会改变原始对象的状态，因为每次调用都是对副本的操作，副本的改变不会影响到原始对象。