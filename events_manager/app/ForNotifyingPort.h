#ifndef __FOR_NOTIFYING_PORT_H__
#define __FOR_NOTIFYING_PORT_H__

#include <string_view>

class ForNotifying {
public:
  virtual void NotifyEvent(std::string_view topic,
                           std::string_view payload) = 0;
};

#endif
