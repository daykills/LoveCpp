/*
56. Merge Intervals
Total Accepted: 57902 Total Submissions: 237563 Difficulty: Hard
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].
*/

#include <iostream>
#include <algorithm>
#include "Common.h"

namespace MergeIntervals
{
  // Definition for an interval.
  struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
  };

  static bool cmp(const Interval &interval1, const Interval &interval2)
  {
    return interval1.start < interval2.start;
  }
  
  vector<Interval> merge(vector<Interval>& intervals)
  {
    vector<Interval> result;
    int n = intervals.size();
    if (n == 0) return move(result);
    sort(intervals.begin(), intervals.end(), cmp);
    for (int i = 0; i < n; i++)
    {
      auto start = intervals[i].start;
      auto end = intervals[i].end;
      while (i < n - 1 && end >= intervals[i + 1].start)
      {
        if (intervals[i + 1].end > end)
          end = intervals[i + 1].end;
        i++;
      }
      result.emplace_back(start, end);
    }
    return move(result);
  }

  int Test(vector<pair<int, int>> intPairs)
  {
    vector<Interval> intervals;
    for (const auto& pair : intPairs)
    {
      cout << "[" << pair.first << "," << pair.second << "] ";
      intervals.emplace_back(pair.first, pair.second);
    }
    cout << endl;
    auto result = merge(intervals);
    for (const auto& interval : result)
    {
      cout << "[" << interval.start << "," << interval.end << "] ";
    }
    return 0;
  }
}