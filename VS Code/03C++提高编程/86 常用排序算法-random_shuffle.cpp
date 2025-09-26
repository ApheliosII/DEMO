#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <ctime>

#include <random>
#include <chrono>

// 常用排序算法  random_shuffle

/*
功能描述：
	洗牌指定范围内的元素随机调整次序
函数原型：
	random_shuffle(iterator beg,iterator end);
	// 指定范围内的元素随机调整次序
	// beg 开始选代器
	// end 结束代器
*/
void myPrint(int val)
{
	cout << val << " ";
}

void test01()
{
	srand((unsigned int)time(NULL)); // 随机数种子

	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	// 利用洗牌算法打乱顺序
	random_shuffle(v.begin(), v.end()); // 依赖rand()

	for_each(v.begin(), v.end(), myPrint);
	cout << endl;
}

// #include <algorithm>
// #include <random>
// #include <vector>

// 使用shuffle（推荐方式）：
void test02()
{
	vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	// 初始化高质量随机生成器
	random_device rd;	// 随机种子
	mt19937 gen(rd()); // Mersenne Twister引擎
	std::cout << "Entropy: " << rd.entropy() << std::endl;  // 输出 0 表示伪随机
	// 优点：在支持真随机数的平台（如 Linux/macOS）上，std::random_device 会从硬件熵池（如 CPU 温度、键盘事件）获取高质量随机种子。
	// 注意：某些平台（如旧版 MinGW）可能将 std::random_device 实现为伪随机生成器，此时需改用其他方法。

	// 混合种子：random_device + 时间戳
	// random_device rd;
	// auto time_seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	// seed_seq seed_seq{rd(), static_cast<unsigned>(time_seed)};
	// mt19937 gen(seed_seq);

	shuffle(vec.begin(), vec.end(), gen);  //10 5 3 8 6 2 7 1 4 9

	for_each(vec.begin(), vec.end(), myPrint);
	cout << endl;
}

// 总结：random_shuffle洗牌算法比较实用，使用时记得加随机数种子

int main()
{
	test01();
	test02();

	// system("pause");

	return 0;
}