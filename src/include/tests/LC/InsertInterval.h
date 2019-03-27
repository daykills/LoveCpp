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
    // Definition for an interval.
    struct Interval {
        int start;
        int end;
        Interval() : start(0), end(0) {}
        Interval(int s, int e) : start(s), end(e) {}
    };
    
    vector<Interval> insert_1(vector<Interval>& intervals, Interval newInterval)
    {
        int n = intervals.size();
        if (0 == n) return vector<Interval>{ newInterval };
        vector<Interval> result;
        for (int i = 0; i < n; i++)
        {
            auto& interval = intervals[i];
            if (newInterval.start > interval.end)
            {
                // newInterval comes after interval
                result.emplace_back(interval);
                continue;
            }
            
            if (newInterval.end < interval.start)
            {
                // newInterval comes before interval
                // add newInterval, and then the rest of intervals
                result.emplace_back(newInterval);
                result.insert(result.end(), intervals.begin() + i, intervals.end());
                return result;
            }
            // there is overlapping, merge interval with newInterval
            newInterval.start = min(newInterval.start, interval.start);
            newInterval.end = max(newInterval.end, interval.end);
        }
        result.emplace_back(newInterval);
        return result;
    }
    
    //static bool cmp(const Interval &interval1, const Interval &interval2)
    //{
    //  return interval1.start < interval2.start;
    //}
    
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
    
    vector<Interval> insert_2(vector<Interval>& intervals, Interval newInterval)
    {
        intervals.emplace_back(newInterval);
        return merge(intervals);
    }
    
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        auto lesser = [](const Interval& first, const Interval& second) {
            return first.end < second.start;
        };
        auto equalRange = equal_range(intervals.begin(), intervals.end(), newInterval, lesser);
        auto it1 = equalRange.first;
        auto it2 = equalRange.second;
        // no overlapping
        if (it1 == it2) {
            intervals.insert(it1, newInterval);
        } else {
            it2--;
            it1->start = min(it1->start, newInterval.start);
            it1->end = max(it2->end, newInterval.end);
            intervals.erase(it1 + 1, it2 + 1);
        }
        return intervals;
    }
    
    int Test()
    {
        vector<pair<int, int>> intPairs = { { 1,3 }, { 6,9 }, { 10, 12 } };
        vector<Interval> intervals;
        for (const auto& pair : intPairs)
        {
            cout << "[" << pair.first << "," << pair.second << "] ";
            intervals.emplace_back(pair.first, pair.second);
        }
        cout << endl;
        
        Interval newInterval(4, 15);
        cout << "[" << newInterval.start << "," << newInterval.end << "] ";
        cout << endl;
        
        auto result = insert(intervals, newInterval);
        for (const auto& interval : result)
        {
            cout << "[" << interval.start << "," << interval.end << "] ";
        }
        cout << endl;
        return 0;
    }
}
