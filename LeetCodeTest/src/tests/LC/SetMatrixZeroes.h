/*
73. Set Matrix Zeroes My Submissions Question
Total Accepted: 61492 Total Submissions: 185650 Difficulty: Medium
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

click to show follow up.

Follow up:
Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include "Common.h"

namespace SetMatrixZeroes
{
  void setZeroes(vector<vector<int>>& matrix)
  {
    int m = matrix.size();
    if (m == 0) return;
    int n = matrix[0].size();

    // use the row/col of the first found '0' cell to store information
    int firstRow = -1, firstCol = -1;

    for (auto i = 0; i < m; i++)
    {
      for (auto j = 0; j < n; j++)
      {
        if (matrix[i][j] == 0)
        {
          // if this is the first time to meet a '0'
          if (firstRow == -1)
          {
            firstRow = i, firstCol = j;
          }
          // store the row/col information
          matrix[firstRow][j] = 0;
          matrix[i][firstCol] = 0;
        }
      }
    }

    if (firstRow == -1) return;
    for (auto i = 0; i < m; i++)
    {
      // skip the firstRow and firstCol
      if (i == firstRow) continue;

      for (auto j = 0; j < n; j++)
      {
        if (j == firstCol) continue;

        if (matrix[i][firstCol] == 0 || matrix[firstRow][j] == 0)
        {
          matrix[i][j] = 0;
        }
      }
    }
    for (auto i = 0; i < m; i++) matrix[i][firstCol] = 0;
    for (auto j = 0; j < n; j++) matrix[firstRow][j] = 0;
  }

  void Test()
  {
    auto matrix = CommonUtils::getIntVector();

    for (auto& line : matrix)
    {
      for (auto num : line)
      {
        cout << num << " ";
      }
      cout << endl;
    }

    setZeroes(matrix);

    cout << "result: " << endl;

    for (auto& line : matrix)
    {
      for (auto num : line)
      {
        cout << num << " ";
      }
      cout << endl;
    }
  }
}