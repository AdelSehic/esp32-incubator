#include "relays.h"

bool heater;

void init_relays() {
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  turn_heat_off();  // Ensure heater starts OFF
  turn_motor_off();
}

void turn_heat_on() {
  digitalWrite(HEATER_PIN, ON);
  heater = true;
}

void turn_heat_off() {
  digitalWrite(HEATER_PIN, OFF);
  heater = false;
}

void turn_motor_on() {
  digitalWrite(MOTOR_PIN, ON);
}

void turn_motor_off() {
  digitalWrite(MOTOR_PIN, OFF);
}

bool control_heat(float temperature, float temp_low, float temp_high) {
  if ( temperature <= temp_low )
    turn_heat_on();
  else if ( temperature >= temp_high )
    turn_heat_off();
  return heater;
}