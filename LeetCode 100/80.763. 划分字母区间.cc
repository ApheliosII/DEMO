/*
my思路：
输入字母字符串string s ;用cpp写代码：
要求：
1. 从前面往后面，找到每个字母第一次和最后一次出现的位置，这样每个字母得到一个区间；
2. 如果区间不重合，就输出每个区间长度，加起来应该等于string s的长度；
3. 如果有重合就合并区间，再输出合并后的区间长度；加起来应该等于string s的长度；
最后输出的是vector<int>

ds:
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        // 记录每个字母最后出现的位置
        unordered_map<char, int> lastOccurrence;
        for (int i = 0; i < s.length(); i++) {
            lastOccurrence[s[i]] = i;
        }
        
        vector<int> result;
        int start = 0;  // 当前区间的起始位置
        int end = 0;    // 当前区间的结束位置
        
        for (int i = 0; i < s.length(); i++) {
            // 更新当前区间的结束位置为当前字母最后出现的位置
            end = max(end, lastOccurrence[s[i]]);
            
            // 如果当前位置等于当前区间的结束位置，说明找到一个完整的区间
            if (i == end) {
                result.push_back(end - start + 1);
                start = i + 1;  // 下一个区间的起始位置
            }
        }
        
        return result;
    }
};

//测试
void test() {

    string s1 ;
    cout << "input: ";
    cin >> s1; //错误输入处理？？？

    vector<int> result1 = Solution().partitionLabels(s1);
    // Solution S;
    // vector<int> result1 = S.partitionLabels(s1);
    cout << "output: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << result1[i];
        if (i < result1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {

    while(1){
        test();
    }
    
    return 0;
}