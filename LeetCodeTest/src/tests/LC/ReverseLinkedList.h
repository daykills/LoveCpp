/*
206. Reverse Linked List My Submissions Question
Total Accepted: 82373 Total Submissions: 216857 Difficulty: Easy
Reverse a singly linked list.

click to show more hints.

Hint:
A linked list can be reversed either iteratively or recursively. Could you implement both?
*/

namespace ReverseLinkedList
{
  // Definition for singly-linked list.
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
  };
  /////////////////////////////////////////////////////////////////////
  ListNode* reverseListRecursive(ListNode* head, ListNode* newHead)
  {
    if (head == nullptr) return newHead;
    // move head to the front of newHead, and update head and newHead
    auto next = head->next;
    head->next = newHead;
    newHead = head;
    return reverseListRecursive(next, newHead);
  }

  ListNode* reverseListRecursive(ListNode* head)
  {
    ListNode* newHead = nullptr;
    return reverseListRecursive(head, newHead);
  }
  /////////////////////////////////////////////////////////////////////
  ListNode* reverseList(ListNode* head)
  {
    ListNode* newHead = nullptr;
    // gradually move nodes to the front of the newHead
    while (head)
    {
      ListNode* next = head->next;
      head->next = newHead;
      newHead = head;
      head = next;
    }
    return newHead;
  }

  static ListNode* Test()
  {
    const int n = 7;
    ListNode* nodes[n];
    for (int i = n - 1; i >= 0; i--)
    {
      nodes[i] = new ListNode(i * i);
      nodes[i]->next = i == (n - 1) ? nullptr : nodes[i + 1];
    }

    ListNode* result = nodes[0];
    int i = 0;
    while (result)
    {
      cout << "i = " << i << " cur = " << result << " label = " << result->val << " next = " << result->next << endl;
      i++;
      result = result->next;
    }

    cout << "***********" << endl;

    result = reverseListRecursive(nodes[0]);
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