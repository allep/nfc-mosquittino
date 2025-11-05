#ifndef __ARDUINO_UNO_R4_WIFI_CONTROLLER_H__
#define __ARDUINO_UNO_R4_WIFI_CONTROLLER_H__

#include <ForControllingPort.h>

#include <string_view>

class ArduinoController : public ForControlling {
public:
  void OnEvent(std::string_view topic, std::string_view payload) override;
};

#endif
