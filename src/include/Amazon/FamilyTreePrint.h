/*
1��skype��������磺�ļ�����coding���Ǹ���һȺnodes��ÿһ��node����3��invariants: unique��id������������label����parent��id��
Ҫ��һ�������nodes�������·�ʽprint������
Node A
	Node B
		Node C
	Node D
Node E
����BD��parentΪA��C��ΪB��AE��Ϊһ��id=0��Ĭ��root����print����Ҳ������node����depthҪ������Ӧ�Ŀո�
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