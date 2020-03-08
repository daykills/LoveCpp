#pragma once
/*
 741. Cherry Pickup
 In a N x N grid representing a field of cherries, each cell is one of three possible integers.
 
 
 0 means the cell is empty, so you can pass through;
 1 means the cell contains a cherry, that you can pick up and pass through;
 -1 means the cell contains a thorn that blocks your way.
 
 Your task is to collect maximum number of cherries possible by following the rules below:
 
 Starting at the position (0, 0) and reaching (N-1, N-1) by moving right or down through valid path cells (cells with value 0 or 1);
 After reaching (N-1, N-1), returning to (0, 0) by moving left or up through valid path cells;
 When passing through a path cell containing a cherry, you pick it up and the cell becomes an empty cell (0);
 If there is no valid path between (0, 0) and (N-1, N-1), then no cherries can be collected.
 
 
 
 
 Example 1:
 
 Input: grid =
 [[0, 1, -1],
 [1, 0, -1],
 [1, 1,  1]]
 Output: 5
 Explanation:
 The player started at (0, 0) and went down, down, right right to reach (2, 2).
 4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1},{0,0,-1},{0,0,0]].
 Then, the player went left, up, up, left to return home, picking up one more cherry.
 The total number of cherries picked up is 5, and this is the maximum possible.
 
 Example 2:
 
 1 1 1 0 0
 0 0 1 0 1
 1 0 1 0 0
 0 0 1 0 0
 0 0 1 1 1
 
 Output:
*/


#include "Common.h"

namespace CherryPickup
{

string gridHash(vector<vector<int>>& grid) {
    auto n = grid.size();
    assert(n == grid[0].size());
    string hash(n * n, 0);
    int cnt = 0;
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            hash[cnt++] = grid[i][j] + '0';
        }
    }
    return hash;
}

void dfs(vector<vector<int>>& grid, int cherry, bool isBack, int i, int j, int& maxCherry,
         vector<vector<unordered_set<string>>>& visited,
         vector<vector<unordered_set<string>>>& visitedBack,
         string& hash) {
    auto n = grid.size();
    assert(n == grid[0].size());
    // base condition
    if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] == -1)
        return;
    if (!isBack) {
        if (visited[i][j].count(hash))
            return;
        visited[i][j].emplace(hash);
    } else {
        if (visitedBack[i][j].count(hash))
            return;
        visitedBack[i][j].emplace(hash);
        // reach back to origin
        if (i == 0 && j == 0) {
            maxCherry = max(maxCherry, cherry);
            return;
        }
    }
    
    auto tmp = grid[i][j];
    grid[i][j] = 0;
    cherry += tmp;
    hash[i * n + j] = '0';
    
    // turning back, not count cherry
    if (!isBack) {
        if (i == n - 1 && j == n - 1) {
            dfs(grid, cherry, true, n - 1, n - 1, maxCherry, visited, visitedBack, hash);
        }
        dfs(grid, cherry, false, i + 1, j, maxCherry, visited, visitedBack, hash);
        dfs(grid, cherry, false, i, j + 1, maxCherry, visited, visitedBack, hash);
    } else {
        dfs(grid, cherry, true, i - 1, j, maxCherry, visited, visitedBack, hash);
        dfs(grid, cherry, true, i, j - 1, maxCherry, visited, visitedBack, hash);
    }
    grid[i][j] = tmp;
    hash[i * n + j] = '0' + tmp;
}

int cherryPickup(vector<vector<int>>& grid) {
    auto n = grid.size();
    assert(n == grid[0].size());
    vector<vector<unordered_set<string>>> visited(n, vector<unordered_set<string>>(n));
    vector<vector<unordered_set<string>>> visitedBack(n, vector<unordered_set<string>>(n));
    string hash(n * n, 0);
    int cnt = 0;
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            hash[cnt++] = grid[i][j] + '0';
        }
    }
    int maxCherry = 0;
    dfs(grid, 0, false, 0, 0, maxCherry, visited, visitedBack, hash);
    return maxCherry;
}

void Test()
{
    vector<vector<int>> grid {
        {1,1,1,1,-1,-1,-1,1,0,0},
        {1,0,0,0,1,0,0,0,1,0},
        {0,0,1,1,1,1,0,1,1,1},
        {1,1,0,1,1,1,0,-1,1,1},
        {0,0,0,0,1,-1,0,0,1,-1},
        {1,0,1,1,1,0,0,-1,1,0},
        {1,1,0,1,0,0,1,0,1,-1},
        {1,-1,0,1,0,0,0,1,-1,1},
        {1,0,-1,0,-1,0,0,1,0,0},
        {0,0,-1,0,1,0,1,0,0,1}
        /*
        {1,1,0},
        {1,1,0},
        {0,1,1},
         */
        /*
        {1,1,1,0,0},
        {0,0,1,0,1},
        {1,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,1,1},
         */
    };
    cout << "result: " << cherryPickup(grid) << endl;
}

}
