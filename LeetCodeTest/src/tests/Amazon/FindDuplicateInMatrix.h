/*
Write a function that determins whether a two-dimentional integer array contains duplicate values within k indices of each other (manhattan distance).

Data format is as below:
4 // number of lines in matrix
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
3 // k
*/
#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include "Common.h"

namespace FindDuplicateInMatrix
{
  // Definition for a point.
  struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
    bool operator==(const Point &other) const
    {
      return x == other.x && y == other.y;
    }
    bool operator!=(const Point &other) const
    {
      return !(*this == other);
    }
  };

  struct PointHash
  {
    std::size_t operator()(const Point & pt) const
    {
      return hash<int>()(pt.x) + (hash<int>()(pt.y) << 10);
    }
  };

  // moves in four directions
  static const int NUM_MOVES = 4;
  // direction 0 - i++; 1 - j++; 2 - i--; 3 - j--; others error
  void move(int& i, int& j, int direction)
  {
    if (direction == 0) i++;
    else if (direction == 1) j++;
    else if (direction == 2) i--;
    else if (direction == 3) j--;
    else assert(false);
  }

  // BSF search for duplicate within k steps
  bool searchDuplicate(const vector<vector<int>>& matrix, int i, int j, int k)
  {
    int m = matrix.size();
    if (m == 0) return false;
    int n = matrix[0].size();
    if (n == 0) return false;
    
    Point start(i, j);
    Point spliter(-1, -1);

    unordered_set<Point, PointHash> visited;
    visited.emplace(i, j);
    
    queue<Point> searchQ;
    searchQ.push(start);

    int distance = 0;
    while (!searchQ.empty())
    {
      // put spliter in the start of each level
      searchQ.push(spliter);

      // before next spliter, all points are at the same level
      while (searchQ.front() != spliter)
      {
        Point cur = searchQ.front();
        searchQ.pop();

        if (cur != start && matrix[cur.x][cur.y] == matrix[start.x][start.y])
          return true;

        for (auto iDirection = 0; iDirection < NUM_MOVES; iDirection++)
        {
          int nextI = cur.x, nextJ = cur.y;
          move(nextI, nextJ, iDirection);
          // check boundary
          if (nextI < 0 || nextI >= m || nextJ < 0 || nextJ >= n)
            continue;
          // if next point is not visited yet, add it to queue
          if (visited.find(Point(nextI, nextJ)) == visited.end())
          {
            visited.emplace(nextI, nextJ);
            searchQ.emplace(nextI, nextJ);
          }
        }
      }
      // pop out spliter
      searchQ.pop();
      // if distance is bigger than k, then search stops
      if (++distance > k) return false;
    }
    return false;
  }

  bool findDuplicateInMatrix(vector<vector<int>>& matrix, int k)
  {
    int m = matrix.size();
    if (m == 0) return false; 
    int n = matrix[0].size();
    if (n == 0) return false;

    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (searchDuplicate(matrix, i, j, k)) return true;
      }
    }
    
    return false;
  }

  void Test()
  {
    auto matrix = CommonUtils::getIntVector();
    int numLines = matrix[0][0];
    assert(numLines + 2 == matrix.size());
    int k = matrix.back()[0];
    matrix.erase(matrix.end() - 1);
    matrix.erase(matrix.begin());
    for (auto& line : matrix)
    {
      for (auto num : line)
      {
        cout << num << " ";
      }
      cout << endl;
    }
    cout << "result: " << findDuplicateInMatrix(matrix, k) << endl;
  }
}