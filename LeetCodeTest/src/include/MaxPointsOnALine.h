/*
149. Max Points on a Line My Submissions Question
Total Accepted: 52751 Total Submissions: 377870 Difficulty: Hard
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace MaxPointsOnALine
{  
  // Definition for a point.
  struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
  };

  // definition for Fraction numbers
  struct Fraction
  {
    int numerator;
    int denominator;
    Fraction() : numerator(0), denominator(0) {}
    Fraction(int _numerator, int _denominator) : numerator(_numerator), denominator(_denominator) {}
    bool operator==(const Fraction &other) const
    {
      // 1/0 == 2/0 == -1/0
      if (denominator == 0 && other.denominator == 0) return true;
      if (denominator == 0 || other.denominator == 0) return false;
      return other.numerator * denominator == numerator * other.denominator;
    }
  };

  // hash function
  struct hash_func
  {
    size_t operator()(const Fraction &f) const
    {
      hash<int> hash;
      if (f.denominator == 0)
        return hash(0);
      return hash(f.numerator / f.denominator);
    }
  };
  
  int maxPoints(vector<Point>& points)
  {
    int n = points.size();
    if (n <= 2) return n;
    
    int result = 0;
    for (int i = 0; i < n; i++)
    {
      unordered_map<Fraction, int, hash_func> fractions;
      const auto& basePoint = points[i];
      int dupCnt = 1;
      for (int j = i + 1; j < n; j++)
      {
        if (points[j].y == basePoint.y && points[j].x == basePoint.x)
        {
          dupCnt++;
          continue;
        }
        Fraction f(points[j].y - basePoint.y, points[j].x - basePoint.x);
        fractions[f]++;
      }
      int max = 0;
      for (auto& pair : fractions)
      {
        if (pair.second > max) max = pair.second;
      }
      max += dupCnt;
      if (max > result) result = max;
    }
    return result;
  }
  static int Test()
  {
    vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(1, 1);
    points.emplace_back(-1, 2);
    points.emplace_back(0, 0);
    points.emplace_back(1, 1);
    points.emplace_back(-1, 2);
    return maxPoints(points);
  }
}