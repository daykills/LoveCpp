/*
61. Rotate List My Submissions Question
Total Accepted: 64682 Total Submissions: 284805 Difficulty: Medium
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.
*/

namespace RotateList
{
	// Definition for singly-linked list.
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(nullptr) {}
	};
	ListNode* rotateRight(ListNode* head, int k)
	{
		if (head == nullptr || head->next == nullptr || k == 0) return head;

		// find last node and number of nodes
		ListNode* lastNode = head;
		int n = 1;
		while (lastNode->next)
		{
			lastNode = lastNode->next;
			n++;
		}

		// connect lastNode with head, to make it a circle
		lastNode->next = head;

		// instead of moving backwards, we can move forward n-k steps; k%n as it as k+n is equavalent to k
		int steps = (n - k % n);

		// move lastNode forward
		for (int i = 0; i < steps; i++) lastNode = lastNode->next;
		// disconnect lastNode and its next, which is the new head
		head = lastNode->next;
		lastNode->next = nullptr;
		return head;
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

		result = rotateRight(nodes[0], 3);
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