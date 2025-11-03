#ifndef __NOTIFIER_MOCK_H__
#define __NOTIFIER_MOCK_H__

#include "ForNotifyingPort.h"

class MockNotifier : public ForNotifying {
public:
  void NotifyEvent(std::string_view topic, std::string_view payload) override {
    lastTopic = topic;
    lastPayload = payload;
    ++notified;
  }

public:
  std::string lastTopic;
  std::string lastPayload;
  unsigned int notified{0};
};

#endif // __NOTIFIER_MOCK_H__
