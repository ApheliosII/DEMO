/*
322. 零钱兑换
中等

给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。

计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。

你可以认为每种硬币的数量是无限的。
*/

// 0-1背包 完全背包【基础算法精讲 18】

#include <iostream>
#include <vector>
#include <limits> // for numeric_limits<int>::max()
#include <sstream>

using namespace std;

// my solution ***
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int coin : coins) {
            for (int j = coin; j <= amount; j++) {
                dp[j] = min(dp[j], dp[j - coin] + 1);
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};

// 方法一：记忆化搜索
class Solution_memo {
    vector<int>count;
    int dp(vector<int>& coins, int rem) {
        if (rem < 0) return -1;
        if (rem == 0) return 0;
        if (count[rem - 1] != 0) return count[rem - 1];
        int Min = INT_MAX;
        for (int coin:coins) {
            int res = dp(coins, rem - coin);
            if (res >= 0 && res < Min) {
                Min = res + 1;
            }
        }
        count[rem - 1] = Min == INT_MAX ? -1 : Min;
        return count[rem - 1];
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 1) return 0;
        count.resize(amount);
        return dp(coins, amount);
    }
};

// 方法二：动态规划 ***
class Solution_dp {
public:
    int coinChange(vector<int>& coins, int amount) {
        int Max = amount + 1;
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int j = 0; j < (int)coins.size(); ++j) {
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};

// 灵
// 一、递归搜索 + 保存计算结果 = 记忆化搜索
class Solution_01 {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector memo(n, vector<int>(amount + 1, -1)); // -1 表示没有计算过

        // lambda 递归函数
        auto dfs = [&](this auto&& dfs, int i, int c) -> int {
            if (i < 0) {
                return c == 0 ? 0 : INT_MAX / 2; // 除 2 防止下面 + 1 溢出
            }
            int& res = memo[i][c]; // 注意这里是引用
            if (res != -1) { // 之前计算过
                return res;
            }
            if (c < coins[i]) { // 只能不选
                return res = dfs(i - 1, c);
            }
            // 不选 vs 继续选
            return res = min(dfs(i - 1, c), dfs(i, c - coins[i]) + 1);
        };

        int ans = dfs(n - 1, amount);
        return ans < INT_MAX / 2 ? ans : -1;
    }
};

// 二、1:1 翻译成递推
class Solution_02 {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector f(n + 1, vector<int>(amount + 1, INT_MAX / 2)); // 除 2 防止下面 + 1 溢出
        f[0][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int c = 0; c <= amount; c++) {
                if (c < coins[i]) {
                    f[i + 1][c] = f[i][c];
                } else {
                    f[i + 1][c] = min(f[i][c], f[i + 1][c - coins[i]] + 1);
                }
            }
        }
        int ans = f[n][amount];
        return ans < INT_MAX / 2 ? ans : -1;
    }
};

// 三、空间优化：两个数组（滚动数组）
class Solution_03 {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector f(2, vector<int>(amount + 1, INT_MAX / 2));
        f[0][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int c = 0; c <= amount; c++) {
                if (c < coins[i]) {
                    f[(i + 1) % 2][c] = f[i % 2][c];
                } else {
                    f[(i + 1) % 2][c] = min(f[i % 2][c], f[(i + 1) % 2][c - coins[i]] + 1);
                }
            }
        }
        int ans = f[n % 2][amount];
        return ans < INT_MAX / 2 ? ans : -1;
    }
};

// 四、空间优化：一个数组
class Solution_04 {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> f(amount + 1, INT_MAX / 2);
        f[0] = 0;
        for (int x : coins) {
            for (int c = x; c <= amount; c++) {
                f[c] = min(f[c], f[c - x] + 1);
            }
        }
        int ans = f[amount];
        return ans < INT_MAX / 2 ? ans : -1;
    }
};


// 增强版测试代码 ========================================
void test_enhanced() {
    vector<int> nums;
    int amount = 0;
    string input;
    
    cout << "========================================" << endl;
    cout << "Test" << endl;
    cout << "========================================" << endl;
    
    // 方式1：单行输入所有数字
    cout <<"Please enter integers array (separated by spaces, press Enter to finish): ";
  
    // 清除输入缓冲区中的所有残留字符
    // cin.clear(); // 清除错误状态
    // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除直到换行符
    
    // 读取输入
    getline(cin, input);
    
    stringstream ss(input);
    int num;
    while (ss >> num) {
        // if (num < 0) {
        //     cout << "Warning:" << endl;
        //     num = abs(num);
        // }
        nums.push_back(num);
    }
    
    cout <<"Target amount: ";
    cin >> amount;

    // 如果用户没有输入任何数字，提供示例
    if (nums.empty() && amount == 0) {
        cout << "No input detected. Using example: [1,2,5] amount = 11" << endl;
        nums = {1,2,5};
        amount = 11;
    }
    
    // 显示输入的数组和目标金额
    cout << "----------------" << endl;
    cout << "Input: coins = [";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    cout << "Input: amount = " << amount << endl;
    
    // 计算并显示结果
    // Solution sol;
    cout << "----------------" << endl;
    cout << "Output: result = "<< Solution().coinChange(nums, amount);
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