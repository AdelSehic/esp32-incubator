#ifndef DHT11_H
#define DHT11_H

#include <Arduino.h>

class DHT11 {
public:
    DHT11(int pin);
    float readHumidity();

private:
    int _pin;
    bool read();
    uint8_t _humidity;
    uint8_t _temperature;
};

#endif