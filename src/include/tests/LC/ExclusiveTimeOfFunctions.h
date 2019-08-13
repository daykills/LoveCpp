/*
 636. Exclusive Time of Functions

 On a single threaded CPU, we execute some functions.  Each function has a unique id between 0 and N-1.
 
 We store logs in timestamp order that describe when a function is entered or exited.
 
 Each log is a string with this format: "{function_id}:{"start" | "end"}:{timestamp}".  For example, "0:start:3" means the function with id 0 started at the beginning of timestamp 3.  "1:end:2" means the function with id 1 ended at the end of timestamp 2.
 
 A function's exclusive time is the number of units of time spent in this function.  Note that this does not include any recursive calls to child functions.
 
 The CPU is single threaded which means that only one function is being executed at a given time unit.
 
 Return the exclusive time of each function, sorted by their function id.
 
 Example 1:
 Input:
 n = 2
 logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
 Output: [3, 4]
 Explanation:
 Function 0 starts at the beginning of time 0, then it executes 2 units of time and reaches the end of time 1.
 Now function 1 starts at the beginning of time 2, executes 4 units of time and ends at time 5.
 Function 0 is running again at the beginning of time 6, and also ends at the end of time 6, thus executing for 1 unit of time.
 So function 0 spends 2 + 1 = 3 units of total time executing, and function 1 spends 4 units of total time executing.
*/
#include <string>
#include <iostream>
#include "Common.h"

namespace ExclusiveTimeOfFunctions
{

vector<int> exclusiveTime(int n, vector<string>& logs) {
    const string kDelimiter = ":";
    // events indexed by time stamp, value is event id and start flat (true for start, false for end)
    vector<int> res(n, 0);
    // stack to store id and start time, no need for status as they are all "start"
    stack<std::pair<int, int>> s;
    for (auto& log : logs) {
        auto pre = 0;
        auto count = 0;
        int funId = -1;
        bool start = false;
        int time = 0;
        while (true) {
            auto n = log.find(kDelimiter, pre);
            auto end = (n == string::npos) ? log.size() : n;
            auto token = log.substr(pre, end - pre);
            if (count == 0) {
                funId = stoi(token);
            } else if (count == 1) {
                start = token == "start";
            } else {
                time = stoi(token);
            }
            pre = end + 1;
            count++;
            if (count == 3 || n == string::npos)
                break;
        }
        if (start) {
            s.emplace(funId, time);
        } else {
            assert(!s.empty() && funId == s.top().first);
            auto& startItem = s.top();
            int timeSpan = time - startItem.second + 1;
            res[funId] += timeSpan;
            s.pop();
            if (!s.empty()) {
                // remove timeSpan from next item
                res[s.top().first] -= timeSpan;
            }
        }
        assert(count == 3);
    }
    return res;
}

static void Test()
{
    vector<string> logs = { "0:start:0", "1:start:2", "1:end:5", "0:end:6"};
    int n = 2;
    exclusiveTime(n, logs);
}

}
