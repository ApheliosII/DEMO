/*
118. 杨辉三角
简单

给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。
*/
#include <iostream>
#include <vector>
using namespace std;

// my
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows == 1) {
            return { {1} };
        }
        vector<vector<int>> triangle;
        for (int i = 0; i < numRows; i++) {
            vector<int> T(i+1, 1);
            triangle.push_back(T);
            for (int j = 1; j < i; j++) {
                triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
            }
        }
        return triangle;
    }
};

// 灵 O(numRows^2);O(1)
class Solution_01 {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> c(numRows);
        for (int i = 0; i < numRows; i++) {
            c[i].resize(i + 1, 1);
            for (int j = 1; j < i; j++) {
                // 左上方的数 + 正上方的数
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
            }
        }
        return c;
    }
};

// 方法一：数学 O(numRows^2);O(1)
class Solution_03 {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret(numRows);
        for (int i = 0; i < numRows; ++i) {
            ret[i].resize(i + 1);
            ret[i][0] = ret[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
            }
        }
        return ret;
    }
};

//测试
void test() {

    int numRows ;
    cout << "input numRows = ";
    cin >> numRows; //错误输入处理？？？

    vector<vector<int>> result = Solution().generate(numRows);
    // for (auto row : result){
    //     for (auto num : row){
    //         cout << num << " ";
    //     }
    //     cout << endl;
    // }

    // 计算居中显示的偏移量（使输出更美观）
    int maxWidth = result.back().size() * 3; // 最后一行的大致宽度
    for (int i = 0; i < result.size(); i++) {
        // 居中对齐：计算每行前的空格数
        int spaces = (maxWidth - result[i].size() * 3) / 2;
        for (int s = 0; s < spaces; s++) {
            cout << " ";
        }
        
        // 输出数字
        for (int num : result[i]) {
            cout << num << "  "; // 两个空格使输出更清晰
        }
        cout << endl;
    }
    

    cout << "----------------------------------------" << endl;
}

int main() {
    
    while(1){
        test();
    }
    
    return 0;
}