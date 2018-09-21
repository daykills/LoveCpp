/*
21. Merge Two Sorted Lists
Total Accepted: 104329 Total Submissions: 303993 Difficulty: Easy
Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
*/

namespace MergeTwoSortedLists
{
  // Definition for singly-linked list.
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
  };

  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
  {
    ListNode dummy(-1);
    auto head = &dummy;
    // pick nodes from l1 and l2 one by one
    while (l1 && l2)
    {
      if (l1->val < l2->val)
      {
        head->next = l1;
        l1 = l1->next;
      }
      else
      {
        head->next = l2;
        l2 = l2->next;
      }
      head = head->next;
    }
    head->next = (l1 == nullptr) ? l2 : l1;
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

    auto result = nodes[0];
    int i = 0;
    while (result)
    {
      cout << "i = " << i << " cur = " << result << " label = " << result->val << " next = " << result->next << endl;
      i++;
      result = result->next;
    }

    cout << "***********" << endl;

    const int m = 5;
    ListNode* nodes2[m];
    for (i = m - 1; i >= 0; i--)
    {
      nodes2[i] = new ListNode(4 * i + 5);
      nodes2[i]->next = i == (m - 1) ? nullptr : nodes2[i + 1];
    }
    result = nodes2[0];
    i = 0;
    while (result)
    {
      cout << "i = " << i << " cur = " << result << " label = " << result->val << " next = " << result->next << endl;
      i++;
      result = result->next;
    }

    cout << "***********" << endl;

    result = mergeTwoLists(nodes[0], nodes2[0]);
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

