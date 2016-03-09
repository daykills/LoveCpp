/*
48. Rotate Image My Submissions Question
Total Accepted: 61259 Total Submissions: 180001 Difficulty: Medium
You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include "Common.h"

namespace RotateImage
{
  void rotate(vector<vector<int>>& matrix)
  {
    int n = matrix.size();
    if (n <= 1) return;
    
    std::reverse(matrix.begin(), matrix.end());
    for (auto i = 0; i < n; i++)
    {
      for (auto j = i + 1; j < n; j++)
      {
        std::swap(matrix[i][j], matrix[j][i]);
      }
    }
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

    rotate(matrix);
    
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