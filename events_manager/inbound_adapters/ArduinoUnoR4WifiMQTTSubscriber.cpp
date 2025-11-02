#include <ArduinoUnoR4WifiMQTTSubscriber.h>

#include <string>

namespace {
constexpr auto RECONNECT_DELAY_MS{500};
}

ArduinoMQTTSubscriber::ArduinoMQTTSubscriber(MqttClient& client) : _mqtt{client} {}

void ArduinoMQTTSubscriber::SetupBlocking(std::string_view clientId,
                                          std::string_view broker,
                                          unsigned int port) {
  _mqtt.setId(clientId.data());

  while (!_mqtt.connect(broker.data(), port)) {
    delay(RECONNECT_DELAY_MS);
  }
}

void ArduinoMQTTSubscriber::Subscribe(std::string_view topic) {
  _mqtt.subscribe(topic.data());

  Serial.println("Subscribe fatta al topic:");
  Serial.println(topic.data());
}

void ArduinoMQTTSubscriber::SetProcessor(ForProcessing *processor) {
  _processor = processor;
}

void ArduinoMQTTSubscriber::Process() {
  _mqtt.poll();

  if (_mqtt.parseMessage()) {
    Serial.println("Received something ...");

    auto t{_mqtt.messageTopic()};
    std::string_view topic{t.c_str()};

    std::string payload{};

    while (_mqtt.available()) {
      payload += (char)_mqtt.read();
    }

    _processor->PushEvent(topic, payload);
  }
}
