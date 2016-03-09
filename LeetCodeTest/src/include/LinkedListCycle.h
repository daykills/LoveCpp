/*
141. Linked List Cycle
Total Accepted: 90595 Total Submissions: 246349 Difficulty: Medium
Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?

*/

#include <string>
#include <iostream>
#include <unordered_set>
#include "Common.h"

namespace LinkedListCycle
{
  // Definition for singly-linked list.
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
  };

  bool hasCycle(ListNode *head)
  {
    if (head == nullptr || head->next == nullptr) return false;

    auto slow = head;
    auto fast = head->next;

    while (fast != nullptr && fast->next != nullptr)
    {
      if (fast == slow) return true;
      // fast first step
      fast = fast->next;      
      // fast second step
      if (fast == slow) return true;
      fast = fast->next;
      slow = slow->next;
    }
    return false;
  }
  /////////////////////////////////////////////////////////////
  // use an unordered map
  bool hasCycle1(ListNode *head)
  {
    unordered_set<ListNode*> history;
    while (head)
    {
      auto iterator = history.find(head);
      if (iterator == history.end())
      {
        history.emplace(head);
      }
      else
      {
        return true;
      }
      head = head->next;
    }
    return false;
  }

  static bool Test()
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

    return hasCycle(nodes[0]);
  }
}
