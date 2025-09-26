#include <iostream>
using namespace std;

// 深拷贝与浅拷贝

//
// 浅拷贝：拷贝的是指针，指向堆区的内存地址，浅拷贝只是复制了指针，并没有复制堆区的内存数据，因此，浅拷贝只是复制了指针，导致两个对象指向同一块堆区的内存数据，修改其中一个对象的值，另一个对象也会受到影响。

// 深拷贝：拷贝的是堆区的内存数据，深拷贝会将堆区的内存数据一份一份的复制，因此，深拷贝会创建新的堆区内存，修改其中一个对象的值，另一个对象不会受到影响。

class Person
{
public:
	Person()
	{
		cout << "Person的默认构造函数的调用" << endl;
	}

	Person(int age, int height)
	{
		m_Age = age;
		m_Height = new int(height); // new 返回的是指针
		cout << "Person的有参构造函数的调用" << endl;
	}

	// 浅拷贝带来的问题是堆区的内存重复释放

	// 自己实现拷贝构造函数  解决浅拷贝带来的问题
	Person(const Person &p)
	{
		cout << "Person的拷贝构造函数的调用" << endl;
		m_Age = p.m_Age;
		// m_Height = p.m_Height;  //编译器默认实现的就是这行代码

		// 深拷贝操作
		m_Height = new int(*p.m_Height); // *p.m_Height 解引用指针，获取堆区的内存数据 160
	}

	~Person()
	{
		// 析构代码，将堆区开辟数据做释放操作
		if (m_Height != NULL)
		{
			delete m_Height;
			m_Height = NULL;
		}
		cout << "Person的析构函数的调用" << endl;
	}

	int m_Age;	   // 年龄
	int *m_Height; // 身高

	// 总结：如果属性有在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的问题
};

void test01()
{
	Person p1(18, 160);

	cout << "p1的年龄为：" << p1.m_Age << " 身高为：" << *p1.m_Height << endl;

	Person p2(p1);

	cout << "p2的年龄为：" << p2.m_Age << " 身高为：" << *p2.m_Height << endl;
}

int main()
{
	test01();

	system("pause");

	return 0;
}
// 输出：
//  Person的有参构造函数的调用
//  p1的年龄为：18 身高为：160
//  Person的拷贝构造函数的调用
//  p2的年龄为：18 身高为：160
//  Person的析构函数的调用
//  Person的析构函数的调用