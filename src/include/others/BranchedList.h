/*
 6. Design a class that can satisfy a data structure like a list. 如附件。
 第一问：打印出来这HELLOWORLD来
 第二问：实现两个函数：
 boolean hasNext();
 String getNext();
 这两个方法需要和面试官聊如何去理解。一下是我和面试官的clarification：
 可以这么理解hasNext()方法：如果你现在处于head，第一个node，hasNext会返回true，因为虽然head和head的next都没有字符，但是第三个node的vertical那么看是有字符的，所以返回true，但是你不需要到到那个node。如果你在head，调用多次hasnext，会一直返回true，因为下个字符一直是H
 getNext的意思是返回下一个字符。如果你处于head，你会🔙H，然后在调用getNext，返回E，以此类推
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace BranchedList
{
class BranchedListNode {
public:
    BranchedListNode() : branch(nullptr), next(nullptr) {}
    ListNode* branch;
    BranchedListNode* next;
};

class DataContainer
{
public:
    DataContainer(BranchedListNode* root) : m_root(root) {
        moveToNext();
    }
    // after get, always move the internal cursor to the next available
    int getNext() {
        assert(hasNext());
        int val = m_root->branch->val;
        moveToNext();
        return val;
    }
    // check if there is next value
    
    bool hasNext() const {
        return m_root && m_root->branch;
    }
    
    void print() {
        while (hasNext()) {
            cout << getNext() << ", ";
        }
        cout << endl;
    }
private:
    void moveToNext() {
        if (m_root->branch)
            m_root->branch = m_root->branch->next;
        if (m_root->branch) return;
        while (m_root->next) {
            m_root = m_root->next;
            if (hasNext())
                break;
        }
    }
    BranchedListNode* m_root;
};

////////////////////////////////////////////////////////////////////////////////////
void Test()
{
    BranchedListNode b0;
    BranchedListNode b1;
    BranchedListNode b2;
    BranchedListNode b3;
    b0.next = &b1;
    b1.next = &b2;
    b2.next = &b3;
    
    ListNode *h1 = makeList({ 10, 11 });
    ListNode *h2 = makeList({ 12, 13 });
    b1.branch = h1;
    b2.branch = h2;
    
    DataContainer container(&b0);
    container.print();
}
}
