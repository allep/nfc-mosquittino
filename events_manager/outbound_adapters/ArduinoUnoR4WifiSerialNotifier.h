#ifndef __ARDUINO_UNO_R4_WIFI_SERIAL_NOTIFIER_H__
#define __ARDUINO_UNO_R4_WIFI_SERIAL_NOTIFIER_H__

#include <ForNotifyingPort.h>

#include <Arduino.h>

class ArduinoSerialNotifier : public ForNotifying {
public:
  void NotifyEvent(std::string_view topic, std::string_view payload) override;
};

#endif

