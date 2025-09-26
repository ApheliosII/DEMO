// 128. 最长连续序列

// 给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

// 请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution 
{
public:
	int longestConsecutive(vector<int> &nums)
	{
		if (nums.empty())
			return 0;

		// unordered_set<int> num_set(nums.begin(), nums.end());

		unordered_set<int> num_set; // 创建一个无序集合，用于存储数组中的元素
		for (const int& num : nums)
		{ // 遍历数组，将每个元素插入集合中
			num_set.insert(num);
		}

		int longestStreak = 0; // 初始化最长连续序列长度为0

		// int& 表示引用（reference），即 num 是一个引用变量，它直接引用 num_set 中的元素，而不是创建元素的副本。
		// const 关键字表示引用的元素是只读的，即在循环体内不能修改 num 的值。
		// 使用 const int& 可以避免不必要的内存复制，并且保证不会意外修改集合中的元素。
		for (const int& num : num_set)
		{ // 遍历集合中的每个元素
			if (!num_set.count(num - 1))
			{ // 如果当前元素的前一个元素不存在于集合中
				// 说明当前元素是一个连续序列的起点
				int currentNum = num;  // 当前起点元素
				int currentStreak = 1; // 当前连续序列长度初始化为1

				// 检查当前元素的下一个元素是否存在
				while (num_set.count(currentNum + 1))
				{
					currentNum += 1;	// 更新当前元素为下一个元素
					currentStreak += 1; // 增加连续序列长度
				}

				// 更新最长连续序列长度
				longestStreak = max(longestStreak, currentStreak);
			}
		}

		return longestStreak; // 返回最长连续序列长度
	}
};

/*
const int& num 和 int num, const int num 的区别

int num：
在每次迭代时，会创建 nums_set 中元素的副本。
这种方式会在每次迭代时进行内存复制操作，如果集合中的元素非常多，可能会导致性能下降。
由于 num 是一个副本，所以在循环体内可以修改 num 的值，但这不会影响到 num_set 中的元素本身。

const int num：
与 int num 类似，但 num 是一个只读的副本，不能在循环体内修改它的值。
虽然避免了修改原始数据的风险，但仍然存在不必要的内存复制问题。

const int& num：
这是最佳实践，因为它即避免了内存复制，又保证了元素的只读性。
通过引用访问集合中的元素，效率更高，特别是在处理大量数据时。
由于 num 是只读引用，所以在循环体内不能修改 num 的值，确保了集合的完整性。
*/

void test()
{
	Solution s;

	// Happy path
	vector<int> nums1 = {100, 4, 200, 1, 3, 2};			// 4		    // Longest sequence is [1, 2, 3, 4]
	vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1}; // 9    		// Longest sequence is [0, 1, 2, 3, 4, 5, 6, 7, 8]
	vector<int> nums3 = {1, 0, 1, 2};					// 3			// Longest sequence is [0, 1, 2]

	// Edge cases
	vector<int> nums4 = {};									 // 0		// Empty array
	vector<int> nums5 = {1};								 // 1		// Single element
	vector<int> nums6 = {1, 3, 5, 7};						 // 1		// All elements are isolated
	vector<int> nums7 = {1, 2, 3, 4, 5};					 // 5		// Already consecutive
	vector<int> nums8 = {-1, -2, -3, -4, -5};				 // 5		// Negative numbers consecutive
	vector<int> nums9 = {1, 2, 2, 3, 4};					 // 4		// Duplicates in the array
	vector<int> nums10 = {10, 5, 6, 3, 2, 20, 100, 1, 3, 2}; // 3 		// Multiple sequences

	cout << s.longestConsecutive(nums1) << endl;
	cout << s.longestConsecutive(nums2) << endl;
	cout << s.longestConsecutive(nums3) << endl;
	cout << s.longestConsecutive(nums4) << endl;
	cout << s.longestConsecutive(nums5) << endl;
	cout << s.longestConsecutive(nums6) << endl;
	cout << s.longestConsecutive(nums7) << endl;
	cout << s.longestConsecutive(nums8) << endl;
	cout << s.longestConsecutive(nums9) << endl;
	cout << s.longestConsecutive(nums10) << endl;
}

int main()
{
	test();

	system("pause");

	// system("cls");

	return 0;
}