/*
70. 爬楼梯
简单

假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
*/
#include <iostream>
#include <vector>
#include <cmath> // 用于pow()
#include <chrono> // 用于高精度计时 
using namespace std::chrono; // 引入chrono命名空间
using namespace std;

// 递归解法
class Solution {
public:
    // my低效率递归: 超出时间限制 O(2^n)
    int climbStairs(int n) {
        int ans = 0;
        if(n == 0 || n == 1){
            return 1;
        }
        ans = climbStairs(n - 1) + climbStairs(n - 2);
        return ans;
    }
};

// 记忆化递归（Memoization）
class Solution_memo {
public:
    int climbStairs(int n) {
        vector<int> memo(n + 1, -1);
        return helper(n, memo);
    }
    
private:
    int helper(int n, vector<int>& memo) {
        if (n == 0 || n == 1) return 1;
        
        if (memo[n] != -1) return memo[n];
        
        memo[n] = helper(n - 1, memo) + helper(n - 2, memo);
        return memo[n];
    }
};

class Solution_memo2 {
    vector<int> memo;

    int dfs(int i) {
        if (i <= 1) { // 递归边界
            return 1;
        }
        int& res = memo[i]; // 注意这里是引用
        if (res) { // 之前计算过
            return res;
        }
        return res = dfs(i - 1) + dfs(i - 2); // 记忆化
    }

public:
    int climbStairs(int n) {
        memo.resize(n + 1);
        return dfs(n);
    }
};

// 动态规划（推荐）
class Solution_01 {
public:
    // 使用vector的DP
    int climbStairs(int n) {
        if (n == 0 || n == 1) return 1;
        
        // int dp[n+1];
        vector<int> dp(n+1); // 使用vector避免可变长度数组的编译器扩展
        dp[0] = 1;
        dp[1] = 1;
        
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        
        return dp[n];
    }

    // 方法一：动态规划 ON;O1 // 空间优化DP
    int climbStairs_01(int n) {
        int p = 0, q = 0, r = 1;
        for (int i = 1; i <= n; ++i) {
            p = q; 
            q = r; 
            r = p + q;
        }
        return r;
    }

};

// 方法二：矩阵快速幂
class Solution_02 {
public:
    vector<vector<long long>> multiply(vector<vector<long long>> &a, vector<vector<long long>> &b) {
        vector<vector<long long>> c(2, vector<long long>(2));
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
            }
        }
        return c;
    }

    vector<vector<long long>> matrixPow(vector<vector<long long>> a, int n) {
        vector<vector<long long>> ret = {{1, 0}, {0, 1}};
        while (n > 0) {
            if ((n & 1) == 1) {
                ret = multiply(ret, a);
            }
            n >>= 1;
            a = multiply(a, a);
        }
        return ret;
    }

    int climbStairs(int n) {
        vector<vector<long long>> ret = {{1, 1}, {1, 0}};
        vector<vector<long long>> res = matrixPow(ret, n);
        return res[0][0];
    }
    // 时间复杂度：O(logn)
    // 空间复杂度：O(1)
};

// 方法三：通项公式
class Solution_03 {
public:
    int climbStairs(int n) {
        double sqrt5 = sqrt(5);
        double fibn = pow((1 + sqrt5) / 2, n + 1) - pow((1 - sqrt5) / 2, n + 1);
        return (int)round(fibn / sqrt5);
    }
};


//测试
void test() {

    int n ;
    cout << "input n = ";
    cin >> n; //错误输入处理？？？

    // 测试递归解法
    auto start1 = high_resolution_clock::now();
    int result1 = Solution().climbStairs(n);
    auto stop1 = high_resolution_clock::now(); 
    auto duration1 = duration_cast<microseconds>(stop1 - start1);

    // 测试动态规划解法
    auto start2 = high_resolution_clock::now();
    int result2 = Solution_01().climbStairs(n);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);

    cout << "Recursion: " << result1 << ", time: " << duration1.count() << " us" << endl;
    cout << "DP: " << result2 << ", time: " << duration2.count() << " us" << endl;
    cout << "gap: " << static_cast<double>(duration1.count()) / duration2.count() << " times " << endl;
    cout << "----------------------------------------" << endl;

    int result3 = Solution_01().climbStairs_01(n);
    int result4 = Solution_02().climbStairs(n);
    int result5 = Solution_03().climbStairs(n);

    cout << "DP: " << result3 << endl;
    cout << "MatrixPow: " << result4 << endl;
    cout << "Fibonacci: " << result5 << endl;
    cout << "----------------------------------------" << endl;
}

int main() {
    
    while(1){
        test();
    }
    
    return 0;
}