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
    // Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    
    //////////////////////////////////////////////////////
    // check if a tree is valid; also return max and min
    bool isValidTree(const TreeNode& root, int& max, int& min) {
        int leftMax = root.val;
        int leftMin = root.val;
        bool leftTreeValid = root.left ? isValidTree(*root.left, leftMax, leftMin) : true;
        if (!leftTreeValid || (root.left && leftMax >= root.val))
            return false;
        int rightMin = root.val;
        int rightMax = root.val;
        bool rightTreeValid = root.right ? isValidTree(*root.right, rightMax, rightMin) : true;
        if (!rightTreeValid || (root.right && rightMin <= root.val))
            return false;
        max = rightMax;
        min = leftMin;
        return true;
    }
    
    bool isValidBST(TreeNode* root) {
        int min, max;
        return root ? isValidTree(*root, max, min) : true;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////
    bool Test()
    {
        //[1, 2, 2, 3, 3, null, null, 4, 4]
        int NULLINT = 32132;
        vector<int> values{ 2, 1, 3 };
        const int n = values.size();
        vector<TreeNode*> nodes(n);
        for (int i = 0; i < n; i++)
        {
            nodes[i] = (values[i] == NULLINT) ? nullptr : new TreeNode(values[i]);
        }
        nodes[0]->left = nodes[1];
        nodes[0]->right = nodes[2];
        
        TreePrinter::Printer<TreeNode> treePrinter;
        treePrinter.printPretty(nodes[0], 1, 1, cout);
        
        
        cout << "result: " << isValidBST(nodes[0]) << endl;
        return true;
    }
}
