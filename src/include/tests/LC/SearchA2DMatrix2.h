/*
240. Search a 2D Matrix II My Submissions Question
Total Accepted: 27924 Total Submissions: 84073 Difficulty: Medium
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
For example,

Consider the following matrix:

[
[1,   4,  7, 11, 15],
[2,   5,  8, 12, 19],
[3,   6,  9, 16, 22],
[10, 13, 14, 17, 24],
[18, 21, 23, 26, 30]
]
Given target = 5, return true.

Given target = 20, return false.
*/

#include <algorithm>
#include "Common.h"

namespace SearchA2DMatrix2
{
  bool searchMatrix(vector<vector<int>>& matrix, int target)
  {
    const int m = matrix.size();
    if (m == 0) return false;
    const int n = matrix[0].size();
    if (n == 0) return false;
    // start search from top right corner.
    int i = 0;
    int j = n - 1;
    while (i < m && j >= 0)
    {
      if (matrix[i][j] == target) return true;
      if (matrix[i][j] > target)
      {
        j--;
      }
      else
      {
        i++;
      }
    }
    return false;
  }
  static int Test()
  {
    using namespace std;
    vector<vector<int>> matrix
    {
      //vector<int>{1, 3}
      vector<int>{1, 4, 7, 11, 15},
      vector<int>{2, 5, 8, 12, 19},
      vector<int>{3, 6, 9, 16, 22}
    };
    return searchMatrix(matrix, 5);
  }
}