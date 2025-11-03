#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

#include <EventsManager.h>
#include <ArduinoUnoR4WifiMQTTSubscriber.h>
#include <ArduinoUnoR4WifiController.h>
#include <ArduinoUnoR4WifiSerialNotifier.h>

#include "Secrets.h"

static const char topic[] = "mqtt-arduino";
const char clientId[] = "arduino-rx1";
int        port = 1883;

static WiFiClient wifiClient;
static MqttClient mqttClient(wifiClient);
static ArduinoMQTTSubscriber subscriber{mqttClient};
static ArduinoController controller{};
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

  // main app injection
  eventsManager.AddController(&controller);
  eventsManager.AddNotifier(&notifier);
  subscriber.SetProcessor(&eventsManager);
}

void loop() {
  subscriber.Process();
}
