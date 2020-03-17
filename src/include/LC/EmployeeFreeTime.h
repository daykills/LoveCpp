/*
 759. Employee Free Time

 We are given a list schedule of employees, which represents the working time for each employee.

 Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.

 Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.

 (Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays. For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined).  Also, we wouldn't include intervals like [5, 5] in our answer, as they have zero length.

  

 Example 1:

 Input: schedule = {{[1,2},{5,6}},{{1,3}},{{4,10}}]
 Output: {{3,4}}
 Explanation: There are a total of three employees, and all common
 free time intervals would be [-inf, 1], [3, 4], [10, inf].
 We discard any intervals that contain inf as they aren't finite.
 Example 2:

 Input: schedule = {{[1,3},{6,7}},{{2,4}},{{2,5},{9,12}}]
 Output: {{5,6},{7,9}}
  

 Constraints:

 1 <= schedule.length , schedule[i].length <= 50
 0 <= schedule[i].start < schedule[i].end <= 10^8
 */

#include "Common.h"

namespace EmployeeFreeTime
{

// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        auto lessor =[&schedule](const vector<int>& lhs, const vector<int>& rhs) {
            auto& lInt = schedule[lhs[0]][lhs[1]];
            auto lVal = lhs[2] == 0 ? lInt.start : lInt.end;
            auto& rInt = schedule[rhs[0]][rhs[1]];
            auto rVal = rhs[2] == 0 ? rInt.start : rInt.end;
            return lVal > rVal;
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(lessor)> minHeap(lessor);
        for (auto i = 0; i < schedule.size(); i++) {
            minHeap.push({i, 0, 0});
        }
        // index / change pairs
        vector<vector<int>> changes;
        while (!minHeap.empty()) {
            auto minInterval = minHeap.top(); minHeap.pop();
            auto iSchedule = minInterval[0];
            auto iInterval = minInterval[1];
            auto startOrEnd = minInterval[2];
            if (startOrEnd == 0) {
                changes.push_back({schedule[iSchedule][iInterval].start, 1});
                startOrEnd = 1;
            } else {
                changes.push_back({schedule[iSchedule][iInterval].end, -1});
                startOrEnd = 0;
                iInterval++;
            }
            if (iInterval < schedule[iSchedule].size()) {
                minHeap.push({iSchedule, iInterval, startOrEnd});
            }
        }
        int cnt = 0;
        vector<Interval> freeTimes;
        for (auto i = 0; i < changes.size(); i++) {
            auto& change = changes[i];
            bool preFree = i > 0 && cnt == 0;
            cnt += change[1];
            if (cnt == 0) {
                assert(preFree == false);
                if (i < changes.size() - 1)
                    freeTimes.emplace_back(change[0], 0);
            } else {
                if (preFree) {
                    assert(!freeTimes.empty());
                    assert(freeTimes.back().end == 0);
                    freeTimes.back().end = change[0];
                    if (freeTimes.back().start == freeTimes.back().end)
                        freeTimes.pop_back();
                }
            }
        }
        return freeTimes;;
    }
};
/**
* Your AutocompleteSystem object will be instantiated and called as such:
* AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
* vector<string> param_1 = obj->input(c);
*/

static void Test()
{
    vector<vector<Interval>> schedule {
        {{1,3},{6,7}},
        {{2,4}},
        {{2,5},{9,12}}
    };
    
    Solution s;
    auto result = s.employeeFreeTime(schedule);
    
    for (auto& interval : result) {
        cout << interval.start << "," << interval.end << endl;
    }
}
}
