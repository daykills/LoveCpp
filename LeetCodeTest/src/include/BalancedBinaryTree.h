/*
110. Balanced Binary Tree
Total Accepted: 93450 Total Submissions: 281255 Difficulty: Easy
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
*/

#include <iostream>
#include "Common.h"

namespace BalancedBinaryTree
{
  // Definition for a binary tree node.
  struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

  //Definition for singly-linked list.
  struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
  };

  int depth(TreeNode* root)
  {
    if (root == nullptr) return 0;
    return max(depth(root->left), depth(root->right)) + 1;
  }

  bool isBalanced(TreeNode* root)
  {
    if (root == nullptr)
    {
      return true;
    }
    else if (root->left == nullptr)
    {
      return depth(root->right) < 2;
    }
    else if (root->right == nullptr)
    {
      return depth(root->left) < 2;
    }
    else if (abs(depth(root->left) - depth(root->right)) > 1)
    {
      return false;
    }
    return isBalanced(root->left) && isBalanced(root->right);
  }

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

    return isBalanced(nodes[0]);
  }
}