#ifndef __ARDUINO_UNO_R4_WIFI_MQTT_NOTIFIER_H__
#define __ARDUINO_UNO_R4_WIFI_MQTT_NOTIFIER_H__

#include <ForNotifyingPort.h>

#include <Arduino.h>
#include <ArduinoMqttClient.h>

class ArduinoMQTTNotifier : public ForNotifying {
public:
  ArduinoMQTTNotifier(MqttClient &mqttClient);
  void SetupBlocking(std::string_view clientId, std::string_view broker,
                     unsigned int port);

  void Poll();
  void NotifyEvent(std::string_view topic, std::string_view payload) override;

private:
  MqttClient &_mqtt;
};

#endif
