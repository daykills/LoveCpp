#pragma once
/*
269: ALIEN DICTIONARY (HARD)
There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you.
You receive a list of words from the dictionary, where words are sorted lexicographically by the rules of this new language.
Derive the order of letters in this language.

For example,
Given the following words in dictionary,

[
"wrt",
"wrf",
"er",
"ett",
"rftt"
]
The correct order is: "wertf".

Note:

You may assume all letters are in lowercase.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return any one of them is fine.

*/

#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "Common.h"

namespace AlienDictionary
{
	class Graph
	{
	public:
		void addVetex(char id)
		{
			// if idSource or idDest is new, add them to m_nodes
			if (m_nodes.count(id) == 0)
				m_nodes.emplace(id, unordered_set<char>());
		}
		void addEdge(char idSource, char idDest)
		{
			// if idSource or idDest is new, add them to m_nodes
			addVetex(idSource);
			addVetex(idDest);
			// add idDest to the adjacent of idDest
			m_nodes[idSource].emplace(idDest);
		}
		void printGraph()
		{
			for (auto& idNodePair : m_nodes)
			{
				cout << "Id [" << idNodePair.first << "]: ";
				for (auto neighbourId : idNodePair.second)
				{
					cout << neighbourId << " ";
				}
				cout << endl;
			}
		}
		string topologicalSort()
		{
			unordered_set<char> visited;
			// add chars into result in reverse order
			vector<char> result;
			for (auto& idNodePair : m_nodes)
			{
				if (visited.count(idNodePair.first)) continue;
				// do topologicalSort from each node
				topologicalSortUtil(visited, result, idNodePair.first);
			}
			// return result in right order
			return string(result.rbegin(), result.rend());
		}
	private:
		// do a topologicalSort starting at startNodeId
		void topologicalSortUtil(unordered_set<char>& visited, vector<char>& result, char startNodeId)
		{
			// startNodeId should always have existed
			assert(m_nodes.count(startNodeId) == 1);
			// mark it as visited
			visited.emplace(startNodeId);
			const auto& adjacent = m_nodes[startNodeId];
			for (auto& neigbourId : adjacent)
			{
				if (visited.count(neigbourId)) continue;
				topologicalSortUtil(visited, result, neigbourId);
			}
			// till this point, all of startNodeId's adjacents (bigger value) are in result
			result.emplace_back(startNodeId);
		}
		// key is the char, and value is its adjacent chars
		unordered_map<char, unordered_set<char>> m_nodes;
	};

	string alienOrder(vector<string>& words)
	{
		int n = words.size();
		if (n == 0) return "";

		Graph g;
		// add all chars into the graph
		for_each(words[0].begin(), words[0].end(), [&g](char& ch) { g.addVetex(ch); });
		for (auto i = 1; i < n; i++)
		{
			for_each(words[i].begin(), words[i].end(), [&g](char& ch) { g.addVetex(ch); });
			int len = min(words[i - 1].length(), words[i].length());
			for (auto j = 0; j < len; j++)
			{
				// different char implies the order
				if (words[i - 1][j] != words[i][j])
				{
					g.addEdge(words[i - 1][j], words[i][j]);
					break;
				}
			}
		}

		g.printGraph();

		return g.topologicalSort();
	}

	////////////////////////////////////////////////////////////////////////////////////
	static void TestTemplate(vector<string>& words)
	{
		cout << "Words: ";
		for (auto& word : words)
		{
			cout << word << " ";
		}
		cout << endl;
		cout << "Order: " << alienOrder(words) << endl;
	}
	static void Test()
	{
		/*
		Input:  words[] = {"caa", "aaa", "aab"}
		Output: Order of characters is 'c', 'a', 'b'
		*/
		vector<string> words1 { "caa", "aaa", "aab" };
		vector<string> words2 { "wrt", "wrf", "er", "ett", "rftt" };
		TestTemplate(words2);
	}
}
