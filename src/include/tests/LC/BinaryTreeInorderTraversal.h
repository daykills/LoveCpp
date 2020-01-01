/*
 94. Binary Tree Inorder Traversal
 Medium
 
 2274
 
 96
 
 Add to List
 
 Share
 Given a binary tree, return the inorder traversal of its nodes' values.
 
 Example:
 
 Input: [1,null,2,3]
 1
 \
 2
 /
 3
 
 Output: [1,3,2]
 Follow up: Recursive solution is trivial, could you do it iteratively?
*/

#include <iostream>
#include <stack>
#include "Common.h"

namespace BinaryTreeInorderTraversal
{

//////////////////////////////////////////////////////

void helper(TreeNode* root, vector<int>& result) {
    if (root == nullptr)
        return;
    helper(root->left, result);
    result.emplace_back(root->val);
    helper(root->right, result);
}
vector<int> inorderTraversalRecursive(TreeNode* root) {
    vector<int> result;
    helper(root, result);
    return result;
}

//////////////////////////////////////////////////////////////////////////////////
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> s;
    auto cur = root;
    while (cur || !s.empty()) {
        // put all left nodes into s
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }
        // output the top of stack
        cur = s.top();
        s.pop();
        result.push_back(cur->val);
        cur = cur->right;
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////////
vector<int> inorderTraversal(TreeNode* root) {
    if (!root) return {};
    stack<TreeNode*> s;
    s.push(root);
    auto moveToLeftMost = [&s]() {
        assert(!s.empty());
        auto cur = s.top()->left;
        // always move to the left most node
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }
    };
    moveToLeftMost();
    vector<int> ans;
    while (!s.empty()) {
        auto cur = s.top();
        s.pop();
        if (cur->right) {
            s.push(cur->right);
            moveToLeftMost();
        }
        ans.push_back(cur->val);
    }
    return ans;
}
//////////////////////////////////////////////////////////////////////////////////
bool Test()
{
    TreeNode *root = makeTree({ 1,null,2,3 });
    
    TreePrinter::Printer<TreeNode> treePrinter;
    treePrinter.printPretty(root, 1, 1, cout);
 
    vector<int> data = inorderTraversalRecursive(root);
    for (auto num : data) {
        cout << num << endl;
    }
    return true;
}
}
