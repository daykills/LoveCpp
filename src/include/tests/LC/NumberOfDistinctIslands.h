/*
 [LeetCode] 694. Number of Distinct Islands
 
 Problem
 Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
 
 Count the number of distinct islands. An island is considered to be the same as another if and only if one island can be translated (and not rotated or reflected) to equal the other.
 
 Example 1:
 11000
 11000
 00011
 00011
 Given the above grid map, return 1.
 Example 2:
 11011
 10000
 00001
 11011
 Given the above grid map, return 3.
 
 Notice that:
 11
 1
 and
 1
 11
 are considered different island shapes, because we do not consider reflection / rotation.
 Note: The length of each dimension in the given grid does not exceed 50.
 */

#include "Common.h"

namespace NumberOfDistinctIslands
{
class Solution {
public:
    // traverse all connected points starting (i,j); add points into path
    void dfs(vector<vector<int>>& grid, int i0, int j0, int i, int j, vector<int>& path) {
        static const vector<pair<int, int>> dirs = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
        assert(grid[i][j] == 1);
        auto m = grid.size();
        auto n = grid[0].size();
        path.push_back(i - i0);
        path.push_back(j - j0);
        grid[i][j] = 0;
        for (auto& dir : dirs) {
            auto nextI = i + dir.first;
            auto nextJ = j + dir.second;
            if (nextI < 0 || nextI >= m || nextJ < 0 || nextJ >= n || grid[nextI][nextJ] == 0)
                continue;
            dfs(grid, i0, j0, nextI, nextJ, path);
        }
    }
    /**
     * @param grid: a list of lists of integers
     * @return: return an integer, denote the number of distinct islands
     */
    int numDistinctIslands(vector<vector<int>>& grid) {
        // write your code here
        set<vector<int>> uniquePaths;
        auto m = grid.size();
        if (m == 0) return 0;
        auto n = grid[0].size();
        for (auto i = 0; i < m; i++) {
            for (auto j = 0; j < n; j++) {
                if (grid[i][j] != 1)
                    continue;
                vector<int> path;
                dfs(grid, i, j, i, j, path);
                uniquePaths.emplace(std::move(path));
            }
        }
        return uniquePaths.size();
    }
};

static void Test()
{
    vector<vector<int>> grid = {
        {1,1,0,1,1},
        {1,0,0,0,0},
        {0,0,0,0,1},
        {1,1,0,1,1}
    };
    Solution solution;
    std::cout << solution.numDistinctIslands(grid) << std::endl;
}
}
