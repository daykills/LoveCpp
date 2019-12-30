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
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
	{
		if (root == nullptr || root == p || root == q) return root;
		auto left = lowestCommonAncestor(root->left, p, q);
		auto right = lowestCommonAncestor(root->right, p, q);

		// when both are non-null, means p q are under left and right children separately
		if (left && right) return root;
		return left ? left : right;
	}

	////////////////////////////////////////////////////////////////////////////////////
	bool Test()
	{
        auto tree = makeTree({ 3,5,1,6,2,0,8,null,null,7,4 });

        auto p = getNodeOfValue(tree, 5);
        auto q = getNodeOfValue(tree, 1);

		TreePrinter::Printer<TreeNode> treePrinter;
        treePrinter.printPretty(tree, 1, 1, cout);

		cout << lowestCommonAncestor(tree, p, q)->val << endl;

  		return true;
	}
}
