/*
460. LFU Cache

Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Note that the number of times an item is used is the number of calls to the get and put functions for that item since it was inserted. This number is set to zero when the item is removed.

Follow up:
Could you do both operations in O(1) time complexity?

*/

#include <string>
#include <iostream>
#include <unordered_map>
#include <list>
#include "Common.h"

namespace LFUCache
{
class LFUCache {
public:
    LFUCache(int capacity) : minFreq(0), size(capacity) {
        
    }
    
    int get(int key) {
        if (data.count(key) == 0 || size == 0)
            return -1;
        auto val = data[key].first;
        // update stored frequence
        auto freq = data[key].second++;
        // update old key list mapped with freq
        auto& keyListForFreq = freqMap[freq];
        auto oldIt = itMap[key];
        keyListForFreq.erase(oldIt);
        if (keyListForFreq.empty()) {
            freqMap.erase(freq);
            if (freq == minFreq)
                minFreq++;
        }
            
        // insert key to key list mapped by (freq + 1)
        freqMap[freq + 1].push_back(key);
        itMap[key] = prev(freqMap[freq + 1].end());
        return val;
    }
    
    void put(int key, int value) {
        if (size == 0) return;
        // key exists, update its value
        if (data.count(key)) {
            data[key].first = value;
            get(key);
            return;
        }
        // evict low freq one
        if (data.size() == size) {
            auto keyToRemove = freqMap[minFreq].front();
            freqMap[minFreq].pop_front();
            itMap.erase(keyToRemove);
            data.erase(keyToRemove);
        }
        // update data
        data[key] = { value, 1 };
        minFreq = 1;
        freqMap[1].push_back(key);
        itMap[key] = prev(freqMap[1].end());
    }
private:
    // minimum frequence of the cache
    int minFreq;
    // freqMap[frequence] -> list of keys with frequence
    unordered_map<int, list<int>> freqMap;
    // data[key] -> pair<val, frequency>
    unordered_map<int, pair<int, int>> data;
    // itMap[key] -> the iterator in freqMap[key]
    unordered_map<int, list<int>::iterator> itMap;
    const int size;
};


static void Test()
{
    /*
    LFUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);       // returns 1
    cache.put(3, 3);    // evicts key 2
    cache.get(2);       // returns -1 (not found)
    cache.get(3);       // returns 3.
    cache.put(4, 4);    // evicts key 1.
    cache.get(1);       // returns -1 (not found)
    cache.get(3);       // returns 3
    cache.get(4);       // returns 4
     */
    LFUCache cache(2);
    cache.put(2, 1);
    cache.put(1, 1);
    cache.put(2, 3);
    cache.put(4, 1);
    cache.get(1);
    cache.get(2);
}

}
#pragma once
