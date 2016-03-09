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

  TreeNode *sortedListToBST(ListNode *head)
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

  static int Test()
  {
    return 0;
  }
}
