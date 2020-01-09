/*
 278. First Bad Version

 You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.
 
 Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
 
 You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.
 
 Example:
 
 Given n = 5, and version = 4 is the first bad version.
 
 call isBadVersion(3) -> false
 call isBadVersion(5) -> true
 call isBadVersion(4) -> true
 
 Then 4 is the first bad version.
 */

#include "Common.h"

int kFirstBadVersion;

namespace FirstBadVersion
{
bool isBadVersion(int version) {
    return version >= kFirstBadVersion;
}

class Solution {
public:
    int firstBadVersionSTL(int n) {
        assert(isBadVersion(n) == true);
        // visited[i]: 0, not visited; 1, true; -1, false
        vector<int> visited(n + 1, 0);
        auto lessor = [&visited, this](int i, int j) {
            bool ansI = visited[i] ? visited[i] > 0 : isBadVersion(i);
            visited[i] = ansI ? 1 : -1;
            
            bool ansJ = visited[j] ? visited[j] > 0 : isBadVersion(j);
            visited[j] = ansJ ? 1 : -1;
            // good ones before bad ones
            return ansI == false && ansJ == true;
        };
        vector<int> checks(n, 0);
        for (auto i = 0; i < n; i++)
            checks[i] = i + 1;
        auto it = lower_bound(checks.begin(), checks.end(), n, lessor);
        return distance(checks.begin(), it) + 1;
    }
    
    int firstBadVersion(int n) {
        long lo = 1;
        long hi = n;
        while (lo < hi) {
            auto mid = (lo + hi) / 2;
            if (isBadVersion(mid)) {
                // if already the first version
                if (mid == 1) return mid;
                if (!isBadVersion(mid - 1)) {
                    return mid;
                } else {
                    hi = mid - 1;
                }
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }
};

int kFirstBadVersion = 4;

static void Test()
{
    int n = 5;
    Solution solution;
    std::cout << solution.firstBadVersion(n) << std::endl;
}
}
