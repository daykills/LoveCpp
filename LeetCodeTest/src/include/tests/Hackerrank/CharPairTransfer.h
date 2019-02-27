#pragma once

/*
Define a mapping from char-pairs to a single char.
Given a destination string, check whether another string can be transformed into the destination string.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace CharPairTransfer
{
	class Solver
	{
	public:
		Solver() {}

		bool validate(const string& str)
		{
			dfsValidate(str);
			return m_resultCache[str];
		}

		void setTarget(const string& target)
		{
			// whenever resetting target, clear cache
			m_target = target;
			m_resultCache.clear();
		}

		void addMapping(const string& pair, const string& encoded)
		{
			assert(pair.length() == 2);
			auto& mapping = m_matrix[pair];
			mapping.append(encoded.begin(), encoded.end());
		}
		void print()
		{
			for (const auto& pair : m_matrix)
			{
				cout << "Char pair: " << pair.first << ", converted to: " << pair.second << endl;
			}
		}
	private:
		void dfsValidate(const string& path)
		{
			// if this path is already traversed
			if (m_resultCache.count(path)) return;
			// set the result as false first
			m_resultCache[path] = false;
			// base condition: when path is as long as the target string
			if (path.length() <= m_target.length())
			{
				m_resultCache[path] = (path == m_target);
				return;
			}
			// path.length > m_target.length() >= 0
			// transfer char-pairs
			for (int i = 0; i < (int)path.length() - 1; i++)
			{
				auto pair = path.substr(i, 2);
				if (m_matrix.count(pair) == 0) continue;
				//get a new string, let i and i+1 replaced by ch
				auto newPath = path;
				newPath.erase(i, 1);
				auto& mapping = m_matrix[pair];
				for (auto ch : mapping)
				{
					newPath[i] = ch;
					dfsValidate(newPath);
					if (m_resultCache[newPath])
					{
						m_resultCache[path] = true;
						return;
					}
				}
			}
		}
		unordered_map<string, bool> m_resultCache;
		unordered_map<string, string> m_matrix;
		string m_target;
	};

	static void Test()
	{
		Solver solver;
		solver.addMapping("aa", "b");
		solver.addMapping("ab", "ac");
		solver.addMapping("ac", "d");
		solver.addMapping("ad", "a");
		solver.addMapping("ba", "d");
		solver.addMapping("bb", "bc");
		solver.addMapping("bc", "a");
		solver.print();
		solver.setTarget("cd");
		cout << solver.validate("abd");
	}
}