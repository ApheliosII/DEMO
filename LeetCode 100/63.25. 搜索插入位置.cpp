#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // 线性查找
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        for(int i = 0; i < n; ++i){
            if(nums[i] >= target){
                return i;
            }
        }
        return n;
    }

    // 二分查找

    // lower_bound 返回最小的满足 nums[i] >= target 的 i
    // 如果数组为空，或者所有数都 < target，则返回 nums.size()
    // 要求 nums 是非递减的，即 nums[i] <= nums[i + 1]

    // 闭区间写法
    int lower_bound(vector<int>& nums, int target) {
        int left = 0, right = (int) nums.size() - 1; // 闭区间 [left, right]
        while (left <= right) { // 区间不为空
            // 循环不变量：
            // nums[left-1] < target
            // nums[right+1] >= target
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1; // 范围缩小到 [mid+1, right]
            } else {
                right = mid - 1; // 范围缩小到 [left, mid-1]
            }
        }
        return left;
    }

    // 左闭右开区间写法
    int lower_bound2(vector<int>& nums, int target) {
        int left = 0, right = nums.size(); // 左闭右开区间 [left, right)
        while (left < right) { // 区间不为空
            // 循环不变量：
            // nums[left-1] < target
            // nums[right] >= target
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1; // 范围缩小到 [mid+1, right)
            } else {
                right = mid; // 范围缩小到 [left, mid)
            }
        }
        return left;
    }

    // 开区间写法
    int lower_bound3(vector<int>& nums, int target) {
        int left = -1, right = nums.size(); // 开区间 (left, right)
        while (left + 1 < right) { // 区间不为空
            // 循环不变量：
            // nums[left] < target
            // nums[right] >= target
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid; // 范围缩小到 (mid, right)
            } else {
                right = mid; // 范围缩小到 (left, mid)
            }
        }
        return right;
    }

};

int main(){
    vector<int> nums = {1,3,5,6};
    int target = 6;
    Solution sol;
    int ans = sol.searchInsert(nums, target);
    int ans1 = sol.lower_bound(nums, target);
    int ans2 = sol.lower_bound2(nums, target);
    int ans3 = sol.lower_bound3(nums, target);
    cout << ans << endl;
    cout << ans1 << endl;
    cout << ans2 << endl;
    cout << ans3 << endl;
    return 0;
}
