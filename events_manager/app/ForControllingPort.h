#ifndef __FOR_CONTROLLING_PORT_H__
#define __FOR_CONTROLLING_PORT_H__

#include <string_view>

class ForControlling {
public:
  virtual void OnEvent(std::string_view topic, std::string_view content) = 0;
};

#endif
