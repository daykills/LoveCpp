/*
109. Convert Sorted List to Binary Search Tree
Total Accepted: 61180 Total Submissions: 207452 Difficulty: Medium
Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
*/

#include <iostream>
#include "Common.h"

namespace ConvertSortedListToBinarySearchTree
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

  TreeNode *sortedListToBST(ListNode *head, int length)
  {
    if (head == nullptr || length == 0) return nullptr;
    int leftLen = length / 2;    
    ListNode* midNode = head;
    for (int i = 0; i < leftLen; i++)
    {
      midNode = midNode->next;
    }
    auto result = new TreeNode(midNode->val);
    result->left = sortedListToBST(head, leftLen);
    int rightLen = length - leftLen - 1;
    result->right = sortedListToBST(midNode->next, rightLen);
    return result;
  }

  TreeNode *sortedListToBSTOld(ListNode *head)
  {
    if (head == nullptr) return nullptr;
    
    auto next = head->next;
    int len = 1;
    while (next)
    {
      len++;
      next = next->next;
    }
    return sortedListToBST(head, len);
  }

  ////////////////////////////////////////////////////////

  // convert sorted array to BST
  TreeNode* sortedArrayToBST(const vector<int>& sortedArray, int start, int end)
  {
    // validate arguments
    int n = end - start + 1;
    if (n <= 0 || start < 0 || end >= (int)sortedArray.size())
      return nullptr;

    // get the index of middle element
    int mid = start + (n >> 1);

    auto headNode = new TreeNode(sortedArray[mid]);
    headNode->left = sortedArrayToBST(sortedArray, start, mid - 1);
    headNode->right = sortedArrayToBST(sortedArray, mid + 1, end);
    return headNode;
  }

  TreeNode *sortedListToBST1(ListNode *head)
  {
    if (nullptr == head) return nullptr;

    vector<int> sortedArray;

    auto next = head;
    while (next != nullptr)
    {
      sortedArray.push_back(next->val);
      next = next->next;
    }

    int n = sortedArray.size();

    return sortedArrayToBST(sortedArray, 0, n - 1);
  }
  ///////////////////////////////////////////////////////////////////////////////////////
  // list is always like this: [left-sub-tree, mid-node, right-sub-tree]
  // keep the head rolling. build the tree from bottom
  // use start and end to mark the position - whether we are in a sub-tree
  TreeNode* buildTree(ListNode*& head, int start, int end)
  {
	  // at the end of list, or at the end of this sub-tree; list still needs to roll
	  if (head == nullptr || start > end) return nullptr;

	  if (start == end)
	  {
		  auto root = new TreeNode(head->val);
		  head = head->next;
		  return root;
	  }
	  // empth root
	  auto root = new TreeNode(-1);
	  int mid = (start + end) / 2;
	  // get left sub-tree
	  root->left = buildTree(head, start, mid - 1);
	  // fill root value
	  root->val = head->val;
	  head = head->next;
	  // get right sub-tree
	  root->right = buildTree(head, mid + 1, end);
	  return root;
  }
  TreeNode* sortedListToBST(ListNode* head)
  {
	  int n = 0;
	  auto headTemp = head;
	  while (head)
	  {
		  head = head->next;
		  n++;
	  }
	  return buildTree(headTemp, 0, n - 1);
  }

  static int Test()
  {
	  int n = 2;
	  vector<ListNode*> nodes(2);
	  for (int i = 0; i < 2; i++)
	  {
		  nodes[n - i - 1] = new ListNode(n - i - 1);
		  if (i != 0) nodes[n - i - 1]->next = nodes[n - i];
	  }

	  sortedListToBST(nodes[0]);
	  return 0;
  }
}
