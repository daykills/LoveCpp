/*
 210. Course Schedule II

 There are a total of n courses you have to take, labeled from 0 to n-1.
 
 Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
 
 Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
 
 There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.
 
 Example 1:
 
 Input: 2, [[1,0]]
 Output: [0,1]
 Explanation: There are a total of 2 courses to take. To take course 1 you should have finished
 course 0. So the correct course order is [0,1] .
 Example 2:
 
 Input: 4, [[1,0],[2,0],[3,1],[3,2]]
 Output: [0,1,2,3] or [0,2,1,3]
 Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both
 courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
 So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .
 Note:
 
 The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
 You may assume that there are no duplicate edges in the input prerequisites.
 */

#include "Common.h"

namespace CourseSchedule2
{
vector<int> findOrderBFS(int numCourses, vector<vector<int>>& prerequisites) {
    // map from course to all courses depend on it
    unordered_map<int, unordered_set<int>> dependantMap;
    // indegree is the number of prerequisites this course depend on
    unordered_map<int, int> indegrees;
    for (auto& prerequisite : prerequisites) {
        dependantMap[prerequisite[1]].emplace(prerequisite[0]);
        indegrees[prerequisite[0]]++;
    }
    queue<int> q;
    // start with zero degree courses (no prerequisite)
    for (auto i = 0; i < numCourses; i++) {
        if (indegrees.count(i) == 0)
            q.push(i);
    }
    vector<int> ans;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        ans.push_back(cur);
        auto it = dependantMap.find(cur);
        if (it == dependantMap.end())
            continue;
        auto& dependants = it->second;
        for (auto dependant : dependants) {
            assert(indegrees.count(dependant) > 0);
            // no more pre
            if (--indegrees[dependant] == 0) {
                q.push(dependant);
                indegrees.erase(dependant);
            }
        }
    }
    if (ans.size() < numCourses) ans.clear();
    return ans;
}

bool dfs(const unordered_map<int, unordered_set<int>>& dependantMap, int curId, unordered_set<int>& visited, unordered_set<int>& stackHist, vector<int>& ans) {
    if (visited.count(curId))
        return true;
    visited.emplace(curId);
    stackHist.emplace(curId);
    
    auto it = dependantMap.find(curId);
    if (it != dependantMap.end()) {
        auto& dependants = it->second;
        for (auto next : dependants) {
            // cycle detect
            if (stackHist.count(next))
                return false;
            if (dfs(dependantMap, next, visited, stackHist, ans) == false)
                return false;
        }
    }
    ans.push_back(curId);
    stackHist.erase(curId);
    return true;
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    // map from course to all courses depend on it
    unordered_map<int, unordered_set<int>> dependantMap;
    for (auto& prerequisite : prerequisites) {
        dependantMap[prerequisite[1]].emplace(prerequisite[0]);
    }
    vector<int> ans;
    unordered_set<int> visited;
    for (auto i = 0; i < numCourses; i++) {
        unordered_set<int> stackHist;
        if (dfs(dependantMap, i, visited, stackHist, ans) == false)
            return {};
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

static void Test()
{
    vector<vector<int>> prerequisites = {
        {1,0},{2,0},{3,1},{3,2}
    }; // Output: [0,1,2,3] or [0,2,1,3]
    auto ans = findOrder(4, prerequisites);
    for (auto node : ans) {
        cout << node << " ";
    }
    cout << endl;
}
}
