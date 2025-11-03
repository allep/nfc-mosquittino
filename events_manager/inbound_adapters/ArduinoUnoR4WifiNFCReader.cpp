#include <ArduinoUnoR4WifiNFCReader.h>

#include <Arduino.h>

namespace {
constexpr auto NFC_READ_PAUSE_MS{1000};
}

ArduinoNFCReader::ArduinoNFCReader(PN532 &nfcModule, std::string_view id,
                                   std::string_view eventId)
    : _nfc{nfcModule}, _id{id.data()}, _eventId{eventId.data()} {}

void ArduinoNFCReader::SetupBlocking() {
  _nfc.begin();

  auto versiondata{_nfc.getFirmwareVersion()};
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1)
      ;

    // TODO FIXME: here we should probably return false
  }

  Serial.print("Found chip PN5");
  Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. ");
  Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.');
  Serial.println((versiondata >> 8) & 0xFF, DEC);

  // Set the max number of retry attempts to read from a card
  // This prevents us from waiting forever for a card, which is
  // the default behaviour of the PN532.
  _nfc.setPassiveActivationRetries(0xFF);

  // configure board to read RFID tags
  _nfc.SAMConfig();

  Serial.println("Waiting for an ISO14443A card");
}

void ArduinoNFCReader::SetProcessor(ForProcessing *processor) {
  _processor = processor;
}

void ArduinoNFCReader::Process() {
  uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};
  uint8_t uidLength{};

  bool success{
      _nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength)};

  if (success) {
    std::string content{"from:"};
    content += _id;
    content += ",value:";

    char buf[3];

    for (uint8_t ix = 0; ix < uidLength; ix++) {
      sprintf(buf, "%02X", uid[ix]);
      buf[2] = 0;
      content += std::string{buf};
    }

    Serial.println("");
    Serial.println(content.c_str());

    if (_processor) {
      _processor->PushEvent(_eventId, content);
    }

    delay(NFC_READ_PAUSE_MS);
  } else {
    Serial.print(".");
  }
}
