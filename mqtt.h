#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <WiFi.h>
#include <PubSubClient.h>

// MQTT Configuration
#define MQTT_BROKER     "192.168.100.2"     // Replace with your broker address
#define MQTT_PORT       1883                // Default MQTT port
#define MQTT_CLIENT_ID  "ESP32_Inkubator"

// MQTT Topics
#define MQTT_TOPIC_PUBLISH_TEMP   "inkubator/temperatura"
#define MQTT_TOPIC_PUBLISH_HUMID  "inkubator/vlaznost"
#define MQTT_TOPIC_PUBLISH_HEATER "inkubator/grijac"
#define MQTT_TOPIC_PUBLISH_STATE  "inkubator/stanje"

void init_mqtt();
void mqtt_loop();
void mqtt_publish(const char* topic, const char* message);
bool is_mqtt_connected();

#endif