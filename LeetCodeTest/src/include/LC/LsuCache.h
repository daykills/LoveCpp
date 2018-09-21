/*
146. LRU Cache My Submissions Question
Total Accepted: 66996 Total Submissions: 425786 Difficulty: Hard
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

*/

#include <string>
#include <iostream>
#include <unordered_map>
#include "Common.h"

namespace LsuCache
{
	class LRUCache {
	public:
		LRUCache(int capacity) : m_capacity(capacity)
		{}

		int get(int key)
		{
			auto it = m_table.find(key);
			if (it == m_table.end()) return -1;

			auto value_it = it->second;
			// move value iter to the front
			m_data.splice(m_data.begin(), m_data, value_it);
			
			Print();
			
			return value_it->value;
		}

		void set(int key, int value)
		{
			auto it = m_table.find(key);
			if (it == m_table.end())
			{
				// remove the element in the back when list is full
				if (m_data.size() == m_capacity)
				{
					m_table.erase(m_data.back().key);
					m_data.pop_back();
				}
				// insert the element
				m_data.emplace_front(key, value);
				m_table.emplace(key, m_data.begin());
			}
			else
			{
				m_data.splice(m_data.begin(), m_data, it->second);
				m_data.begin()->value = value;
			}
			Print();
		}

	private:
		struct Node
		{
			int key;
			int value;
			Node(int _key, int _value) : key(_key), value(_value) {}
		};
		void Print()
		{
			cout << "data: ";
			for (auto& node : m_data)
			{
				cout << "[" << node.key << ", " << node.value << "] ";
			}
			cout << endl;
		}
		unordered_map<int, list<Node>::iterator> m_table;
		int m_capacity;
		list<Node> m_data;
	};

	static void Test()
	{
		LRUCache cache(2);
		cache.set(1, 100);
		cache.set(2, 200);
		cache.set(3, 300);
		cache.get(2);
		cache.set(4, 400);
		cache.set(2, 201);
		cache.set(5, 500);
	}
}
#pragma once
