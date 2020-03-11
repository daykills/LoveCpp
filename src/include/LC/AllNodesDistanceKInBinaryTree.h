#pragma once
/*
 863. All Nodes Distance K in Binary Tree

 We are given a binary tree (with root node root), a target node, and an integer value K.
 
 Return a list of the values of all nodes that have a distance K from the target node.  The answer can be returned in any order.
 
 Example 1:
 
 Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
 
 Output: [7,4,1]
 
 Explanation:
 The nodes that are a distance 2 from the target node (with value 5)
 have values 7, 4, and 1.

 
 Note that the inputs "root" and "target" are actually TreeNodes.
 The descriptions of the inputs above are just serializations of these objects.
 
 Note:
 
 The given tree is non-empty.
 Each node in the tree has unique values 0 <= node.val <= 500.
 The target node is a node in the tree.
 0 <= K <= 1000.
*/

#include "Common.h"

namespace AllNodesDistanceKInBinaryTree
{

class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if (!root || !target) return {};
        if (K == 0) return { target->val };
        // map all parent nodes
        mapParentNode(root);
        
        queue<TreeNode*> q;
        q.push(target);
        unordered_set<TreeNode*> visited;
        int dist = 0;
        while (!q.empty()) {
            auto cnt = q.size();
            // reaching K distance
            if (K == dist) {
                vector<int> ans;
                while (!q.empty()) {
                    auto cur = q.front(); q.pop();
                    ans.push_back(cur->val);
                }
                return ans;
            }
            for (auto i = 0; i < cnt; i++) {
                auto cur = q.front(); q.pop();
                visited.emplace(cur);
                vector<TreeNode*> nextNodes { cur->left, cur->right, m_parent[cur] };
                for (auto nextNode : nextNodes) {
                    if (nextNode && visited.count(nextNode) == 0)
                        q.push(nextNode);
                }
            }
            dist++;
        }
        
        return {};
    }
private:
    void mapParentNode(TreeNode* parent) {
        assert(parent);
        if (parent->left) {
            m_parent[parent->left] = parent;
            mapParentNode(parent->left);
        }
        if (parent->right) {
            m_parent[parent->right] = parent;
            mapParentNode(parent->right);
        }
    }
    unordered_map<TreeNode*, TreeNode*> m_parent;
};

///////////////////////////
TreeNode* getTarget(TreeNode* root, int target) {
    if (!root) return nullptr;
    if (root->val == target) return root;
    auto targetInLeft = getTarget(root->left, target);
    if (targetInLeft) return targetInLeft;
    auto targetInRight = getTarget(root->right, target);
    if (targetInRight) return targetInRight;
    return nullptr;
}
                    
void Test()
{
    TreeNode *root = makeTree({ 3,5,1,6,2,0,8,null,null,7,4 });
    auto target = getTarget(root, 5);
    int K  = 2;
    TreePrinter::Printer<TreeNode> treePrinter;
    treePrinter.printPretty(root, 1, 1, cout);
    Solution s;
    auto nodes = s.distanceK(root, target, K);
    for (auto node : nodes) {
        cout << node << endl;
    }
}
}
