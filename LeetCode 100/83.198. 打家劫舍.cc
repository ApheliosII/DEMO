/*
198. 打家劫舍
中等

你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
*/

/*
        # ===============最简单想法=============
        # dp[i][1]表示偷第i间房的最大金额，dp[i][0]表示不偷这间房的最大金额
        # 递推关系
        # ① dp[i][1] = dp[i-1][0] + nums[i] # 偷这间房 则上一次肯定不能偷
        # ② dp[i][0] = max(dp[i-1][0], dp[i-1][1]) # 不偷这间房的最大，则是上一次不管偷不偷的最大
        # ===============优化===============================
        # 若dp[i]表示直到第i间房的最大金额 
        # 首先明确dp[i][0] = dp[i-1]  因为第i个房间不偷的最大金额就等于第i-1个房间的最大金额
        # 则上面式子可以表示为
        # ① dp[i][1] = dp[i-2] + nums[i][因为dp[i-1][0] = max(dp[i-2][0],dp[i-2][1])==dp[i-2]]
        # ② dp[i][0] = dp[i-1]
        # 故dp[i] = max(dp[i][1],dp[i][0])= max(dp[i-2] + nums[i], dp[i-1])
        # 从而得到递推关系  
*/
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

/*思路：
dp[0] = nums[0];
dp[1] = max(nums[0], nums[1]);
for (int i = 2; i < size; i++) {
    dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
}
*/
// my


// 灵 O(numRows^2);O(1)


// 方法一：动态规划
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int size = nums.size();
        if (size == 1) {
            return nums[0];
        }
        vector<int> dp = vector<int>(size, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < size; i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[size - 1];
    }
};

// 上述方法使用了数组存储结果。考虑到每间房屋的最高总金额只和该房屋的前两间房屋的最高总金额相关，因此可以使用滚动数组，在每个时刻只需要存储前两间房屋的最高总金额。
// O(n);O(1)
class Solution_optimized {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int size = nums.size();
        if (size == 1) {
            return nums[0];
        }
        int first = nums[0], second = max(nums[0], nums[1]);
        for (int i = 2; i < size; i++) {
            int temp = second;
            second = max(first + nums[i], second);
            first = temp;
        }
        return second;
    }
};

// krahets java python

// ikaruga
class Solution_01 {
public:
    int rob(vector<int>& nums) 
    {
        int sumOdd = 0;
        int sumEven = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (i % 2 == 0)
            {
                sumEven += nums[i];
                sumEven = max(sumOdd, sumEven);
            }
            else
            {
                sumOdd += nums[i];
                sumOdd = max(sumOdd, sumEven);
            }
        }
        return max(sumOdd, sumEven);
    }
};


// 灵
// 一、递归搜索 + 保存计算结果 = 记忆化搜索
class Solution_02 {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> memo(n, -1); // -1 表示没有计算过

        // lambda 递归函数
        // dfs(i) 表示从 nums[0] 到 nums[i] 最多能偷多少
        auto dfs = [&](this auto&& dfs, int i) -> int {
            if (i < 0) { // 递归边界（没有房子）
                return 0;
            }
            if (memo[i] != -1) { // 之前计算过
                return memo[i];
            }
            return memo[i] = max(dfs(i - 1), dfs(i - 2) + nums[i]);
        };

        return dfs(n - 1); // 从最后一个房子开始思考
    }
};
// O(n);O(n)


// 二、1:1 翻译成递推
class Solution_03 {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(n + 2);
        for (int i = 0; i < n; i++) {
            f[i + 2] = max(f[i + 1], f[i] + nums[i]);
        }
        return f[n + 1];
    }
};
// O(n);O(n)

// 三、空间优化
class Solution_04 {
public:
    int rob(vector<int>& nums) {
        int f0 = 0, f1 = 0;
        for (int x : nums) {
            int new_f = max(f1, f0 + x);
            f0 = f1;
            f1 = new_f;
        }
        return f1;
    }
};
// O(n);O(1)

// 测试
// 逐个数输入测试
// void test() {
//     vector<int> nums;
//     cout << "input vector<int> nums size: ";
//     int n;
//     cin >> n;
    
//     cout << "input " << n << " integers: ";
//     for (int i = 0; i < n; i++) {
//         int num;
//         cin >> num;
//         nums.push_back(num);
//     }

//     int result = Solution().rob(nums);
//     cout << "output: " << result << endl;

//     cout << "----------------------------------------" << endl;
// }

// int main() {
    
//     while(1){
//         test();
//     }
    
//     return 0;
// }


// 优化的测试函数
void test_enhanced() {
    vector<int> nums;
    string input;
    
    cout << "========================================" << endl;
    cout << "House Robber Problem Test" << endl;
    cout << "========================================" << endl;
    
    // 方式1：单行输入所有数字（更友好）
    cout << "Please enter the house values array (separated by spaces, press Enter to finish):";
    // cin.ignore(); // 清除之前的换行符
    // 这行代码会在每次测试开始时立即消耗一个字符（通常是之前输入留下的换行符），如果此时输入缓冲区是空的，程序就会等待你输入一个字符（比如回车），然后才能继续执行到真正的输入部分。
    // 意思先回车再输入，这样程序才会等待用户输入，而不是直接开始执行测试。

    // 清除输入缓冲区中的所有残留字符
    cin.clear(); // 清除错误状态
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除直到换行符


    getline(cin, input);
    
    // 解析输入的数字 这段代码是C++中用于字符串解析的常用技巧
    // 1. 创建字符串流
    // 2. 声明整数变量
    // 3. 循环读取数字
    // 4. 将数字添加到向量
    stringstream ss(input);
    int num;
    while (ss >> num) {
        if (num < 0) {
            cout << "Warning: Amount should be a non-negative integer. Taking absolute value." << endl;
            num = abs(num);
        }
        nums.push_back(num);
    }
    
    // 如果用户没有输入任何数字，提供示例
    if (nums.empty()) {
        cout << "No input detected. Using example: [2,7,9,3,1]" << endl;
        nums = {2, 7, 9, 3, 1};
    }
    
    // 显示输入的数组
    cout << "House values array: [";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // 计算并显示结果
    int result = Solution().rob(nums);
    int result1 = Solution_optimized().rob(nums);
    cout << "Maximum amount that can be robbed: " << result << " = " << result1 << endl;
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
    
    cout << "Program ended. Thank you for using!" << endl;
    return 0;
}