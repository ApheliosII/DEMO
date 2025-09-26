// 自己的通用的数组类
#pragma once
#include <iostream>
using namespace std;

template <class T>
class MyArray
{
public:
	// 有参构造 参数 容量
	MyArray(int capacity)
	{
		// cout << "MyArray有参构造调用" << endl;
		this->m_Capacity = capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];
	}

	// 拷贝构造
	MyArray(const MyArray &arr)
	{
		// cout << "MyArray拷贝构造调用" << endl;
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		// this->pAddress = arr.pAddress;  // 浅拷贝：只拷贝指针，不拷贝堆区数据，导致数据共享问题，重复释放

		// 深拷贝
		this->pAddress = new T[arr.m_Capacity];

		// 将arr中的数据都拷贝过来
		for (int i = 0; i < this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}

	// operator= 防止浅拷贝问题   a = b = c 链式编程所以返回 MyArray&
	MyArray &operator=(const MyArray &arr)
	{
		// cout << "MyArray的operator=调用" << endl;
		// 先判断原来堆区是否有数据，如果有先释放 nullptr
		if (this->pAddress != NULL)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}

		// 深拷贝
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[arr.m_Capacity];
		for (int i = 0; i < this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}

	// 尾插法
	void Push_Back(const T &val)
	{
		// 判断容量是否等于大小
		if (this->m_Capacity == this->m_Size)
		{
			return;
		}
		this->pAddress[this->m_Size] = val; // 在数组末尾插入数据
		this->m_Size++;						// 更新数组大小
	}

	// 尾删法
	void Pop_Back()
	{
		// 让用户访问不到最后一个元素，即为尾删，逻辑删除
		// 判断大小是否等于0
		if (this->m_Size == 0)
		{
			return;
		}
		this->m_Size--;
	}

	// 通过下标访问数组中的元素
	// 返回引用：1. 实现左值语义 (支持赋值操作) arr[0] = 100，见总结
	T &operator[](int index) // const
	{
		return this->pAddress[index];
	}

	// 返回数组容量
	int getCapacity()
	{
		return this->m_Capacity;
	}

	// 返回数组大小
	int getSize() // const
	{
		return this->m_Size;
	}

	// 析构函数
	~MyArray()
	{
		if (this->pAddress != NULL)
		{
			// cout << "MyArray析构函数调用" << endl;
			delete[] this->pAddress;
			this->pAddress = NULL;
		}
	}

private:
	T *pAddress; // 指针指向堆区开辟的真实数组

	int m_Capacity; // 数组容量

	int m_Size; // 数组大小
};

/*
在 C++ 中运算符重载返回引用主要是为了支持以下关键特性：

1. 实现左值语义 (支持赋值操作)
arr[0] = 100;  // 需要返回左值引用才能接受赋值

如果返回值而不是引用：
实际修改的是临时副本而非原数组
代码编译时会报错（不能给临时对象赋值）

2. 保持与内置数组的一致性
内置数组的 [] 运算符天然返回引用：

int builtin_arr[5];
builtin_arr[2] = 10;  // 内置数组直接支持赋值

3. 性能优化
避免不必要的拷贝：

引用避免了返回大对象时的拷贝开销
对基本类型（如 int）效果不明显，但对大型类对象意义重大

4. 支持链式调用
arr[1] = arr[2] = 3;  // 需要引用支持连续的赋值操作


对比实验 (如果返回值)
T operator[](int index) {
	return pAddress[index];
}
	
// 实际使用会报错：
arr[0] = 100;  // Error: 表达式必须是可修改的左值

特别说明
如果要实现只读访问，可以额外提供 const 版本：
const T& operator[](int index) const {
	return pAddress[index];
}

*/