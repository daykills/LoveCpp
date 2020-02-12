/*
1轮skype的美国大哥：聊简历，coding题是给你一群nodes，每一个node里有3个invariants: unique的id，可能重名的label，其parent的id。
要求将一组乱序的nodes按照如下方式print出来：
Node A
	Node B
		Node C
	Node D
Node E
这里BD的parent为A，C的为B，AE的为一个id=0的默认root（不print），也就是子node按照depth要缩进相应的空格。
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <cassert>
#include "Common.h"

namespace FamilyTreePrint
{
	struct Node
	{
		int id;
		string label;
		int parent;
		bool operator == (const Node& other) const
		{
			return other.id == this->id;
		}
		Node(int _id, string _label, int _parent) : id(_id), label(_label), parent(_parent) {}
	};

	struct NodeHash
	{
		size_t operator () (const Node& node)
		{
			return hash<int>()(node.id);
		}
	};

	class Graph
	{
	public:
		void AddNode(const Node& node)
		{
			// parent must pre-exist.
			assert(m_connection.count(node.parent) > 0);
			if (m_connection.count(node.id) > 0) return;
		}
	private:
		unordered_map<int, Node> m_nodes;
		// key is the node id, value is all of its direct children
		unordered_map<int, set<Node>> m_connection;
	};

	static void Test()
	{
	}
}