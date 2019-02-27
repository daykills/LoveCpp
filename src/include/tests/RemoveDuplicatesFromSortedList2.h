/*
82. Remove Duplicates from Sorted List II
Total Accepted: 63548 Total Submissions: 242649 Difficulty: Medium
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/

#include <string>
#include <iostream>
#include "Common.h"

namespace RemoveDuplicatesFromSortedList2
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

      auto searchNode = head->next;
      while (searchNode && searchNode->val == head->val)
      {
        auto tmpNode = searchNode;
        searchNode = searchNode->next;
        delete tmpNode;
      }
      // if duplicate, remove head
      if (searchNode != head->next)
      {
        delete head;
        // reset preNode->next as current head is not usable
        preNode->next = nullptr;
      }
      else
      {
        // non-duplicate, preNode takes head in.
        preNode = head;
      }
      head = searchNode;
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