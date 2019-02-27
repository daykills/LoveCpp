/*
111. Minimum Depth of Binary Tree My Submissions Question
Total Accepted: 99473 Total Submissions: 326863 Difficulty: Easy
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
*/

#include <iostream>
#include <stack>
#include "Common.h"

namespace MinimumDepthOfBinaryTree
{
	// Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	int findMinDepth(TreeNode* root)
	{
		if (root == nullptr) return INT_MAX;

		if (root->left == nullptr && root->right == nullptr) return 1;

		return min(findMinDepth(root->left), findMinDepth(root->right)) + 1;
	}
	int minDepth(TreeNode* root)
	{
		if (root == nullptr) return 0;
		return findMinDepth(root);
	}
	////////////////////////////////////////////////////////////////////////////////////
	void Test()
	{
		//[1, 2, 2, 3, 3, null, null, 4, 4]
		const int n = 2;
		TreeNode* nodes[n];
		for (int i = 0; i < n; i++)
		{
			nodes[i] = new TreeNode(i);
		}
		nodes[0]->left = nodes[1];

		TreePrinter::Printer<TreeNode> treePrinter;
		treePrinter.printPretty(nodes[0], 1, 1, cout);

		cout << minDepth(nodes[0]) << endl;		
	}
}