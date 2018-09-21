#pragma once
/*
51. N-Queens My Submissions Question
Total Accepted: 50552 Total Submissions: 193110 Difficulty: Hard
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.



Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
[".Q..",  // Solution 1
"...Q",
"Q...",
"..Q."],

["..Q.",  // Solution 2
"Q...",
"...Q",
".Q.."]
]
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace CloneGraph
{
	struct UndirectedGraphNode {
		int label;
		vector<UndirectedGraphNode *> neighbors;
		UndirectedGraphNode(int x) : label(x) {};
	};
	// save visited nodes and the pointer of their copy. key is the original pointer, value is the new one
	unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> m_visited;

	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
	{
		if (node == nullptr) return nullptr;

		// node is aways non-visited
		auto clone = new UndirectedGraphNode(node->label);
		// update visited
		m_visited.emplace(node, clone);
		for (auto neighbor : node->neighbors)
		{
			auto it = m_visited.find(neighbor);
			// if neighbor is already cloned, get the clone through visited; otherwise, clone it
			auto cloneNeighbor = (it == m_visited.end()) ? cloneGraph(neighbor) : it->second;
			clone->neighbors.emplace_back(cloneNeighbor);
		}
		return clone;
	}

	void Test()
	{
		cloneGraph(nullptr);
	}
}