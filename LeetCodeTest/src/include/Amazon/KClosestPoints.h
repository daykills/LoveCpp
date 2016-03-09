/*
Find the K closest points to the origin in 2D plane, given an array containing N points.
这一题的基本思想肯定是使用一个大小为K的bomK(大顶堆). 遍历所有N个点,如果当前点到原点的距离小于堆顶的值,则入堆,最后输出堆里面的元素即可..
由于N远大于K,而此时最费时的工作是计算x2 + y2， 所有要找到一个herious，大概的确定范围然后在对这个范围里面的元素做复杂计算。
herious的方法有很多，可以用欧拉distance(x + y)，或者 max(x, y)。
想法是这样的，先使用max(x, y) 来排序最开始所有的点，sort array。
然后 使用大顶堆来做。
当最后发现大顶堆的堆顶的元素的x2 + y2 <= 来到的元素的max(x, y)要小的话就停止。此时堆里面的元素即结果。
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace KClosestPoints
{
  // Definition for a point.
  struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
  };

  // define a distance and its comparator
  struct Distance
  {
    Distance(int _distance, int _index) : distance(_distance), index(_index) {}
    int distance;
    int index;
  };
  //Overload the < operator.
  bool operator < (const Distance& d1, const Distance &d2)
  {
    return d1.distance < d2.distance;
  }

  vector<Point> kClosestPoints(vector<Point>& points, int k)
  {
    // use a maximum heap to keep the smallest distances
    priority_queue<Distance> distances;
    for (int i = 0; i < (int)points.size(); i++)
    {
      int distance = points[i].x * points[i].x + points[i].y * points[i].y;
      // if heap is not full
      if ((int)distances.size() < k)
      {
        distances.emplace(distance, i);
      }
      else if (distance < distances.top().distance)
      {
        // pop the top, and push the new distance
        distances.pop();
        distances.emplace(distance, i);
      }
    }
    vector<Point> result;
    while(!distances.empty())
    {
      result.emplace_back(points[distances.top().index]);
      distances.pop();
    }
    return result;
  }

  void Test()
  {
    vector<Point> points;
    points.emplace_back(0, 2);
    points.emplace_back(3, 1);
    points.emplace_back(-1, 2);
    points.emplace_back(5, 0);
    points.emplace_back(1, 1);
    points.emplace_back(-1, 2);
    for (auto& pt : points)
    {
      cout << "x = " << pt.x << " y = " << pt.y << endl;
    }
    cout << "==============" << endl;
    auto result = kClosestPoints(points, 3);
    for (auto& pt : result)
    {
      cout << "x = " << pt.x << " y = " << pt.y << endl;
    }
  }
}