/*
279. 完全平方数
中等

给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。

完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。
*/
#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <cmath>
#include <cstring> // memset

using namespace std;

// my solution

// 方法一：动态规划
/* 思路：

*/
class Solution {
public:
    int numSquares(int n) {
        // **************************************
        vector<int> dp(n + 1, 0); // 显式初始化为 0
        // vector<int> dp(n + 1); // 值初始化为 0
        for (int i = 1; i <= n; i++) {
            int min_num = INT_MAX;
            for (int j = 1; j * j <= i; j++) {
                min_num = min(min_num, dp[i - j * j]);
            }
            dp[i] = 1 + min_num;
        }
        return dp[n];
    }
};
// O(n * sqrt(n)); O(n) 

// 方法二：数学
class Solution_math {
public:
    // 判断是否为完全平方数
    bool isPerfectSquare(int x) {
        int y = sqrt(x);
        return y * y == x;
    }

    // 判断是否能表示为 4^k*(8m+7)
    bool checkAnswer4(int x) {
        while (x % 4 == 0) {
            x /= 4;
        }
        return x % 8 == 7;
    }

    int numSquares(int n) {
        if (isPerfectSquare(n)) {
            return 1;
        }
        if (checkAnswer4(n)) {
            return 4;
        }
        for (int i = 1; i * i <= n; i++) {
            int j = n - i * i;
            if (isPerfectSquare(j)) {
                return 2;
            }
        }
        return 3;
    }
};
// O(sqrt(n)); O(1)

// 灵
// 0-1 背包和完全背包【基础算法精讲 18】
// 一、记忆化搜索
// 写在外面，多个测试数据之间可以共享，减少计算量
int memo[101][10001];

auto init_01 = [] {
    memset(memo, -1, sizeof(memo)); // -1 表示没有计算过
    return 0;
}();

int dfs(int i, int j) {
    if (i == 0) {
        return j == 0 ? 0 : INT_MAX;
    }
    int& res = memo[i][j]; // 注意这里是引用
    if (res != -1) { // 之前计算过
        return res;
    }
    if (j < i * i) {
        res = dfs(i - 1, j); // 只能不选
    } else {
        res = min(dfs(i - 1, j), dfs(i, j - i * i) + 1); // 不选 vs 选
    }
    return res;
}

class Solution_01 {
public:
    int numSquares(int n) {
        return dfs(sqrt(n), n);
    }
};

// 二、1:1 翻译成递推
const int N = 10000;
int f[101][N + 1];

auto init_02 = [] {
    ranges::fill(f[0], INT_MAX);
    f[0][0] = 0;
    for (int i = 1; i * i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (j < i * i) {
                f[i][j] = f[i - 1][j]; // 只能不选
            } else {
                f[i][j] = min(f[i - 1][j], f[i][j - i * i] + 1); // 不选 vs 选
            }
        }
    }
    return 0;
}();

class Solution_02 {
public:
    int numSquares(int n) {
        return f[(int) sqrt(n)][n]; // 也可以写 f[100][n]
    }
};

// 三、空间优化
const int N3 = 10000;
int dp[N3 + 1];

//
auto init_03 = [] {
    ranges::fill(dp, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i * i <= N3; i++) {
        for (int j = i * i; j <= N3; j++) {
            dp[j] = min(dp[j], dp[j - i * i] + 1); // 不选 vs 选
        }
    }
    return 0;
}();

class Solution_03 {
public:
    int numSquares(int n) {
        return dp[n];
    }
};


// 测试代码
void test() {
    Solution sol;
    int n;
    cout <<"Please enter an integer: ";
    cin  >> n;
    cout << "Output: " << sol.numSquares(n) << endl;
}

// 增强版测试代码
void test_enhanced() {
    vector<int> nums;
    string input;
    
    cout << "========================================" << endl;
    cout << "Test" << endl;
    cout << "========================================" << endl;
    
    // 方式1：单行输入所有数字
    cout << "Please enter an integer (separated by spaces, press Enter to finish): ";
  
    // 清除输入缓冲区中的所有残留字符
    cin.clear(); // 清除错误状态
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除直到换行符
    
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
    
    // 如果用户没有输入任何数字，提供示例
    if (nums.empty()) {
        cout << "No input detected. Using example: [12,13,14,15,16]" << endl;
        nums = {12,13,14,15,16};
    }
    
    // 显示输入的数组
    cout << "Input integers: [";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // 计算并显示结果
    Solution sol;
    Solution_03 sol_03;
    cout << "Minimum Number of Perfect Squares: ";
    for (int i = 0; i < nums.size(); i++) {
        int result = sol_03.numSquares(nums[i]);
        cout << result;
        if (i < nums.size() - 1) cout << ", ";
    }
}

int main() {
    char choice;
    
    do {
        // test();
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