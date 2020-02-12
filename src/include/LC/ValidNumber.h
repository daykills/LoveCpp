/*
65. Valid Number My Submissions Question
Total Accepted: 42391 Total Submissions: 354486 Difficulty: Hard
Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
Note: It is intended for the problem statement to be ambiguous.
You should gather all requirements up front before implementing one.

Update (2015-02-10):
The signature of the C++ function had been updated.
If you still see your function signature accepts a const char * argument, please click the reload button  to reset your code definition.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace ValidNumber
{
  bool isNumber(string s){
    bool numberStarted = false;
    bool isDecimal = false;
    bool sign = false;
    bool numberEnded = false;
    // states for scientific
    bool isScientific = false;
    bool numberStartedExponential = false;
    bool signExponential = false;
    bool isDecimalExponential = false;

    for (auto ch : s)
    {
      // handle white spaces
      if (ch == ' ')
      {
        // white space following '.'
        if (isDecimal && !numberStarted) return false;
        // white space following '+/-'
        if (sign && !numberStarted) return false;
        // before and after number, we can have white spaces
        if (numberEnded || !numberStarted) continue;
        // mark the end of number
        numberEnded = true;
        continue;
        // otherwise return false;
        return false;
      }

      // handle sign
      if (ch == '-' || ch == '+')
      {
        // duplicate sign
        if (isScientific)
        {
          if (numberStartedExponential || signExponential || isDecimalExponential) return false;
          signExponential = true;
        }
        else
        {
          if (numberStarted || sign || isDecimal) return false;
          sign = true;
        }
        continue;
      }

      // handle decimal
      if (ch == '.')
      {
        // if no integer part or decimal is already detected, return false
        if (numberEnded || isDecimal || isScientific) return false;
        // mark number as decimal
        isDecimal = true;
        continue;
      }

      // handle exponential
      if (ch == 'e')
      {
        // e is already detected, or there is no regular numeric part, or number ended already
        if (isScientific || !numberStarted || numberEnded) return false;

        isScientific = true;
        continue;
      }

      // number is ended with white space
      if (numberEnded) return false;

      // get digital number
      int num = (int)(ch - '0');
      if (num < 0 || num > 9) return false;
      numberStarted = true;
      // mark for scientific
      if (isScientific) numberStartedExponential = true;
    }
    return isScientific ? numberStartedExponential : numberStarted;
  }

  static void Test()
  {
    cout << "result is " << isNumber("   +0 123") << endl;
  }
}