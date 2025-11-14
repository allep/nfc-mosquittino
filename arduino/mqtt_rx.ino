#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

#include <EventsManager.h>
#include <ArduinoUnoR4WifiMQTTSubscriber.h>
#include <ArduinoUnoR4WifiController.h>
#include <ArduinoUnoR4WifiSerialNotifier.h>
#include <ArduinoUnoR4WifiLedMatrix.h>

#include "Secrets.h"

#include <map>

static const char topic[] = "mqtt-arduino";
const char clientId[] = "arduino-rx1";
int        port = 1883;

static WiFiClient wifiClient;
static MqttClient mqttClient(wifiClient);
static ArduinoMQTTSubscriber subscriber{mqttClient};
static ArduinoController controller{};
static ArduinoLedMatrixController ledMatrix{};
static ArduinoSerialNotifier notifier{};
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

  subscriber.SetupBlocking(clientId, broker, port);
  subscriber.Subscribe(topic);

  Serial.println("MQTT broker connected.");
}

void SetupLedMatrix() {
  ContentMap contentMap = {
    {"F31531FA", LEDMATRIX_HEART_BIG}, // small round tag
    {"04FCD53A255580", LEDMATRIX_CLOUD_WIFI},
    {"04BCD53A255580", LEDMATRIX_DANGER},
    {"04FBD53A255580", LEDMATRIX_MUSIC_NOTE},
    {"04DED53A255580", LEDMATRIX_CHIP},
    {"041CD53A255581", LEDMATRIX_LIKE},
    {"F322770C", LEDMATRIX_RESISTOR}, // white card
  };

  ledMatrix.Init(std::move(contentMap));
}

void MainInjection() {
  eventsManager.AddController(&controller);
  eventsManager.AddController(&ledMatrix);
  eventsManager.AddNotifier(&notifier);
  subscriber.SetProcessor(&eventsManager);
}

void setup() {
  SetupSerialBlocking();
  SetupWifiBlocking();
  SetupMQTT();
  SetupLedMatrix();

  MainInjection();
}

void loop() {
  subscriber.Process();
}
