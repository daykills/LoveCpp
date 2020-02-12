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
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.size() <= 1) return intervals;
    
    auto lesser = [](const vector<int>& lhs, const vector<int>& rhs) {
        assert(lhs.size() == rhs.size() && lhs.size() == 2);
        return lhs[0] < rhs[0];
    };
    std::sort(intervals.begin(), intervals.end(), lesser);
    vector<vector<int>> result { intervals[0] };
    for (auto& cur : intervals) {
        auto& last = result.back();
        assert(last[0] <= cur[0]);
        if (last[1] < cur[0]) {
            result.push_back(cur);
        } else {
            last[1] = max(last[1], cur[1]);
        }
    }
    return result;
}
    
int Test()
{
    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    for (const auto& pair : intervals)
    {
        cout << "[" << pair[0] << "," << pair[1] << "] ";
    }
    cout << endl;
    auto result = merge(intervals);
    for (const auto& interval : result)
    {
        cout << "[" << interval[0] << "," << interval[1] << "] ";
    }
    return 0;
}
}
