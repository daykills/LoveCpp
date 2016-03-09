/*
19. Remove Nth Node From End of List
Total Accepted: 91390 Total Submissions: 321486 Difficulty: Easy
Given a linked list, remove the nth node from the end of list and return its head.

For example,

Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.
*/

#include <string>
#include <iostream>
#include "Common.h"

namespace RemoveNthNodeFromEndOfList
{
  // Definition for singly-linked list.
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
  };

  ListNode* removeNthFromEnd(ListNode* head, int n)
  {
    if (n <= 0 || head == nullptr) return head;
    auto fast = head;
    for (int i = 0; i < n; i++)
    {
      if (fast == nullptr)
        return head;
      fast = fast->next;
    }
    ListNode dummy(-1);
    dummy.next = head;
    auto preNode = &dummy;    
    while (fast)
    {
      fast = fast->next;
      preNode = preNode->next;
    }
    auto tmpNode = preNode->next;
    preNode->next = preNode->next->next;
    delete tmpNode;
    return dummy.next;
  }

  static bool Test()
  {
    const int n = 2;
    ListNode* nodes[n];
    for (int i = n - 1; i >= 0; i--)
    {
      nodes[i] = new ListNode((i * i + 199) % 3);
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

    result = removeNthFromEnd(nodes[0], 2);
    i = 0;
    while (result)
    {
      cout << "i = " << i << " cur = " << result << " val = " << result->val << " next = " << result->next << endl;
      i++;
      result = result->next;
    }

    return true;
  }
}