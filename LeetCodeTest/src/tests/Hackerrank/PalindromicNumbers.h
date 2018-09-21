#pragma once
/*
The number 131071 = 2^17 - 1 has two interesting properties:
(1)  Its base-17 representation, (19b91)17, is palindromic (reading the same backward as forward).
(2)  Its base-2 representation, (11111111111111111)2, has a run of at least 17 consecutive 1 bits.
What is the next number with both of these properties?
*/

#include <iostream>
#include <climits>
#include <string>
#include <vector>
#include <list>

using namespace std;

namespace PalindromicNumbers
{
	class PalindromicNumberSolver
	{
	public:
		PalindromicNumberSolver(const string& curNumber) : m_curNumber(curNumber)
		{
			auto num = toNum(curNumber);
			auto numStr = toStr(num);
			cout << "Original: " << curNumber << " Integer: " << num << " String: " << numStr << endl;
		}
		unsigned long long solve()
		{
			string cur = m_curNumber;
			while (true)
			{
				auto next = findNextPalindromic(cur);
			}
		}
	private:
		const string m_curNumber;
		// get the number of maximum consecutive '1' bits
		int numOfConsecutiveOnes(unsigned long long num)
		{
			int count = 0;
			while (num)
			{
				num = (num & (num << 1));
				count++;
			}
			return count;
		}
		// convert base-17 number from string to decimal integer
		unsigned long long toNum(const string& input)
		{
			const int base = 17;
			unsigned long long result = 0;
			for(auto digit : input)
			{
				if (isdigit(digit))
					result = result * base + digit - '0';
				else
					result = result * base + (digit - 'a' + 10);
			}
			return result;
		}
		// convert the integer number to base-17 number as string
		string toStr(unsigned long long num)
		{
			const int base = 17;
			if (num == 0) return "0";
			// use list<char> to avoid expensive insertion in the loop if use std::string
            std::list<char> result;
			while (num)
			{
				int digit = num % base;
				char ch = (digit < 10) ? digit + '0' : (digit - 10) + 'a';
				result.insert(result.begin(), ch);
				num = num / base;
			}
			return string(result.begin(), result.end());
		}
		string findNextPalindromic(const string& cur)
		{
            throw;
		}
	};

	int Test() {
		string cur = "19b91";
		PalindromicNumberSolver solver(cur);
		return 0;
	}
}

namespace PalindromicNumbersOther
{

	/**
	* algorithm class to find the number with:
	* 1) base of 17 representation is palindrome
	* 2) base of 2 representation has 17 consective 1 bits
	*/
	class findNextPNumber {
	public:
		/**
		* @string input, input string representing a number using 17 as base
		*       which has p form
		* @return unsigned long long, return the next 17 based palidoromed number
		*           which has at least 17 consecutive 1 bits
		*/
		unsigned long long findNextPNumber17Bits(const string& input) {
			string cur = input;
			string next;
			while (1) {
				next = nextPNumber(cur);
				unsigned long long num = decode(next);
				if (num == ULLONG_MAX) //
					return 0;
				if (count_consecutive_ones(num) >= 17) {
					return num;
				}
				cur = next;
			}
			return 0;
		}
	private:
		/**
		* Test if an input string contains all 'G's (16)
		* if all is 'G', return true
		* else return false
		*/
		bool isAll16s(const string &num) {
			int n = num.size();
			for (int i = 0; i < n; i++) {
				if (num[i] != 'g')
					return false;
			}
			return true;
		}
		;
		/**
		*  input a string with 17 as base and output
		*  the value as 10 base
		*/
		unsigned long long decode(const string& in) {
			unsigned long long result = 0;
			int n = in.size();
			for (int i = 0; i < n; i++) {
				if (isdigit(in[i]))
					result = result * 17 + in[i] - '0';
				else
					result = result * 17 + (10 + in[i] - 'a');
			}
			return result;
		}
		;

		/**
		*  count the maximum consecutive bits of 1s
		*/
		int count_consecutive_ones(unsigned long long input) {
			int count = 0;
			while (input) {
				input = (input & (input << 1));
				count++;
			}
			return count;
		}

		/**
		* generate next p number
		*/
		string nextPNumber(const string& num)
		{
			if (isAll16s(num))
				return '1' + string(num.size(), '0') + '1';
			int n = num.size();
			int mid = n / 2;
			int carry = 1;
			
			vector<int> nums(n);
			// decode of special chars
			for (int i = 0; i < n; i++) {
				if (isdigit(num[i]))
					nums[i] = num[i] - '0';
				else
					nums[i] = 10 + num[i] - 'a';
			}
			int j;
			// If there are odd digits, then increment
			// the middle digit and store the carry
			if (n % 2 == 1) {
				nums[mid] += carry;
				carry = nums[mid] / 17;
				nums[mid] %= 17;
				j = mid + 1;
			}
			else
				j = mid;

			// Add 1 to the rightmost digit of the left side, propagate the carry
			// towards MSB digit and simultaneously copying mirror of the left side
			// to the right side.
			int i = mid - 1;
			while (i >= 0) {
				nums[i] += carry;
				carry = nums[i] / 17;
				nums[i] %= 17;
				nums[j++] = nums[i--]; // copy mirror to right
			}
			// encode to special chars
			string result;
			for (int i = 0; i < n; i++) {
				if (nums[i] < 10)
					result += (nums[i] + '0');
				else
					result += (nums[i] - 10 + 'a');
			}
			return result;
		}
	};

	int Test() {
		string cur = "19b91";
		findNextPNumber solver;
		cout << solver.findNextPNumber17Bits(cur) << endl;
		return 0;
	}
}
