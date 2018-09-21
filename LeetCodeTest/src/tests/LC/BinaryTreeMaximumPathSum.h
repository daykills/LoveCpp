#pragma once
/*
124. Binary Tree Maximum Path Sum My Submissions Question
Total Accepted: 61155 Total Submissions: 265154 Difficulty: Hard
Given a binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path does not need to go through the root.

For example:
Given the below binary tree,

1
/ \
2   3
Return 6.

BinaryTreeMaximumPathSum

*/

#include <iostream>
#include <queue>
#include "Common.h"

namespace BinaryTreeMaximumPathSum
{
	// Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	void dfsSearch(TreeNode* root, unordered_map<TreeNode*, int>& maxPath)
	{
		// base condition
		if (root == nullptr) return;
		// check which child can make the root-to-leaf path bigger
		vector<TreeNode*> children{ root->left, root->right };
		int childSum = 0;
		for (auto child : children)
		{
			if (child == nullptr) continue;
			dfsSearch(child, maxPath);
			childSum = max(childSum, maxPath[child]);
		}
		// add root to the table. the initial sum is its val
		maxPath[root] = root->val + childSum;
	}
	int maxPathSum(TreeNode* root)
	{
		// maxPath saves the maxPath sum from root to leaf with the key (TreeNode*) as the root
		unordered_map<TreeNode*, int> maxPath;
		dfsSearch(root, maxPath);
		int result = INT_MIN;
		for (auto& pair : maxPath)
		{
			auto sum = pair.first->val;
			// check which child can make the path bigger
			vector<TreeNode*> children{ pair.first->left, pair.first->right };
			for (auto child : children)
			{
				if (child)
				{
					sum = max(maxPath[child] + sum, sum);
				}
			}
			result = max(result, sum);
		}
		return result;
	}

	int getN()
	{
		cout << "1" << endl;
		return 7;
	}

	////////////////////////////////////////////////////////////////////////////////////
	static void Test()
	{
		//[1, 2, 2, 3, 3, null, null, 4, 4]
		const int n = 7;
		TreeNode* nodes[n];
		
		for (int i = 0; i < getN(); i++)
		{
			srand(i);
			nodes[i] = new TreeNode(rand() % 23);
		}
		nodes[0]->left = nodes[1];
		nodes[0]->right = nodes[2];
		nodes[1]->left = nodes[3];
		nodes[1]->right = nodes[4];
		nodes[3]->left = nodes[5];
		nodes[3]->right = nodes[6];

		TreePrinter::Printer<TreeNode> treePrinter;
		treePrinter.printPretty(nodes[0], 1, 1, cout);

		cout << "result: " << maxPathSum(nodes[0]) << endl;
	}
}
