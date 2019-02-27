#pragma once
/*
95. Unique Binary Search Trees II My Submissions Question
Total Accepted: 52265 Total Submissions: 180760 Difficulty: Medium
Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

1         3     3      2      1
\       /     /      / \      \
3     2     1      1   3      2
/     /       \                 \
2     1         2                 3
confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
*/

#include <iostream>
#include <queue>
#include "Common.h"

namespace UniqueBinarySearchTrees2
{
	// Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	vector<TreeNode*> generateTrees(int start, int end)
	{
		if (start > end) return vector<TreeNode*>(1, nullptr);

		vector<TreeNode*> result;

		for (auto root = start; root <= end; root++)
		{
			auto leftTrees = generateTrees(start, root - 1);
			auto rightTrees = generateTrees(root + 1, end);
			for (auto left : leftTrees)
			{
				for (auto right : rightTrees)
				{
					auto rootNode = new TreeNode(root);
					rootNode->left = left;
					rootNode->right = right;
					result.emplace_back(rootNode);
				}
			}
		}
		return result;
	}

	vector<TreeNode*> generateTrees(int n)
	{
		if (n == 0) return vector<TreeNode*>();

		return generateTrees(1, n);
	}
	////////////////////////////////////////////////////////////////////////////////////
	static void Test()
	{
		auto result = generateTrees(4);

		for (auto tree : result)
		{
			TreePrinter::Printer<TreeNode> treePrinter;
			treePrinter.printPretty(tree, 1, 1, cout);
		}
	}
}