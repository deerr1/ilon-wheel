#include "core_esp8266_features.h"
#pragma once
#include <Arduino.h>

enum connectType {
  General,
  SlotExpander
};

class Motor
{
private:
    int8_t _dirPin;
    int8_t _speedPin;
    connectType _type;
public:
    Motor(int8_t dirPin, int8_t speedPin, connectType type = General) {
        _dirPin = dirPin;
        _speedPin = speedPin;
        _type = type;

        if(_type == General) {      
          pinMode(_dirPin, OUTPUT);
          pinMode(_speedPin, OUTPUT);
        }
        else {

        }
    }

    void run(int8_t speed) {
        if(speed >= 0) {
            digitalWrite(_dirPin, HIGH);
        }
        else
        {
            digitalWrite(_dirPin, LOW);
        }
        digitalWrite(_speedPin, speed);
        delay(1000);
        digitalWrite(_speedPin, 0);
    }

};


