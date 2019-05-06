/*
Add Two Numbers - Total Accepted: 114548 Total Submissions: 523300 Difficulty: Medium

You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

*/

#include <iostream>
#include "Common.h"

namespace AddTwoNumbers
{
  struct ListNode
  {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL)
    {}
  };

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        auto result = l1;
        // assume l1 is the longer list; if not, swap l1 and l2 later
        do {
            auto sum = l1->val + carry;
            if (l2) {
                sum += l2->val;
            }
            // in place update
            l1->val = sum % 10;
            carry = sum / 10;
            // if l1 finishes early, swap it with l2
            if (l2 && !l1->next) {
                l1->next = l2->next;
                l2->next = nullptr;
            }
            // end
            if (l1->next == nullptr) {
                if (carry)
                    l1->next = new ListNode(carry);
                break;
            }
            l1 = l1->next;
            if (l2)
                l2 = l2->next;
            
        } while (true);
        return result;
    }

  static int Test()
  {
    auto p1 = new ListNode(0);
    //p1->next = new ListNode(8);
    auto p2 = new ListNode(1);
    addTwoNumbers(p1, p2);
    return 0;
  }
}
