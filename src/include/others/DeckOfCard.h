/*
 7. 实现一个interface
 interface IDeckOfCard {
     int remainingCard;
     Card[] getFromTop(int n);
     Card[] getFromBottom(int n);
     void shuffle();
 }
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace DeckOfCard
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
