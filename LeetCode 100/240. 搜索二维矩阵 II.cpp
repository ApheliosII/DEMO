#include <iostream>
#include <vector>
using namespace std;

//3
class Solution {
	public:
		bool searchMatrix(vector<vector<int>>& matrix, int target) {
			int m = matrix.size(), n = matrix[0].size();
            //&&
			for (int i = 0, j = n - 1; i < m && j >=0;) {
				if (matrix[i][j] == target) {
					return true;
				}
				else if (matrix[i][j] > target){
					--j;
				}
				else if (matrix[i][j] < target){
					++i;
				}
			}
			return false;
		}
	};
	

int main()
{
	Solution s;
	vector<vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}};
	int target = 55;
	cout << s.searchMatrix(matrix, target) << endl;

	system("pause");
	return 0;
}