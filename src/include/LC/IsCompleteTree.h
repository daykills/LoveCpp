/*
 958. Check Completeness of a Binary Tree
 
 Given a binary tree, determine if it is a complete binary tree.
 
 Definition of a complete binary tree from Wikipedia:
 In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
 
 Example 1:
 
 Input: [1,2,3,4,5,6]
 Output: true
 Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.
 Example 2:
 
 Input: [1,2,3,4,5,null,7]
 Output: false
 Explanation: The node with value 7 isn't as far left as possible.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include <cstdint>
#include "Common.h"

namespace IsCompleteTree
{
bool isCompleteTree(TreeNode* root) {
    if (root == nullptr) return true;
    queue<TreeNode*> q;
    q.emplace(root);
    bool startMissingChild = false;
    while (!q.empty()) {
        auto levelSize = q.size();
        for (auto i = 0; i < levelSize; i++) {
            vector<TreeNode*> children = { q.front()->left, q.front()->right };
            q.pop();
            for (auto child : children) {
                if (child == nullptr) {
                    startMissingChild = true;
                    continue;
                }
                // if startMissingChild, no child allowed
                if (startMissingChild) {
                    return false;
                }
                q.emplace(child);
            }
        }
    }
    return true;
}

void Test()
{
    TreeNode *root = makeTree({ 1,2,3,4,5,null,7 });
    TreePrinter::Printer<TreeNode> treePrinter;
    treePrinter.printPretty(root, 1, 1, cout);
    cout << isCompleteTree(root) << std::endl;
}
}
