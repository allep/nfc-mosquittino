#ifndef __CONTROLLER_MOCK_H__
#define __CONTROLLER_MOCK_H__

#include "ForControllingPort.h"

class MockController : public ForControlling {
public:
  void OnEvent() override { ++numEvents; }

public:
  unsigned int numEvents{0};
};

#endif // __CONTROLLER_MOCK_H__

