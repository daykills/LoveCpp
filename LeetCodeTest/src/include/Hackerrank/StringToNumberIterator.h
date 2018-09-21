#pragma once

/*
Read from istream to an iterator that can print valid numbers one by one

137
-104
2 58
+0
++3
+1
23.9
2000000000
-0
five
-1
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace StringToNumberIterator
{
	class Solution {

	public:
		class iterator
		{
		public:
			iterator(vector<int>& numbers, int pos) : m_numbers(numbers), m_pos(pos)
			{}

			int operator*() const
			{
				return m_numbers[m_pos];
			}

			iterator operator +(int offset) const
			{
				auto pos = m_pos + offset;
				// to ensure the pos is within range of 0 ~ m_numbers.size()
				pos = max(pos, 0);
				pos = min((int)m_numbers.size(), pos);
				iterator it(m_numbers, pos);
				return it;
			}
			iterator operator ++()
			{
				iterator it = *this + 1;
				m_pos = it.m_pos;
				return it;
			}
			bool operator ==(const iterator& other) const
			{
				return other.m_pos == m_pos;
			}
			bool operator !=(const iterator& other) const
			{
				return !(*this == other);
			}
		private:
			vector<int>& m_numbers;
			int m_pos;
		};

		Solution(istream& s)
		{
			m_numbers.clear();
			while (!s.eof())
			{
				string line;
				getline(s, line);
				int result = 0;
				if (parse(line, result))
					m_numbers.emplace_back(result);
			}
		}
		iterator begin()
		{
			iterator it(m_numbers, 0);
			return it;
		}
		iterator end()
		{
			iterator it(m_numbers, m_numbers.size());
			return it;
		}
	private:
		bool parse(const string& line, int& result)
		{
			if (line.empty()) return false;
			result = 0;
			int sign = 1;
			bool signFound = false;
			bool numberStarted = false;
			for (auto ch : line)
			{
				if (ch == ' ')
				{
					if (signFound) return false;
					else continue;
				}

				// to detect the sign
				if (ch == '-' || ch == '+')
				{
					// duplicate sign detected
					if (signFound) return false;
					sign = (ch == '+') ? 1 : -1;
					signFound = true;
					continue;
				}
				// check whether it's a number, or number started with 0
				int num = (int)(ch - '0');
				if (num < 0 || num > 9)
				{
					return false;
				}

				// set signFound whenever a number is detected
				signFound = true;

				// calculate result
				result = result * 10 + num * sign;

				// check overflow
				if (sign == 1 && result > 1000000000)
				{
					return false;
				}
				else if (sign == -1 && result < -1000000000)
				{
					return false;
				}
			}
			return true;
		}
		vector<int> m_numbers;
	};

	void Test() {
		string m_filename = "data\\string_array_data.txt";
		shared_ptr<istream> input;
		input.reset(new ifstream(m_filename), [](std::ifstream* ptr) { ptr->close(); });

		Solution sol(*input);
		for (Solution::iterator it = sol.begin(); it != sol.end(); ++it)
		{
			int x = *it;
			cout << x << endl;
		}
	}
}