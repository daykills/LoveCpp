/*
 https://docs.microsoft.com/en-us/dotnet/api/system.threading.readerwriterlock?view=netframework-4.8
 Defines a lock that supports single writers and multiple readers.
 */

#include "Common.h"

namespace ReaderWriterLock {

class ReaderWriterLock {
public:
    ReaderWriterLock() = default;
    ~ReaderWriterLock() = default;
private:
};

constexpr int kNumThreads = 26;
static bool sRunning = true;
static int sResource = 0;

static void readerProc(int i)
{
    // Randomly select a way for the thread to read and write from the shared
    // resource.
    cout << "Read: " << i << endl;
}

static void Test() {
    vector<thread> threads;
    for (auto i = 0; i < kNumThreads; i++) {
        threads.emplace_back(readerProc, i);
    }
    
    for (auto i = 0; i < kNumThreads; i++) {
        threads[i].join();
    }
}

}
