#ifndef __NOTIFIER_MOCK_H__
#define __NOTIFIER_MOCK_H__

#include "ForNotifyingPort.h"

class MockNotifier : public ForNotifying {
public:
  void NotifyEvent(std::string topic, std::string payload) override {
    lastTopic = topic;
    lastPayload = payload;
    notified = true;
  }

public:
  std::string lastTopic;
  std::string lastPayload;
  bool notified = false;
};

#endif // __NOTIFIER_MOCK_H__
