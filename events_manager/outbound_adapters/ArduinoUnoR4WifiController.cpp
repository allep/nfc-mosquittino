#include <ArduinoUnoR4WifiController.h>

void ArduinoController::OnEvent(std::string_view topic,
                                std::string_view payload) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // TODO FIXME: move to a timer / interrupt based approach instead
  digitalWrite(LED_BUILTIN, LOW);
}
