/*
 731. My Calendar II
 
 Implement a MyCalendarTwo class to store your events. A new event can be added if adding the event will not cause a triple booking.
 
 Your class will have one method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.
 
 A triple booking happens when three events have some non-empty intersection (ie., there is some time that is common to all 3 events.)
 
 For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a triple booking. Otherwise, return false and do not add the event to the calendar.
 
 Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)
 Example 1:
 
 MyCalendar();
 MyCalendar.book(10, 20); // returns true
 MyCalendar.book(50, 60); // returns true
 MyCalendar.book(10, 40); // returns true
 MyCalendar.book(5, 15); // returns false
 MyCalendar.book(5, 10); // returns true
 MyCalendar.book(25, 55); // returns true
 Explanation:
 The first two events can be booked.  The third event can be double booked.
 The fourth event (5, 15) can't be booked, because it would result in a triple booking.
 The fifth event (5, 10) can be booked, as it does not use time 10 which is already double booked.
 The sixth event (25, 55) can be booked, as the time in [25, 40) will be double booked with the third event;
 the time [40, 50) will be single booked, and the time [50, 55) will be double booked with the second event.
 
 Note:
 
 The number of calls to MyCalendar.book per test case will be at most 1000.
 In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace MyCalendarTwo
{

class MyCalendarTwo {

public:
    MyCalendarTwo() {
    }
    
    bool book(int start, int end) {
        // no overlap with any overlap
        for (auto& overlap : m_overlaps) {
            if (overlap.second <= start || end <= overlap.first) continue;
            return false;
        }
        // update m_overlaps
        for (auto& interval : m_intervals) {
            if (interval.second <= start || end <= interval.first) continue;
            m_overlaps.emplace_back(max(start, interval.first), min(end, interval.second));
        }
        m_intervals.emplace_back(start, end);
        return true;
    }
private:
    // sorted intervals
    std::vector<std::pair<int, int>> m_intervals;
    // sorted overlapping intervals
    std::vector<std::pair<int, int>> m_overlaps;
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */

void Test() {
    MyCalendarTwo obj;
    vector<pair<int, int>> intervals = { {10,20},{50,60},{10,40},{5,15},{5,10},{25,55}};
    vector<bool> results = {true,true,true,false,true,true};
    //vector<pair<int, int>> intervals = { {33,44},{85,95},{20,37},{91,100},{89,100},{77,87},{80,95},{42,61},{40,50},{85,99},{74,91},{70,82},{5,17},{77,89},{16,26},{21,31},{30,43},{96,100},{27,39},{44,55},{15,34},{85,99},{74,93},{84,94},{82,94},{46,65},{31,49},{58,73},{86,99},{73,84},{68,80},{5,18},{75,87},{88,100},{25,41},{66,79},{28,41},{60,70},{62,73},{16,33} };
    //vector<bool> results = { true,true,true,true,false,true,false,true,false,false,false,true,true,false,true,false,false,true,false,true,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false };
    
    assert(results.size() == intervals.size());
    for (auto i = 0; i < intervals.size(); i++) {
        if (obj.book(intervals[i].first, intervals[i].second) != results[i])
            throw;
    }
}
}
