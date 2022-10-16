#ifndef DRIVE_H
#define DRIVE_H

#include "motor.h"

Motor motor_b(13, 8, 11);
Motor motor_a(12, 9, 3);

inline void begin() {
  motor_a.begin();
  motor_b.begin();
}

inline void stop() {
  motor_a.brake();
  motor_b.brake();
}
#endif