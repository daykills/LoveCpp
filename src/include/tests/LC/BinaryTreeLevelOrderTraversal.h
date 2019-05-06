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
    
    vector<vector<int>> levelOrder(TreeNode* root)
    {
        vector<vector<int>> result;
        
        levelOrderRecusion(root, 0, result);
        
        return result;
    }
    
    vector<vector<int>> levelOrderOneLoop(TreeNode* root) {
        if (root == nullptr)
            return vector<vector<int>>();
        // use nullptr as the level separator
        vector<vector<int>> result;
        std::queue<TreeNode*> q;
        q.push(nullptr);
        q.push(root);
        bool separatorSet = false;
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            // See a separator
            if (cur == nullptr) {
                result.emplace_back();
                separatorSet = false;
                continue;
            }
            auto& level = result.back();
            level.push_back(cur->val);
            for (auto i = 0; i < 2; i++) {
                auto child = i == 0 ? cur->left : cur->right;
                if (child) {
                    if (separatorSet == false) {
                        q.push(nullptr);
                        separatorSet = true;
                    }
                    q.push(child);
                }
            }
        }
        return result;
    }
    
    ////////////////////////////////////////////////////////
    // breadth first traversal
    vector<vector<int>> levelOrderBF(TreeNode* root)
    {
        vector<vector<int>> result;
        
        if (root == nullptr) return result;
        
        // nullptr as the spliter
        TreeNode* spliter = nullptr;
        queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty())
        {
            // start of each level, inser a spliter in the back of the queue
            queue.push(spliter);
            vector<int> level;
            // emplace all the nodes of the current level
            while (queue.front() != spliter)
            {
                auto cur = queue.front();
                queue.pop();
                level.emplace_back(cur->val);
                // enqueue nodes of the next level
                if (cur->left !=  nullptr)
                    queue.emplace(cur->left);
                if (cur->right != nullptr)
                    queue.emplace(cur->right);
            }
            result.emplace_back(level);
            // pop up spliter
            queue.pop();
        }
        return result;
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
