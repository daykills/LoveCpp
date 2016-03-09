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

TEST(Set4Advanced, IfDependencyIsUpdatedDuringEvaluationThenCalculatedIsEvaluatedAgainButNotConcurrently)
{
    // run this test in a thread so that we can timeout if there is a deadlock
    auto t = std::async(std::launch::async, [&]
    {
        auto o = create(100);
        bool doUpdate = true;
        bool evaluating = false;
        int count = 0;
        auto c = create([&]()
            {
                EXPECT_FALSE(evaluating);
                evaluating = true;
                ++count;

                auto result = o->getValue();

                // One should never actually write code like this.  The evaluator function
                // should be pure (no side-effects)
                if (doUpdate)
                {
                    doUpdate = false;
                    // Update the value, which should trigger another evaluation after this one.
                    o->setValue(result + 1);
                }

                evaluating = false;
                return result;
            },
            [](int) {});

        EXPECT_EQ(2, count);
        EXPECT_EQ(101, c->getValue());

        o->setValue(0);
        EXPECT_EQ(3, count);
        EXPECT_EQ(0, c->getValue());

        doUpdate = true;
        o->setValue(-100);
        EXPECT_EQ(5, count);
        EXPECT_EQ(-99, c->getValue());
    });

    auto result = t.wait_for(std::chrono::seconds(5));
    EXPECT_TRUE(result == std::future_status::ready) << "Deadlock detected.";
}

// One thread will change the value after the other thread has read it but before it has finished
// calculating
TEST(Set4Advanced, IfDependencyIsUpdatedByOtherThreadWhileEvaluatingThenCalculatedIsEvaluatedAgainButNotConcurrently)
{
    auto o = create(100);
    bool wait = true;
    std::atomic_bool evaluating(false);
    std::atomic_int evalcount(0);
    int count = 0;
    std::atomic_int barrier(0);
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
    std::unique_ptr<IDynamicProperty<int>> c;

    // Launch a thread to create the calculated property
    // while it is reading "o", another thread will change the value
    auto changeValue = [&]()
    {
        // wait for the calculation thread to have read the value
        waitForBarrier(barrier);
        o->setValue(o->getValue() + 1);
    };

    auto t1 = std::async(std::launch::async, [&]
        {
            c = create([&]()
                {
                    if (evaluating.exchange(true)) ++evalcount;
                    ++count;

                    auto result = o->getValue();

                    if (wait)
                    {
                        wait = false;
                        waitForBarrier(barrier);
                        // give the other thread time to finish its work.
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    }

                    if (!evaluating.exchange(false)) ++evalcount;
                    return result;
                },
                [](int) { });
        });

    auto t2 = std::async(std::launch::async, changeValue);

    t1.wait();
    t2.wait();

    EXPECT_EQ(0, evalcount.load());
    EXPECT_EQ(0, deadlock.load());
    EXPECT_EQ(2, count);
    EXPECT_EQ(101, o->getValue());
    EXPECT_EQ(101, c->getValue());

    o->setValue(0);
    EXPECT_EQ(3, count);
    EXPECT_EQ(0, c->getValue());

    // Spin up a thread to change the value
    // then, we will change the value ourselves to trigger the first
    // evaluation which will ultimately trigger a 2nd when changeValue thread runs.
    wait = true;
    barrier.store(0);
    auto t3 = std::async(std::launch::async, changeValue);
    o->setValue(-100);
    t3.wait();

    EXPECT_EQ(0, evalcount.load());
    EXPECT_EQ(0, deadlock.load());
    EXPECT_EQ(5, count);
    EXPECT_EQ(-99, c->getValue());
};
