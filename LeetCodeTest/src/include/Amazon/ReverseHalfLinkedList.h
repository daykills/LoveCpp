/*
Reverse Second Half of Linked List, e.g. 1-2-3-4-5-6 change to 1-2-3-6-5-4, 1-2-3-4-5 change to 1-2-5-4-3
*/
namespace ReverseHalfLinkedList
{
  // Definition for singly-linked list.
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
  };

  ListNode* reverseList(ListNode* head)
  {
    ListNode* newHead = nullptr;
    // one by one, move nodes to the front of the newHead
    while (head)
    {
      ListNode* next = head->next;
      head->next = newHead;
      newHead = head;
      head = next;
    }
    return newHead;
  }

  static ListNode* reverseHalf(ListNode* root)
  {
    if (root == nullptr || root->next == nullptr) return root;
    auto fast = root->next;
    auto slow = root;
    while (fast && fast->next)
    {
      fast = fast->next->next;
      slow = slow->next;
    }
    // if we have even number of nodes, slow at the last node of first half
    // if we have odd number of nodes, slow at the last very middle node

    // reverse slow's next
    slow->next = reverseList(slow->next);
    return root;
  }

  static ListNode* Test()
  {
    const int n = 8;
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
    
    result = reverseHalf(nodes[0]);
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