/*
147. Insertion Sort List
Total Accepted: 62803 Total Submissions: 221343 Difficulty: Medium
Sort a linked list using insertion sort.
*/

#include <iostream>
#include <unordered_map>
#include "Common.h"

namespace InsertionSortList
{
  // Definition for singly-linked list.
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
  };

  ListNode* insertionSortList(ListNode* head)
  {
    if (head == nullptr) return nullptr;

    ListNode* sortedHead = head;

    ListNode* sortedTail = head;

    head = head->next;
    sortedTail->next = nullptr;

    while (head)
    {
      auto tempNode = head; // get the node
      head = head->next;
      // if value is greater than the tail, append to the tail
      if (sortedTail->val <= tempNode->val)
      {
        sortedTail->next = tempNode;
        sortedTail = tempNode;
        tempNode->next = nullptr;
      }
      else if (sortedHead->val >= tempNode->val)
      {
        // append it before the head
        tempNode->next = sortedHead;
        sortedHead = tempNode;
      }
      else
      {
        // sortedHead < head < sortedTail; insert it in the middle
        // find the right place to insert the node
        auto preNode = sortedHead;
        auto curNode = sortedHead->next;
        while (curNode != sortedTail)
        {
          if (curNode->val >= tempNode->val)
          {
            break;
          }
          preNode = curNode;
          curNode = curNode->next;
        }
        // insert between preNode and curNode
        preNode->next = tempNode;
        tempNode->next = curNode;
      }
    }

    return sortedHead;
  }

  static int Test()
  {
    const int n = 7;
    ListNode* nodes[n];
    for (int i = n - 1; i >= 0; i--)
    {
      nodes[i] = new ListNode((i * i + 199) % 11);
      nodes[i]->next = i == (n - 1) ? nullptr : nodes[i + 1];
    }
    
    auto result = nodes[0];
    int i = 0;
    while (result)
    {
      cout << "i = " << i << " cur = " << result << " label = " << result->val << " next = " << result->next << endl;
      i++;
      result = result->next;
    }

    cout << "***********" << endl;

    result = insertionSortList(nodes[0]);
    i = 0;

    while (result)
    {
      cout << "i = " << i << " cur = " << result << " label = " << result->val << " next = " << result->next << endl;
      i++;
      result = result->next;
    }

    return 0;
  }
}