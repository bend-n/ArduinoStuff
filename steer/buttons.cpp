#include "buttons.h"
#include "Joystick.h"
#include "Streaming.h"

#define INVERT == HIGH ? LOW : HIGH
#define TEXT == HIGH ? "high" : "low"

namespace Controller {
/// pins
#define STEER_X A0
#define ACCEL 10
#define ANY 7 // used for A in gamepad mode, and x in button mode (a accel)````
#define BRAKE 8

#ifdef GAMEPAD_USE_BUTTONS
#define PAD_B 1
#define PAD_X 2
#endif

#ifdef MODE_STEERING_WHEEL
Joystick_ Gamepad(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS, 16, 1, false, false, true, false, false,
                  true, false, false, true, true, true);
#elif defined(MODE_GAMEPAD)
#define PAD_A 0
Joystick_ Gamepad(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 10, 0, true, true, true, true, true, true,
                  false, false, false, false, false);
#endif

void begin() {
  pinMode(STEER_X, INPUT);
  pinMode(ACCEL, INPUT_PULLUP);
  pinMode(BRAKE, INPUT_PULLUP);
  pinMode(ANY, INPUT_PULLUP);
  Gamepad.begin();
#ifdef MODE_STEERING_WHEEL
  Gamepad.setBrakeRange(0, 1);
  Gamepad.setSteering(1023 / 2);
  Gamepad.setSteeringRange(0, 1);
#elif defined(MODE_GAMEPAD)
  Gamepad.setRzAxisRange(0, 1);
  Gamepad.setXAxis(1023 / 2);
  Gamepad.setYAxis(1023 / 2);
#ifdef GAMEPAD_USE_TRIGGERS
  Gamepad.setZAxisRange(0, 1);
#endif
#endif
}

void any() {
  static uint8_t last_any = LOW;
  uint8_t new_any = digitalRead(ANY) INVERT;
  if (new_any != last_any) {
    Serial << "ANY set to " << (new_any TEXT) << endl;
    last_any = new_any;
#ifdef GAMEPAD_USE_BUTTONS
    Gamepad.setButton(PAD_X, new_any);
#else
    Gamepad.setButton(PAD_A, new_any);
#endif
  }
}

void accel() {
  static uint8_t last_accel_value = LOW; // my pot broke so were back to digital
  uint8_t new_accel = digitalRead(ACCEL) INVERT;
  if (new_accel != last_accel_value) {
    Serial << "ACCEL set to " << (new_accel TEXT) << endl;
    last_accel_value = new_accel;
#ifdef MODE_GAMEPAD
#ifdef GAMEPAD_USE_BUTTONS
    Gamepad.setButton(PAD_A, new_accel);
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
  static uint8_t last_brake_value = LOW; // still digital
  uint8_t new_brake = digitalRead(BRAKE) INVERT;
  if (new_brake != last_brake_value) {
    Serial << "BRAKE set to " << (new_brake TEXT) << endl;
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
  static uint16_t last_x_value = 1023 / 2;
  uint16_t new_x = analogRead(STEER_X);
  if (new_x != last_x_value) {
    // Serial << "X set to " << new_x << endl;
    last_x_value = new_x;
#ifdef MODE_GAMEPAD
    Gamepad.setXAxis(new_x);
#elif defined(MODE_STEERING_WHEEL)
    Gamepad.setSteering(new_x);
#endif
  }
}

void send() {
  x();
  any();
  accel();
  brake();
}

} // namespace Controller
