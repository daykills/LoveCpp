/*
54. Spiral Matrix My Submissions Question
Total Accepted: 53959 Total Submissions: 243584 Difficulty: Medium
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
[ 1, 2, 3 ],
[ 4, 5, 6 ],
[ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include "Common.h"

namespace SpiralMatrix
{
  vector<int> spiralOrder(vector<vector<int>>& matrix)
  {
    int m = matrix.size();
    if (m == 0) return vector<int>();;
    int n = matrix[0].size();

    vector<int> path(m * n);
    int nIterations = (min(m, n) + 1) / 2;
    int count = 0;
    for (auto i = 0; i < nIterations; i++)
    {
      // top line
      for (auto col = i; col < n - i; col++, count++)
        path[count] = matrix[i][col];

      // right line, skip row=i as it's already taken by top line
      for (auto row = i + 1; row < m - i; row++, count++)
        path[count] = matrix[row][n - i - 1];

      // bottom, if it overlaps with top line, skip it
      if (m - i - 1 != i)
      {
        // skip col=n-i-1
        for (auto col = n - i - 2; col >= i; col--, count++)
          path[count] = matrix[m - i - 1][col];
      }
      // left, if it overlaps with right line, skip it
      if (n - i - 1 != i)
      {
        // skip row=m-i-1
        for (auto row = m - i - 2; row >= i + 1; row--, count++)
          path[count] = matrix[row][i];
      }
    }
    return path;
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

    auto result = spiralOrder(matrix);

    cout << "result: ";
    
    for (auto num : result)
    {
      cout << num << " ";
    }
    cout << endl;    
  }
}