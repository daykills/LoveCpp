#pragma once
/*
117. Populating Next Right Pointers in Each Node II My Submissions Question
Total Accepted: 58247 Total Submissions: 178053 Difficulty: Hard
Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,
1
/  \
2    3
/ \    \
4   5    7
After calling your function, the tree should look like:
1 -> NULL
/  \
2 -> 3 -> NULL
/ \    \
4-> 5 -> 7 -> NULL

*/

#include <iostream>
#include <queue>
#include "Common.h"

namespace PopulatingNextRightPointersInEachNode2
{
	// Definition for a binary tree node.
	struct TreeLinkNode {
		int val;
		TreeLinkNode *left, *right, *next;
		TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
	};

	void connect(TreeLinkNode *root)
	{
		while (root)
		{
			auto head = root;
			// set root as null, and set it to be the first child found later
			root = nullptr;
			TreeLinkNode* lastChildNode = nullptr;
			while (head)
			{
				vector<TreeLinkNode*> children{ head->left, head->right };
				for (auto child : children)
				{
					if (child != nullptr)
					{
						// if the last ChildNode is not set yet
						if (lastChildNode == nullptr)
						{
							lastChildNode = child;
							// this child will become the root of next iteration
							root = child;
							continue;
						}
						// link the lastChildNode with current one
						lastChildNode->next = child;
						lastChildNode = child;
					}
				}
				head = head->next;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
	static void Test()
	{
		//[1, 2, 2, 3, 3, null, null, 4, 4]
		const int n = 7;
		TreeLinkNode* nodes[n];

		for (int i = 0; i < n; i++)
		{
			srand(i);
			nodes[i] = new TreeLinkNode(rand() % 23);
		}
		nodes[0]->left = nodes[1];
		nodes[0]->right = nodes[2];
		nodes[1]->left = nodes[3];
		nodes[1]->right = nodes[4];
		nodes[3]->left = nodes[5];
		nodes[3]->right = nodes[6];

		TreePrinter::Printer<TreeLinkNode> treePrinter;
		treePrinter.printPretty(nodes[0], 1, 1, cout);

		connect(nodes[0]);
	}
}

