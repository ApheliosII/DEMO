#include <iostream>
#include <vector>
#include <string>
#include <cstdint>  // 必须包含此头文件才能使用 uint8_t
using namespace std;    

//灵
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector board(n, string(n, '.')); // 一开始棋盘是空的，没有皇后
        vector<uint8_t> col(n), diag1(n * 2 - 1), diag2(n * 2 - 1); // vector<uint8_t> 效率比 vector<bool> 高
        auto dfs = [&](this auto&& dfs, int r) {
            if (r == n) {
                ans.push_back(board); // 复制整个棋盘
                return;
            }
            // 在 (r,c) 放皇后
            for (int c = 0; c < n; c++) {
                int rc = r - c + n - 1;
                if (!col[c] && !diag1[r + c] && !diag2[rc]) { // 判断能否放皇后
                    board[r][c] = 'Q'; // 放皇后
                    col[c] = diag1[r + c] = diag2[rc] = true; // 皇后占用了 c 列和两条斜线
                    dfs(r + 1);
                    col[c] = diag1[r + c] = diag2[rc] = false; // 恢复现场
                    board[r][c] = '.';
                }
            }
            
        };
        dfs(0);
        return ans;
    }
};

int main() {
    Solution sol;
    auto ans = sol.solveNQueens(4);
    for (auto& board : ans) {
        for (auto& row : board) {
            cout << row << endl;
        }
        cout << endl;
    }
    return 0;
}

//vector<uint8_t>