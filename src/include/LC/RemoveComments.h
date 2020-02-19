/*    722. Remove Comments
 
 https://leetcode.com/problems/remove-comments/
 
 Given a C++ program, remove comments from it. The program source is an array where source[i] is the i-th line of the source code. This represents the result of splitting the original source code string by the newline character \n.

 In C++, there are two types of comments, line comments, and block comments.
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace RemoveComments
{
class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        vector<string> cleaned;
        bool isOpen = false;
        string halfLine;
        for (auto& line : source) {
            if (isOpen) {
                
            } else {
                auto posLine = line.find("//");
                auto posBlock = line.find("/*");
                if (posLine == string::npos && posBlock == string::npos) {
                    cleaned.push_back(line);
                    continue;
                }
                
                if (posBlock == string::npos) {
                    
                }
                    || posLine != string::npos) {
                    
                }
            }
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////
void Test()
{
    vector<string> source = {
        "/*Test program */",
        "int main()",
        "{ ",
        "  // variable declaration ",
        "int a, b, c;",
        "/* This is a test",
        "   multiline  ",
        "   comment for ",
        "   testing */",
        "a = b + c;",
        "}"
    };
    Solution s;
    auto cleaned = s.removeComments(source);
    for (auto& line : cleaned)
        cout << line << endl;
}
}
