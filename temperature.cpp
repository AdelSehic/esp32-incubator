#include "temperature.h"
#include <DallasTemperature.h>
#include <OneWire.h>

// Setup a OneWire instance to communicate with any OneWire devices
OneWire oneWire(DS18_PIN);

// Pass our OneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

// Initialize temperature sensor
void init_temperature() {
  sensors.begin();
}

// Read temperature from the DS18B20 sensor
float read_temperature() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}