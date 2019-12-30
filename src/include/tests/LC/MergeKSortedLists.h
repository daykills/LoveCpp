/*
23. Merge k Sorted Lists
 Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
 
 Example:
 
 Input:
 [
 1->4->5,
 1->3->4,
 2->6
 ]
 Output: 1->1->2->3->4->4->5->6
*/
namespace MergeKSortedLists
{
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    
    auto lessor = [](const ListNode* lhs, const ListNode* rhs) {
        return lhs->val > rhs->val;
    };
    // top is has the smallest root node
    priority_queue<ListNode*, vector<ListNode*>, decltype(lessor)> minHeap(lessor);
    while (!lists.empty()) {
        if (lists.back())
            minHeap.emplace(lists.back());
        lists.pop_back();
    }
    if (minHeap.empty()) return nullptr;
    
    ListNode dummy(0);
    auto pre = &dummy;
    // get the smallest node one by one
    while (!minHeap.empty()) {
        pre->next = minHeap.top();
        minHeap.pop();
        auto next = pre->next->next;
        if (next)
            minHeap.push(next);
        pre = pre->next;
    }
    pre->next = nullptr;
    return dummy.next;
}

static ListNode* Test()
{
    vector<vector<int>> nodes = {
        {1},
        {0},
    };
    vector<ListNode*> lists;
    for (auto& values : nodes) {
        lists.emplace_back();
        if (values.empty())
            continue;
        auto root = new ListNode(values.front());
        auto pre = root;
        for (auto i = 1; i < values.size(); i++) {
            pre->next = new ListNode(values[i]);
            pre = pre->next;
        }
        lists.back() = root;
    }
    for (auto list : lists) {
        while (list) {
            cout << list->val << " -> ";
            list = list->next;
        }
        cout << endl;
    }
    cout << "***********" << endl;
    
    auto result = mergeKLists(lists);
    while (result) {
        cout << result->val << " -> ";
        result = result->next;
    }
    cout << endl;
    
    return 0;
}
}
