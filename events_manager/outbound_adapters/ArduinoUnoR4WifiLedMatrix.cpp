#include <ArduinoUnoR4WifiLedMatrix.h>

#include <Arduino.h>

#include <string_view>

using namespace std::literals;

namespace {
constexpr std::string_view marker{";value:"sv};
}

void ArduinoLedMatrixController::Init(ContentMap &&contentMap) {
  _contentMap = std::move(contentMap);
  _matrix.begin();
}

void ArduinoLedMatrixController::OnEvent(std::string_view topic,
                                         std::string_view payload) {

  const auto valuePos{payload.rfind(marker)};

  if (valuePos != std::string_view::npos) {
    const auto key{payload.substr(valuePos + marker.size())};
    if (_contentMap.find(key.data()) != _contentMap.end()) {
      _matrix.loadFrame(_contentMap[key.data()]);
      return;
    }
  }

  _matrix.loadFrame(LEDMATRIX_EMOJI_SAD);
}
