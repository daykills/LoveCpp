/*
226. Invert Binary Tree My Submissions QuestionEditorial Solution
Total Accepted: 83509 Total Submissions: 185309 Difficulty: Easy
Invert a binary tree.

4
/   \
2     7
/ \   / \
1   3 6   9
to
4
/   \
7     2
/ \   / \
9   6 3   1
*/

#include <iostream>
#include <stack>
#include "Common.h"

namespace InvertBinaryTree
{
	// Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	TreeNode* invertTree(TreeNode* root)
	{
		if (root == nullptr) return nullptr;

		queue<TreeNode*> q;
		q.push(root);

		while (!q.empty())
		{
			auto cur = q.front();
			q.pop();
			if (cur->left) q.push(cur->left);
			if (cur->right) q.push(cur->right);
			std::swap(cur->left, cur->right);			
		}
		return root;
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

		invertTree(nodes[0]);
		cout << endl;
		treePrinter.printPretty(nodes[0], 1, 1, cout);		

		return true;
	}
}