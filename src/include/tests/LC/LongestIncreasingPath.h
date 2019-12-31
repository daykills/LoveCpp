/*
 329. Longest Increasing Path in a Matrix
 Given an integer matrix, find the length of the longest increasing path.
 
 From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).
 
 Example 1:
 
 Input: nums =
 [
 [9,9,4],
 [6,6,8],
 [2,1,1]
 ]
 Output: 4
 Explanation: The longest increasing path is [1, 2, 6, 9].
 Example 2:
 
 Input: nums =
 [
 [3,4,5],
 [3,2,6],
 [2,2,1]
 ]
 Output: 4
 Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
 */

#include <algorithm>
#include <cassert>
#include "Common.h"

namespace LongestIncreasingPath
{
int longestIncreasingPath(vector<vector<int>>& matrix) {
    auto m = matrix.size();
    if (m == 0) return 0;
    auto n = matrix[0].size();
    if (n == 0) return 0;
    // dp[i][j] is the longest path length starting at i, j
    // 0 means un-explored yet
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // traverse from i, j to look for longest path
    std::function<int(int, int)> dfs = [&](int i, int j) {
        const static vector<pair<int, int>> dirs = {
            { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }
        };
        if (dp[i][j]) return dp[i][j];
        // minimum length is 1
        dp[i][j] = 1;
        for (auto& dir : dirs) {
            int nextI = i + dir.first;
            int nextJ = j + dir.second;
            if (nextI >= m || nextI < 0 || nextJ >= n || nextJ < 0)
                continue;
            if (matrix[nextI][nextJ] <= matrix[i][j])
                continue;
            dp[i][j] = max(dp[i][j], 1 + dfs(nextI, nextJ));
        }
        return dp[i][j];
    };
    auto ans = 0;
    for (auto i = 0; i < m; i++) {
        for (auto j = 0; j < n; j++) {
            ans = max(ans, dfs(i, j));
        }
    }
    return ans;
}

static void Test()
{
    vector<vector<int>> matrix = {
        {9,9,4},
        {6,6,8},
        {2,1,1},
        // 1-2-6-9
    };
    
    cout << "Result: " << longestIncreasingPath(matrix) << std::endl;
}

}

