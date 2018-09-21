/*
94. Binary Tree Inorder Traversal
Total Accepted: 106539 Total Submissions: 277189 Difficulty: Medium
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
1
\
2
/
3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.

*/

#include <iostream>
#include <stack>
#include "Common.h"

namespace BinaryTreeInorderTraversal
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

  // Morris Traversal
  // http://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html
  ///////////////////////////////////////////////////////
  vector<int> inorderTraversal(TreeNode* root)
  {
    using namespace std;
    vector<int> result;
    TreeNode * cur = root;
    while (NULL != cur)
    {
      if (cur->left == NULL)
      {
        result.push_back(cur->val);
        cur = cur->right;
      }
      else
      {
        auto pre = cur->left;
        while (pre->right != NULL && pre->right != cur)
          pre = pre->right;
        if (pre->right == NULL)
        {
          pre->right = cur;
          cur = cur->left;
        }
        else //reset
        {
          pre->right = NULL;
          result.push_back(cur->val);
          cur = cur->right;
        }
      }
    }
    return move(result);
  }

  ////////////////////////////////////////////////////////////////////////////////////
  vector<int> inorderTraversalStack(TreeNode* root)
  {
	  vector<int> result;
	  if (root == nullptr) return result;
	  stack<TreeNode*> stack;
	  auto cur = root;
	  while (!stack.empty() || cur != nullptr)
	  {
		  if (cur)
		  {
			  stack.push(cur);
			  cur = cur->left;
		  }
		  else
		  {
			  if (stack.empty()) break;
			  auto top = stack.top();
			  stack.pop();

			  result.emplace_back(top->val);
			  cur = top->right;
		  }
	  }
	  return result;
  }
  ////////////////////////////////////////////////////////////////////////////////////
  // recursive
  void inorderTraversalRecursive(TreeNode* root, vector<int>& result)
  {
    if (root == nullptr) return;
    inorderTraversalRecursive(root->left, result);
    result.emplace_back(root->val);
    inorderTraversalRecursive(root->right, result);
  }

  vector<int> inorderTraversal1(TreeNode* root)
  {
    vector<int> result;
    inorderTraversalRecursive(root, result);
    return move(result);
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

    for(auto value : inorderTraversal(nodes[0]))
    {
      cout << value << " ";
    }
    cout << endl;
    return true;
  }
}