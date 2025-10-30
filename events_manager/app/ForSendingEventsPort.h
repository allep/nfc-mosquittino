#ifndef __FOR_PROCESSING_EVENTS_PORT_H__
#define __FOR_PROCESSING_EVENTS_PORT_H__

#include <string>

class ForProcessing {
public:
  virtual void PushEvent(std::string topic, std::string payload) = 0;
};

#endif
