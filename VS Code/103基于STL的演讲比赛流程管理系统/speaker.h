#pragma once
#include<iostream>
using namespace std;

//选手类
class Speaker  
{
public:  //可以私有 set get
	string m_Name;  //姓名
	double m_Score[2];  //分数  最多有两轮得分
};