#include "mqtt.h"
#include "wifi_manager.h"  // Include WiFi manager
#include <ArduinoJson.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void init_mqtt() {
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(mqtt_callback);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);

  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';

  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print("JSON Parsing failed: ");
    Serial.println(error.f_str());
    return;
  }

  if (doc.containsKey("temp_high")) {
    temp_high = doc["temp_high"];
    Serial.print("Updated temp_high: ");
    Serial.println(temp_high);
  }
  if (doc.containsKey("temp_low")) {
    temp_low = doc["temp_low"];
    Serial.print("Updated temp_low: ");
    Serial.println(temp_low);
  }
}

bool is_mqtt_connected() {
  return mqttClient.connected();
}

void mqtt_reconnect() {
  Serial.println("Attempting MQTT connection...");
  if (mqttClient.connect(MQTT_CLIENT_ID)) {
    Serial.println("Connected to MQTT broker!");
    mqttClient.subscribe(MQTT_TOPIC_SUBSCRIBE_CONFIG);  // Subscribe to topic
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