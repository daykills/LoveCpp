#pragma once
/*

*/

#include <iostream>
#include <climits>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

namespace GoodUser
{
	class Graph
	{
	public:
		vector<int> topSort()
		{
			unordered_set<int> visited;
			unordered_set<int> result;
			for (auto& pair : m_edges)
			{
				vector<int> tempResult;
				if (visited.count(pair.first)) continue;
				dfsTopSort(pair.first, visited, tempResult);
				for (auto i = 0; i < (int)(tempResult.size() - 1); i++)
					result.erase(tempResult[i]);
				result.emplace(tempResult.back());
			}
			return vector<int>(result.begin(), result.end());
		}
		void addNode(int id)
		{
			if (m_edges.count(id)) return;
			m_edges.emplace(id, unordered_set<int>());
		}
		void addEdge(int source, int dest)
		{
			addNode(source);
			addNode(dest);
			m_edges[source].emplace(dest);
		}
		void print()
		{
			for (auto& pair : m_edges)
			{
				cout << "source: " << pair.first << ", dest: ";
				for (auto dest : pair.second)
				{
					cout << " " << dest;
				}
				cout << endl;
			}
		}
	private:
		void dfsTopSort(int cur, unordered_set<int>& visited, vector<int>& result)
		{
			visited.emplace(cur);
			auto& edges = m_edges[cur];
			for (auto edge : edges)
			{
				if (visited.count(edge)) continue;
				dfsTopSort(edge, visited, result);
			}
			result.emplace_back(cur);
		}
		unordered_map<int, unordered_set<int>> m_edges;
	};


	static void Test()
	{
		Graph g;
		//g.addEdge(4, 1);
		//g.addEdge(3, 1);
		//g.addEdge(1, 2);
		g.addEdge(2, 1);

		g.print();

		auto result = g.topSort();
		cout << "result:";
		for (auto node : result)
		{
			cout << " " << node;
		}
		cout << endl;
	}
}