#pragma once
/*
130. Surrounded Regions My Submissions Question
Total Accepted: 49590 Total Submissions: 311982 Difficulty: Medium
Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
*/

#include "Common.h"

namespace SurroundedRegions
{
class Solution {
public:
    const static char kBlock = 'X';
    const static char kPass = 'O';
    const static char kEscape = 'A';
    
    // mark all connected 'O' as 'X'
    void dfs(vector<vector<char>>& grid, int row, int col) {
        auto m = grid.size();
        assert(m > 0);
        auto n = grid[0].size();
        assert(n > 0);
        
        static const vector<pair<int, int>> kDirs = {
            { 1, 0 }, { 0, 1 }, { 0, -1 }, { -1, 0 },
        };
        
        if (row < 0 || row >= m || col < 0 || col >= n
            || grid[row][col] != kPass)
            return;;
        
        grid[row][col] = kEscape;
        
        for (auto& dir : kDirs) {
            auto nextRow = row + dir.first;
            auto nextCol = col + dir.second;
            
            dfs(grid, nextRow, nextCol);
        }
    }
    
    void solve(vector<vector<char>>& grid) {
        auto m = grid.size();
        if (m == 0) return;
        auto n = grid[0].size();
        if (n == 0) return;
        
        // start from border cells. Mark all connected empty cell as 'X'
        for (int i = 0; i < m; i++) {
            bool isBottomOrTop = i == 0 || i == m - 1;
            for (int j = 0; j < n; j++) {
                bool isBorder = isBottomOrTop || j == 0 || j == n -1;
                if (!isBorder)
                    continue;
                dfs(grid, i, j);
            }
        }
        
        // mark all surrounded cells
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == kPass)
                    grid[i][j] = kBlock;
            }
        }
        // mark all escape cells
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == kEscape)
                    grid[i][j] = kPass;
            }
        }
    }
};


///////////////////////////

void Test()
{
    vector<vector<string>> boardStr
    {
        {"X","X","X","X"},
        {"X","O","O","X"},
        {"X","X","O","X"},
        {"X","O","X","X"},
        /*
        {"O","O","O","O","X","X"},
        {"O","O","O","O","O","O"},
        {"O","X","O","X","O","O"},
        {"O","X","O","O","X","O"},
        {"O","X","O","X","O","O"},
        {"O","X","O","O","O","O"}
         */
        //{"O"}
        /*
         {"XXXX"},
         {"XOOX"},
         {"XXOX"},
         {"XOXX"},
         */
        /*
        "XOOOOOOOOOOOOOOOOOOO",
        "OXOOOOXOOOOOOOOOOOXX",
        "OOOOOOOOXOOOOOOOOOOX",
        "OOXOOOOOOOOOOOOOOOXO",
        "OOOOOXOOOOXOOOOOXOOX",
        "XOOOXOOOOOXOXOXOXOXO",
        "OOOOXOOXOOOOOXOOXOOO",
        "XOOOXXXOXOOOOXXOXOOO",
        "OOOOOXXXXOOOOXOOXOOO",
        "XOOOOXOOOOOOXXOOXOOX",
        "OOOOOOOOOOXOOXOOOXOX",
        "OOOOXOXOOXXOOOOOXOOO",
        "XXOOOOOXOOOOOOOOOOOO",
        "OXOXOOOXOXOOOXOXOXOO",
        "OOXOOOOOOOXOOOOOXOXO",
        "XXOOOOOOOOXOXXOOOXOO",
        "OOXOOOOOOOXOOXOXOXOO",
        "OOOXOOOOOXXXOOXOOOXO",
        "OOOOOOOOOOOOOOOOOOOO",
        "XOOOOXOOOXXOOXOXOXOO"
         */
    };
    
    vector<vector<char>> board;
    cout << "Matrix: " << endl;
    for (auto& line : boardStr)
    {
        vector<char> lineCh;
        for (auto ch : line)
        {
            cout << ch << " ";
            lineCh.emplace_back(ch[0]);
        }
        board.emplace_back(move(lineCh));
        cout << endl;
    }
    Solution s;
    s.solve(board);
    cout << "Result: " << endl;
    for (auto& line : board)
    {
        for (auto ch : line)
        {
            cout << ch << " ";
        }
        cout << endl;
    }
}
}
