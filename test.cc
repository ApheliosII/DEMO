#include <iostream>
#include <string>
#include <vector>
#include <climits>
using namespace std;

// void test01()
// {   
//     int n = 10;
//     vector<int> ans(n), next(11, INT_MAX);
//     cout << "ans: " << ans.size() << endl;
//     cout << "next: " << next.size() << endl;
//     for(auto i : ans)
//         cout << i << " ";
//     cout << endl;
//     for(auto i : next)
//         cout << i << " ";
//     cout << endl;

// }

// int main()
// {   
//     //test01();
//     int *p = (int *) main;
//     printf("p = %p\n", *p);
//     // p = 00000000e5894855
//     printf("p = %p\n", p);
//     // p = 00007ff708e2174e
//     return 0;    

// }

// #include <stdio.h>

// int main() {
//     // A wrapper of open system call
//     FILE *fp = fopen("nonexist.file", "r");
//     if (!fp) {
//         perror("open");
//         return 1;
//     }
// }
/*
198. 打家劫舍
中等

你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
*/
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

/*思路：

*/
// my
// class Solution {
// public:
//     int rob(vector<int>& nums) {
//         if (nums.size() == 1) {
//             return nums[0];
//         }
        
//     }
// };

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

//测试

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

#include <iostream>
int main() {
    #if __cplusplus >= 202002L
        std::cout << "支持 C++20! __cplusplus = " << __cplusplus << std::endl;
    #else
        std::cout << "不支持 C++20. __cplusplus = " << __cplusplus << std::endl;
    #endif
    return 0;
}