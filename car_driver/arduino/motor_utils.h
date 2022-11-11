#ifndef MOTOR_UTILS_H
#define MOTOR_UTILS_H

namespace motor_utils {
// @param direction LOW is backwards, HIGH is forward
// @param speed 0-255
inline void set(uint8_t motor_pin, uint8_t brake_pin, uint8_t speed_pin,
                int8_t direction, uint8_t speed) {
  digitalWrite(motor_pin, direction);
  digitalWrite(brake_pin, LOW);  // brake off
  analogWrite(speed_pin, speed); // speed up
}

inline void brake(uint8_t brake_pin, uint8_t speed_pin) {
  digitalWrite(brake_pin, HIGH); // engage brake
  analogWrite(speed_pin, 0);     // slow
}
} // namespace motor_utils
#endif