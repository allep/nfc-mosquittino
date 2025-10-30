#ifndef __ARDUINO_UNO_R4_WIFI_CONTROLLER_H__
#define __ARDUINO_UNO_R4_WIFI_CONTROLLER_H__

#include <ForControllingPort.h>

class ArduinoController : public ForControllingPort {
public:
  void OnEvent() override;
};

#endif
