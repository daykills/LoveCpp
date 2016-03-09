#include "gtest/gtest.h"

#include <string>
#include <memory>
#include <array>
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

TEST(Set2BasicCalculatedProperties, ReadFunctionIsEvaluatedExactlyOnceDuringConstruction)
{
    int evalCount = 0;
    auto p = create([&]() { return ++evalCount; }, [](int) { ADD_FAILURE(); });
    EXPECT_EQ(1, evalCount);
}

TEST(Set2BasicCalculatedProperties, InitialValueIsResultOfReadFunction)
{
    int evalCount = 0;
    auto p = create([&]() { return ++evalCount; }, [](int) { ADD_FAILURE(); });
    EXPECT_EQ(1, p->getValue());
}

TEST(Set2BasicCalculatedProperties, ReadingValueShouldNotTriggerAnotherEvaulation)
{
    int evalCount = 0;
    auto p = create([&]() { return ++evalCount; }, [](int) { ADD_FAILURE(); });
    EXPECT_EQ(1, p->getValue());
    EXPECT_EQ(1, evalCount);
}

TEST(Set2BasicCalculatedProperties, WhenWriteMethodDoesNothingReadIsNotTriggered)
{
    int evalCount = 0;
    auto p = create([&]() { return ++evalCount; }, [](int) { });
    std::list<int> notifications;
    p->subscribe([&](int v) { notifications.push_back(v); });
    p->setValue(10); // should do nothing since our write method does nothing
    EXPECT_EQ(1, p->getValue());
    EXPECT_EQ(1, evalCount);
    EXPECT_EQ(std::list<int>(), notifications); // notification was not sent out
}

TEST(Set2BasicCalculatedProperties, WhenWriteMethodDoesNotModifyDynamicPropertyReadIsNotTriggered)
{
    int value = 0;
    int evalCount = 0;
    auto p = create([&]() { return value + ++evalCount; }, [&](int v) { value = v; });
    std::list<int> notifications;
    p->subscribe([&](int v) { notifications.push_back(v); });
    p->setValue(10);
    EXPECT_EQ(10, value); // write method ran and updated our local value variable
    EXPECT_EQ(1, p->getValue()); // but since it did not update any dynamic properties our read function accessed, the calculated value is unchanged
    EXPECT_EQ(1, evalCount); // read function was not called again since no dependencies ever changed
    EXPECT_EQ(std::list<int>({}), notifications); // notification was not sent out
}

TEST(Set2BasicCalculatedProperties, WhenWriteMethodUpdatesDependencyReadIsTriggered)
{
    auto value = create(42);
    int evalCount = 0;
    auto p = create([&]() { ++evalCount; return value->getValue(); }, [&](int v) { value->setValue(v); });
    std::list<int> notifications;
    p->subscribe([&](int v) { notifications.push_back(v); });
    EXPECT_EQ(42, p->getValue());
    EXPECT_EQ(1, evalCount);

    p->setValue(100);
    EXPECT_EQ(100, value->getValue());
    EXPECT_EQ(100, p->getValue());
    EXPECT_EQ(2, evalCount);
    EXPECT_EQ(std::list<int>({100}), notifications); // notification was sent out
}

TEST(Set2BasicCalculatedProperties, WhenWriteMethodUpdatesNonDependentValueReadIsNotTriggered)
{
    auto value = create(42);
    int evalCount = 0;
    auto otherValue = create(99);
    auto p = create([&]() { ++evalCount; return value->getValue(); }, [&](int v) { otherValue->setValue(v); });
    std::list<int> notifications;
    p->subscribe([&](int v) { notifications.push_back(v); });
    EXPECT_EQ(42, p->getValue());
    EXPECT_EQ(1, evalCount);

    p->setValue(100); // should update otherValue, but not value
    EXPECT_EQ(100, otherValue->getValue());
    EXPECT_EQ(42, p->getValue());
    EXPECT_EQ(1, evalCount);
    EXPECT_EQ(std::list<int>({}), notifications); // notification was not sent out
}

TEST(Set2BasicCalculatedProperties, WhenDependencyIsModifiedCalculatedPropertyIsReevaluated)
{
    auto value = create(42);
    auto p = create([&]() { return 10 * value->getValue(); }, [&](int v) { value->setValue(v / 10); });
    std::list<int> notifications;
    p->subscribe([&](int v) { notifications.push_back(v); });

    EXPECT_EQ(420, p->getValue());

    value->setValue(55); // should trigger a new evaluation
    EXPECT_EQ(550, p->getValue());
    EXPECT_EQ(std::list<int>({550}), notifications); // notification was sent out
}

TEST(Set2BasicCalculatedProperties, WhenMultipleDependenciesExistPropertyIsReevaluatedWhenAnyChange)
{
    auto a = create("forty-two");
    auto b = create(42);
    auto c = create(99);
    auto p = create([&]() { return b->getValue() + c->getValue() + strlen(a->getValue()); }, [](int) { });
    std::list<int> notifications;
    p->subscribe([&](int v) { notifications.push_back(v); });

    EXPECT_EQ(42 + 99 + strlen("forty-two"), p->getValue());

    b->setValue(100);
    EXPECT_EQ(100 + 99 + strlen("forty-two"), p->getValue());

    a->setValue("");
    EXPECT_EQ(100 + 99, p->getValue());
    EXPECT_EQ(std::list<int>({100 + 99 + (int)strlen("forty-two"), 100 + 99}), notifications); // notification was sent out
}

TEST(Set2BasicCalculatedProperties, CanBeDependentOnOtherCalculatedProperties)
{
    auto a = create(42);
    // b is a*10
    auto b = create([&]() { return a->getValue() * 10; }, [&](int v) { a->setValue(v / 10); });
    // c is b * -1
    auto c = create([&]() { return -1 * b->getValue(); }, [&](int v) { b->setValue(-1 * v); });

    EXPECT_EQ(420, b->getValue());
    EXPECT_EQ(-420, c->getValue());

    a->setValue(31);
    EXPECT_EQ(310, b->getValue());
    EXPECT_EQ(-310, c->getValue());

    c->setValue(1000);
    EXPECT_EQ(-100, a->getValue());
    EXPECT_EQ(-1000, b->getValue());
    EXPECT_EQ(1000, c->getValue());
}

TEST(Set2BasicCalculatedProperties, CapturesNewDependenciesOnSubsequentReads)
{
    std::array<std::unique_ptr<IDynamicProperty<int>>, 3> values {{ create(42), create(99), create(2012) }};
    auto which = create(0); // index into values

    // will take on value[which]
    auto p = create([&]() { return values[which->getValue()]->getValue(); }, [&](int v) { values[which->getValue()]->setValue(v); });

    EXPECT_EQ(42, p->getValue());

    p->setValue(24);
    EXPECT_EQ(24, p->getValue());
    EXPECT_EQ(24, values[0]->getValue());

    which->setValue(2);
    EXPECT_EQ(2012, p->getValue());
    EXPECT_EQ(24, values[0]->getValue()); // should not have been affected

    values[2]->setValue(3012);
    EXPECT_EQ(3012, p->getValue());
    EXPECT_EQ(3012, values[2]->getValue());

    values[1]->setValue(1999); // no impact
    EXPECT_EQ(3012, p->getValue());
    EXPECT_EQ(3012, values[2]->getValue());

    which->setValue(1);
    EXPECT_EQ(1999, p->getValue());
}

