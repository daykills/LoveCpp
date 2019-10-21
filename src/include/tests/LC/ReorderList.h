/*
 143. Reorder List

 Given a singly linked list L: L0→L1→…→Ln-1→Ln,
 reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
 
 You may not modify the values in the list's nodes, only nodes itself may be changed.
 
 Example 1:
 
 Given 1->2->3->4, reorder it to 1->4->2->3.
 Example 2:
 
 Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace ReorderList
{

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void reorderList(ListNode* head) {
    if (!head) return;

    // find the mid point.
    // If it contains odd number of nodes, mid has one less node.
    ListNode dummy(0);
    dummy.next = head;
    auto* p1 = &dummy;
    auto* p2 = &dummy;
    while (p2) {
        p1 = p1->next;
        p2 = p2->next;
        if (p2 == nullptr) break;
        p2 = p2->next;
    }
    auto mid = p1->next;
    p1->next = nullptr;
    
    // reverse nodes starting mid
    ListNode reverse(0);
    auto next = mid;
    while (next) {
        auto oldNext = reverse.next;
        reverse.next = next;
        next = next->next;
        reverse.next->next = oldNext;
    }
    
    // merge nodes from both order and revese
    auto* pre = &dummy;
    next = head;
    mid = reverse.next;
    while (next) {
        pre->next = next;
        pre = next;
        next = next->next;
        if (mid) {
            pre->next = mid;
            pre = mid;
            mid = mid->next;
        }
    }
}

void Test()
{
    vector<int> vals = { 1, 2, 3, 4, 5 };
    ListNode dummy(0);
    auto* pre = &dummy;
    for (auto val : vals) {
        pre->next = new ListNode(val);
        pre = pre->next;
    }
    reorderList(dummy.next);
}
}
