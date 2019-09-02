/*
 432. All O`one Data Structure

 Implement a data structure supporting the following operations:
 
 Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1. Key is guaranteed to be a non-empty string.
 Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise decrements an existing key by 1. If the key does not exist, this function does nothing. Key is guaranteed to be a non-empty string.
 GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".
 GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".
 Challenge: Perform all these in O(1) time complexity.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace AllO1DataStructure
{

class AllOne {
public:
    /** Initialize your data structure here. */
    AllOne() {}
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if (m_keyMap.count(key)) {
            auto bucketIter = m_keyMap[key];
            auto val = bucketIter->val + 1;
            bucketIter->keys.erase(key);
            auto nextIter = std::next(bucketIter);
            // if already last bucket
            if (nextIter == m_buckets.end()) {
                nextIter = m_buckets.insert(m_buckets.end(), { val, { key } });
            } else if (nextIter->val == val) {
                nextIter->keys.emplace(key);
            } else {
                // new bucket
                nextIter = m_buckets.insert(nextIter, { val, { key } });
            }
            m_keyMap[key] = nextIter;
            if (bucketIter->keys.empty()) {
                m_buckets.erase(bucketIter);
            }
        } else {
            // new bucket with val 1
            if (!m_buckets.empty() && m_buckets.front().val == 1) {
                m_buckets.front().keys.emplace(key);
            } else {
                m_buckets.push_front({ 1, { key } });
            }
            m_keyMap[key] = m_buckets.begin();
        }
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if (m_buckets.empty())
            return;
        if (m_keyMap.count(key)) {
            auto bucketIter = m_keyMap[key];
            auto val = bucketIter->val - 1;
            bucketIter->keys.erase(key);
            m_keyMap.erase(key);
            if (val > 0) {
                if (bucketIter == m_buckets.begin()) {
                    m_buckets.push_front( {val - 1, { key } });
                    m_keyMap[key] = m_buckets.begin();
                } else {
                    auto preIter = prev(bucketIter);
                    if (preIter->val == val) {
                        preIter->keys.emplace(key);
                        m_keyMap[key] = preIter;
                    } else {
                        auto newIter = m_buckets.insert(bucketIter, { val, { key } });
                        m_keyMap[key] = newIter;
                        bucketIter->keys.erase(key);
                    }
                }
            }
            if (bucketIter->keys.empty()) {
                m_buckets.erase(bucketIter);
            }
        }
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if (m_buckets.empty())
            return "";
        return *m_buckets.back().keys.begin();
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if (m_buckets.empty())
            return "";
        return *m_buckets.front().keys.begin();
    }
private:
    struct Bucket { int val; unordered_set<string> keys; };
    using BucketList = std::list<Bucket>;
    BucketList m_buckets;
    // key -> the list iterator
    unordered_map<string, BucketList::iterator> m_keyMap;
};

static void Test()
{
    /*
    // ["AllOne","inc","inc","inc","inc","getMaxKey","inc","inc","inc","dec","inc","inc","inc","getMaxKey"]
    // [[],["hello"],["goodbye"],["hello"],["hello"],[],["leet"],["code"],["leet"],["hello"],["leet"],["code"],["code"],[]]
    AllOne inst;
    inst.inc("hello");
    inst.inc("goodbye");
    inst.inc("hello");
    inst.inc("hello");
    std::cout << "getMaxKey: " << inst.getMaxKey() << std::endl;
    std::cout << "getMinKey: " << inst.getMinKey() << std::endl;
    inst.inc("leet");
    inst.inc("code");
    inst.inc("leet");
    inst.dec("hello");
    inst.inc("leet");
    inst.inc("code");
    inst.inc("code");
    std::cout << "getMaxKey: " << inst.getMaxKey() << std::endl;
    std::cout << "getMinKey: " << inst.getMinKey() << std::endl;
     */
    
    // ["AllOne","inc","inc","inc","inc","inc","dec","dec","getMaxKey","getMinKey"]
    // [[],["a"],["b"],["b"],["b"],["b"],["b"],["b"],[],[]]
    AllOne inst;
    inst.inc("a");
    inst.inc("b");
    inst.inc("b");
    inst.inc("b");
    inst.inc("b");
    std::cout << "getMaxKey: " << inst.getMaxKey() << std::endl;
    std::cout << "getMinKey: " << inst.getMinKey() << std::endl;
    inst.dec("b");
    inst.dec("b");
    std::cout << "getMaxKey: " << inst.getMaxKey() << std::endl;
    std::cout << "getMinKey: " << inst.getMinKey() << std::endl;
}
}
