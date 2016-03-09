#include "gtest/gtest.h"

#include <string>
#include <memory>
#include <array>
#include <future>
#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>
#include "DynamicProperty.h"

using namespace CppTest;

namespace
{
    template <typename T> std::unique_ptr<IDynamicProperty<T>> create(T value)
    {
        return std::unique_ptr<IDynamicProperty<T>>(DynamicProperty::create(value));
    }

    template <typename R, typename W> std::unique_ptr<IDynamicProperty<int>> create(R read, W write)
    {
        std::function<int()> r = read;
        std::function<void(int)> w = write;
        return std::unique_ptr<IDynamicProperty<int>>(DynamicProperty::create(r, w));
    }
}


TEST(Set3Intermediate, ReleasesDependenciesNotUsedInSubsequentReads)
{
    std::array<std::unique_ptr<IDynamicProperty<int>>, 3> values {{ create(42), create(99), create(2012) }};
    std::array<int, 3> readCounts {{ 0, 0, 0 }};
    std::array<int, 3> expected {{ 0, 0, 0 }};
    auto which = create(0); // index into values

    // will take on value[which]
    auto p = create([&]()
        {
            readCounts[which->getValue()]++;
            return values[which->getValue()]->getValue();
        },
        [](int) { });

    expected[0]++;
    EXPECT_EQ(expected, readCounts);

    values[1]->setValue(100); // no effect
    EXPECT_EQ(expected, readCounts);

    which->setValue(2);
    expected[2]++;
    EXPECT_EQ(expected, readCounts);

    values[0]->setValue(10); // no effect
    EXPECT_EQ(expected, readCounts);
}

TEST(Set3Intermediate, CalculatedsEvaluatedOnDifferentThreadsShouldNotCaptureEachOthersDependencies)
{
    auto oa = create(100);
    auto ob = create(1000);
    bool wait = true;
    std::atomic_int barrier1(0);
    std::atomic_int barrier2(0);
    std::atomic_int deadlock(0);
    auto waitForBarrier = [&](std::atomic_int & b)
    {
        ++b;

        std::chrono::milliseconds delay(100);
        int count = 0;
        while (b.load() != 2)
        {
            if (++count > 20)
            {
                ++deadlock;
                return;
            }

            std::this_thread::sleep_for(delay);
        }
    };

    std::unique_ptr<IDynamicProperty<int>> a, b;

    // Launch a thread to create a
    // B will do the same.
    // Both creates will block on a synchronization variable
    // to ensure that both threads access their separate observable values
    // "concurrently".
    // Then we can check to see if they captured each others dependencies on accident.
    auto ta = std::async(std::launch::async, [&]
        {
            a = create([&]()
                {
                    // wait for thread b to get inside its read method also
                    if (wait)
                    {
                        waitForBarrier(barrier1);
                    }

                    auto result = oa->getValue();

                    // wait for thread b to have accessed ob.
                    if (wait)
                    {
                        waitForBarrier(barrier2);
                    }

                    return result;
                },
                [](int) { });
        });

    // create b in a thread also
    auto tb = std::async(std::launch::async, [&]
        {
            b = create([&]()
                {
                    EXPECT_EQ(true, wait); // we should never evaluate after the first time.  If we evaluate again, then it is because we captured oa as a dependency
                    if (wait)
                    {
                        waitForBarrier(barrier1);
                    }

                    auto result = ob->getValue();

                    if (wait)
                    {
                        waitForBarrier(barrier2);
                    }

                    return result;
                },
                [](int) { });
        });

    // Wait for both threads to complete
    // C++11 doesn't have a waitAll(ta, tb) method
    ta.wait();
    tb.wait();

    EXPECT_EQ(0, deadlock.load());
    EXPECT_EQ(100, a->getValue());
    EXPECT_EQ(1000, b->getValue());

    wait = false;
    oa->setValue(-100); // should only trigger update on a
    EXPECT_EQ(-100, a->getValue());
    EXPECT_EQ(1000, b->getValue());
}

