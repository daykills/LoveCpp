/*
57. Insert Interval
Total Accepted: 51578 Total Submissions: 223239 Difficulty: Hard
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
*/

#include <iostream>
#include <algorithm>
#include "Common.h"

namespace InsertInterval
{
    
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    auto lessor = [](const vector<int>& lhs, const vector<int>& rhs) {
        return lhs[1] < rhs[0];
    };
    auto range = equal_range(intervals.begin(), intervals.end(), newInterval, lessor);
    auto lower = range.first;
    auto upper = range.second;
    if (lower == upper) {
        intervals.insert(lower, newInterval);
    } else {
        auto start = min((*lower)[0], newInterval[0]);
        auto end = max((*(upper - 1))[1], newInterval[1]);
        (*lower)[0] = start;
        (*lower)[1] = end;
        intervals.erase(lower + 1, upper);
    }
    return intervals;
}
    
int Test()
{
    vector<vector<int>> intervals = { { 1,3 }, { 6,9 } };
    
    vector<int> newInterval = { 2, 5 };
    cout << "[" << newInterval[0] << "," << newInterval[1] << "] ";
    cout << endl;
    
    auto result = insert(intervals, newInterval);
    for (const auto& interval : result)
    {
        cout << "[" << interval[0] << "," << interval[1] << "] ";
    }
    cout << endl;
    return 0;
}
}
