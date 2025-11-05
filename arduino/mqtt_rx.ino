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

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Connessione WiFi...");
  if (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.println("Connessione fallita!");
    while (true);
  }
  Serial.println("Connesso al WiFi!");

  delay(2000);

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Connessione al broker MQTT
  Serial.print("Connessione al broker MQTT...");
  Serial.println(broker);

  subscriber.SetupBlocking(clientId, broker, port);
  subscriber.Subscribe(topic);

  Serial.println("Connesso al broker MQTT!");

  std::map<std::string, const uint32_t*> contentMap = {
    {"F31531FA", LEDMATRIX_HEART_BIG},
    {"04FCD53A255580", LEDMATRIX_CLOUD_WIFI},
    {"04BCD53A255580", LEDMATRIX_DANGER},
  };

  ledMatrix.Init(std::move(contentMap));

  // main app injection
  eventsManager.AddController(&controller);
  eventsManager.AddController(&ledMatrix);
  eventsManager.AddNotifier(&notifier);
  subscriber.SetProcessor(&eventsManager);
}

void loop() {
  subscriber.Process();
}
