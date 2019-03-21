/*
83. Remove Duplicates from Sorted List
Total Accepted: 97858 Total Submissions: 272475 Difficulty: Easy
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
*/

#include <string>
#include <iostream>
#include "Common.h"

namespace RemoveDuplicatesFromSortedList
{
  // Definition for singly-linked list.
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
  };

  ListNode* deleteDuplicates(ListNode* head)
  {
    ListNode dummy(-1);
    ListNode* preNode = &dummy;
    while (head)
    {
      preNode->next = head;
      head = head->next;
      while (head && head->val == preNode->next->val)
      {
        delete preNode->next;;
        preNode->next = head;
        head = head->next;
      }
      preNode = preNode->next;
    }
    return dummy.next;
  }

  static bool Test()
  {
    const int n = 7;
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

    result = deleteDuplicates(nodes[0]);
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