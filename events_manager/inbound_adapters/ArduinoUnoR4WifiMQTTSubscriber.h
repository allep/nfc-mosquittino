#ifndef __ARDUINO_UNO_R4_WIFI_MQTT_SUBSCRIBER_H__
#define __ARDUINO_UNO_R4_WIFI_MQTT_SUBSCRIBER_H__

#include <ForSendingEventsPort.h>

#include <Arduino.h>
#include <ArduinoMqttClient.h>

#include <string_view>

class ArduinoMQTTSubscriber {
public:
  ArduinoMQTTSubscriber(MqttClient &mqttClient);
  void SetupBlocking(std::string_view clientId, std::string_view broker,
                     unsigned int port);
  void Subscribe(std::string_view topic);

  void SetProcessor(ForProcessing *processor);

  void Process();

private:
  MqttClient &_mqtt;
  ForProcessing *_processor{};
};

#endif
