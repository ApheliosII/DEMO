/*
152. 乘积最大子数组
中等

给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续 子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

测试用例的答案是一个 32-位 整数。
*/
#include <iostream>
#include <vector>
#include <limits> // for numeric_limits<int>::max()
#include <sstream>
#include <algorithm> // for ranges::max()

using namespace std;

// my

// 方法一：动态规划 On;On
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        vector <long> maxF(nums.begin(),nums.end()), minF(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); ++i) {
            maxF[i] = max(maxF[i - 1] * nums[i], max((long)nums[i], minF[i - 1] * nums[i]));
            minF[i] = min(minF[i - 1] * nums[i], min((long)nums[i], maxF[i - 1] * nums[i]));
            if(minF[i]<INT_MIN) {
                minF[i]=nums[i];
            }
        }
        return *max_element(maxF.begin(), maxF.end());
    }
};

// 优化 On;O1
class Solution_opt {
public:
    int maxProduct(vector<int>& nums) {
        long maxF = nums[0], minF = nums[0], ans = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            long mx = maxF, mn = minF;
            maxF = max(mx * nums[i], max((long)nums[i], mn * nums[i]));
            minF = min(mn * nums[i], min((long)nums[i], mx * nums[i]));
            if(minF<INT_MIN) {
                minF=nums[i];
            }
            ans = max(maxF, ans);
        }
        return ans;
    }
};

// 灵
// 写法一
class Solution_0 {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        vector<int> f_max(n), f_min(n);
        f_max[0] = f_min[0] = nums[0];
        for (int i = 1; i < n; i++) {
            int x = nums[i];
            // 把 x 加到右端点为 i-1 的（乘积最大/最小）子数组后面，
            // 或者单独组成一个子数组，只有 x 一个元素
            f_max[i] = max({f_max[i - 1] * x, f_min[i - 1] * x, x});
            f_min[i] = min({f_max[i - 1] * x, f_min[i - 1] * x, x});
        }
        return ranges::max(f_max); // 注意: -std=c++20 才有 ranges::max() #include <algorithm>
    }
};

// 写法二（空间优化）
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = INT_MIN; // 注意答案可能是负数
        int f_max = 1, f_min = 1;
        for (int x : nums) {
            int mx = f_max;
            f_max = max({f_max * x, f_min * x, x});
            f_min = min({mx * x, f_min * x, x});
            ans = max(ans, f_max);
        }
        return ans;
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
        cout << "No input detected. Using example: nums = [2,3,-2,4]" << endl;
        nums = {2,3,-2,4};
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
    cout << "Output: result = "<< Solution_0().maxProduct(nums);
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