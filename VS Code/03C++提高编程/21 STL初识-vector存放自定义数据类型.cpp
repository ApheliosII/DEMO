#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<algorithm>  //标准算法头文件

//vector容器存放自定义数据类型

class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}
	
	friend ostream &operator<<(ostream &out, const Person &p) // 本质  operator<<(cout, p)  简化  cout<<p
	{
		out << "name = " << p.m_Name << " age = " << p.m_Age;
		return out;
	}

	string m_Name;
	int m_Age;
};

void test01()
{
	//创建一个vector容器，数组
	vector<Person> v;

	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);
	Person p5("eee", 50);

	//向容器中插入数据
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);

	//遍历容器中的数据
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		//*it  --  Person
		//it  --   Person*
		//cout << "姓名： " << (*it).m_Name << "\t年龄： " << (*it).m_Age << endl;
		cout << "姓名： " << it->m_Name << "\t年龄： " << it->m_Age << endl;
	}
}

void myPrint(Person*  val)
{
	cout << *val << endl;
}

//存放自定义数据类型 指针
void test02()
{
	vector<Person*> v;

	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);
	Person p5("eee", 50);

	//向容器中插入数据
	v.push_back(&p1);
	v.push_back(&p2);
	v.push_back(&p3);
	v.push_back(&p4);
	v.push_back(&p5); 

	//遍历容器中的数据
	for (vector<Person*>::iterator it = v.begin(); it != v.end(); it++)
	{
		//*it  --  Person*
		//**it  --  Person
		//cout << "：：姓名： " << (**it).m_Name << "\t年龄： " << (**it).m_Age << endl;
		cout << "：：姓名： " << (*it)->m_Name << "\t年龄： " << (*it)->m_Age << endl;
	}

	for_each(v.begin(), v.end(), myPrint); 
}

int main()
{
	test01();

	test02();

	system("pause");

	return 0;
}