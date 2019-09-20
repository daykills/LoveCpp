/*
 463. Island Perimeter
 Easy

 1220

 88

 Favorite

 Share
 You are given a map in form of a two-dimensional integer grid where 1 represents land and 0 represents water.

 Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).

 The island doesn't have "lakes" (water inside that isn't connected to the water around the island). One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.

  

 Example:

 Input:
 [[0,1,0,0],
  [1,1,1,0],
  [0,1,0,0],
  [1,1,0,0]]

 Output: 16

 */

#include "Common.h"

namespace IslandPerimeter
{
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        vector<vector<int>> dirs = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
        auto m = grid.size();
        auto n = grid[0].size();
        for (auto i = 0; i < m; i++) {
            for (auto j = 0; j < n; j++) {
                if (grid[i][j] == 0) continue;
                int totalSize = 0;
                stack<pair<int, int>> s;
                s.emplace(i, j);
                grid[i][j] = -1;
                while (!s.empty()) {
                    int curI = s.top().first;
                    int curJ = s.top().second;
                    // mark visited
                    s.pop();
                    for (auto& dir : dirs) {
                        int nextI = curI + dir[0];
                        int nextJ = curJ + dir[1];
                        if (nextI < 0 || nextI >= m || nextJ < 0 || nextJ >= n || grid[nextI][nextJ] == 0) {
                            totalSize++;
                            continue;
                        }
                        if (grid[nextI][nextJ] == 1) {
                            grid[nextI][nextJ] = -1;
                            s.emplace(nextI, nextJ);
                        }
                    }
                }
                return totalSize;
            }
        }
        return 0;
    }
};

static void Test()
{
    Solution solution;
    vector<vector<int>> grid = {
        /*
        { 0,1,0,0 },
        { 1,1,1,0 },
        { 0,1,0,0 },
        { 1,1,0,0 }
         */
        { 1,1 },
        { 1,1 }
    };
    std::cout << solution.islandPerimeter(grid) << std::endl;
}
}
