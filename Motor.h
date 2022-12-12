#include "core_esp8266_features.h"
#pragma once
#include <Arduino.h>
#include <GpioExpander.h>

#define minSpeed 20

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
    GpioExpander* _expander;
public:
    Motor(int8_t dirPin, int8_t speedPin, connectType type = General, GpioExpander expander = NULL) {
        _dirPin = dirPin;
        _speedPin = speedPin;
        _type = type;

        if(_type == General) {      
          pinMode(_dirPin, OUTPUT);
          pinMode(_speedPin, OUTPUT);
        }
        else {
          _expander = &expander;
          _expander->pinMode(_dirPin, OUTPUT);
          _expander->pinMode(_speedPin, OUTPUT);
        }
    }

    void run(int8_t speed) {
        speed = constrain(speed, -254, 254);
        setDir(speed);
        if(abs(speed) > minSpeed) {
          writeAnalog(_speedPin, speed);
          // delay(300);
          // digitalWrite(_speedPin, 0);
        }
        else {
          writeAnalog(_speedPin, 0);
          // delay(300);
        }
    }

    void setDir(int8_t speed) {
      if(speed > 0) {
            writeDigital(_dirPin, HIGH);
        }
        else
        {
            writeDigital(_dirPin, LOW);
        }
    }

    void writeDigital(int8_t pin, int8_t value) {
      if(_type == General) {
        digitalWrite(pin, value);
      }
      else {
        _expander->digitalWrite(pin, value);
      }
    }

    void writeAnalog(int8_t pin, int8_t value) {
      if(_type == General) {
        analogWrite(pin, value);
      }
      else {
        _expander->analogWrite(pin, value);
      }
    }
};


