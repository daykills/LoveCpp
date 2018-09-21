/*
51. N-Queens My Submissions Question
Total Accepted: 50552 Total Submissions: 193110 Difficulty: Hard
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.



Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
[".Q..",  // Solution 1
"...Q",
"Q...",
"..Q."],

["..Q.",  // Solution 2
"Q...",
"...Q",
".Q.."]
]
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace NQueens
{
  // check whether we can put a queen at row,col
  bool canPutQueenAt(const vector<int>& queenCols, int row, int col)
  {
    for (auto queenRow = 0; queenRow < (int)queenCols.size(); queenRow++)
    {
      auto queenCol = queenCols[queenRow];
      if (queenCol == -1) return true;
      // remember to check diagnoal
      if (queenCol == col || abs(queenRow - row) == abs(queenCol - col)) return false;
    }
    return true;
  }

  void dfsTraverse(vector<int>& queenCols, int numQueensAlreadySet, int n, vector<vector<string>>& solutions)
  {
    // base condition
    // n queens are placed, create one result
    if (numQueensAlreadySet == n)
    {
      vector<string> oneSolution(n, string(n, '.'));
      for (auto row = 0; row < n; row++)
      {
        oneSolution[row][queenCols[row]] = 'Q';
      }
      solutions.emplace_back(move(oneSolution));
      return;
    }

    // work on one new row
    int row = numQueensAlreadySet;
    for (int col = 0; col < n; col++)
    {
      // if row/col is not valid, skip it
      if (!canPutQueenAt(queenCols, row, col)) continue;
      queenCols[numQueensAlreadySet] = col;
      // traverse for rest of queens
      dfsTraverse(queenCols, numQueensAlreadySet + 1, n, solutions);
      queenCols[numQueensAlreadySet] = -1;
    }
  }

  vector<vector<string>> solveNQueens(int n)
  {
    vector<vector<string>> result;
    // ith queen is placed at ith row, so we only need to figure out col
    vector<int> queenCols(n, -1);
    // dfs traverse through all possible solutions, and add valid ones to result.
    dfsTraverse(queenCols, 0, n, result);
    return move(result);
  }

  void Test()
  {
    int n = 6;
    auto result = solveNQueens(n);
    cout << "Number of queens: " << n << endl;
    cout << endl << "Result: " << endl;
    for (auto& combination : result)
    {
      for (auto& num : combination)
      {
        cout << num << endl;
      }
      cout << "==========================" << endl;
    }
  }
}