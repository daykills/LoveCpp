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
    
    vector<Interval> merge(vector<Interval>& intervals) {
        if (intervals.size() <= 1) return intervals;
        
        auto lesser = [](const Interval& first, const Interval& second) {
            return first.start < second.start;
        };
        std::sort(intervals.begin(), intervals.end(), lesser);
        vector<Interval> result { intervals[0] };
        for (auto& cur : intervals) {
            auto& last = result.back();
            assert(last.start <= cur.start);
            if (last.end < cur.start) {
                result.push_back(cur);
            } else {
                last.end = max(last.end, cur.end);
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
