/*
 147. Insertion Sort List
 Total Accepted: 62803 Total Submissions: 221343 Difficulty: Medium
 Sort a linked list using insertion sort.
 */

#include <iostream>
#include <unordered_map>
#include "Common.h"

namespace InsertionSortList
{
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(NULL == head || NULL == head->next) return head;
        ListNode  result(1);
        result.next = head;
        ListNode * cur = head;
        while(cur && cur->next)
        {
            ListNode * nextNode = cur->next;
            if(nextNode->val >= cur->val)
            {
                cur = nextNode;
                continue;
            }
            //insert nextNode to result
            ListNode * pos = &result;
            while(pos->next->val < nextNode->val)
                pos = pos->next;
            //[pos, pos->next]  -->[pos, nextNode, pos->next]
            cur->next = nextNode->next;
            nextNode->next = pos->next;
            pos->next = nextNode;
        }
        return result.next;
    }
};

static int Test()
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
    
    result = insertionSortList(nodes[0]);
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
