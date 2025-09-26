#include <iostream>
#include <vector>
using namespace std;

//哈希表
class SolutionA
{
public:
	int firstMissingPositive(vector<int> &nums)
	{
		int n = nums.size();
		for (int &num : nums)
		{
			if (num <= 0)
			{
				num = n + 1;
			}
		}
		/* 			for(int i = 0; i < n; ++i){
						if(nums[i] <= n){
							nums[nums[i] - 1] = - (nums[nums[i] - 1]) ;
						}
					} */
		for (int i = 0; i < n; ++i)
		{
			int index = abs(nums[i]);
			if (index <= n)
			{
				nums[index - 1] = -abs(nums[index - 1]);
			}
		}
		for (int i = 0; i < n; ++i)
		{
			if (nums[i] > 0)
			{
				return i + 1;
			}
		}
		return n + 1;
	}
};


//置换
class SolutionB
{
public:
	int firstMissingPositive(vector<int> &nums)
	{
		int n = nums.size();
		for (int i = 0; i < n; ++i)
		{
			while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
			{
				swap(nums[i], nums[nums[i] - 1]);
			}
		}
		for (int i = 0; i < n; ++i)
		{
			if (nums[i] != i + 1)
			{
				return i + 1;
			}
		}
		return n + 1;
	}
};

int main()
{
	SolutionA s;
	vector<int> nums = {3, 4, -1, 1};
	// vector<int> nums = {1,2,0};
	cout << s.firstMissingPositive(nums) << endl;

	system("pause");
	return 0;
}