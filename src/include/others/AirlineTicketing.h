/*
 You're building a tool to estimate the cost of various airplane tickets based on the airline, distance and seating class. Your tool must take in this information as a series of inputs (one ticket calculation per line of input) and produce a list of output costs.
 
 Each airline contains its own cost requirements. Ultimately, the airline is only interested in two major components: the space you take on the plane, and the distance you fly. You must generate estimates using this gathered data:
 
 Airlines: United, Delta, Southwest
 
 Operating Costs:
 
 - Economy:  No charge
 - Premium:  $25
 - Business: $50 + $0.25/mile
 
 Per-Airline Prices:
 
 - Delta charges $0.50/mile
 + OperatingCost
 
 - United charges $0.75/mile
 + OperatingCost
 + $0.10/mile for Premium seats
 
 - Southwest charges $1.00/mile
 
 
 Keep in mind that, while there are only three airlines listed above, your solution should be able to expand to dozens of individual airlines, most of which will base their adjustments in part on the "Operating Costs" above.
 
 Additional airlines could use arbitrary functions of miles and seating class. For example, "LuigiAir charges $100 or 2 * OperatingCost, whichever is higher."
 
 You can assume that the input will be provided as a list of strings and that there could be millions of lines of input. Each string will provide the Airline, Distance and Seating Class. Please review the examples below:
 
 Example Input:
 -------------------------------------------
 United 150.0 Premium
 Delta 60.0 Business
 Southwest 1000.0 Economy
 -------------------------------------------
 
 Example Output:
 -------------------------------------------
 152.50
 95.00
 1000.00
 -------------------------------------------
 
 Explanation of Output:
 -------------------------------------------
 152.50      (150.0 * (0.75 + 0.10) + 25)
 95.00       (60.0 * (0.50 + 0.25) + 50)
 1000.00     (1000.0 * 1.00)
 -------------------------------------------
 */

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include <cassert>

using namespace std;

const vector<string> input = {
    "United 150.0 Premium",
    "Delta 60.0 Business",
    "Southwest 1000.0 Economy"
};

namespace AirlineTicketing {

class TicketEstimator {
public:
    using operating_cost_type = function<float(float distance)>;
    using airline_cost_type = function<float(const string& seating, float distance)>;
    
    static TicketEstimator& inst() {
        static TicketEstimator s_inst;
        return s_inst;
    }

    float price(const string& airline, const string& seating, float distance) {
        assert(m_airlineCostMap.count(airline));
        return m_airlineCostMap[airline](seating, distance);
    }
    
    operating_cost_type getOperatingCostStrategy(const string& seating) {
        assert(m_operatingCostMap.count(seating));
        return m_operatingCostMap[seating];
    }
    
    void registerOperatingCostStrategy(const string& seating, function<float(float distance)> operatingCostBlock) {
        assert(m_operatingCostMap.count(seating) == 0);
        m_operatingCostMap.emplace(seating, operatingCostBlock);
    }
    
    void registerAirlinePricingStrategy(const string& airline, airline_cost_type airlinePricingBlock) {
        assert(m_airlineCostMap.count(airline) == 0);
        m_airlineCostMap.emplace(airline, airlinePricingBlock);
    }
    
protected:
    TicketEstimator() = default;
    unordered_map<string, operating_cost_type> m_operatingCostMap;
    unordered_map<string, airline_cost_type> m_airlineCostMap;
};

static void registerStrategies() {
    auto& esitmator = TicketEstimator::inst();
    /*
     - Economy:  No charge
     - Premium:  $25
     - Business: $50 + $0.25/mile
     */
    esitmator.registerOperatingCostStrategy("Economy", [](float distance) { return 0; });
    esitmator.registerOperatingCostStrategy("Premium", [](float distance) { return 25; });
    esitmator.registerOperatingCostStrategy("Business", [](float distance) { return 50 + 0.25 * distance; });
    
    /*
     Per-Airline Prices:
     - Delta charges $0.50/mile
     + OperatingCost
     
     - United charges $0.75/mile
     + OperatingCost
     + $0.10/mile for Premium seats
     
     - Southwest charges $1.00/mile
     */
    esitmator.registerAirlinePricingStrategy("Delta", [&esitmator](const string& seating, float distance) {
        return 0.5 * distance + esitmator.getOperatingCostStrategy(seating)(distance);
    });
    esitmator.registerAirlinePricingStrategy("United", [&esitmator](const string& seating, float distance) {
        return 0.75 * distance + esitmator.getOperatingCostStrategy(seating)(distance) + (seating == "Premium" ? 0.1 * distance : 0);
    });
    esitmator.registerAirlinePricingStrategy("Southwest", [&esitmator](const string& seating, float distance) {
        return distance;
    });
}

void estimateCost(const vector<string>& inputs) {
    auto& estimater = TicketEstimator::inst();
    for (auto& input : inputs) {
        string airline, seating;
        float distance = 0;
        istringstream is(input);
        is >> airline >> distance >> seating;
        cout << estimater.price(airline, seating, distance) << endl;
    }
}

void Test() {
    registerStrategies();
    /*
     Example Input:
     -------------------------------------------
     United 150.0 Premium
     Delta 60.0 Business
     Southwest 1000.0 Economy
     -------------------------------------------
     */
    vector<string> inputs {
        "United 150.0 Premium",
        "Delta 60.0 Business",
        "Southwest 1000.0 Economy",
    };
    /*
     Explanation of Output:
     -------------------------------------------
     152.50      (150.0 * (0.75 + 0.10) + 25)
     95.00       (60.0 * (0.50 + 0.25) + 50)
     1000.00     (1000.0 * 1.00)
     -------------------------------------------
     */
    estimateCost(inputs);
}
    
}// AirlineTicketing
