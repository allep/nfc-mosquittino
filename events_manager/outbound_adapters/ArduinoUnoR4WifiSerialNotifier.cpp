#include <ArduinoUnoR4WifiSerialNotifier.h>

void ArduinoSerialNotifier::NotifyEvent(const std::string_view topic,
                                        const std::string_view payload) {
  Serial.print("Event received - topic: ");
  Serial.print(topic.data());
  Serial.print(", payload: ");
  Serial.println(payload.data());
}
