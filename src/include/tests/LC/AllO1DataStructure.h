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
        if (m_keyMap.count(key) == 0) {
            // update bucket
            if (m_buckets.empty() || m_buckets.front().val > 1) {
                m_buckets.insert(m_buckets.begin(), { 1, { key } });
            } else {
                m_buckets.front().keys.emplace(key);
            }
            // update key map
            m_keyMap[key] = m_buckets.begin();
            return;
        }
        // update bucket
        auto itBucket = m_keyMap[key];
        itBucket->keys.erase(key);
        
        auto itNext = next(itBucket);
        if (itNext == m_buckets.end() || itNext->val > itBucket->val + 1) {
            // insert new node
            m_buckets.insert(itNext, { itBucket->val + 1, { key } });
        } else {
            // add key to next iterator
            itNext->keys.emplace(key);
        }
        // update keyMap
        m_keyMap[key] = next(itBucket);
        if (itBucket->keys.empty())
            m_buckets.erase(itBucket);
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if (m_keyMap.count(key) == 0)
            return;
        auto itBucket = m_keyMap[key];
        // erase key
        if (itBucket->val == 1) {
            itBucket->keys.erase(key);
            if (itBucket->keys.empty())
                m_buckets.erase(itBucket);
            m_keyMap.erase(key);
            return;
        }
        
        if (itBucket == m_buckets.begin() || prev(itBucket)->val < itBucket->val - 1) {
            m_buckets.insert(itBucket, { itBucket->val - 1, { key } });
        } else {
            prev(itBucket)->keys.emplace(key);
        }
        itBucket->keys.erase(key);
        m_keyMap[key] = prev(itBucket);
        if (itBucket->keys.empty())
            m_buckets.erase(itBucket);
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if (m_buckets.empty()) return "";
        return *m_buckets.back().keys.begin();
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if (m_buckets.empty()) return "";
        return *m_buckets.front().keys.begin();
    }
private:
    // bucket to keep all the keys with the same value
    struct Bucket { int val; unordered_set<string> keys; };
    using BucketList = list<Bucket>;
    BucketList m_buckets;
    // key map keeps key location
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
    /*
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
    */
    // ["AllOne","inc","inc","inc","inc","inc","inc","inc","inc","inc","inc","inc","inc","getMinKey"]
    // [[],["a"],["b"],["c"],["d"],["a"],["b"],["c"],["d"],["c"],["d"],["d"],["a"],[]]
    AllOne inst;
    inst.inc("a");
    inst.inc("b");
    inst.inc("c");
    inst.inc("d");
    inst.inc("a");
    inst.inc("b");
    inst.inc("c");
    inst.inc("d");
    inst.inc("c");
    inst.inc("d");
    inst.inc("d");
    inst.inc("a");
    
    std::cout << "getMaxKey: " << inst.getMaxKey() << std::endl;
    std::cout << "getMinKey: " << inst.getMinKey() << std::endl;
}
}
