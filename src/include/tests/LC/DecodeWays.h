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
        if (n == 0 || s[0] == '0')
            return 0;
        // num of ways when k = [0, n]
        // num_pre_pre is set as 1 it accounts for one possiblity
        int num_pre_pre = 1;
        // num_pre is initialized as 1 as s[0] != '0'
        int num_pre = 1;
        for (auto k = 1; k < n; k++) {
            auto num = 0;
            auto cur_ch = s[k];
            if (cur_ch != '0')
                num += num_pre;
            
            auto pre_ch = s[k - 1];
            if ((pre_ch == '2' && cur_ch <= '6') ||
                pre_ch == '1')
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
