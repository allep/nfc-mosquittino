#ifndef __ARDUINO_UNO_R4_WIFI_NFC_READER_H__
#define __ARDUINO_UNO_R4_WIFI_NFC_READER_H__

#include <ForSendingEventsPort.h>

#include <PN532.h>

class ArduinoNFCReader {
public:
  ArduinoNFCReader(PN532 &nfcModule);
  void SetupBlocking();

  void SetProcessor(ForProcessing *processor);

  void Process();

private:
  PN532 &_nfc;
  ForProcessing *_processor{};
};

#endif
