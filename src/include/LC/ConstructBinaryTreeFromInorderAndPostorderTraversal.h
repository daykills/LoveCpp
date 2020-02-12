#pragma once
/*
106. Construct Binary Tree from Inorder and Postorder Traversal My Submissions Question
Total Accepted: 51643 Total Submissions: 180070 Difficulty: Medium
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
*/

#include <iostream>
#include <queue>
#include "Common.h"

namespace ConstructBinaryTreeFromInorderAndPostorderTraversal
{
	// Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	TreeNode* buildTree(vector<int>& inorder, int inStart, int inEnd, vector<int>& postorder, int postStart, int postEnd)
	{
		// no nodes at all
		if (inStart > inEnd) return nullptr;
		// root is always the last one of postorder
		TreeNode* root = new TreeNode(postorder[postEnd]);
		// if only one node left
		if (inStart == inEnd) return root;
		// count how many nodes for the right tree
		int countRightNodes = 0;
		for (int i = inEnd; i >= inStart && inorder[i] != root->val; i--)
		{
			countRightNodes++;
		}
		// build right tree with inorder[inEnd - countRightNodes + 1, inEnd] and postOrder[postEnd - countRightNodes, postEnd - 1]
		root->right = buildTree(inorder, inEnd - countRightNodes + 1, inEnd, postorder, postEnd - countRightNodes, postEnd - 1);
		// build left tree
		int countLeftNodes = inEnd - inStart - countRightNodes;
		root->left = buildTree(inorder, inStart, inEnd - countRightNodes - 1, postorder, postStart, postEnd - countRightNodes - 1);

		return root;
	}

	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
	{
		int n = inorder.size();
		return buildTree(inorder, 0, n - 1, postorder, 0, n - 1);
	}
	////////////////////////////////////////////////////////////////////////////////////
	static void Test()
	{
		vector<int> inorder{ 4, 2, 5, 1, 3, 7 };
		vector<int> postorder{ 4, 5, 2, 7, 3, 1 };
		
		auto tree = buildTree(inorder, postorder);

		TreePrinter::Printer<TreeNode> treePrinter;
		treePrinter.printPretty(tree, 1, 1, cout);
	}
}
