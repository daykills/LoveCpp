/*
 785. Is Graph Bipartite?

 Given an undirected graph, return true if and only if it is bipartite.
 
 Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B such that every edge in the graph has one node in A and another node in B.
 
 The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.  Each node is an integer between 0 and graph.length - 1.  There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.
 
 Example 1:
 Input: [[1,3], [0,2], [1,3], [0,2]]
 Output: true
 Explanation:
 The graph looks like this:
 0----1
 |    |
 |    |
 3----2
 We can divide the vertices into two groups: {0, 2} and {1, 3}.
 Example 2:
 Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
 Output: false
 Explanation:
 The graph looks like this:
 0----1
 | \  |
 |  \ |
 3----2
 We cannot find a way to divide the set of nodes into two independent subsets.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace IsBipartite
{
class Solution {
public:
    void dfs(const vector<vector<int>>& graph, int node, unordered_map<int, bool>& group, bool& fail) {
        // node must be already grouped
        assert(group.count(node));
        bool nextGroup = !group[node];
        auto& nextNodes = graph[node];
        for (auto next : nextNodes) {
            if (group.count(next)) {
                if (group[next] != nextGroup) {
                    fail = true;
                    return;
                }
                continue;
            }
            group[next] = nextGroup;
            dfs(graph, next, group, fail);
        }
    }
    bool isBipartite(vector<vector<int>>& graph) {
        // group true for A; false for B
        unordered_map<int, bool> group;
        for (auto i = 0; i < graph.size(); i++) {
            // if node is already visited
            if (group.count(i))
                continue;
            bool fail = false;
            // randomly assign a node to group A
            // dfs will traverse all its connected nodes
            group.emplace(i, true);
            dfs(graph, i, group, fail);
            if (fail)
                return false;
        }
        return true;
    }
};

static void Test()
{
    Solution solution;
    vector<vector<int>> graph = {{4},{},{4},{4},{0,2,3}};
    std::cout << solution.isBipartite(graph) << std::endl;
}
}
