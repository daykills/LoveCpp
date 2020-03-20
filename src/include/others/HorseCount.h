/* ===============================================================
 There are a lot of horses in the yard, and we want to count how many there are.  Unfortunately, we've only got a recording of the sounds from the yard.  All the horses say "neigh".  The problem is they can "neigh" many times.  The recording from the yard is sadly all mixed together.  So, we need to figure out from the overlapping sounds how many horses there could be.

 For example, we've got two horses in the yard, and we hear this "neigneighh".  From this recording, we can successfully deduce there are 2 horses.  Another example is "neighneigh".  From this example, we can only tell there is one horse in the yard.

 As an additional complexity, our recording might not be perfect.  If it's a bad recording, we should give "Invalid" as the response.

 The input will be given as a string on one line.  The output should be printed on it's own line.

 Sample Input
 nenigehnieighgh

 nenieighgh

 Sample Output
 2
 */

#include "Common.h"

// ==============================================================
namespace HorseCount {

int horseCount(const string& voice) {
    const char kStart = 'n';
    const char kEnd = 'h';
    unordered_map<char, int> chatToInd {
        { kStart, 0 },
        { 'e', 1 },
        { 'i', 2 },
        { 'g', 3 },
        { kEnd, 4 },
    };
    
    vector<int> count(chatToInd.size() - 1, 0);
    int maxCount = 0;
    for (auto c : voice) {
        auto i = chatToInd[c];
        if (c == kStart) {
            count[i]++;
        } else {
            if (c == kEnd) {
                int totalCount = 0;
                for (auto n : count) {
                    totalCount += n;
                }
                maxCount = max(maxCount, totalCount);
            } else {
                count[i]++;
            }
            count[i - 1]--;
        }
    }
    return maxCount;
}

// ==============================================================
// Main Function: Enable/Disable methods to run each exercise
void Test() {
    cout << horseCount("neighneigh") << endl;
}

}
