#include <ArduinoUnoR4WifiMQTTNotifier.h>

ArduinoUnoR4WifiMQTTNotifier::ArduinoUnoR4WifiMQTTNotifier(MqttClient& mqttClient) : _mqtt{mqttClient} {}

void ArduinoUnoR4WifiMQTTNotifier::Poll() { _mqtt.poll(); }

void ArduinoUnoR4WifiMQTTNotifier::NotifyEvent(std::string_view topic, std::string_view payload) {
  _mqtt.beginMessage(topic);
  _mqtt.print(payload);
  _mqtt.endMessage();
}
