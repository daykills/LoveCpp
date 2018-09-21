#pragma once
/*
Given integer A and B, calculate how many numbers falling in range [A, B] are perfect squares of another int. Example  A = 4, B = 17, then return 3 because 2^2=4, 3^2=9, 4^2=16.
*/

#include <iostream>
#include <climits>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

namespace FindSquares
{
	vector<int> findSquares(int a, int b)
	{
		int num = (int)ceil(sqrt(a));
		int sqr = num * num;
		vector<int> result;
		while (sqr <= b)
		{
			result.emplace_back(sqr);
			sqr += 2 * num + 1; 
			num++;			
		}
		return result;
	}
	void Test()
	{
		int a = 3, b = 100;
		auto result = findSquares(a, b);
		cout << "a: " << a << " b: " << b << endl;
		cout << "Squares: " << endl;
		for (auto& square : result)
		{
			cout << square << " ";
		}
		cout << endl;
	}
}