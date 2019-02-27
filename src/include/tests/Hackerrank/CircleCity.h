#pragma once
/*
https://www.hackerrank.com/challenges/circle-city

Given the square of radius, d(=r2)d(=r2), of the city, Roy has to determine if it is possible to protect all the suburbs.

Input Format
The first line of input contains integer tt; tt test cases follow.
Each of the next tt lines contains two space-separated integers: dd, the square of the radius of the city, and kk, the maximum number of police stations the headquarters is willing to build.

Constraints
1¡Üt¡Ü10^3
1¡Üd¡Ü2¡Á10^9
0¡Ük¡Ü2¡Á10^9

Output Format
For each test case, print in a new line possible if it is possible to protect all the suburbs;, otherwise, print impossible.

Sample Input

5
1 3
1 4
4 4
25 11
25 12
Sample Output

impossible
possible
possible
impossible
possible
Explanation

For d=1d=1, there are 44 points on circumference - [(0,1), (0,-1), (1,0), (-1,0)].
For d=4d=4, there are 44 points on circumference - [(0,2), (0,-2), (2,0),(-2,0)].
For d=25d=25, there are 1212 points on circumference - [(0,5), (0,-5), (3,4), (-3,4), (3,-4), (-3,-4), (4,3), (-4,3), (4,-3), (-4,-3), (5,0), (-5,0)].
Test Case #01: There are 44 suburbs on the border, while we are allowed to construct max k=3k=3 police stations.
Test Case #02: We can cover all the 44 suburbs as exactly 44 stations are allowed.
Test Case #03: We can cover all the 44 suburbs as exactly 44 stations are allowed.
Test Case #04: It is impossible to cover 1212 suburbs, on the border, with 1111 police stations.
Test Case #05: We can to cover all 1212 suburbs, on the border, with 1212 police stations.
*/

#include <iostream>
#include <climits>
#include <string>
#include <vector>
using namespace std;

namespace CircleCity
{
	int pointsWithinRadiusR(int r)
	{
		vector<int> sqares(20001, -1);
		return 0;
	}

	int Test()
	{
		string cur = "19b91";
		int r = 1;
		cout << "R: " << r << " Num of points: " << pointsWithinRadiusR(r) << endl;
		return 0;
	}
}