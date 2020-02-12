/*
129. Sum Root to Leaf Numbers My Submissions Question
Total Accepted: 71524 Total Submissions: 221813 Difficulty: Medium
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

1
/ \
2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.

*/

#include <iostream>
#include <queue>
#include "Common.h"

namespace SumRootToLeafNumbers
{
    // Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    
    void dfs(TreeNode* root, int preNum, int& total) {
        if (!root)
            return;
        auto newNum = preNum * 10 + root->val;
        // leaf
        if (!root->left && !root->right) {
            total += newNum;
            return;
        }
        dfs(root->left, newNum, total);
        dfs(root->right, newNum, total);
    }
    int sumNumbers(TreeNode* root) {
        int total = 0;
        dfs(root, 0, total);
        return total;
    }
    ////////////////////////////////////////////////////////////////////////////////////
    static void Test()
    {
        //[1, 2, 2, 3, 3, null, null, 4, 4]
        const int n = 7;
        TreeNode* nodes[n];
        for (int i = 0; i < n; i++)
        {
            nodes[i] = new TreeNode(i + 1);
        }
        nodes[0]->left = nodes[1];
        nodes[0]->right = nodes[2];
        nodes[1]->left = nodes[3];
        nodes[1]->right = nodes[4];
        nodes[3]->left = nodes[5];
        nodes[3]->right = nodes[6];
        
        TreePrinter::Printer<TreeNode> treePrinter;
        treePrinter.printPretty(nodes[0], 1, 1, cout);
        
        cout << "result: " << sumNumbers(nodes[0]) << endl;
    }
}
