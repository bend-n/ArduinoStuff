#ifndef MOTOR_UTILS_H
#define MOTOR_UTILS_H

namespace motor_utils {
// @param direction LOW is backwards, HIGH is forward
// @param speed 0-255
inline void set(int motor, int brake, int speed_pin, int direction, int speed) {
  digitalWrite(motor, direction);
  digitalWrite(brake, LOW);      // brake off
  analogWrite(speed_pin, speed); // speed up
}

inline void brake(int brake_pin, int speed_pin) {
  digitalWrite(brake_pin, HIGH); // engage brake
  analogWrite(speed_pin, 0);     // slow
}
} // namespace motor_utils
#endif