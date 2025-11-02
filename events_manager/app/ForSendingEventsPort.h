#ifndef __FOR_PROCESSING_EVENTS_PORT_H__
#define __FOR_PROCESSING_EVENTS_PORT_H__

#include <string_view>

class ForProcessing {
public:
  virtual void PushEvent(std::string_view topic, std::string_view payload) = 0;
};

#endif
