/*
145. Binary Tree Postorder Traversal
Total Accepted: 86900 Total Submissions: 252520 Difficulty: Hard
Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
1
\
2
/
3
return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?

*/

#include <iostream>
#include <stack>
#include "Common.h"

namespace BinaryTreePostorderTraversal
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
  vector<int> postorderTraversal(TreeNode* root)
  {
    vector<int> result;
    if (root == nullptr) return result;
    stack<TreeNode*> stack;
    TreeNode* last = nullptr;
    stack.emplace(root);
    while (!stack.empty())
    {
      auto top = stack.top();
      if (top == nullptr)
      {
        stack.pop();
      }
      else
      {
        // if both child nodes are traversed already, we pop the top node
        if ((top->left == nullptr && top->right == nullptr)
            || ((last != nullptr && top->right == last) || (top->left == last && top->right == nullptr)))
        {
          result.emplace_back(top->val);
          last = top;
          stack.pop();
        }
        else
        {
          if (top->right) stack.emplace(top->right);
          if (top->left) stack.emplace(top->left);
        }
      }
    }
    return result;
  }
  ////////////////////////////////////////////////////////////////////////////////////
  void postorderTraversalRecursive(TreeNode* root, vector<int>& result)
  {
    if (root == nullptr) return;
    postorderTraversalRecursive(root->left, result);
    postorderTraversalRecursive(root->right, result);
    result.emplace_back(root->val);
  }

  vector<int> postorderTraversal1(TreeNode* root)
  {
    vector<int> result;
    postorderTraversalRecursive(root, result);
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

    for (auto value : postorderTraversal(nodes[0]))
    {
      cout << value << " ";
    }
    cout << endl;
    return true;
  }
}
