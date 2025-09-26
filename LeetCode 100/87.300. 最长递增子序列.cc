/*
300. 最长递增子序列
中等

给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
*/

#include <iostream>
#include <vector>
#include <limits> // for numeric_limits<int>::max()
#include <sstream>

using namespace std;

// my solution ***
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        int maxLength = 1; // 记录全局最大值，初始为1（至少有一个元素）
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            // 更新全局最大值
            maxLength = max(maxLength, dp[i]);
        }
        // return dp[nums.size() - 1]; // X错误X
        // 返回dp数组中的最大值，而非最后一个元素
        return maxLength;
    }
};

// 方法一：动态规划 *** On^2;On
class Solution_01 {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = (int)nums.size();
        if (n == 0) {
            return 0;
        }
        vector<int> dp(n, 0);
        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};

// 方法二：贪心 + 二分查找 Onlogn; On
class Solution_02 {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = 1, n = (int)nums.size();
        if (n == 0) {
            return 0;
        }
        vector<int> d(n + 1, 0);
        d[len] = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > d[len]) {
                d[++len] = nums[i];
            } else {
                int l = 1, r = len, pos = 0; // 如果找不到说明所有的数都比 nums[i] 大，此时要更新 d[1]，所以这里将 pos 设为 0
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (d[mid] < nums[i]) {
                        pos = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                d[pos + 1] = nums[i];
            }
        }
        return len;
    }
};

// 灵
// 方法一：记忆化搜索

// 方法二：递推

// 方法三：贪心 + 二分查找

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
        cout << "No input detected. Using example: nums = [10,9,2,5,3,7,101,18]" << endl;
        nums = {10,9,2,5,3,7,101,18};
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
    cout << "Output: result = "<< Solution().lengthOfLIS(nums);
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
// [1,3,6,7,9,4,10,5,6]
// 6

// compile run cpp flags 设置为：-std=c++23 -Wall -Wextra -g3