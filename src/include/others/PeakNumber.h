/*
 在一个array 中找peak element
 array > array, array > array
 假设array[-1] < array[0], array[array.length - 1] > array[array.length]
 第一个简单例子 数字都不同
 input： [1, 2, 3, 6, 4, 3, 7, 6]
 return: [6, 7]

 第二个假设数字是可以相等的
 input: [0, 1, 2, 2, 3, 4]
 return:4

 第三个是这个数列很长，我们分成几个交给不同机器处理
 怎么处理边界上false postive 的peak element。
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace PeakNumber
{
class IDeckOfCard {
public:
    IDeckOfCard() = default;
    virtual ~IDeckOfCard() = default;
    virtual vector<int> getFromTop(int n) = 0;
    virtual vector<int> getFromBottom(int n) = 0;
    virtual void shuffule() = 0;
};

class DeckOfCard : public IDeckOfCard
{
public:
    // size: valid cards are [top, bottom]
    DeckOfCard(int size)
        : m_cards(size)
        , m_top(0)
        , m_bottom(size - 1)
        , m_empty(false) {
    }
    
    vector<int> getFromTop(int n) override {
        if (n == 0 || m_empty) return {};
        vector<int> cards;
        cards.reserve(n);
        while (n > 0 && m_top != m_bottom) {
            cards.push_back(m_cards[m_top]);
            m_top = (m_top + 1) % m_cards.size();
            n--;
        }
        if (n > 0) {
            assert(m_top == m_bottom);
            cards.push_back(m_cards[m_top])
            m_empty = true;
        }
        return cards;
    }
    vector<int> getFromBottom(int n) override {
        if (n == 0 || m_empty) return {};
        vector<int> cards;
        cards.reserve(n);
        while (n > 0 && m_top != m_bottom) {
            cards.push_back(m_cards[m_top]);
            m_bottom = (m_bottom + m_cards.size() - 1) % m_cards.size();
            n--;
        }
        if (n > 0) {
            assert(m_top == m_bottom);
            cards.push_back(m_cards[m_top])
            m_empty = true;
        }
        return cards;
    }
    void shuffule() override {
        m_empty = false;
        m_top = 0;
        m_bottom = m_cards.size() - 1;
    }
    
private:
    vector<int> m_cards;
    int m_bottom;
    int m_top;
    bool m_empty;
};

////////////////////////////////////////////////////////////////////////////////////
void Test()
{
    DeckOfCard cards(100);
}
}
