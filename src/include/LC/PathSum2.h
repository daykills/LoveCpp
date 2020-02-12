#pragma once
/*
113. Path Sum II My Submissions Question
Total Accepted: 75497 Total Submissions: 269894 Difficulty: Medium
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,
5
/ \
4   8
/   / \
11  13  4
/  \    / \
7    2  5   1
return
[
[5,4,11,2],
[5,8,4,5]
]
*/

#include <iostream>
#include <queue>
#include "Common.h"

namespace PathSum2
{
	// Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	void dfsSearch(TreeNode* root, int sum, vector<int>& path, vector<vector<int>>& result)
	{
		// base condition: if root is null, return
		if (root == nullptr)
		{
			return;
		}

		path.emplace_back(root->val);
		sum -= root->val;

		// base condition: if leaf is reached, return
		if (root->left == nullptr && root->right == nullptr && sum == 0)
		{
			result.emplace_back(path);
			path.pop_back();
			return;
		}

		dfsSearch(root->left, sum, path, result);
		dfsSearch(root->right, sum, path, result);

		path.pop_back();
	}

	vector<vector<int>> pathSum(TreeNode* root, int sum)
	{
		vector<int> path;
		vector<vector<int>> result;
		dfsSearch(root, sum, path, result);
		return result;
	}
	////////////////////////////////////////////////////////////////////////////////////
	static void Test()
	{
		//auto tree = buildTree(inorder, postorder);

		//TreePrinter::Printer<TreeNode> treePrinter;
		//treePrinter.printPretty(tree, 1, 1, cout);
	}
}
