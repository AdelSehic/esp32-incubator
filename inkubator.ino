#include "temperature.h"
#include "relays.h"
#include "wifi_manager.h"
#include "mqtt.h"
#include <ArduinoJson.h>
#include <dht11.h>

#define LOOP_MS 2000

DHT11 dht(26);

// Temperatures limit
float temp_high = 37.6;
float temp_low = 37.35;

float cached_humidity = 0.0;

void publish_data(float temperature, float humidity, bool heater) {
  StaticJsonDocument<200> doc;

  doc["temperatura"] = temperature;
  cached_humidity = humidity != -1 ? humidity : cached_humidity;
  doc["vlaznost"] = cached_humidity;
  doc["grijac"] = heater ? "ON" : "OFF";

  char jsonString[200];
  serializeJson(doc, jsonString);

  mqtt_publish(MQTT_TOPIC_PUBLISH_STATE, jsonString);
}

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  init_temperature();
  init_relays();
  init_wifi();
  init_mqtt();
}

void loop() {
  unsigned long loop_start = millis();

  if(!is_wifi_connected()) {
    reconnect_wifi();
  }
  mqtt_loop();

  float temperature = read_temperature();
  float humidity = dht.readHumidity();
  bool heater = control_heat(temperature, temp_low, temp_high);

  publish_data(temperature, humidity, heater);

  unsigned long elapsed_time = millis() - loop_start;
  if (elapsed_time < LOOP_MS) {
    delay(LOOP_MS - elapsed_time);
  }
}
