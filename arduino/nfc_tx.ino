#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

#include <EventsManager.h>
#include <ArduinoUnoR4WifiNFCReader.h>
#include <ArduinoUnoR4WifiMQTTNotifier.h>

#include <SoftwareSerial.h>
#include <PN532_SWHSU.h>
#include <PN532.h>

#include "Secrets.h"

SoftwareSerial SWSerial{3, 2};
PN532_SWHSU pn532swHsu{SWSerial};
PN532 nfc{pn532swHsu};

static const char clientId[] = "arduino-tx1";
static const char topic[] = "mqtt-arduino";

// Mqtt notifier configuration
int port = 1883;

static WiFiClient wifiClient;
static MqttClient mqttClient(wifiClient);
static ArduinoMQTTNotifier notifier{mqttClient};
static ArduinoNFCReader nfcReader{nfc, clientId, topic};
static EventsManager eventsManager{};

void SetupSerialBlocking() {
  Serial.begin(115200);
  while (!Serial);
}

void SetupWifiBlocking() {
  Serial.println("Wifi connection ...");
  if (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.println("Connection failed!");
    while (true);
  }
  Serial.println("Wifi connected.");

  delay(2000);

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void SetupMQTT() {
  Serial.print("MQTT broker connection to ");
  Serial.print(broker);
  Serial.println(" ...");

  notifier.SetupBlocking(clientId, broker, port);
  nfcReader.SetupBlocking();

  Serial.println("MQTT broker connected.");
}

void MainInjection() {
  eventsManager.AddNotifier(&notifier);
  nfcReader.SetProcessor(&eventsManager);
}
  
void setup(void) {
  SetupSerialBlocking();
  SetupWifiBlocking();
  SetupMQTT();

  MainInjection();
}

void loop(void) {
  nfcReader.Process();
}
