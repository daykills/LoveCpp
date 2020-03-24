#pragma once

/*
 Depth First Traversal for a Graph
 Depth First Traversal (or Search) for a graph is similar to Depth First Traversal of a tree.
 The only catch here is, unlike trees, graphs may contain cycles, so we may come to the same node again.
 To avoid processing a node more than once, we use a boolean visited array.
 For example, in the following graph, we start traversal from vertex 2.
 When we come to vertex 0, we look for all adjacent vertices of it. 2 is also an adjacent vertex of 0.
 If we don’t mark visited vertices, then 2 will be processed again and it will become a non-terminating process.
 A Depth First Traversal of the following graph is 2, 0, 1, 3.
 */

#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include "Common.h"

using namespace std;
namespace Graph
{
// directional graph
class Graph
{
public:
    void addVetex(int id)
    {
        // if idSource or idDest is new, add them to m_nodes
        if (m_nodes.count(id) == 0)
            m_nodes.emplace(id, unordered_set<int>());
    }
    // add a edge from idSource to idDest - directional
    void addEdge(int idSource, int idDest)
    {
        // if idSource or idDest is new, add them to m_nodes
        addVetex(idSource);
        addVetex(idDest);
        // add edge
        m_nodes[idSource].emplace(idDest);
    }
    
    // regular bfs is not able to detect cyclic
    // try topological sort + indegree
    vector<int> bfs()
    {
        vector<int> result;
        unordered_set<int> visited;
        // start from each node, and do a dfs. skip visited nodes
        for (auto idNodePair : m_nodes)
        {
            if (visited.count(idNodePair.first) == 0)
                bfsUtil(idNodePair.first, visited, result);
        }
        return result;
    }
    
    // if there is cycle, return empty
    vector<int> dfs()
    {
        vector<int> result;
        unordered_set<int> visited;
        // start from each node, and do a dfs. skip visited nodes
        for (auto idNodePair : m_nodes)
        {
            // keep the stack history to detect cyclic
            unordered_set<int> stackHist;
            if (dfsUtil(idNodePair.first, visited, stackHist, result) == false)
                return {};
        }
        return result;
    }
    
    // if there is cycle, return empty
    vector<int> topologicalSort()
    {
        vector<int> result;
        unordered_set<int> visited;
        // start from each node, and do a dfs. skip visited nodes
        for (auto idNodePair : m_nodes)
        {
            // keep the stack history to detect cyclic
            unordered_set<int> stackHist;
            if (topologicalUtil(idNodePair.first, visited, stackHist, result) == false)
                return {};
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
    
    vector<int> topologicalSortBFS()
    {
        // number of prerequisites / dependancies
        unordered_map<int, int> indegrees;
        for (auto& idNodePair : m_nodes) {
            for (auto to : idNodePair.second)
                indegrees[to]++;
        }
        queue<int> q;
        // for cycles, indegrees are never zero; thus, ignored for search
        for (auto& idNodePair : m_nodes) {
            auto cur = idNodePair.first;
            // nodes without dependancies
            if (indegrees.count(cur) == 0)
                q.push(cur);
        }
        vector<int> result;
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            result.push_back(cur);
            // reduce indegree for all neighbor nodes
            for (auto nextId : m_nodes[cur])
            {
                if (--indegrees[nextId] == 0) {
                    q.push(nextId);
                    indegrees.erase(nextId);
                }
            }
        }
        if (result.size() != m_nodes.size())
            result.clear();
        return result;
    }
    
    template<class T = int>
    void printGraph()
    {
        for (auto& idNodePair : m_nodes)
        {
            cout << "Id [" << (T)idNodePair.first << "]: ";
            for (auto neighbourId : idNodePair.second)
            {
                cout << (T)neighbourId << " ";
            }
            cout << endl;
        }
    }
    
private:
    // utility function for bfs
    void bfsUtil(int nodeId, unordered_set<int>& visited, vector<int>& traverse)
    {
        if (m_nodes.count(nodeId) == 0)
            throw std::invalid_argument("The node id doesn't exist in the graph.");
        queue<int> q;
        // visited is updated whenever a node id is pushed into queue
        q.emplace(nodeId);
        visited.emplace(nodeId);
        while (!q.empty())
        {
            auto& neighbourIds = m_nodes[q.front()];
            traverse.emplace_back(q.front());
            q.pop();
            // add nodes for next level
            for (auto neighbourId : neighbourIds)
            {
                if (visited.count(neighbourId) == 0)
                {
                    q.emplace(neighbourId);
                    visited.emplace(neighbourId);
                }
            }
        }
    }
    // utility function for dfs.
    // return false if cyclic detected
    bool dfsUtil(int nodeId, unordered_set<int>& visited, unordered_set<int> stackHist, vector<int>& traversed)
    {
        assert(m_nodes.count(nodeId));
        if (visited.count(nodeId))
            return true;
        traversed.emplace_back(nodeId);
        visited.emplace(nodeId);
        stackHist.emplace(nodeId);
        auto& neighbourIds = m_nodes[nodeId];
        for (auto neighbourId : neighbourIds)
        {
            // any node in the stack history, then cyclic is detected
            if (stackHist.count(neighbourId))
                return false;
            if (visited.count(neighbourId))
                continue;
            if (dfsUtil(neighbourId, visited, stackHist, traversed) == false)
                return false;
        }
        stackHist.erase(nodeId);
        return true;
    }
    // utility function for dfs
    bool topologicalUtil(int nodeId, unordered_set<int>& visited, unordered_set<int> stackHist, vector<int>& traverse)
    {
        if (visited.count(nodeId))
            return true;
        
        assert(m_nodes.count(nodeId));
        
        visited.emplace(nodeId);
        stackHist.emplace(nodeId);
        auto& neighbourIds = m_nodes[nodeId];
        for (auto neighbourId : neighbourIds)
        {
            // cycle detected
            if (stackHist.count(neighbourId))
                return false;
            if (visited.count(neighbourId)) continue;
            if (topologicalUtil(neighbourId, visited, stackHist, traverse) == false)
                return false;
        }
        traverse.emplace_back(nodeId);
        stackHist.erase(nodeId);
        return true;
    }
    // hash map for nodes, key is the node id, value is the adjacent ids
    // HACK: switch to map to make sure smaller nodes got traversed first
    map<int, unordered_set<int>> m_nodes;
};

static bool Test()
{
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(5, 4);
    //g.addEdge(5, 1);
    g.addEdge(6, 7);
    
    auto result = g.topologicalSortBFS();
    for (auto id : result)
    {
        cout << id << " ";
    }
    cout << endl;
    
    return false;
}
}
