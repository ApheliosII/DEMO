//普通员工文件
#pragma once 
#include<iostream>
using namespace std;
#include "worker.h"

//员工类
class Employee :public Worker
{
public:

	//构造函数：属性初始化
	Employee(int id, string name, int dId);

	//子类重写父类的纯虚函数
	//显示个人信息
	virtual void showInfo();

	//获取职工岗位名称
	virtual string getDeptName();
};