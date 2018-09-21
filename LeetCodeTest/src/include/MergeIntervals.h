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

  static bool CompareInterval(const Interval& int1, const Interval& int2)
  {
    return int1.start < int2.start;
  }

  vector<Interval> merge(vector<Interval>& intervals) {
    int n = intervals.size();
    if (n <= 1) return intervals;

    // sort the intervals by start
    sort(intervals.begin(), intervals.end(), CompareInterval);

    vector<Interval> result(1, intervals[0]);
    // go through all intervals, merge one by one
    for (auto i = 1; i < n; i++)
    {
      auto& curInt = result.back();
      auto& mergingInt = intervals[i];
      // curInt.start is guaranteed to be smaller than mergingInt.start
      if (mergingInt.start <= curInt.end)
      {
        // mergingInt is fully contained
        if (mergingInt.end <= curInt.end) continue;
        // extend curInt.end
        curInt.end = mergingInt.end;
      }
      else
      {
        // no overlapping, add directly
        result.emplace_back(mergingInt);
      }
    }
    return result;
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