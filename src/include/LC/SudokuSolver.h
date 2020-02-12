/*
37. Sudoku Solver My Submissions Question
Total Accepted: 46776 Total Submissions: 191708 Difficulty: Hard
Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.

A sudoku puzzle...

...and its solution numbers marked in red.
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include "Common.h"

namespace SudokuSolver
{
  const int GRID_SIZE = 9;

  bool validNumberAtCell(vector<vector<char>>& board, int row, int col, char v)
  {
    for (auto i = 0; i < GRID_SIZE; i++)
    {
      // check row
      if (board[row][i] == v) return false;
      // check col
      if (board[i][col] == v) return false;
      // check sub grid
      auto subRow = (row / 3) * 3 + i / 3;
      auto subCol = (col / 3) * 3 + i % 3;
      if (board[subRow][subCol] == v) return false;
    }
    return true;
  }

  // solve current step using recursive
  bool solve(vector<vector<char>>& board, const vector<pair<int, int>>& emptyCells, int step)
  {
    // base condition. if all steps are done, return success;
    if (step == (int)emptyCells.size()) return true;

    // try different values for current emptyCell
    const int row = emptyCells[step].first;
    const int col = emptyCells[step].second;
    for (auto v = '1'; v <= '9'; v++)
    {
      if (!validNumberAtCell(board, row, col, v)) continue;
      // v is allowed
      board[row][col] = v;
      // if we can solve for further steps, it's solved
      if (solve(board, emptyCells, step + 1)) return true;
      // failed to solve use value v. roll back to '.'
      board[row][col] = '.';
    }
    // all possible numbers fail
    return false;
  }

  void solveSudoku(vector<vector<char>>& board)
  {
    // find all empty cells to fill
    vector<pair<int, int>> emptyCells;
    for (auto row = 0; row < GRID_SIZE; row++)
    {
      for (auto col = 0; col < GRID_SIZE; col++)
      {
        if (board[row][col] == '.')
        {
          emptyCells.emplace_back(row, col);
        }
      }
    }
    solve(board, emptyCells, 0);
  }

  void Test()
  {
    vector<string> input{ "..9748...", "7........", ".2.1.9...", "..7...24.", ".64.1.59.", ".98...3..", "...8.3.2.", "........6", "...2759.." };
    vector<vector<char>> matrix;
    for (auto& line : input)
    {
      matrix.emplace_back(vector<char>(line.begin(), line.end()));
    }

    for (auto& line : matrix)
    {
      for (auto ch : line)
      {
        cout << ch << " ";
      }
      cout << endl;
    }
    cout << endl;

    solveSudoku(matrix);

    for (auto& line : matrix)
    {
      for (auto ch : line)
      {
        cout << ch << " ";
      }
      cout << endl;
    }
  }
}