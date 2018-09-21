/*
86. Partition List
Total Accepted: 57581 Total Submissions: 200711 Difficulty: Medium
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.

*/

#include <string>
#include <iostream>
#include "Common.h"

namespace PartitionList
{
	// Definition for singly-linked list.
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(nullptr) {}
	};

	ListNode* partition(ListNode* head, int x) {
		ListNode dummyLess(-1);
		ListNode* curNodeLess = &dummyLess;
		ListNode dummyGreat(-1);
		ListNode* curNodeGreat = &dummyGreat;
		while (head)
		{
			if (head->val < x)
			{
				curNodeLess->next = head;
				curNodeLess = head;
			}
			else
			{
				curNodeGreat->next = head;
				curNodeGreat = head;
			}
			head = head->next;
		}
		curNodeLess->next = dummyGreat.next;
		curNodeGreat->next = nullptr;
		return dummyLess.next;
	}

	static bool Test()
	{
		vector<int> nums{ 2, 3, 1 };
		const int n = nums.size();
		vector<ListNode*> nodes(n);
		
		for (int i = n - 1; i >= 0; i--)
		{
			nodes[i] = new ListNode(nums[i]);
			nodes[i]->next = i == (n - 1) ? nullptr : nodes[i + 1];
		}

		auto result = nodes[0];
		int i = 0;
		while (result)
		{
			cout << "i = " << i << " cur = " << result << " val = " << result->val << " next = " << result->next << endl;
			i++;
			result = result->next;
		}

		cout << "***********" << endl;

		result = partition(nodes[0], 1);
		i = 0;
		while (result)
		{
			cout << "i = " << i << " cur = " << result << " val = " << result->val << " next = " << result->next << endl;
			i++;
			result = result->next;
		}

		return true;
	}
}