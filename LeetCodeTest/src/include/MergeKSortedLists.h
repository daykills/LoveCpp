/*
23. Merge k Sorted Lists
Total Accepted: 72642 Total Submissions: 322524 Difficulty: Hard
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
*/
namespace MergeKSortedLists
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
    ListNode* preNode = &dummy;
    while (l1 && l2)
    {
      if (l1->val < l2->val)
      {
        preNode->next = l1;
        l1 = l1->next;
      }
      else
      {
        preNode->next = l2;
        l2 = l2->next;
      }
      preNode = preNode->next;
    }
    preNode->next = l1 == nullptr ? l2 : l1;
    return dummy.next;
  }

  ListNode* mergeKLists(vector<ListNode*>& lists)
  {
    int n = lists.size();

    if (n == 0) return nullptr;

    for (int step = 1; step < n; step = step << 1)
    {
      for (int i = 0; i < n; i += step << 1)
      {
        if (i + step < n)
        {
          lists[i] = mergeTwoLists(lists[i], lists[i + step]);
        }
      }
    }
    
    return lists[0];
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
    vector<ListNode*> sortedLists(2);
    sortedLists[0] = nodes[0];
    sortedLists[1] = nodes2[0];
    result = mergeKLists(sortedLists);
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