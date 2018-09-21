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

  // function to merge two sorted lists
  ListNode* mergeLists(ListNode* list1, ListNode* list2)
  {
    if (list1 == nullptr) return list2;

    ListNode dummy(-1);
    ListNode* preNode = &dummy;

    while (list1 != nullptr && list2 != nullptr)
    {
      // pick nodes from the smaller ones
      if (list1->val <= list2->val)
      {
        preNode->next = list1;
        list1 = list1->next;
      }
      else
      {
        preNode->next = list2;
        list2 = list2->next;
      }
      preNode = preNode->next;
    }
    preNode->next = (list1 == nullptr) ? list2 : list1;
    return dummy.next;
  }
  ListNode* mergeKLists(vector<ListNode*>& lists)
  {
    // when n <= 1
    int n = lists.size();
    if (n == 0) return nullptr;
    if (n == 1) return lists[0];

    // job queue
    queue<ListNode*> jobQ;
    // add all lists to the job queue
    for (auto list : lists)
    {
      jobQ.push(list);
    }
    while (true)
    {
      auto list1 = jobQ.front();
      jobQ.pop();
      auto list2 = jobQ.front();
      jobQ.pop();
      auto merged = mergeLists(list1, list2);
      if (jobQ.empty())
      {
        return merged;
      }
      else
      {
        // add the job to the back of the queue, so that we don't have one too-long list
        jobQ.push(merged);
      }
    }
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