#include <iostream>
#include <vector>

using namespace std;

//my solution
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if( m == 0 ){
            return false;
        }
        int n = matrix[0].size();

        // for(int i = 0; i < m; ++i){
        //     int l = 0, r = n - 1, mid;
        //     while(l <= r){
        //         mid = l + (r - l)/2;
        //         if(matrix[i][mid] == target){
        //             return true;
        //         }
        //         else if(matrix[i][mid] < target){
        //             l = mid + 1;
        //         }
        //         else if(matrix[i][mid] > target){
        //             r = mid - 1;
        //         }
        //     }
        // }
        // return false;

        int i = 0, j = m - 1, mid_m;
        while(i <= j){
            mid_m = i + (j - i)/2;
            if (matrix[mid_m][0] == target) {
                return true;
            }
            else if(matrix[mid_m][0] < target){
                i = mid_m + 1;
            }
            else{
                j = mid_m - 1;
            }
        }
        if(j < 0){ return false;}

        int l = 0, r = n - 1, mid;
        while(l <= r){
            mid = l + (r - l)/2;
            if(matrix[j][mid] == target){
                return true;
            }
            else if(matrix[j][mid] < target){
                l = mid + 1;
            }
            else if(matrix[j][mid] > target){
                r = mid - 1;
            }
        }
    
        return false;
    } 
};

//my solution_02
class Solution_02 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if( m == 0 ){
            return false;
        }
        int n = matrix[0].size();

        for(int i = 0; i < m; ++i){
            int l = 0, r = n - 1, mid;
            while(l <= r){
                mid = l + (r - l)/2;
                if(matrix[i][mid] == target){
                    return true;
                }
                else if(matrix[i][mid] < target){
                    l = mid + 1;
                }
                else if(matrix[i][mid] > target){
                    r = mid - 1;
                }
            }
        }
        return false;
    } 
};

void test01(){
    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    int target = 3;
    Solution sol;
    bool res = sol.searchMatrix(matrix, target);
    cout << res << endl;
}

void test02(){
    vector<vector<int>> matrix = {{1,3,5,7}};
    int target = 3;
    Solution sol;
    bool res = sol.searchMatrix(matrix, target);
    cout << res << endl;
}

void test03(){
    vector<vector<int>> matrix = {{1,3,5,7}};
    int target = 0;
    Solution sol;
    bool res = sol.searchMatrix(matrix, target);
    cout << res << endl;
}

void test04(){
    vector<vector<int>> matrix = {{1,3,5,7}};
    int target = 9;
    Solution sol;
    bool res = sol.searchMatrix(matrix, target);
    cout << res << endl;
}

int main(){

    test01();
    test02();
    test03();
    test04();

    return 0;
}