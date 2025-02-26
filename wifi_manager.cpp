#include "wifi_manager.h"
#include "secrets.h"

void init_wifi() {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) { // 20 attempts max
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFailed to connect to WiFi.");
    }
}

bool is_wifi_connected() {
    return WiFi.status() == WL_CONNECTED;
}

void reconnect_wifi() {
    if (!is_wifi_connected()) {
        Serial.println("WiFi lost, reconnecting...");
        WiFi.disconnect();
        WiFi.reconnect();
    }
}