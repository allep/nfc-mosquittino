#ifndef __CONTROLLER_MOCK_H__
#define __CONTROLLER_MOCK_H__

#include "ForControllingPort.h"

class MockController : public ForControlling {
public:
  void OnEvent(std::string_view topic, std::string_view payload) override {
    ++numEvents;
  }

public:
  unsigned int numEvents{0};
};

#endif // __CONTROLLER_MOCK_H__

