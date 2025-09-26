#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	void rotate(vector<vector<int>> &matrix)
	{
		int n = matrix.size();
		vector<vector<int>> ans(n, vector<int>(n, 0));
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				ans[j][n - 1 - i] = matrix[i][j];
			}
		}
		matrix = ans;
	}
};

int main()
{
	Solution s;
	vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	s.rotate(matrix);
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[0].size(); ++j)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	system("pause");
	return 0;
}