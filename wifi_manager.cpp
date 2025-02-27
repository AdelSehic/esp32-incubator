#include "esp_wifi_types_generic.h"
#include "esp32-hal-gpio.h"
#include "wifi_manager.h"
#include "secrets.h"

bool indicator_state = false;

void set_indicator() {
  indicator_state = true;
  digitalWrite(WIFI_INDICATOR, indicator_state);
}

void reset_indicator() {
  indicator_state = false;
  digitalWrite(WIFI_INDICATOR, indicator_state);
}

void toggle_indicator() {
  indicator_state = !indicator_state;
  digitalWrite(WIFI_INDICATOR, indicator_state);
}

void init_wifi() {
  pinMode(WIFI_INDICATOR, OUTPUT);
  set_indicator();

  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) { // 20 attempts max
    delay(500);
    Serial.print(".");
    toggle_indicator();
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    reset_indicator();
  } else {
    Serial.println("\nFailed to connect to WiFi.");
    set_indicator();
  }
}

bool is_wifi_connected() {
  if ( WiFi.status() != WL_CONNECTED )
    return false;
  reset_indicator();
  return true;
}

void reconnect_wifi() {
  toggle_indicator();
  WiFi.disconnect();
  WiFi.reconnect();
}