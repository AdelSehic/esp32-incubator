#include "mqtt.h"
#include "wifi_manager.h"  // Include WiFi manager

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void init_mqtt() {
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
}

bool is_mqtt_connected() {
  return mqttClient.connected();
}

void mqtt_reconnect() {

  WiFiClient testClient;
  if (testClient.connect(MQTT_BROKER, MQTT_PORT)) {
    Serial.println("MQTT Broker is reachable!");
    testClient.stop();
  } else {
    Serial.println("Cannot reach MQTT Broker!");
  }

  Serial.println("Attempting MQTT connection...");
  if (mqttClient.connect(MQTT_CLIENT_ID)) {
    Serial.println("Connected to MQTT broker!");
  } else {
    Serial.print("Failed, rc=");
    Serial.println(mqttClient.state());
  }
}

void mqtt_loop() {
  if (!mqttClient.connected()) {
    mqtt_reconnect();
  }
  mqttClient.loop();
}

void mqtt_publish(const char* topic, const char* message) {
  if (mqttClient.connected()) {
    mqttClient.publish(topic, message);
  } else {
    Serial.println("MQTT not connected. Message not sent.");
  }
}