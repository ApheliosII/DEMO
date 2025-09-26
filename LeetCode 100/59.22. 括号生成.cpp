#include <iostream>
#include <vector>
using namespace std;

class Solution
{
    // 辅助函数：检查当前字符串是否为有效的括号组合
    bool valid(const string &str)
    {
        int balance = 0; // 平衡计数器：左括号+1，右括号-1
        for (char c : str)
        {
            if (c == '(')
            {
                ++balance; // 遇到左括号，平衡+1
            }
            else
            {
                --balance; // 遇到右括号，平衡-1
            }
            if (balance < 0)
            {                 // 平衡不能为负数（右括号比左括号多）
                return false; // 出现无效情况，直接返回false
            }
        }
        return balance == 0; // 最终平衡必须归零（左右括号数量相等）
    }

    // 递归生成所有可能的括号组合（暴力枚举）
    void generate_all(string &current, int n, vector<string> &result)
    {
        // cout << "当前字符串: \"" << current << "\"" << endl;
        // 终止条件：当前字符串长度达到目标长度（2n）
        if (n == current.size())
        {
            if (valid(current))
            {                              // 检查有效性
                result.push_back(current); // 有效则存入结果集
            }
            return; // 结束当前递归分支
        }

        // 递归尝试添加左括号
        current += '(';                           // 添加左括号
        generate_all(current, n, result); // 继续递归
        current.pop_back();                       // 回溯：移除最后添加的字符

        // 递归尝试添加右括号
        current += ')';                           // 添加右括号
        generate_all(current, n, result); // 继续递归
        current.pop_back();                       // 回溯：移除最后添加的字符
    }

public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> result;                // 存储所有有效结果的容器
        string current;                       // 当前正在构建的括号字符串
        generate_all(current, n * 2, result); // 目标长度是n对括号，即2n个字符
        return result;                        // 返回最终结果集
    }
};

int main()
{
    Solution sol;
    vector<string> result = sol.generateParenthesis(3);
    for (string s : result)
    {
        cout << s << endl;
    }
    return 0;
}