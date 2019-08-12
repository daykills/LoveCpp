#pragma once
/*
117. Populating Next Right Pointers in Each Node II My Submissions Question
Total Accepted: 58247 Total Submissions: 178053 Difficulty: Hard
Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,
1
/  \
2    3
/ \    \
4   5    7
After calling your function, the tree should look like:
1 -> NULL
/  \
2 -> 3 -> NULL
/ \    \
4-> 5 -> 7 -> NULL

*/

#include <iostream>
#include <queue>
#include "Common.h"

namespace PopulatingNextRightPointersInEachNode2
{
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    
    Node() {}
    
    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};

Node* connect(Node* root) {
    auto result = root;
    Node* firstOfLevel = nullptr;
    Node* preNode = nullptr;
    auto updateNodes = [&firstOfLevel, &preNode](Node* child) {
        if (!child) return;
        if (!firstOfLevel) {
            firstOfLevel = child;
        }
        if (preNode) {
            preNode->next = child;
        }
        preNode = child;
    };
    while (root) {
        auto parent = root;
        firstOfLevel = nullptr;
        preNode = nullptr;
        while (parent) {
            updateNodes(parent->left);
            updateNodes(parent->right);
            parent = parent->next;
        }
        root = firstOfLevel;
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////////
static void Test()
{
    //[1, 2, 2, 3, 3, null, null, 4, 4]
    /*
    const int n = 7;
    Node* nodes[n];
    
    for (int i = 0; i < n; i++)
    {
        srand(i);
        nodes[i] = new Node();
    }
    nodes[0]->left = nodes[1];
    nodes[0]->right = nodes[2];
    nodes[1]->left = nodes[3];
    nodes[1]->right = nodes[4];
    nodes[3]->left = nodes[5];
    nodes[3]->right = nodes[6];
    
    TreePrinter::Printer<TreeLinkNode> treePrinter;
    treePrinter.printPretty(nodes[0], 1, 1, cout);
    
    connect(nodes[0]);
     */
}
}

