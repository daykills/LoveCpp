/*
92. Reverse Linked List II My Submissions Question
Total Accepted: 63773 Total Submissions: 233970 Difficulty: Medium
Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ¡Ü m ¡Ü n ¡Ü length of list.
*/

namespace ReverseLinkedList2
{
  // Definition for singly-linked list.
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
  };
  /////////////////////////////////////////////////////////////////////
  ListNode* reverseBetween(ListNode* head, int m, int n)
  {
    if (head == nullptr) return nullptr;
    if (m == n) return head;
    ListNode dummy(-1);
    dummy.next = head;
    auto pre = &dummy;
    // notice that m == 1 meaning to reverse from head
    while (m > 1 && pre->next)
    {
      pre = pre->next;
      m--;
      n--;
    }
    // actually, no need to check here as m < length of list
    if (m != 1) return head;
    // one by one, move start node to the front of newHead
    ListNode* newHead = nullptr;
    auto start = pre->next;
    auto mthNode = start;
    while (n >= 1)
    {
      pre->next = start->next;
      start->next = newHead;
      newHead = start;
      start = pre->next;
      n--;
    }
    // m-th node is the end of newHead; connect it with rest of those nodes
    mthNode->next = pre->next;
    // let pre->next point to newHead
    pre->next = newHead;
    return dummy.next;
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

    result = reverseBetween(nodes[0], 2, 4);
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