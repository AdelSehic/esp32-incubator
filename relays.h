#ifndef HEATER_H
#define HEATER_H

#include <Arduino.h>

// relays are active low, inverse logic
#define ON  false
#define OFF true
#define HEATER_PIN 32
#define MOTOR_PIN 33

void init_relays();
void turn_heat_on();
void turn_heat_off();
void turn_motor_on();
void turn_motor_off();
bool control_heat(float temperature, float temp_low, float temp_high);

#endif