/*
 743. Network Delay Time

 There are N network nodes, labelled 1 to N.

 Given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node, v is the target node, and w is the time it takes for a signal to travel from source to target.

 Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal? If it is impossible, return -1.

 Example 1:

 Input: times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
 Output: 2

 Note:

 N will be in the range [1, 100].
 K will be in the range [1, N].
 The length of times will be in the range [1, 6000].
 All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 0 <= w <= 100.
 
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace NetworkDelayTime
{
class Solution {
public:
    void dfs(const unordered_map<int, unordered_map<int, int>>& timeMap, vector<int>& delays, int cur) {
        assert(delays[cur - 1] != INT_MAX);
        auto it = timeMap.find(cur);
        if (it == timeMap.end())
            return;
        auto& nextNodes = it->second;
        for (const auto& nodeAndTime : nextNodes) {
            auto newDelay = delays[cur - 1] + nodeAndTime.second;
            if (delays[nodeAndTime.first - 1] > newDelay) {
                delays[nodeAndTime.first - 1] = newDelay;
                dfs(timeMap, delays, nodeAndTime.first);
            }
        }
    }
    
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        // u->v->w
        unordered_map<int, unordered_map<int, int>> timeMap;
        for (auto& time : times) {
            assert(time.size() == 3);
            timeMap[time[0]].emplace(time[1], time[2]);
        }
        vector<int> delays(N, INT_MAX);
        delays[K - 1] = 0;
        dfs(timeMap, delays, K);
        auto maxDelay = *max_element(delays.begin(), delays.end());
        return maxDelay == INT_MAX ? -1 : maxDelay;
    }
};

////////////////////////////////////////////////////////////////////////////////////
void Test()
{
    Solution s;
    vector<vector<int>> times = {
        {2,1,1},{2,3,1},{3,4,1}};
    int N = 4, K = 2;
    cout << s.networkDelayTime(times, N, K) << endl;
}
}
