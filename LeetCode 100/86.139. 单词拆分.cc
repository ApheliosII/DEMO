/*
139. 单词拆分
中等

给你一个字符串 s 和一个字符串列表 wordDict 作为字典。如果可以利用字典中出现的一个或多个单词拼接出 s 则返回 true。

注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits> // for numeric_limits<int>::max()
#include <sstream>
#include <algorithm>  // 用于 ranges::max（C++20 特性）

using namespace std;

// my solution ***

// 方法一：动态规划 ***
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        auto wordDictSet = unordered_set <string> ();
        for (auto word: wordDict) {
            wordDictSet.insert(word);
        }

        auto dp = vector <bool> (s.size() + 1);
        dp[0] = true;
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[s.size()];
    }
};

// 灵
class Solution_01 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int max_len = ranges::max(wordDict, {}, &string::length).length();
        unordered_set<string> words(wordDict.begin(), wordDict.end());

        int n = s.length();
        vector<int> memo(n + 1, -1); // -1 表示没有计算过
        auto dfs = [&](this auto&& dfs, int i) -> bool {
            if (i == 0) { // 成功拆分！
                return true;
            }
            int& res = memo[i]; // 注意这里是引用
            if (res != -1) { // 之前计算过
                return res;
            }
            for (int j = i - 1; j >= max(i - max_len, 0); j--) {
                if (words.count(s.substr(j, i - j)) && dfs(j)) {
                    return res = true; // 记忆化
                }
            }
            return res = false; // 记忆化
        };
        return dfs(n);
    }
};

/*
ranges::max(wordDict, {}, &string::length).length();
作用​​：找出 wordDict中所有单词的最大长度。
​​语法与逻辑​​：
    ranges::max是 C++20 标准引入的算法，用于直接在一个范围（如容器）中查找最大值
    wordDict是要查找的范围（一个字符串向量）。
    {}表示使用默认的比较器（即 std::less<>）。
    &string::length是一个​​投影函数​​（projection），它告诉 ranges::max不要直接比较字符串本身，而是比较每个字符串的 length()返回值

最终 .length()获取这个最长单词的长度值。
*/


// 1:1 翻译成递推
class Solution_02{
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int max_len = ranges::max(wordDict, {}, &string::length).length();
        unordered_set<string> words(wordDict.begin(), wordDict.end());

        int n = s.length();
        vector<int> f(n + 1);
        f[0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = i - 1; j >= max(i - max_len, 0); j--) {
                if (f[j] && words.count(s.substr(j, i - j))) {
                    f[i] = true;
                    break;
                }
            }
        }
        return f[n];
    }
};


// 增强版测试代码 ========================================
void test_enhanced() {
    string s;
    vector<string> wordDict;
    string input;
    
    cout << "========================================" << endl;
    cout << "Test" << endl;
    cout << "========================================" << endl;
    
    // 方式1：单行输入所有数字
    cout <<"Input wordDict: (separated by spaces, press Enter to finish): ";
  
    // 清除输入缓冲区中的所有残留字符
    // cin.clear(); // 清除错误状态
    // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除直到换行符
    
    // 读取输入
    getline(cin, input);
    
    stringstream ss(input);
    string str;
    while (ss >> str) {
        wordDict.push_back(str);
    }
    
    cout <<"s: ";
    // cin >> s;
    getline(cin, s);

    // 如果用户没有输入字，提供示例
    if (wordDict.empty() || s.empty()) {
        cout << "No input detected. Using example: wordDict = [\"leet\",\"code\"]; s = \"leetcode\" " << endl;
        wordDict = {"leet","code"};
        s = "leetcode";
    }
    
    // 显示输入
    cout << "----------------" << endl;
    cout << "Input: wordDict = [";
    for (int i = 0; i < wordDict.size(); i++) {
        cout << wordDict[i];
        if (i < wordDict.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    cout << "Input: s = " << s << endl;
    
    // 计算并显示结果
    // Solution sol;
    cout << "----------------" << endl;
    cout << "Output: result = "<< Solution().wordBreak(s, wordDict);
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