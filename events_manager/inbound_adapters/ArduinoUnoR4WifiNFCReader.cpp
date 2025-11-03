#include <ArduinoUnoR4WifiNFCReader.h>

#include <Arduino.h>

ArduinoNFCReader::ArduinoNFCReader(PN532 &nfcModule) : _nfc{nfcModule} {}

void ArduinoNFCReader::SetupBlocking() {
  _nfc.begin();

  auto versiondata{_nfc.getFirmwareVersion()};
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1)
      ;
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
  bool success{};
  uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0}; // Buffer to store the returned UID
  uint8_t uidLength; // Length of the UID (4 or 7 bytes depending on ISO14443A
                     // card type)

  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success =
      _nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success) {
    Serial.println("Found a card!");
    Serial.print("UID Length: ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("UID Value: ");
    for (uint8_t i = 0; i < uidLength; i++) {
      Serial.print(" 0x");
      Serial.print(uid[i], HEX);
    }
    Serial.println("");
    // Wait 1 second before continuing
    delay(1000);
  } else {
    // PN532 probably timed out waiting for a card
    Serial.println("Timed out waiting for a card");
  }
}
