/*
142. Linked List Cycle II
Total Accepted: 65623 Total Submissions: 208614 Difficulty: Medium
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?

H-----X-->---Y---+
      |          |
      +---<------+

H is the header; X is the start of cycle; Y is the first time they meet
H -> X = a
X -> Y = b
Y -> X = c

fast = a + b + n*(b+c) = 2 * (a+b) = 2 * slow
-> (n-1)*(b+c) + c = a;

slow + a = (a + b) + (n-1)*(b+c) + c = a + n * (b + c), meaning, with "a" more steps, slow can reach X.

Let the fast go back to header, and move together with slow at the same pace. They will meet again at X.

*/

#include <string>
#include <iostream>
#include <unordered_set>
#include "Common.h"

namespace LinkedListCycle2
{
  // Definition for singly-linked list.
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
  };

  ListNode *detectCycle(ListNode *head)
  {
    auto slow = head;
    auto fast = head;
    while (fast && fast->next)
    {
      fast = fast->next->next;
      slow = slow->next;
      if (slow == fast)
      {
        fast = head;
        while (fast != slow)
        {
          fast = fast->next;
          slow = slow->next;
        }
        return slow;
      }
    }
    return nullptr;
  }

  ///////////////////////////////////////////////////
  // use unordered_set to save the history
  ListNode *detectCycle1(ListNode *head)
  {
    unordered_set<ListNode*> history;
    while (head)
    {
      if (history.find(head) == history.end())
      {
        history.emplace(head);
      }
      else
      {
        return head;
      }
      head = head->next;
    }
    return nullptr;
  }

  static void Test()
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

    detectCycle(nodes[0]);
  }
}
