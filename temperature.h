#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <OneWire.h>
#include <DallasTemperature.h>

#define DS18_PIN 25

// Function declarations
void init_temperature();
float read_temperature();
bool control_heat(float temperature, float temp_low, float temp_high);

#endif