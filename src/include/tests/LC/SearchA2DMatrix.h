/*
74. Search a 2D Matrix
Total Accepted: 69642 Total Submissions: 210025 Difficulty: Medium
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
[1,   3,  5,  7],
[10, 11, 16, 20],
[23, 30, 34, 50]
]
Given target = 3, return true.
*/

#include <algorithm>
#include "Common.h"

namespace SearchA2DMatrix
{
  void getRowCol(const int n, const int index, int& row, int& col)
  {
    row = index / n;
    col = index % n;
  }

  bool searchMatrix(vector<vector<int>>& matrix, int target)
  {
    const int m = matrix.size();
    if (m == 0) return false;
    const int n = matrix[0].size();
    if (n == 0) return false;
    int lo = 0;
    int hi = m * n - 1;
    while (lo < hi)
    {
      // iMedian ranges from lo to hi - 1
      int iMedian = (lo + hi) >> 1;
      int row, col;
      getRowCol(n, iMedian, row, col);
      if (matrix[row][col] == target) return true;
      else if (matrix[row][col] < target)
      {
        lo = iMedian + 1; 
      }
      else
      {
        hi = iMedian;     // without "- 1"
      }
    }

    // need a final judge for lo
    int row, col;
    getRowCol(n, lo, row, col);
    return (matrix[row][col] == target);
  }
  static int Test()
  {
    using namespace std;
    vector<vector<int>> matrix
    {
      vector<int>{1, 3}
      /*vector<int>{1, 3, 5, 7},
      vector<int>{10, 11, 16, 20},
      vector<int>{23, 30, 34, 50}*/
    };
    return searchMatrix(matrix, 4);
  }
}