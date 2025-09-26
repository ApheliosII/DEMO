#include <iostream>
using namespace std;

// 封装意义二：
//  类在设计时，可以把属性和行为放在不同的权限下，加以控制
//  访问权限有三种：
//
//  1. public     公共权限   成员 类内可以访问 类外可以访问
//  2. protected  保护权限   成员 类内可以访问 类外不可以访问 儿子可以访问父亲中的保护内容
//  3. private    私有权限   成员 类内可以访问 类外不可以访问 儿子不可以访问父亲的私有内容

class Person
{
public:
	// 公共权限
	string m_Name; // 姓名

protected:
	// 保护权限
	string m_Car; // 汽车

private:
	// 私有权限
	int m_Password; // 银行卡密码

public:
	void func()
	{
		m_Name = "张三";
		m_Car = "拖拉机";
		m_Password = 123456;
	}

	// void show()
	// {
	// 	cout << "姓名：" << m_Name << " 车：" << m_Car << " 银行卡密码：" << m_Password << endl;
	// }
};

int main()
{
	// 实例化具体对象
	Person p1;

	p1.m_Name = "李四";
	// p1.m_Car = "奔驰";  //保护权限内容，类外访问不到
	// p1.m_Password = 123;  //私有权限内容，类外访问不到

	p1.func();
	
	//p1.show();

	system("pause");

	return 0;
}