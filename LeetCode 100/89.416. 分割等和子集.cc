/*
416. 分割等和子集
中等

给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
*/
#include <iostream>
#include <vector>
#include <limits> // for numeric_limits<int>::max()
#include <sstream>
#include <numeric> // for accumulate()
using namespace std;

// my

// 动态规划
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) {
            return false;
        }
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int maxNum = *max_element(nums.begin(), nums.end());
        if (sum & 1) {
            return false;
        }
        int target = sum / 2;
        if (maxNum > target) {
            return false;
        }
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));
        for (int i = 0; i < n; i++) {
            dp[i][0] = true;
        }
        dp[0][nums[0]] = true;
        for (int i = 1; i < n; i++) {
            int num = nums[i];
            for (int j = 1; j <= target; j++) {
                if (j >= num) {
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - num];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n - 1][target];
    }
};
 
// 增强版测试代码 ========================================
void test_enhanced() {
    vector<int> nums;
    string input;
    
    cout << "========================================" << endl;
    cout << "Test" << endl;
    cout << "========================================" << endl;
    
    // 方式1：单行输入所有数字
    cout <<"Input nums: (separated by spaces, press Enter to finish): ";
  
    // 清除输入缓冲区中的所有残留字符
    // cin.clear(); // 清除错误状态
    // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除直到换行符
    
    // 读取输入
    getline(cin, input);
    
    stringstream ss(input);
    int num;
    while (ss >> num) {
        nums.push_back(num);
    }

    // 如果用户没有输入字，提供示例
    if (nums.empty()) {
        cout << "No input detected. Using example: nums = [1,5,11,5]" << endl;
        nums = {1,5,11,5};
    }
    
    // 显示输入
    cout << "----------------" << endl;
    cout << "Input: nums = [";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    
    // 计算并显示结果
    // Solution sol;
    cout << "----------------" << endl;
    cout << "Output: result = "<< Solution().canPartition(nums);
    // Solution::coinChange(nums, amount); // 静态调用 
    // static int coinChange(vector<int>& coins, int amount) { ... } // 静态成员函数
}

int main() {
    char choice;
    
    do {
        test_enhanced();
        
        cout << "\nContinue testing? (y/n): ";
        cin >> choice;
        // 清除输入缓冲区
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    } while (choice == 'y' || choice == 'Y');
    
    cout << "Program ended Thank you for using!" << endl;
    return 0;
}

// compile run cpp flags 设置为：-std=c++23 -Wall -Wextra -g3   