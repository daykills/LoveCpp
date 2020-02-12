/*
Given two binary trees, check if the first tree is subtree of the second one. A subtree of a tree T is a tree S consisting of a node in T and all of its descendants in T. The subtree corresponding to the root node is the entire tree; the subtree corresponding to any other node is called a proper subtree.
For example, in the following case, tree S is a subtree of tree T.
*/
#include <iostream>
#include <algorithm>
#include "Common.h"

namespace SubtreeTest
{
  // Definition for a binary tree node.
  struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
  bool isIdentical(TreeNode* t1, TreeNode* t2)
  {
    if (t1 == nullptr) return t2 == nullptr;
    if (t2 == nullptr) return t1 == nullptr;
    // compare node value
    if (t1->val != t2->val) return false;
    // compare children
    return isIdentical(t1->left, t2->left) && isIdentical(t1->right, t2->right);
  }
  bool isSubtree(TreeNode* tree, TreeNode* subtree)
  {
    if (subtree == nullptr) return true;
    // if tree is empty while subtree not, then return false
    if (tree == nullptr) return false;
    // if both trees are identical, return true; or start comparing children with subtree
    return isIdentical(tree, subtree) || isSubtree(tree->left, subtree) || isSubtree(tree->right, subtree);
  }

  void Test()
  {
    //[1, 2, 2, 3, 3, null, null, 4, 4]
    TreeNode* T = new TreeNode(26);
    T->right = new TreeNode(3);
    T->right->right = new TreeNode(3);
    T->left = new TreeNode(10);
    T->left->left = new TreeNode(4);
    T->left->left->right = new TreeNode(30);
    T->left->right = new TreeNode(6);

    // TREE 2
    /* Construct the following tree
    10
    /    \
    4      6
    \
    30
    */
    TreeNode* S = new TreeNode(10);
    S->right = new TreeNode(6);
    S->left = new TreeNode(4);
    S->left->right = new TreeNode(30);

    TreePrinter::Printer<TreeNode> treePrinter;
    treePrinter.printPretty(T, 1, 1, cout);
    treePrinter.printPretty(S, 1, 1, cout);
    
    cout << "Result: " << isSubtree(T, S) << endl;
  }
}
