/*
70. Climbing Stairs
You are climbing a stair case. It takes n steps to reach to the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/

#include <string>
#include <iostream>
#include "Common.h"

namespace DecodeWays
{
    int numDecodings(string s) {
        auto n = s.size();
        if (n < 1 || s[0] == '0') return 0;
        
        // num of ways for str ending at k - 1
        auto num_pre = 1;
        // num of ways for str ending at k - 2
        auto num_pre_pre = 1;
        
        for (auto k = 1; k < n; k++) {
            auto num = 0;
            if (s[k] != '0')
                num += num_pre;
            auto pre_ch = s[k - 1];
            if (pre_ch == '1' || (pre_ch == '2' && s[k] <= '6'))
                num += num_pre_pre;
            num_pre_pre = num_pre;
            num_pre = num;
        }
        return num_pre;
    }

  static void Test()
  {
    string input("12034");
    cout << input << " can have: " << numDecodings(input) << endl;
  }
}
