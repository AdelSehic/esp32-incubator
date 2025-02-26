#include "dht11.h"
#include <Arduino.h>

DHT11::DHT11(int pin) {
    _pin = pin;
    pinMode(_pin, INPUT);
}

float DHT11::readHumidity() {
    if (read()) {
        return (float)_humidity;
    }
    return -1;  // Return -1 if reading failed
}

bool DHT11::read() {
    uint8_t bits[5];
    uint8_t i = 0;
    
    // Send start signal to the sensor
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(18); // 18ms low signal to initiate reading
    digitalWrite(_pin, HIGH);
    delayMicroseconds(40);
    pinMode(_pin, INPUT);
    
    // Wait for the response
    unsigned long timeout = micros();
    while (digitalRead(_pin) == LOW) {
        if (micros() - timeout > 1000) return false;  // Timeout if no response
    }
    
    timeout = micros();
    while (digitalRead(_pin) == HIGH) {
        if (micros() - timeout > 1000) return false;  // Timeout if no response
    }
    
    // Read the data
    for (int j = 0; j < 5; j++) {
        bits[j] = 0;
        for (int i = 7; i >= 0; i--) {
            timeout = micros();
            while (digitalRead(_pin) == LOW) {
                if (micros() - timeout > 1000) return false; // Timeout if no data
            }
            timeout = micros();
            while (digitalRead(_pin) == HIGH) {
                if (micros() - timeout > 1000) return false; // Timeout if no data
            }
            if (micros() - timeout > 40) {
                bits[j] |= (1 << i);  // Set the bit if high for more than 40us
            }
        }
    }
    
    // Check checksum
    if (bits[4] != (bits[0] + bits[1] + bits[2] + bits[3])) {
        return false;  // Checksum mismatch, return false if invalid data
    }

    _humidity = bits[0];  // Humidity is the first byte
    _temperature = bits[2];  // Temperature is the third byte (not used here)

    return true;
}