#ifndef __ARDUINO_UNO_R4_WIFI_NFC_READER_H__
#define __ARDUINO_UNO_R4_WIFI_NFC_READER_H__

#include <ForSendingEventsPort.h>

#include <PN532.h>

#include <string>
#include <string_view>

class ArduinoNFCReader {
public:
  ArduinoNFCReader(PN532 &nfcModule, std::string_view id,
                   std::string_view eventId);
  void SetupBlocking();

  void SetProcessor(ForProcessing *processor);

  void Process();

private:
  PN532 &_nfc;
  std::string _id{};
  std::string _eventId{};
  ForProcessing *_processor{};
};

#endif
