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

  // recursive, 21%
  static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2, int carry)
  {
    //only comes the carry,like 5, 5 = 10, or carry = 0
    if (l1 == nullptr && l2 == nullptr && carry == 0)
      return nullptr;

    auto pResult = new ListNode(carry);

    if (l1 != nullptr)
    {
      pResult->val += l1->val;
      l1 = l1->next;
    }

    if (l2 != nullptr)
    {
      pResult->val += l2->val;
      l2 = l2->next;
    }

    carry = pResult->val / 10;
    pResult->val = pResult->val % 10;
    pResult->next = addTwoNumbers(l1, l2, carry);
    
    return pResult;
  }

  // recursive
  static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
  {
    return addTwoNumbers(l1, l2, 0);
  }

  // traverse method 69.99%
  static ListNode* addTwoNumbers1(ListNode* l1, ListNode* l2)
  {
    // if one number is null
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;

    ListNode dummy(-1);
    ListNode* pPre = &dummy;
    int carry = 0;    
    do
    {
      int sum = l1->val + l2->val + carry;

      carry = sum / 10;
      sum = sum % 10;

      pPre->next = new ListNode(sum);
      pPre = pPre->next;
      l1 = l1->next;
      l2 = l2->next;
    }
    while (l1 != nullptr && l2 != nullptr);
    // continue with the unfinished list
    if (l1 == nullptr) pPre->next = l2;
    else pPre->next = l1;
    // if carry is not zero
    if (carry != 0)
    {
      while (pPre->next != nullptr)
      {
        auto& pCur = pPre->next;
        int sum = pCur->val + carry;
        pCur->val = sum % 10;
        carry = sum / 10;
        pPre = pCur;
      }
      if (carry != 0)
      {
        pPre->next = new ListNode(carry);
      }
    }
    return dummy.next;
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