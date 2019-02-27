/*
24. Swap Nodes in Pairs My Submissions Question
Total Accepted: 85437 Total Submissions: 246068 Difficulty: Medium
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
*/
namespace SwapNodesInPairs
{
  // Definition for singly-linked list.
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
  };

  ListNode* swapPairs(ListNode* head)
  {
    ListNode dummy(-1);
    dummy.next = head;

    ListNode* preNode = &dummy;

    // check if we have two good nodes after preNode
    while (preNode->next && preNode->next->next)
    {
      auto first = preNode->next;
      auto second = first->next;
      first->next = second->next;
      second->next = first;
      preNode->next = second;
      preNode = first;
    }
    return dummy.next;
  }

  static void Test()
  {
    const int n = 5;
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

    result = swapPairs(nodes[0]);
    i = 0;
    while (result)
    {
      cout << "i = " << i << " cur = " << result << " val = " << result->val << " next = " << result->next << endl;
      i++;
      result = result->next;
    }
  }
}