#pragma once
/*
105. Construct Binary Tree from Preorder and Inorder Traversal My Submissions Question
Total Accepted: 58949 Total Submissions: 208794 Difficulty: Medium
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
*/

#include <iostream>
#include <queue>
#include "Common.h"

namespace ConvertSortedListToBinarySearchTreeConstructBinaryTreeFromPreorderAndInorderTraversal
{
	// Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	TreeNode* buildTree(vector<int>& preorder, int startPre, int endPre, vector<int>& inorder, int startIn, int endIn)
	{
		if (startPre > endPre) return nullptr;
		// the front of preorder vector is always the root
		auto root = new TreeNode(preorder[startPre]);
		if (startPre == endPre) return root;

		int countLeftTree = 0;
		for (int i = startIn; i + countLeftTree <= endIn && inorder[i + countLeftTree] != root->val; )
		{
			countLeftTree++;
		}
		
		root->left = buildTree(preorder, startPre + 1, startPre + countLeftTree, inorder, startIn, startIn + countLeftTree - 1);
		root->right = buildTree(preorder, startPre + countLeftTree + 1, endPre, inorder, startIn + countLeftTree + 1, endIn);
		return root;
	}

	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
	{
		int n = preorder.size();
		return buildTree(preorder, 0, n - 1, inorder, 0, n - 1);
	}
	////////////////////////////////////////////////////////////////////////////////////
	static void Test()
	{
		vector<int> preorder{ 1, 2, 3 };
		vector<int> inorder{ 1, 2, 3 };

		auto tree = buildTree(preorder, inorder);

		TreePrinter::Printer<TreeNode> treePrinter;
		treePrinter.printPretty(tree, 1, 1, cout);
	}
}

