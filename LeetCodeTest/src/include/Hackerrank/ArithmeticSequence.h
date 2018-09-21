#pragma once
/*
Give array, return the number of possible arithmetic sequence {-1,1,3,3,3,2,1,0} return 5
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace ArithmeticSequence
{
	int numArithmeticSequence(vector<int>)
	{
		return 0;
	}

	void Test()
	{
		vector<int> nums{ -1,1,3,3,3,2,1,0 };
		cout << " Num of ArithmeticSequence: " << numArithmeticSequence(nums) << endl;
	}
}