#include "gtest/gtest.h"

#include <string>
#include <memory>
#include "DynamicProperty.h"

using namespace CppTest;

namespace
{
    template <typename T> std::unique_ptr<IDynamicProperty<T>> create(T value)
    {
        return std::unique_ptr<IDynamicProperty<T>>(DynamicProperty::create(value));
    }

}

TEST(Set1BasicDynamicProperties, CanBeConstructedWithInitialValue)
{
    auto p = create(42);
    EXPECT_EQ(42, p->getValue());
}

TEST(Set1BasicDynamicProperties, ValueCanBeChanged)
{
    auto p = create(42);
    p->setValue(100);
    EXPECT_EQ(100, p->getValue());
}


TEST(Set1BasicDynamicProperties, NothingImmediatelyHappensWhenSubscribed)
{
    auto p = create(42);
    p->subscribe([] (int) { ADD_FAILURE(); });
}

TEST(Set1BasicDynamicProperties, SubscriptionReceivesNotificationsWhenValueChanges)
{
    auto p = create(42);
    std::list<int> notifications;
    p->subscribe([&] (int v) { notifications.push_back(v); });

    p->setValue(100);
    EXPECT_EQ(std::list<int>({ 100 }), notifications);

    p->setValue(200);
    EXPECT_EQ(std::list<int>({ 100, 200 }), notifications);

    p->setValue(0);
    EXPECT_EQ(std::list<int>({ 100, 200, 0 }), notifications);
}

TEST(Set1BasicDynamicProperties, SubscriptionNotNotifiedAfterItIsDisconnected)
{
    auto p = create(42);
    std::list<int> notifications;
    auto subscription = p->subscribe([&] (int v) { notifications.push_back(v); });

    p->setValue(100);
    p->setValue(200);
    p->setValue(0);
    EXPECT_EQ(std::list<int>({ 100, 200, 0 }), notifications);

    subscription.disconnect();

    // No more notifications
    p->setValue(1);
    p->setValue(2);
    p->setValue(3);
    EXPECT_EQ(std::list<int>({ 100, 200, 0 }), notifications);
}

TEST(Set1BasicDynamicProperties, MultipleSubscribersAreNotified)
{
    auto p = create(-1);
    std::list<int> notifications[3];
    std::list<int> expected[3];
    boost::signals2::connection subscriptions[3];

    subscriptions[0] = p->subscribe([&] (int v) { notifications[0].push_back(v); });
    p->setValue(1);
    expected[0].push_back(1);

    subscriptions[1] = p->subscribe([&] (int v) { notifications[1].push_back(v); });
    p->setValue(2);
    expected[0].push_back(2);
    expected[1].push_back(2);

    subscriptions[2] = p->subscribe([&] (int v) { notifications[2].push_back(v); });
    p->setValue(3);
    expected[0].push_back(3);
    expected[1].push_back(3);
    expected[2].push_back(3);

    subscriptions[1].disconnect();
    p->setValue(4);
    expected[0].push_back(4);
    expected[2].push_back(4);

    subscriptions[2].disconnect();
    p->setValue(5);
    expected[0].push_back(5);

    subscriptions[0].disconnect();
    p->setValue(6);

    EXPECT_EQ(expected[0], notifications[0]);
    EXPECT_EQ(expected[1], notifications[1]);
    EXPECT_EQ(expected[2], notifications[2]);
}


