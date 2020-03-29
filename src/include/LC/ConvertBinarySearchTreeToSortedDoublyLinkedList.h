/*
 426. Convert Binary Search Tree to Sorted Doubly Linked List
 
 Convert a Binary Search Tree to a sorted Circular Doubly-Linked List in place.
 
 You can think of the left and right pointers as synonymous to the predecessor and successor pointers in a doubly-linked list. For a circular doubly linked list, the predecessor of the first element is the last element, and the successor of the last element is the first element.
 
 We want to do the transformation in place. After the transformation, the left pointer of the tree TreeNode should point to its predecessor, and the right pointer should point to its successor. You should return the pointer to the smallest element of the linked list.
 
 
 
 Example 1:
 
 
 
 Input: root = [4,2,5,1,3]
 
 
 Output: [1,2,3,4,5]
 
 Explanation: The figure below shows the transformed BST. The solid line indicates the successor relationship, while the dashed line means the predecessor relationship.
 
 Example 2:
 
 Input: root = [2,1,3]
 Output: [1,2,3]
 Example 3:
 
 Input: root = []
 Output: []
 Explanation: Input is an empty tree. Output is also an empty Linked List.
 Example 4:
 
 Input: root = [1]
 Output: [1]
 */

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace ConvertBinarySearchTreeToSortedDoublyLinkedList
{

/*
 // Definition for a TreeNode.
 class TreeNode {
 public:
 int val;
 TreeNode* left;
 TreeNode* right;
 
 TreeNode() {}
 
 TreeNode(int _val) {
 val = _val;
 left = NULL;
 right = NULL;
 }
 
 TreeNode(int _val, TreeNode* _left, TreeNode* _right) {
 val = _val;
 left = _left;
 right = _right;
 }
 };
 */
class Solution {
public:
    /*
     观察到原二叉搜索树中结点4连接着结点2和结点5，而在双向链表中，连接的是结点3和结点5，这就是为啥要用中序遍历了，因为只有中序遍历，结点3之后才会遍历到结点4，这时候可以将结点3和结点4串起来。决定了用中序遍历之后，就要考虑是迭代还是递归的写法，博主建议写递归的，一般写起来都比较简洁，而且递归是解树类问题的神器啊，十有八九都是用递归，一定要熟练掌握。再写中序遍历之前，其实还有难点，因为需要把相邻的结点连接起来，所以需要知道上一个遍历到的结点是什么，所以用一个变量 pre，来记录上一个遍历到的结点。还需要一个变量 head，来记录最左结点，这样的话，在递归函数中，先判空，之后对左子结点调用递归，这样会先一直递归到最左结点，此时如果 head 为空的话，说明当前就是最左结点，赋值给 head 和 pre，对于之后的遍历到的结点，那么可以和 pre 相互连接上，然后 pre 赋值为当前结点 TreeNode，再对右子结点调用递归即可
     */
    void inorder(TreeNode* n, TreeNode*& prev, TreeNode*& head) {
        // First TreeNode without left children is head
        if (!head && !n->left) {
            head = n;
        }
        auto left = n->left;
        auto right = n->right;
        // process left
        if (left) inorder(left, prev, head);
        
        // process current
        // connect with prev
        if (prev)
            prev->right = n;
        n->left = prev;
        prev = n;
        
        // right
        if(right) inorder(right, prev, head);
    }
    TreeNode* treeToDoublyList(TreeNode* root) {
        if (!root) return NULL;
        TreeNode* prev = NULL;
        TreeNode* head = NULL;
        inorder(root, prev, head);
        prev->right = head;
        head->left = prev;
        return head;
    }
};

static void Test()
{
    TreeNode *root = makeTree({ 4,2,5,1,3,null,null });
    TreePrinter::Printer<TreeNode> treePrinter;
    treePrinter.printPretty(root, 1, 1, cout);
    Solution s;
    auto head = s.treeToDoublyList(root);
    auto cur = head;
    do {
        cout << cur->val << endl;
        cur = cur->right;
    } while (cur != head);
}
}
