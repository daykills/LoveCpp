/*
25. Reverse Nodes in k-Group My Submissions Question
Total Accepted: 55112 Total Submissions: 203329 Difficulty: Hard
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5
*/
namespace SwapNodReverseNodesInKGroupesInPairs
{
  // Definition for singly-linked list.
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
  };

  // check whether starting from head, there is at least k nodes
  bool kGroupComplete(ListNode* head, int k)
  {
    int i = 0;
    while (i < k && head != nullptr)
    {
      head = head->next;
      i++;
    }
    return i == k;
  }

  ListNode* reverseKGroup(ListNode* head, int k)
  {
    ListNode dummy(-1);
    dummy.next = head;
    ListNode* preNode = &dummy;
    // if there are at least k nodes after preNode, do reversing
    while (kGroupComplete(preNode->next, k))
    {
      // move nodes to reverse one by one
      ListNode* reverse = nullptr;
      for (auto i = 0; i < k; i++)
      {
        // move one node from original list to reverse
        auto toBeMoved = preNode->next;
        preNode->next = toBeMoved->next;
        // merge it to reverse
        toBeMoved->next = reverse;
        reverse = toBeMoved;
      }
      // store the rest of the nodes
      auto rest = preNode->next;
      // move reversed list back
      preNode->next = reverse;
      // connect the end of the reversed list to the rest
      while (preNode->next != nullptr) preNode = preNode->next;
      preNode->next = rest;
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

    result = reverseKGroup(nodes[0], 3);
    i = 0;
    while (result)
    {
      cout << "i = " << i << " cur = " << result << " val = " << result->val << " next = " << result->next << endl;
      i++;
      result = result->next;
    }
  }
}