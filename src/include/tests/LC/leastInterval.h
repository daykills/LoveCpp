/*
 621. Task Scheduler

 Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks. Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

 However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.

 You need to return the least number of intervals the CPU will take to finish all the given tasks.

  

 Example:

 Input: tasks = ['A','A','A','B','B','B'], n = 2
 Output: 8
 Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
  

 Note:

 The number of tasks is in the range [1, 10000].
 The integer n is in the range [0, 100].
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace LeastInterval
{
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> taskMap;
        for (auto task : tasks)
            taskMap[task]++;
        auto comp = [&taskMap](char task1, char task2) {
            return taskMap[task1] < taskMap[task2];
        };
        // the top is always the task with most backlog
        priority_queue<char, std::vector<char>, std::function<bool(char, char)>> pq(comp);
        // tasks waiting for cooling down
        vector<pair<char, int>> waitList;
        for (auto& pair : taskMap) {
            waitList.emplace_back(pair.first, 0);
        }
        auto time = 0;
        for (;!waitList.empty() || !pq.empty(); time++) {
            // move ready tasks into priority queue
            auto oldWaitList = std::move(waitList);
            for (auto& taskAndTime : oldWaitList) {
                if (taskAndTime.second == 0) {
                    pq.push(taskAndTime.first);
                } else {
                    waitList.emplace_back(taskAndTime.first, taskAndTime.second - 1);
                }
            }
            if (pq.empty())
                continue;
            // execute next task with most backlog
            auto next = pq.top();
            pq.pop();
            taskMap[next]--;
            if (taskMap[next] > 0) {
                waitList.emplace_back(next, n);
            }
        }
        
        return time;
    }
};
static void Test()
{
    Solution solution;
    vector<char> tasks = { 'B','D','H','D','C','E','C','B','B','F','D','H','J','H','B','I','E','I','E','C','A','C','I','D','H','B','I','E','H','J','F','I','D','J','E','I','I','G','E','D','G','G','I','I','A','E','J','D','H','B','D','H','A','B','F','H','D','A','J','F','J','H','B','C','J','J','H','F','B','H','E','F','E','C','E','H','J','G','F','I','I','I','D','C','A','F','G','I','J','D','D','D','I','A','E','E','C','I','H','H','A','F','E','B','C','G','J','F','C','G','D','B','D','E','C','C','H','H','C','H','J','A','A','I','A','A','B','J','H','B','J','H','C','F','A','D','A','I','E','G','E','A','A','A','J','G','E','D','G','E','G','C','B','E','G','F','I','F','E','C','C','A','J','E','I','D','A','F','I','J','H','B','B','G','F','B','G','C','E','B','J','B','J','H','C','I','E','G','G','E','J','D','B','I','H','B','D','I','H','D','G','F','A','A','H','C','D','B','D','B','H','G','B','C','I','B','D','C','I','I','B','G','B','J','B','E','F','G','H','B','J','D','C','I','D','B','I','F','J','I','B','J','C','I','G','D','F','I','G','D'
 };
    std::cout << solution.leastInterval(tasks, 49) << std::endl;
}
}
