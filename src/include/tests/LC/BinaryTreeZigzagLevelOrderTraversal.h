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
    ////////////////////////////////////////////////////////////////////////////////////
    vector<vector<int>> zigzagLevelOrderOld(TreeNode* root)
    {
        vector<vector<int>> result;
        if (root == nullptr) return result;
        TreeNode dummy(-1);
        TreeNode* spliter = &dummy;
        queue<TreeNode*> queue;
        queue.emplace(root);
        bool isReverse = false;
        while (!queue.empty())
        {
            vector<int> level;
            // place spliter in the end
            queue.emplace(spliter);
            // start dequeue from the front
            while (queue.front() != spliter)
            {
                auto front = queue.front();
                level.emplace_back(front->val);
                if (front->left) queue.emplace(front->left);
                if (front->right) queue.emplace(front->right);
                queue.pop();
            }
            if (isReverse)
            {
                reverse(level.begin(), level.end());
            }
            isReverse = !isReverse;
            result.emplace_back(level);
            queue.pop();
        }
        return result;
    }
    
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> rst;
        if (root == nullptr)
            return rst;
        TreeNode* kSpliter = nullptr;
        std::queue<TreeNode*> q;
        q.push(root);
        bool reverse = false;
        std::vector<int> level;
        while (!q.empty()) {
            q.push(kSpliter);
            // process current level
            while (q.front() != kSpliter) {
                TreeNode* front = q.front();
                q.pop();
                if (front == kSpliter)
                    break;
                level.emplace_back(front->val);
                if (front->left)
                    q.push(front->left);
                if (front->right)
                    q.push(front->right);
            }
            // pop out the front spliter
            q.pop();
            if (reverse) {
                std::reverse(level.begin(), level.end());
            }
            reverse = !reverse;
            rst.emplace_back(std::move(level));
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
