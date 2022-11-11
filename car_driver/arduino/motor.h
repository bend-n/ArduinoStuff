#ifndef MOTOR_H
#define MOTOR_H

class Motor {
private:
  int pin;
  int brake_pin;
  int speed_pin;

  // @param direction LOW is backwards, HIGH is forward
  // @param speed 0-255
  void set(int8_t direction, uint8_t speed) {
    digitalWrite(pin, direction);
    digitalWrite(brake_pin, LOW);  // brake off
    analogWrite(speed_pin, speed); // speed up
  }

public:
  // @param speed -100-100, the speed to go at, negative = backwards
  void speed(int8_t speed) {
    if (speed == 0)
      brake();
    else if (speed < 0)
      backward(abs(speed) + 155); // negative number: -100 + 355 = 255
    else
      forward(speed + 155); // positive number: 100 + 155 = 255
  }

  void brake() {
    digitalWrite(brake_pin, HIGH); // engage brake
    analogWrite(speed_pin, 0);     // slow
  }

  inline void forward(uint8_t speed) { set(HIGH, speed); }
  inline void backward(uint8_t speed) { set(LOW, speed); }

  void begin() {
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