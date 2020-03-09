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
// max cherries to be picked up by two ppl starting r1, c1, r2, c2
int dfs(vector<vector<int>>& grid, int r1, int c1, int r2,
        vector<vector<vector<int>>>& dp) {
    auto n = grid.size();
    assert(n == grid[0].size());
    
    int c2 = r1 + c1 - r2;
    // only need to check upper bound
    if (r1 >= n || c1 >= n || r2 >= n || c2 >= n
        || grid[r1][c1] == - 1 || grid[r2][c2] == - 1)
        return INT_MIN;
    
    if (dp[r1][c1][r2] != 0)
        return dp[r1][c1][r2];
    
    int tmp1 = grid[r1][c1];
    int tmp2 = grid[r2][c2];
    // when one person reaches end, we return as the other one has to reach the end as well - they have same steps
    // we could return INT_MIN if the other person is not at end, but not necessary
    if (r1 == n - 1 && c1 == n - 1)
        return r2 == r1 ? tmp1 : INT_MIN;
    if (r2 == n - 1 && c2 == n - 1)
        return r2 == r1 ? tmp2 : INT_MIN;
    
    int cherry = 0;
    // reach the same spot, only one gets cherry
    if (r1 == r2 && c1 == c2) {
        cherry = tmp1;
    } else {
        cherry = tmp1 + tmp2;
    }
    // mark them picked
    grid[r1][c1] = grid[r2][c2] = 0;
    
    int moreCherry = INT_MIN;
    moreCherry = max(moreCherry, dfs(grid, r1 + 1, c1, r2 + 1, dp));
    moreCherry = max(moreCherry, dfs(grid, r1 + 1, c1, r2, dp));
    moreCherry = max(moreCherry, dfs(grid, r1, c1 + 1, r2 + 1, dp));
    moreCherry = max(moreCherry, dfs(grid, r1, c1 + 1, r2, dp));
    grid[r1][c1] = tmp1;
    grid[r2][c2] = tmp2;
    
    dp[r1][c1][r2] = cherry + moreCherry;
    return dp[r1][c1][r2];
}

int cherryPickup(vector<vector<int>>& grid) {
    auto n = grid.size();
    assert(n == grid[0].size());
    
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, 0)));
    
    int maxCherry = dfs(grid, 0, 0, 0, dp);
    return max(0, maxCherry);
}

void Test()
{
    vector<vector<int>> grid {
        /*
        {1,1,-1},
        {1,-1,1},
        {-1,1,1}
        */
        /*
        {1,1,1,0,0},
        {0,0,1,0,1},
        {1,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,1,1}
        */
        
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
        {1,1,1},
        {1,1,0},
        {0,1,1},
         */
    };
    cout << "result: " << cherryPickup(grid) << endl;
}

}
