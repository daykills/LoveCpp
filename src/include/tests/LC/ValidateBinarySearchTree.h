/*
 98. Validate Binary Search Tree
 Medium
 Given a binary tree, determine if it is a valid binary search tree (BST).
 
 Assume a BST is defined as follows:
 
 The left subtree of a node contains only nodes with keys less than the node's key.
 The right subtree of a node contains only nodes with keys greater than the node's key.
 Both the left and right subtrees must also be binary search trees.
 Example 1:
 
 Input:
   2
  / \
 1   3
 Output: true
 Example 2:
 
     5
    / \
   1   4
      / \
     3   6
 Output: false
 Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value
 is 5 but its right child's value is 4.

*/

#include <iostream>
#include <stack>
#include "Common.h"

namespace ValidateBinarySearchTree
{
//////////////////////////////////////////////////////
bool checkBST(TreeNode* root, long min, long max)
{
    if(root == nullptr) return true;
    if(root->val >= max || root->val <= min) return false;
    return checkBST(root->left, min, root->val) && checkBST(root->right, root->val, max);
}

bool isValidBST(TreeNode* root) {
    return checkBST(root, LONG_MIN, LONG_MAX);
}

////////////////////////////////////////////////////////////////////////////////////
bool inorderTraverse(TreeNode* root, long& lastNum) {
    if (!root) return true;
    auto isValid = inorderTraverse(root->left, lastNum);
    if (!isValid || lastNum >= root->val) {
        return false;
    }
    
    lastNum = root->val;
    return inorderTraverse(root->right, lastNum);
}

bool isValidBST(TreeNode* root) {
    long lastNum = LONG_MIN;
    return inorderTraverse(root, lastNum);
}

////////////////////////////////////////////////////////////////////////////////////

bool Test()
{
    auto tree = makeTree({ 2,1,3 });
    
    TreePrinter::Printer<TreeNode> treePrinter;
    treePrinter.printPretty(tree, 1, 1, cout);
    
    cout << "result: " << isValidBSTNew(tree) << endl;
    delTree(tree);
    return true;
}
}
