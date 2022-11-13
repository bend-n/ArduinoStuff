#ifndef DRIVE_H
#define DRIVE_H

#include "motor.h"

Motor motor_a(12, 9, 3), motor_b(13, 8, 11);

inline void begin() {
  motor_a.begin();
  motor_b.begin();
}

inline void brake() {
  motor_a.brake();
  motor_b.brake();
}

inline void forward(uint8_t speed) {
  motor_a.forward(speed);
  motor_b.forward(speed);
}

inline void forward(uint8_t a_speed, uint8_t b_speed) {
  motor_a.forward(a_speed);
  motor_b.forward(b_speed);
}

inline void backward(uint8_t speed) {
  motor_a.backward(speed);
  motor_b.backward(speed);
}

inline void backward(uint8_t a_speed, uint8_t b_speed) {
  motor_a.backward(a_speed);
  motor_b.backward(b_speed);
}

inline void speed(int8_t speed) {
  motor_a.speed(speed);
  motor_b.speed(speed);
}

inline void speed(uint8_t a_speed, uint8_t b_speed) {
  motor_a.speed(a_speed);
  motor_b.speed(b_speed);
}
#endif