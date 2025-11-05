#ifndef __ARDUINO_UNO_R4_WIFI_LED_MATRIX_H__
#define __ARDUINO_UNO_R4_WIFI_LED_MATRIX_H__

#include <ForControllingPort.h>

#include <map>
#include <string>
#include <string_view>

#include <Arduino_LED_Matrix.h>

using ContentMap = std::map<std::string, const uint32_t *>;

class ArduinoLedMatrixController : public ForControlling {
public:
  void Init(ContentMap &&contentMap);
  void OnEvent(std::string_view topic, std::string_view payload) override;

private:
  ArduinoLEDMatrix _matrix{};
  ContentMap _contentMap{};
};

#endif
