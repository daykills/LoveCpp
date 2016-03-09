/*
138. Copy List with Random Pointer

Total Accepted: 56707 Total Submissions: 219236 Difficulty: Hard

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.
*/
#include <iostream>
#include <unordered_map>
#include "Common.h"

namespace CopyListWithRandomPointer
{
  //Definition for singly - linked list with a random pointer.
  struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(nullptr), random(nullptr) {}
  };

  // non-deep copy of the new nodes - only populate the label, not next and random pointers
  RandomListNode* GetNewNode(RandomListNode *node, unordered_map<RandomListNode*, RandomListNode*>& map)
  {
    if (node == nullptr) return nullptr;
    RandomListNode *newNode = nullptr;
    auto iteratorToNewPointer = map.find(node);
    if (iteratorToNewPointer == map.end())
    {
      newNode = new RandomListNode(node->label);
      map.emplace(node, newNode);
    }
    else
    {
      newNode = iteratorToNewPointer->second;
    }
    return newNode;
  }

  // smart method that takes no extra space
  RandomListNode *copyRandomList(RandomListNode *head)
  {
    if (head == nullptr) return nullptr;
    auto curNode = head;
    // make a shallow copy of each node, and insert the copied node after the original node
    while (curNode)
    {
      RandomListNode* copyNode = new RandomListNode(curNode->label);
      copyNode->next = curNode->next;
      copyNode->random = curNode->random;
      curNode->next = copyNode;
      curNode = copyNode->next;
    }
    // go through all copied nodes, and update the random
    auto curCopiedNode = head->next;
    while (true)
    {
      if (curCopiedNode->random)
      {
        // update random to the new one
        curCopiedNode->random = curCopiedNode->random->next;
      }
      // move to next copied node
      if (curCopiedNode->next == nullptr) break;
      curCopiedNode = curCopiedNode->next->next;
    }

    // break the copied node off from the origin
    curNode = head;
    auto copiedHead = head->next;
    curCopiedNode = copiedHead;
    while (true)
    {
      curNode->next = curCopiedNode->next;
      curNode = curNode->next;
      if (curNode == nullptr)
      {
        curCopiedNode->next = nullptr;
        break;
      }
      else
      {
        curCopiedNode->next = curNode->next;
        curCopiedNode = curCopiedNode->next;
      }
    }
    return copiedHead;
  }

  /********************************************************************************************/

  // regular method that takes space N for map
  RandomListNode *copyRandomList1(RandomListNode *head)
  {
    if (head == nullptr) return nullptr;
    // map between the original and new pointers
    unordered_map<RandomListNode*, RandomListNode*> map;

    RandomListNode dummy(-1);

    RandomListNode* preNode = &dummy;
    RandomListNode* curNode = nullptr;

    while (head != nullptr)
    {
      curNode = GetNewNode(head, map);
      curNode->random = GetNewNode(head->random, map);
      preNode->next = curNode;
      preNode = curNode;
      head = head->next;
    }
    return dummy.next;
  }

  /********************************************************************************************/
  static int Test()
  {
    const int n = 3;
    RandomListNode* nodes[n];
    for (int i = n - 1; i >= 0; i--)
    {
      nodes[i] = new RandomListNode(i);
      nodes[i]->next = i == (n - 1) ? nullptr : nodes[i + 1];
    }

    nodes[0]->random = nodes[1];
    nodes[1]->random = nodes[0];
    nodes[2]->random = nodes[1];

    auto result = nodes[0];
    int i = 0;
    while (result)
    {
      cout << "i = " << i << " cur = " << result << " label = " << result->label << " next = " << result->next << " random = " << result->random << endl;
      i++;
      result = result->next;
    }

    cout << "***********" << endl;
    
    result = copyRandomList(nodes[0]);
    i = 0;
    while (result)
    {
      cout << "i = " << i << " cur = " << result << " label = " << result->label << " next = " << result->next << " random = " << result->random << endl;
      i++;
      result = result->next;
    }

    return 0;
  }
}