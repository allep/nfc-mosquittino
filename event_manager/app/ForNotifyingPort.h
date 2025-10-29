#ifndef __FOR_NOTIFYING_PORT_H__
#define __FOR_NOTIFYING_PORT_H__

#include <string>

class ForNotifying {
public:
  virtual void NotifyEvent(std::string topic, std::string payload) = 0;
};

#endif
