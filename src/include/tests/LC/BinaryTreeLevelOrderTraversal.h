/*
102. Binary Tree Level Order Traversal
Total Accepted: 86452 Total Submissions: 275348 Difficulty: Easy
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},
3
/ \
9  20
/  \
15   7
return its level order traversal as:
[
[3],
[9,20],
[15,7]
]
confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.

*/

#include <iostream>
#include <queue>
#include "Common.h"

namespace BinaryTreeLevelOrderTraversal
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

//////////////////////////////////////////////////////////////////////////////////
void levelOrderRecusion(TreeNode *root, unsigned int level, vector<vector<int> > &result)
{
    if (root == nullptr) return;
    // no value from this level yet
    if (result.size() <= level)
    {
        result.emplace_back(vector<int>());
    }
    result[level].emplace_back(root->val);
    levelOrderRecusion(root->left, level + 1, result);
    levelOrderRecusion(root->right, level + 1, result);
}

vector<vector<int>> levelOrderDFS(TreeNode* root)
{
    vector<vector<int>> result;
    
    levelOrderRecusion(root, 0, result);
    
    return result;
}

////////////////////////////////////////////////////////
// breadth first traversal
vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root)
        return {};
    vector<vector<int>> ans;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        auto nNodes = q.size();
        ans.emplace_back(nNodes);
        auto& level = ans.back();
        for (auto i = 0; i < nNodes; i++) {
            auto cur = q.front();
            q.pop();
            level[i] = cur->val;
            if (cur->left)
                q.push(cur->left);
            if (cur->right)
                q.push(cur->right);
        }
    }
    return ans;
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
    
    for (auto level : levelOrder(nodes[0]))
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
