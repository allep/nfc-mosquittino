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

  EXPECT_TRUE(notifier.notified);
  EXPECT_EQ(notifier.lastTopic, testTopic);
  EXPECT_EQ(notifier.lastPayload, testPayload);
  EXPECT_EQ(controller.numEvents, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
