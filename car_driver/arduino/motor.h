#ifndef MOTOR_H
#define MOTOR_H

#include "motor_utils.h"

struct Motor {
  int pin;
  int brake_pin;
  int speed_pin;

  inline void forward(int8_t speed) {
    motor_utils::set(pin, brake_pin, speed_pin, HIGH, speed);
  }
  inline void backward(int8_t speed) {
    motor_utils::set(pin, brake_pin, speed_pin, LOW, speed);
  }
  inline void brake() { motor_utils::brake(brake_pin, speed_pin); }

  inline void begin() {
    pinMode(pin, OUTPUT);
    pinMode(brake_pin, OUTPUT);
  }

  Motor(const uint8_t _pin, const uint8_t _brake_pin,
        const uint8_t _speed_pin) {
    pin = _pin;
    brake_pin = _brake_pin;
    speed_pin = _speed_pin;
  }
};
#endif