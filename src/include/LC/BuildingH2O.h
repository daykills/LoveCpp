/*
 https://leetcode.com/problems/building-h2o/discuss/360839/C%2B%2B-futurepromise-releases-3-in-one-group-as-required
 1117. Building H2O
 
 There are two kinds of threads, oxygen and hydrogen. Your goal is to group these threads to form water molecules. There is a barrier where each thread has to wait until a complete molecule can be formed. Hydrogen and oxygen threads will be given releaseHydrogen and releaseOxygen methods respectively, which will allow them to pass the barrier. These threads should pass the barrier in groups of three, and they must be able to immediately bond with each other to form a water molecule. You must guarantee that all the threads from one molecule bond before any other threads from the next molecule do.
 
 In other words:
 
 If an oxygen thread arrives at the barrier when no hydrogen threads are present, it has to wait for two hydrogen threads.
 If a hydrogen thread arrives at the barrier when no other threads are present, it has to wait for an oxygen thread and another hydrogen thread.
 We don’t have to worry about matching the threads up explicitly; that is, the threads do not necessarily know which other threads they are paired up with. The key is just that threads pass the barrier in complete sets; thus, if we examine the sequence of threads that bond and divide them into groups of three, each group should contain one oxygen and two hydrogen threads.
 
 Write synchronization code for oxygen and hydrogen molecules that enforces these constraints.
 
 
 
 Example 1:
 
 Input: "HOH"
 Output: "HHO"
 Explanation: "HOH" and "OHH" are also valid answers.
 Example 2:
 
 Input: "OOHHHH"
 Output: "HHOHHO"
 Explanation: "HOHHHO", "OHHHHO", "HHOHOH", "HOHHOH", "OHHHOH", "HHOOHH", "HOHOHH" and "OHHOHH" are also valid answers.
 
 
 Constraints:
 
 Total length of input string will be 3n, where 1 ≤ n ≤ 20.
 Total number of H will be 2n in the input string.
 Total number of O will be n in the input string.
 */


#include "Common.h"

namespace BuildingH2O
{

mutex s_mut;
vector<char> s_result;
void releaseHydrogen() {
    s_result.push_back('H');
}

void releaseOxygen() {
    s_result.push_back('O');
}
/* future / promis

class H2O {
public:
    H2O(){
    }

    void hydrogen(function<void()> releaseHydrogen) {
        process(m_hPromiseQ).get();
        lock_guard<mutex> lck(m_mut2);
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
    }

    void oxygen(function<void()> releaseOxygen) {
        process(m_oPromiseQ).get();
        lock_guard<mutex> lck(m_mut2);
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
    }
    
private:
    
    future<void> process(queue<promise<void>>& q) {
        lock_guard<mutex> lck(m_mut);
        q.emplace();
        future<void> f = q.back().get_future();
        if (m_hPromiseQ.size() >= 2 && m_oPromiseQ.size() >= 1) {
            m_hPromiseQ.front().set_value(); m_hPromiseQ.pop();
            m_hPromiseQ.front().set_value(); m_hPromiseQ.pop();
            m_oPromiseQ.front().set_value(); m_oPromiseQ.pop();
        }
        return f;
    }
    
    queue<promise<void>> m_oPromiseQ;
    queue<promise<void>> m_hPromiseQ;
    
    mutex m_mut;
    mutex m_mut2;
};
 */

class H2O {
public:
    H2O() : m_hCnt(0) {
    }

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex> lck(m_mut);
        m_cvH.wait(lck, [this]() {
            return m_hCnt < 2;
        });
        m_hCnt++;
        m_cvO.notify_one();
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex> lck(m_mut);
        m_cvO.wait(lck, [this]() {
            return m_hCnt == 2;
        });
        m_hCnt -= 2;
        m_cvH.notify_one();
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
    }
    
private:
    
    atomic<int> m_hCnt;
    condition_variable m_cvO;
    condition_variable m_cvH;
    mutex m_mut;
};

static void Test()
{
    string input = "HHHHHHHHHHOHHOHHHHOOHHHOOOOHHOOHOHHHHHOOHOHHHOOOOOOHHHHHHHHH";
    vector<thread> workers;
    H2O h2o;
    for (auto i = 0; i < input.size(); i++) {
        auto element = input[i];
        workers.push_back(std::thread([&h2o, element]()
                                      {
            std::mt19937_64 eng{std::random_device{}()};  // or seed however you want
            std::uniform_int_distribution<> dist{1, 100};
            std::this_thread::sleep_for(std::chrono::milliseconds{dist(eng)});
            if (element == 'O')
                h2o.oxygen(releaseOxygen);
            else
                h2o.hydrogen(releaseHydrogen);
        }));
    }
    std::for_each(workers.begin(), workers.end(), [](std::thread &t)
                  {
        t.join();
    });
    int hCnt = 0;
    int oCnt = 0;
    for (auto i = 0; i < s_result.size(); i++) {
        if (s_result[i] == 'H')
            hCnt++;
        else
            oCnt++;
        cout << s_result[i];
        if (i % 3 == 2) {
            cout << "_";
            if (oCnt * 2 != hCnt)
                cout << "X";
        }
    }
    cout << endl;
}
}
