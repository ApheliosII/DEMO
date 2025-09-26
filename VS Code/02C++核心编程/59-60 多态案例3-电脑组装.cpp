#include <iostream>
using namespace std;

// 多态案例3 电脑组装
// 案例描述：
//
// 电脑主要组成部件为CPU（用于计算），显卡（用于显示），内存条（用于存储）
// 将每个零件封装出抽象基类，并且提供不同的厂商生产不同的零件，例如Intel厂商和Lenovo厂商
// 创建电脑类提供让电脑工作的函数，并且调用每个零件工作的接口
// 测试时组装三台不同的电脑进行工作

// 抽象不同零件类
// 抽象CPU类
class CPU
{
public:
	// 抽象计算函数
	virtual void calculator() = 0;

	// 虚析构函数，防止内存泄漏，这里子类没有数据在堆区，所以可以不写虚析构函数，最好写上
	virtual ~CPU() {};
};

// 抽象显卡类
class VideoCard
{
public:
	// 抽象显示函数
	virtual void display() = 0;

	virtual ~VideoCard() {};
};

// 抽象内存条类
class Memory
{
public:
	// 抽象存储函数
	virtual void storage() = 0;

	virtual ~Memory() {};
};

// 电脑类
class Computer
{
public:
	Computer(CPU *cpu, VideoCard *vc, Memory *mem)
	{
		m_cpu = cpu;
		m_vc = vc;
		m_mem = mem;
	}

	// 提供工作函数
	void work()
	{
		// 让零件工作起来，调用接口
		m_cpu->calculator();

		m_vc->display();

		m_mem->storage();
		// 多态
	}

	// 提供析构函数 释放3个电脑零件
	~Computer()
	{
		// 释放CPU零件
		if (m_cpu != NULL)
		{
			delete m_cpu;
			m_cpu = NULL;
		}
		// 释放显卡零件
		if (m_vc != NULL)
		{
			delete m_vc;
			m_vc = NULL;
		}
		// 释放内存条零件
		if (m_mem != NULL)
		{
			delete m_mem;
			m_mem = NULL;
		}
	}

private:
	CPU *m_cpu;		 // CPU的零件指针
	VideoCard *m_vc; // 显卡零件指针
	Memory *m_mem;	 // 内存条零件指针
};

// 具体厂商
// Inter厂商
class IntelCPU : public CPU
{
public:
	virtual void calculator()
	{
		cout << "Intel的CPU开始计算了！" << endl;
	}
};

class IntelVideoCard : public VideoCard
{
public:
	virtual void display()
	{
		cout << "Intel的显卡开始显示了！" << endl;
	}
};

class IntelMemory : public Memory
{
public:
	virtual void storage()
	{
		cout << "Intel的内存条开始存储了！" << endl;
	}
};

// Lenovo厂商
class LenovoCPU : public CPU
{
public:
	virtual void calculator()
	{
		cout << "Lenovo的CPU开始计算了！" << endl;
	}
};

class LenovoVideoCard : public VideoCard
{
public:
	virtual void display()
	{
		cout << "Lenovo的显卡开始显示了！" << endl;
	}
};

class LenovoMemory : public Memory
{
public:
	virtual void storage()
	{
		cout << "Lenovo的内存条开始存储了！" << endl;
	}
};

void test01()
{
	// 第一台电脑零件
	CPU *intelCpu = new IntelCPU;
	VideoCard *intelCard = new IntelVideoCard;
	Memory *intelMem = new IntelMemory;

	cout << "第一台电脑开始工作" << endl;
	// 创建第一台电脑
	Computer *computer1 = new Computer(intelCpu, intelCard, intelMem);
	computer1->work();
	delete computer1;

	cout << "-----------------------" << endl;
	cout << "第二台电脑开始工作" << endl;
	// 第二台电脑组装
	Computer *computer2 = new Computer(new LenovoCPU, new LenovoVideoCard, new LenovoMemory);
	computer2->work();
	delete computer2;

	cout << "-----------------------" << endl;
	cout << "第三台电脑开始工作" << endl;
	// 第三台电脑组装
	Computer *computer3 = new Computer(new LenovoCPU, new IntelVideoCard, new LenovoMemory);
	computer3->work();
	delete computer3;
}

int main()
{
	test01();

	system("pause");

	return 0;
}

// 在 C++多态场景 中，是否要为 CPU 基类添加虚析构函数，需要根据 对象销毁方式 决定：

// 必须加虚析构函数的情况 ✅
// 如果存在以下操作：
// CPU* cpu = new IntelCPU();  // 基类指针指向派生类对象
// delete cpu;                 // 通过基类指针销毁派生类对象

// 必须添加虚析构函数，否则会导致：
// 派生类析构函数不执行（内存泄漏风险）
// 未定义行为（UB）

// 可以不加的情况 ❌
// 如果满足以下所有条件：
// 不通过基类指针销毁对象（例如直接 delete 派生类指针）
// 派生类没有需要释放的资源（例如堆内存、文件句柄等）

// 总结：基类不加虚析构函数， 
// 当前代码可能侥幸运行，但属于 未定义行为，不可依赖。
// 必须添加虚析构函数，这是 C++ 多态设计的必要规范。
// 防御性编程：即使当前子类无资源，也要为未来可能的扩展提供保障。