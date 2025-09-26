#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> res;
        auto dfs = [&](this auto &&dfs, vector<int> nums, int x)
        {
            if (x == nums.size() - 1)
            {
                res.push_back(nums); // 添加排列方案
                return;
            }
            for (size_t i = x; i < nums.size(); ++i)
            {
                swap(nums[i], nums[x]); // 交换，将 nums[i] 固定在第 x 位
                dfs(nums, x + 1);       // 开启固定第 x + 1 位元素
                swap(nums[i], nums[x]); // 恢复交换
            }
        };

        dfs(nums, 0);
        return res;
    }
};

void print(vector<vector<int>> &res)
{
    for (auto &v : res)
    {
        for (auto &n : v)
        {
            cout << n << " ";
        }
        cout << endl;
    }
} 

void test01()
{
    Solution s;
    vector<int> nums = {1, 2, 3};
    auto res = s.permute(nums);
    print(res);
}

void test02()
{
    Solution s;
    vector<int> nums = {3, 2, 1, 0};
    auto res = s.permute(nums);
    print(res);
}

int main()
{
    //test01();
    test02();

    return 0;
}