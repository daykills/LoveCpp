/*
236. Lowest Common Ancestor of a Binary Tree My Submissions QuestionEditorial Solution
Total Accepted: 39543 Total Submissions: 137845 Difficulty: Medium
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).?

_______3______
/              \
___5__          ___1__
/      \        /      \
6      _2       0       8
/  \
7   4
For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

*/

#include <iostream>
#include <stack>
#include "Common.h"

namespace LowestCommonAncestorOfABinaryTree
{
	// Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};	

	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
	{
		if (root == nullptr || root == p || root == q) return root;
		auto left = lowestCommonAncestor(root->left, p, q);
		auto right = lowestCommonAncestor(root->right, p, q);

		// when both are non-null, means p q are left and right children
		if (left && right) return root;
		return left ? left : right;
	}

	////////////////////////////////////////////////////////////////////////////////////
	bool Test()
	{
		//[1, 2, 2, 3, 3, null, null, 4, 4]
		const int n = 7;
		TreeNode* nodes[n];
		for (int i = 0; i < n; i++)
		{
			nodes[i] = new TreeNode(i);
		}
		nodes[0]->left = nodes[1];
		nodes[0]->right = nodes[2];
		nodes[1]->left = nodes[3];
		nodes[1]->right = nodes[4];
		nodes[3]->left = nodes[5];
		nodes[3]->right = nodes[6];

		TreePrinter::Printer<TreeNode> treePrinter;
		treePrinter.printPretty(nodes[0], 1, 1, cout);		

		cout << lowestCommonAncestor(nodes[0], nodes[1], nodes[6])->val << endl;

  		return true;
	}
}