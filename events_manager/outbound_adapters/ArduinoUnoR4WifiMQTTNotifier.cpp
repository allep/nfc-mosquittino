#include <ArduinoUnoR4WifiMQTTNotifier.h>

ArduinoMQTTNotifier::ArduinoMQTTNotifier(MqttClient &mqttClient)
    : _mqtt{mqttClient} {}

void ArduinoMQTTNotifier::Poll() { _mqtt.poll(); }

void ArduinoMQTTNotifier::NotifyEvent(std::string_view topic,
                                      std::string_view payload) {
  const std::string t{topic};
  const std::string p{payload};
  _mqtt.beginMessage(t.c_str());
  _mqtt.print(p.c_str());
  _mqtt.endMessage();
}
