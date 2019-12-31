/*
 332. Reconstruct Itinerary

 Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.
 
 Note:
 
 If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary {"JFK", "LGA"} has a smaller lexical order than {"JFK", "LGB"}.
 All airports are represented by three capital letters (IATA code).
 You may assume all tickets form at least one valid itinerary.
 Example 1:
 
 Input: [{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}]
 Output: {"JFK", "MUC", "LHR", "SFO", "SJC"}
 Example 2:
 
 Input: [{"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}]
 Output: {"JFK","ATL","JFK","SFO","ATL","SFO"}
 Explanation: Another possible reconstruction is {"JFK","SFO","ATL","JFK","ATL","SFO"}.
 But it is larger in lexical order.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace ReconstructItinerary
{
vector<string> findItinerary(vector<vector<string>>& tickets) {
    vector<string> ans;
    if (tickets.empty()) return ans;
    unordered_map<string, multiset<string>> fromToMap;
    for (auto& fromTo : tickets)
        fromToMap[fromTo[0]].emplace(fromTo[1]);
    
    stack<string> s;
    s.push("JFK");
    while (!s.empty()) {
        auto& destinations = fromToMap[s.top()];
        // reaching a leaf. add it to itinerary.
        if (destinations.empty()) {
            ans.push_back(s.top());
            fromToMap.erase(s.top());
            s.pop();
            continue;
        }
        // recurse from the first dest to maintain lexical order
        auto itFirstDest = destinations.begin();
        s.push(*itFirstDest);
        destinations.erase(itFirstDest);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

void Test()
{
    vector<vector<string>> tickets = {
        {"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}
    };
    
    auto result = findItinerary(tickets);
    for (auto& ticket : result)
    {
        cout << ticket << endl;
    }
}
}
