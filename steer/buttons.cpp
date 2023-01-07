#include "buttons.h"
#include "Joystick.h"
// #include "Streaming.h"

namespace Controller {
/// vars
unsigned int last_x_value = 1023 / 2;
unsigned int last_accel_value = 0;
unsigned int last_brake_value = LOW; // still digital

/// pins
#define STEER_X A0
#define ACCEL A1
#define BRAKE 8

#ifdef GAMEPAD_USE_BUTTONS
#define PAD_A 0
#define PAD_B 1
#endif

#ifdef MODE_STEERING_WHEEL
Joystick_ Gamepad(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS, 0, 0, false, false, false, false, false,
                  false, false, false, true, true, true);
#elif defined(MODE_GAMEPAD)
#ifdef GAMEPAD_USE_TRIGGERS
Joystick_ Gamepad(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 0, 0, true, true, true, false, false, true,
                  false, false, false, false, false);
#elif defined(GAMEPAD_USE_BUTTONS)
Joystick_ Gamepad(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 2, 0, true, true, false, false, false, false,
                  false, false, false, false, false);
#endif
#endif

void begin() {
  pinMode(STEER_X, INPUT);
  pinMode(ACCEL, INPUT);
  pinMode(BRAKE, INPUT_PULLUP);
  Gamepad.begin();
#ifdef MODE_STEERING_WHEEL
  Gamepad.setBrakeRange(0, 1);
  Gamepad.setSteering(last_x_value);
#elif defined(MODE_GAMEPAD)
  Gamepad.setXAxis(last_x_value);
  Gamepad.setYAxis(1023 / 2);
#ifdef GAMEPAD_USE_TRIGGERS
  Gamepad.setZAxisRange(0, 1);
#endif
#endif
}

inline bool boolify(unsigned int analog) { return analog < (1023 / 2) ? 0 : 1; }

void accel() {
  unsigned int new_accel = analogRead(ACCEL);
  if (new_accel != last_accel_value) {
    last_accel_value = new_accel;
#ifdef MODE_GAMEPAD
#ifdef GAMEPAD_USE_BUTTONS
    Gamepad.setButton(PAD_A, boolify(new_accel));
#elif defined(GAMEPAD_USE_TRIGGERS)
    Gamepad.setRzAxis(new_accel);
#endif
#elif defined(MODE_STEERING_WHEEL)
    Gamepad.setAccelerator(new_accel);
#endif
  }
}

/// @brief still a button
void brake() {
  unsigned int new_brake = digitalRead(BRAKE) == HIGH ? LOW : HIGH;
  if (new_brake != last_brake_value) {
    last_brake_value = new_brake;
#ifdef MODE_GAMEPAD
#ifdef GAMEPAD_USE_BUTTONS
    Gamepad.setButton(PAD_B, new_brake);
#elif defined(GAMEPAD_USE_TRIGGERS)
    Gamepad.setZAxis(new_brake); // if this becomes pot, remember to change this
#endif
#elif defined(MODE_STEERING_WHEEL)
    Gamepad.setBrake(new_brake);
#endif
  }
}

void x() {
  unsigned int new_x = analogRead(STEER_X);
  if (new_x != last_x_value) {
    last_x_value = new_x;
#ifdef MODE_GAMEPAD
    Gamepad.setXAxis(new_x);
#elif defined(MODE_STEERING_WHEEL)
    Gamepad.setSteering(new_x);
#endif
  }
}

void send() {
  accel();
  brake();
  x();
}

} // namespace Controller