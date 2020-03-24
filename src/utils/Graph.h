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
    // add a edge from idSource to idDest - directional
    void addEdge(int idSource, int idDest, int weight = 0)
    {
        m_nodes.emplace(idSource);
        m_nodes.emplace(idDest);
        // add edge
        m_edges[idSource].emplace(idDest, weight);
    }
    
    // regular bfs is not able to detect cyclic
    // try topological sort + indegree
    vector<int> bfs()
    {
        vector<int> result;
        unordered_set<int> visited;
        // start from each node, and do a dfs. skip visited nodes
        for (auto node : m_nodes)
        {
            if (visited.count(node) == 0)
                bfsUtil(node, visited, result);
        }
        return result;
    }
    
    // if there is cycle, return empty
    vector<int> dfs()
    {
        vector<int> result;
        unordered_set<int> visited;
        // start from each node, and do a dfs. skip visited nodes
        for (auto node : m_nodes)
        {
            // keep the stack history to detect cyclic
            unordered_set<int> stackHist;
            if (dfsUtil(node, visited, stackHist, result) == false)
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
        for (auto node : m_nodes)
        {
            // keep the stack history to detect cyclic
            unordered_set<int> stackHist;
            if (topologicalUtil(node, visited, stackHist, result) == false)
                return {};
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
    
    vector<int> topologicalSortBFS()
    {
        // number of prerequisites / dependancies
        unordered_map<int, int> indegrees;
        for (auto& idNodePair : m_edges) {
            for (auto idAndWeight : idNodePair.second) {
                indegrees[idAndWeight.first]++;
            }
        }
        queue<int> q;
        // for cycles, indegrees are never zero; thus, ignored for search
        for (auto cur : m_nodes) {
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
            for (auto nextIdAndWeight : m_edges[cur])
            {
                auto nextId = nextIdAndWeight.first;
                if (--indegrees[nextId] == 0) {
                    q.push(nextId);
                    indegrees.erase(nextId);
                }
            }
        }
        if (result.size() != m_edges.size())
            result.clear();
        return result;
    }
    
    // Get shortest paths from src to all other vertices with Dijkstra
    void shortestPath(int src) {
        using weight_and_node_type = pair<int, int>;
        // min heap to have shortest distance on top
        priority_queue<weight_and_node_type, vector<weight_and_node_type> , greater<weight_and_node_type>> minHeap;
        // map for distances from source, init as INT_MAX
        map<int, int> dist;
        for (auto node : m_nodes) dist.emplace(node, INT_MAX);
        minHeap.emplace(0, src);
        dist[src] = 0;
        while (!minHeap.empty()) {
            // The first vertex in pair is the minimum distance
            // vertex, extract it from priority queue.
            auto& curPair = minHeap.top();
            auto curDist = curPair.first;
            auto cur = curPair.second;
            minHeap.pop();
            if (m_edges.count(cur) == 0) continue;
            auto& nextNodes = m_edges[cur];
            for (auto& nodeAndWeight : nextNodes) {
                auto next = nodeAndWeight.first;
                auto weight = nodeAndWeight.second;
                if (dist[next] > curDist + weight) {
                    dist[next] = curDist + weight;
                    minHeap.emplace(dist[next], next);
                }
            }
        }
        for (auto& nodeAndDist : dist) {
            cout << nodeAndDist.first << ": " << nodeAndDist.second << endl;
        }
    }
    
    template<class T = int>
    void printGraph()
    {
        for (auto& edge : m_edges)
        {
            cout << "Id [" << (T)edge.first << "]: ";
            for (auto nodeAndDist : edge.second)
            {
                cout << (T)nodeAndDist.first << " ";
            }
            cout << endl;
        }
    }
    
private:
    // utility function for bfs
    void bfsUtil(int nodeId, unordered_set<int>& visited, vector<int>& traverse)
    {
        if (m_edges.count(nodeId) == 0)
            throw std::invalid_argument("The node id doesn't exist in the graph.");
        queue<int> q;
        // visited is updated whenever a node id is pushed into queue
        q.emplace(nodeId);
        visited.emplace(nodeId);
        while (!q.empty())
        {
            auto& neighbourIds = m_edges[q.front()];
            traverse.emplace_back(q.front());
            q.pop();
            // add nodes for next level
            for (auto neighbourIdAndWeight : neighbourIds)
            {
                auto neighbourId = neighbourIdAndWeight.first;
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
        assert(m_edges.count(nodeId));
        if (visited.count(nodeId))
            return true;
        traversed.emplace_back(nodeId);
        visited.emplace(nodeId);
        stackHist.emplace(nodeId);
        auto& neighbourIds = m_edges[nodeId];
        for (auto neighbourIdAndWeight : neighbourIds)
        {
            auto neighbourId = neighbourIdAndWeight.first;
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
        
        visited.emplace(nodeId);
        stackHist.emplace(nodeId);
        // it has no coming out edge
        if (m_edges.count(nodeId) == 0)
            return true;
        auto& neighbourIds = m_edges[nodeId];
        for (auto neighbourIdAndWeight : neighbourIds)
        {
            auto neighbourId = neighbourIdAndWeight.first;
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
    // m_edge also stores the weight of edge
    map<int, unordered_map<int, int>> m_edges;
    unordered_set<int> m_nodes;
};

static void Test()
{
    Graph g;
    /*
     g.addEdge(1, 2);
     g.addEdge(2, 3);
     g.addEdge(2, 4);
     g.addEdge(3, 4);
     g.addEdge(3, 5);
     g.addEdge(5, 4);
     //g.addEdge(5, 1);
     g.addEdge(6, 7);
     */
    
    //  making above shown graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    g.printGraph();
    g.shortestPath(0);
    
    auto result = g.topologicalSort();
    for (auto id : result)
    {
        cout << id << " ";
    }
    cout << endl;
}
}
