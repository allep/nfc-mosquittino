#include <gtest/gtest.h>

#include "EventsManager.h"

#include "MockController.h"
#include "MockNotifier.h"

TEST(EventsManagerTest, SingleEventNotifyAndControl) {
  EventsManager manager{};

  MockNotifier notifier;
  MockController controller;

  manager.SetNotifier(&notifier);
  manager.SetController(&controller);

  static const char *testTopic = "TestTopic";
  static const char *testPayload = "TestPayload";

  manager.PushEvent(testTopic, testPayload);

  EXPECT_EQ(notifier.notified, 1);
  EXPECT_EQ(notifier.lastTopic, testTopic);
  EXPECT_EQ(notifier.lastPayload, testPayload);
  EXPECT_EQ(controller.numEvents, 1);
}

TEST(EventsManagerTest, MultipleEventSameContentNotifyAndControl) {
  EventsManager manager{};

  MockNotifier notifier;
  MockController controller;

  manager.SetNotifier(&notifier);
  manager.SetController(&controller);

  static const char *testTopic = "TestTopic";
  static const char *testPayload = "TestPayload";

  manager.PushEvent(testTopic, testPayload);
  manager.PushEvent(testTopic, testPayload);

  EXPECT_EQ(notifier.notified, 2);
  EXPECT_EQ(notifier.lastTopic, testTopic);
  EXPECT_EQ(notifier.lastPayload, testPayload);
  EXPECT_EQ(controller.numEvents, 2);
}

TEST(EventsManagerTest, MultipleEventDifferentContentNotifyAndControl) {
  EventsManager manager{};

  MockNotifier notifier;
  MockController controller;

  manager.SetNotifier(&notifier);
  manager.SetController(&controller);

  static const char *firstTestTopic = "TestTopic";
  static const char *firstTestPayload = "TestPayload";
  static const char *secondTestTopic = "AnotherTopic";
  static const char *secondTestPayload = "AnotherPayload";

  manager.PushEvent(firstTestTopic, firstTestPayload);
  manager.PushEvent(secondTestTopic, secondTestPayload);

  EXPECT_EQ(notifier.notified, 2);
  EXPECT_EQ(notifier.lastTopic, secondTestTopic);
  EXPECT_EQ(notifier.lastPayload, secondTestPayload);
  EXPECT_EQ(controller.numEvents, 2);
}

TEST(EventsManagerTest, MultipleEventsWithReset) {
  EventsManager manager{};

  MockNotifier notifier;
  MockController controller;

  manager.SetNotifier(&notifier);
  manager.SetController(&controller);

  static const char *topic = "TestTopic";
  static const char *payload = "TestPayload";

  manager.PushEvent(topic, payload);

  EXPECT_EQ(notifier.notified, 1);
  EXPECT_EQ(notifier.lastTopic, topic);
  EXPECT_EQ(notifier.lastPayload, payload);
  EXPECT_EQ(controller.numEvents, 1);

  manager.ResetNotifier();
  manager.ResetController();

  manager.PushEvent(topic, payload);

  EXPECT_EQ(notifier.notified, 1);
  EXPECT_EQ(notifier.lastTopic, topic);
  EXPECT_EQ(notifier.lastPayload, payload);
  EXPECT_EQ(controller.numEvents, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
