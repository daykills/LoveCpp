/*
 94. Binary Tree Inorder Traversal
 Medium
 Given a binary tree, return the inorder traversal of its nodes' values.
 
 Example:
 
 Input: [1,null,2,3]
 1
    \
      2
    /
 3
 
 Output: [1,3,2]
 Follow up: Recursive solution is trivial, could you do it iteratively?

*/

#include <iostream>
#include <stack>
#include "Common.h"

namespace ValidateBinarySearchTree
{
  // Definition for a binary tree node.
  struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

  //////////////////////////////////////////////////////

  void inOrderTraverse(TreeNode* root, vector<int>& data)
  {
	  if (root == nullptr) return;
	  inOrderTraverse(root->left, data);
	  data.emplace_back(root->val);
	  inOrderTraverse(root->right, data);
  }

  bool isValidBstExtraSpace(TreeNode* root)
  {
	  vector<int> data;
	  inOrderTraverse(root, data);
	  for (int i = 1; i < (int)data.size(); i++)
	  {
		  if (data[i] <= data[i - 1]) return false;
	  }
	  return true;
  }

  /////////////////////////////////////////////////////

  // pre is the previously evaluated node
  bool checkBST(TreeNode* root, TreeNode*& pre)
  {
	  if (root == nullptr) return true;
	  
	  if (!checkBST(root->left, pre)) return false;

	  if (pre != nullptr)
	  {
		  if (pre->val >= root->val) return false;
	  }

	  pre = root;
	  
	  return checkBST(root->right, pre);
  }

  bool isValidBST(TreeNode* root)
  {
	  TreeNode* pre = nullptr;
	  return checkBST(root, pre);
  }
  ////////////////////////////////////////////////////////////////////////////////////
  bool Test()
  {
    //[1, 2, 2, 3, 3, null, null, 4, 4]
    int NULLINT = 32132;
    vector<int> values{ 0, NULLINT, 1 };
    const int n = values.size();
    vector<TreeNode*> nodes(n);
    for (int i = 0; i < n; i++)
    {
      nodes[i] = (values[i] == NULLINT) ? nullptr : new TreeNode(values[i]);
    }
    nodes[0]->left = nodes[1];
    nodes[0]->right = nodes[2];

    TreePrinter::Printer<TreeNode> treePrinter;
    treePrinter.printPretty(nodes[0], 1, 1, cout);

    
    cout << "result: " << isValidBST(nodes[0]) << endl;
    return true;
  }
}
