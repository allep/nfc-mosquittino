#include <ArduinoUnoR4WifiController.h>

void ArduinoController::OnEvent() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

