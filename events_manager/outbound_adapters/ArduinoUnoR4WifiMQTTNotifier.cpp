#include <ArduinoUnoR4WifiMQTTNotifier.h>

namespace {
constexpr auto RECONNECT_DELAY_MS{500};
}

ArduinoMQTTNotifier::ArduinoMQTTNotifier(MqttClient &mqttClient)
    : _mqtt{mqttClient} {}

void ArduinoMQTTNotifier::SetupBlocking(std::string_view clientId,
                                        std::string_view broker,
                                        unsigned int port) {
  _mqtt.setId(clientId.data());

  while (!_mqtt.connect(broker.data(), port)) {
    delay(RECONNECT_DELAY_MS);
  }
}

void ArduinoMQTTNotifier::Poll() { _mqtt.poll(); }

void ArduinoMQTTNotifier::NotifyEvent(std::string_view topic,
                                      std::string_view payload) {
  const std::string t{topic};
  const std::string p{payload};
  _mqtt.beginMessage(t.c_str());
  _mqtt.print(p.c_str());
  _mqtt.endMessage();
}
