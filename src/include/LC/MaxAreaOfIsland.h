/*
 695. Max Area of Island

 Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
 
 Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)
 
 Example 1:
 
 [[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]
 Given the above grid, return 6. Note the answer is not 11, because the island must be connected 4-directionally.
 Example 2:
 
 [[0,0,0,0,0,0,0,0]]
 Given the above grid, return 0.
 Note: The length of each dimension in the given grid does not exceed 50.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace MaxAreaOfIsland
{
int maxAreaOfIsland(vector<vector<int>>& grid) {
    vector<pair<int, int>> dirs = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
    auto m = grid.size();
    auto n = grid[0].size();
    int maxArea = 0;
    for (auto i = 0; i < m; i++) {
        for (auto j = 0; j < n; j++) {
            if (grid[i][j] != 1) continue;
            stack<pair<int, int>> s;
            s.emplace(i, j);
            grid[i][j] = -1;
            auto area = 0;
            while (!s.empty()) {
                area++;
                auto top = s.top();
                s.pop();
                int curI = top.first;
                int curJ = top.second;
                for (auto& dir : dirs) {
                    int nextI = curI + dir.first;
                    int nextJ = curJ + dir.second;
                    if (nextI >= m || nextI < 0 || nextJ >= n || nextJ < 0) continue;
                    if (grid[nextI][nextJ] != 1) continue;
                    grid[nextI][nextJ] = -1;
                    s.emplace(nextI, nextJ);
                }
            }
            maxArea = max(maxArea, area);
        }
    }
    return maxArea;
}

void Test()
{
    vector<vector<int>> grid = {{1,1,0,0,0},{1,1,0,0,0},{0,0,0,1,1},{0,0,0,1,1}};
    cout << maxAreaOfIsland(grid) << std::endl;
}
}
