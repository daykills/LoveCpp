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
		vector<int> dfs()
		{
			vector<int> result;
			unordered_set<int> visited;
			// start from each node, and do a dfs. skip visited nodes
			for (auto idNodePair : m_nodes)
			{
				if(visited.count(idNodePair.first) == 0)
					dfsUtil(idNodePair.first, visited, result);
			}
			return move(result);
		}
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
			return move(result);
		}
		vector<int> topologicalSort()
		{
			vector<int> result;			
			unordered_set<int> visited;
			// start from each node, and do a dfs. skip visited nodes
			for (auto idNodePair : m_nodes)
			{
				if (visited.count(idNodePair.first) == 0)
					topologicalUtil(idNodePair.first, visited, result);
			}
			std::reverse(result.begin(), result.end());
			return move(result);
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
		// utility function for dfs
		void dfsUtil(int nodeId, unordered_set<int>& visited, vector<int>& traverse)
		{
			if (m_nodes.count(nodeId) == 0)
				throw std::invalid_argument("The node id doesn't exist in the graph.");
			traverse.emplace_back(nodeId);
			visited.emplace(nodeId);
			auto& neighbourIds = m_nodes[nodeId];
			for (auto neighbourId : neighbourIds)
			{
				if (visited.count(neighbourId)) continue;				
				dfsUtil(neighbourId, visited, traverse);
			}
		}
		// utility function for dfs
		void topologicalUtil(int nodeId, unordered_set<int>& visited, vector<int>& traverse)
		{
			if (m_nodes.count(nodeId) == 0)
				throw std::invalid_argument("The node id doesn't exist in the graph.");
			
			visited.emplace(nodeId);
			auto& neighbourIds = m_nodes[nodeId];
			for (auto neighbourId : neighbourIds)
			{
				if (visited.count(neighbourId)) continue;
				topologicalUtil(neighbourId, visited, traverse);
			}
			traverse.emplace_back(nodeId);
		}
		// hash map for nodes, key is the node id, value is the adjacent ids
		unordered_map<int, unordered_set<int>> m_nodes;
	};

	static bool Test()
	{
		Graph g;
		g.addEdge(5, 2);
		g.addEdge(5, 0);
		g.addEdge(4, 0);
		g.addEdge(4, 1);
		g.addEdge(2, 3);
		g.addEdge(3, 1);

		auto result = g.topologicalSort();
		for (auto id : result)
		{
			cout << id << " ";
		}
		cout << endl;

		return false;
	}
}