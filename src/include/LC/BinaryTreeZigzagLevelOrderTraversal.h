/*
 103. Binary Tree Zigzag Level Order Traversal
 Total Accepted: 52780 Total Submissions: 189880 Difficulty: Medium
 Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).
 
 For example:
 Given binary tree {3,9,20,#,#,15,7},
 3
 / \
 9  20
 /  \
 15   7
 return its zigzag level order traversal as:
 [
 [3],
 [20,9],
 [15,7]
 ]
 confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
 
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace BinaryTreeZigzagLevelOrderTraversal
{
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> rst;
    if (!root) return rst;
    std::queue<TreeNode*> q;
    q.push(root);
    bool reverse = false;
    while (!q.empty()) {
        auto n = q.size();
        rst.emplace_back(n, 0);
        auto& level = rst.back();
        for (auto i = 0; i < n; i++) {
            auto cur = q.front();
            q.pop();
            if (cur->left)
                q.push(cur->left);
            if (cur->right)
                q.push(cur->right);
            if (reverse)
                level[n - i - 1] = cur->val;
            else
                level[i] = cur->val;
        }
        reverse = !reverse;
    }
    return rst;
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
    
    for (auto level : zigzagLevelOrder(nodes[0]))
    {
        for (auto value : level)
        {
            cout << value << " ";
        }
        cout << endl;
    }
    return true;
}
}
