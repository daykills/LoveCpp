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

int maximalSquareAccum(vector<vector<char>>& matrix) {
    auto m = matrix.size();
    if (m == 0)
        return 0;
    auto n = matrix[0].size();
    if (n == 0)
        return 0;
    vector<vector<int>> hist(m, vector<int>(n, 0));
    int ans = 0;
    for (auto i = 0; i < m; i++) {
        for (auto j = 0; j < n; j++) {
            hist[i][j] = matrix[i][j] - '0';;
            if (i > 0) hist[i][j] += hist[i - 1][j];
            if (j > 0) hist[i][j] += hist[i][j - 1];
            if (i > 0 && j > 0) hist[i][j] -= hist[i - 1][j - 1];
            
            // calculate area
            for (int k = 0; k <= min(i, j); k++) {
                auto sz = k + 1;
                auto area = hist[i][j];
                if (i - sz >= 0) area -= hist[i - sz][j];
                if (j - sz >= 0) area -= hist[i][j - sz];
                if (i - sz >= 0 && j - sz >= 0) area += hist[i - sz][j - sz];
                if (area != sz * sz) break;
                ans = max(ans, area);
            }
        }
    }
    return ans;
}

void Test() {
    vector<vector<char>> matrix = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
    cout << maximalSquareAccum(matrix) << endl;
}
}
