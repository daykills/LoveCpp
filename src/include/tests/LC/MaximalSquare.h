/*
 221. Maximal Square
 Medium
 
 1723
 
 41
 
 Favorite
 
 Share
 Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.
 
 Example:
 
 Input:
 
 1 0 1 0 0
 1 0 1 1 1
 1 1 1 1 1
 1 0 0 1 0
 
 Output: 4
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace MaximalSquare
{

int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.empty()) {
        return 0;
    }
    int m = matrix.size();
    int n = matrix[0].size();
    int sz = 0;
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!i || !j || matrix[i][j] == '0') {
                dp[i][j] = matrix[i][j] - '0';
            } else {
                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
            }
            sz = max(dp[i][j], sz);
        }
    }
    return sz * sz;
}

void Test() {
    vector<vector<char>> matrix = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
    cout << maximalSquare(matrix) << endl;
}
}
