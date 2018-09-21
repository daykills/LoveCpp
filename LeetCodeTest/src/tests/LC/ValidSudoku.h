/*
36. Valid Sudoku My Submissions Question
Total Accepted: 67075 Total Submissions: 223815 Difficulty: Easy
Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.


A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include "Common.h"

namespace ValidSudoku
{
  bool isValidSudoku(vector<vector<char>>& board)
  {
    const int BOARD_SIZE = 9;
    int n = board.size();
    if (n != BOARD_SIZE) return false;

    // history, whether one number has appeared in one row/col
    vector<vector<bool>> row(n, vector<bool>(n, false));
    vector<vector<bool>> col(n, vector<bool>(n, false));
    vector<vector<bool>> grid(n, vector<bool>(n, false));

    for (auto iRow = 0; iRow < n; iRow++)
    {
      auto iGridRow = iRow / 3;
      for (auto iCol = 0; iCol < n; iCol++)
      {
        if (board[iRow][iCol] == '.') continue;
        int num = (int)(board[iRow][iCol] - '1');

        if (row[iRow][num]) return false;
        if (col[iCol][num]) return false;
        row[iRow][num] = col[iCol][num] = true;

        auto iGridCol = iCol / 3;
        auto iGrid = iGridRow * 3 + iGridCol;
        if (grid[iGrid][num]) return false;
        grid[iGrid][num] = true;
      }
    }
    return true;
  }

  void Test()
  {
    vector<string> input{ ".87654321", "2........", "3........", "4........", "5........", "6........", "7........", "8........", "9........" };

    for (auto& line : input)
    {
      cout << line << " " << endl;
    }

    vector<vector<char>> matrix;
    for (auto& line : input)
    {
      matrix.emplace_back(vector<char>(line.begin(), line.end()));
    }

    cout << "result: " << isValidSudoku(matrix) << endl;
  }
}