#include "core_esp8266_features.h"
#pragma once
#include <Arduino.h>

#define minSpeed 30

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
        speed = constrain(speed, -254, 254);
        setDir(speed);
        if(abs(speed) > minSpeed) {
          digitalWrite(_speedPin, speed);
          delay(500);
          digitalWrite(_speedPin, 0);
        }
        else {
          digitalWrite(_speedPin, 0);
          delay(500);
        }
    }

    void setDir(speed) {
      if(speed > minSpeed) {
            digitalWrite(_dirPin, HIGH);
        }
        else
        {
            digitalWrite(_dirPin, LOW);
        }
    }

};


