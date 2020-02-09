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

void reorderListOnePass(ListNode* head) {
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

void reorderListNew(ListNode* head) {
    if (!head || !head->next) return;
    
    // find the second half of the list
    ListNode dummy(0);
    dummy.next = head;
    auto slow = &dummy;
    auto fast = slow;
    while (fast && fast->next
           && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    auto halfHead = slow->next;
    slow->next = nullptr;
    
    // reverse half head;
    ListNode* reversed = nullptr;
    auto cur = halfHead;
    while (cur) {
        auto newRevHead = cur;
        cur = cur->next;
        newRevHead->next = reversed;
        reversed = newRevHead;
    }
    
    // merge reversed and head
    dummy.next = nullptr;
    auto prev = &dummy;
    while (head) {
        assert(prev);
        prev->next = head;
        head = head->next;
        prev = prev->next;
        
        prev->next = reversed;
        if (reversed) {
            reversed = reversed->next;
            prev = prev->next;
        }
    }
    head = dummy.next;
}

// recursive way:
// L0→Ln→L1→Ln-1→L2→Ln-2→… = L0→Ln→PREV_RESULT
void reorderList(ListNode* head) {
    if (!head || head->next == nullptr)
        return;
    // find the last node
    auto prev = head;
    auto last = head->next;
    while (last->next) {
        prev = last;
        last = last->next;
    }
    // break the last node from the list
    prev->next = nullptr;
    // start recursion
    auto subHead = head->next;
    reorderList(subHead);
    // merge into complete list
    head->next = last;
    last->next = subHead;
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
    reorderListNew(dummy.next);
    auto cur = dummy.next;
    while (cur) {
        cout << cur->val << endl;
        cur = cur->next;
    }
}
}
