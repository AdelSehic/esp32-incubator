# ESP32 Chicken Egg Incubator Controller

## Overview
This project provides firmware for an ESP32-based chicken egg incubator controller. The system accurately monitors and regulates temperature and humidity to create optimal conditions for successful egg hatching.

## Features
- **Temperature Control**: Maintains temperature between configurable thresholds (default 37.3°C - 37.8°C)
- **Humidity Monitoring**: Tracks humidity levels using a DHT11 sensor
- **Remote Monitoring**: Publishes all sensor data over MQTT for remote monitoring and control
- **Automatic Heater Control**: Intelligently controls a heating element to maintain proper temperature
- **Motor Control**: Controls egg turning motor (hardware support included, logic implementation needed)
- **WiFi Connectivity**: Connects to your local WiFi network for remote access

## Hardware Requirements
- ESP32 Development Board
- DS18B20 Temperature Sensor
- DHT11 Humidity Sensor
- Relay Module (2-channel)
- Heating Element
- Egg Turning Motor
- 5V Power Supply

## Connection Diagram
- **DS18B20 Temperature Sensor**: Connected to pin 25
- **DHT11 Humidity Sensor**: Connected to pin 26
- **Heater Relay**: Connected to pin 32
- **Motor Relay**: Connected to pin 33

## Software Dependencies
The following libraries are required:
- ArduinoJson
- PubSubClient (MQTT)
- OneWire
- DallasTemperature
- DHT11 (custom implementation included)

## Configuration
Before uploading, update the following settings in `secrets.h`:
```
#define WIFI_SSID "your-ssid"
#define WIFI_PASSWORD "your-password"
```

And configure your MQTT broker settings in `mqtt.h`:
```
#define MQTT_BROKER     "10.1.1.108"        // Your MQTT broker IP
#define MQTT_PORT       1883                // Default MQTT port
#define MQTT_CLIENT_ID  "ESP32_Inkubator"
```

## MQTT Topics
The controller publishes to the following MQTT topics:
- `inkubator/stanje` - Complete state information (JSON format)
- `inkubator/temperatura` - Temperature readings
- `inkubator/vlaznost` - Humidity readings
- `inkubator/grijac` - Heater status (ON/OFF)

## Temperature Control Logic
The controller maintains the temperature within the specified range:
- If temperature falls below 37.3°C, the heater turns ON
- If temperature rises above 37.8°C, the heater turns OFF

## Project Structure
- `inkubator.ino` - Main application file
- `temperature.cpp/.h` - Temperature sensor control
- `dht11.cpp/.h` - DHT11 humidity sensor library
- `relays.cpp/.h` - Relay control for heater and motor
- `wifi_manager.cpp/.h` - WiFi connection management
- `mqtt.cpp/.h` - MQTT communication
- `secrets.h` - WiFi credentials

## Getting Started
1. Install all required libraries in Arduino IDE
2. Configure your WiFi and MQTT settings
3. Upload the code to your ESP32
4. Connect the hardware according to the pin configuration
5. Power on the device and monitor via MQTT

## Troubleshooting
- If WiFi connection fails, the device will automatically attempt reconnection
- If MQTT connection fails, check your broker IP and ensure it's reachable
- For humidity readings of -1, check DHT11 sensor connections

## Future Improvements
- Implement egg turning schedule
- Add web interface for configuration
- Add OTA (Over The Air) updates
- Implement data logging
