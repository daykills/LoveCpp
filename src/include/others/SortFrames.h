/*
油管每个视频的stream分成若干个frame，每个frame以开始时刻作为标记，传输的时候有可能out of order，比如[0 10 33 6 28 9 50 ...]，假设每个乱序的frame距离正确的位最多为K，问如何sort这个frame stream
*/

#include "Common.h"

namespace SortFrames
{
class Solution {
public:
    vector<int> sortFrames(vector<int>& frames, int k) {
        return {};
    }
};

static void Test()
{
    vector<int> frames {
        0, 10, 33,  6, 28,  9, 50
    //  0,  6,  9, 10, 28, 33, 50
    };
    Solution s;
    auto result = s.sortFrames(frames, 3);
    for (auto frame : result)
        cout << frame << endl;    // should be 8
}

}
