#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

void init_wifi();
bool is_wifi_connected();
void reconnect_wifi();

#endif