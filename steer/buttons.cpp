#include "buttons.h"
#include "Joystick.h"
// #include "Streaming.h"

namespace Controller {
unsigned int last_x_value = 1023 / 2;
uint8_t last_button_states[] = {LOW, LOW};
#define STEER_X A0
#define ACCEL 9
#define BRAKE 8
constexpr uint8_t buttons[] = {ACCEL, BRAKE};
#ifdef GAMEPAD_USE_BUTTONS
#define A 0
#define B 1
constexpr uint8_t pad_map[] = {A, B};
#endif
constexpr uint8_t button_count = sizeof(buttons);

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
  for (int i = 0; i < button_count; i++)
    pinMode(buttons[i], INPUT_PULLUP);
  pinMode(STEER_X, INPUT);
  Gamepad.begin();
#ifdef MODE_STEERING_WHEEL
  Gamepad.setAcceleratorRange(0, 1);
  Gamepad.setBrakeRange(0, 1);
  Gamepad.setSteering(last_x_value);
#elif defined(MODE_GAMEPAD)
  Gamepad.setXAxis(last_x_value);
  Gamepad.setYAxis(1023 / 2);
#ifdef GAMEPAD_USE_TRIGGERS
  Gamepad.setRzAxisRange(0, 1);
  Gamepad.setZAxisRange(0, 1);
#endif
#endif
}

void send() {
  for (int i = 0; i < button_count; i++) {
    uint8_t state = digitalRead(buttons[i]) == LOW ? HIGH : LOW;
    if (state != last_button_states[i]) {
#ifdef MODE_GAMEPAD
#ifdef GAMEPAD_USE_BUTTONS
      Gamepad.setButton(pad_map[i], state);
#elif defined(GAMEPAD_USE_TRIGGERS)
      switch (buttons[i]) {
      case ACCEL:
        Gamepad.setRzAxis(state);
        break;
      case BRAKE:
        Gamepad.setZAxis(state);
      }
#endif
#elif defined(MODE_STEERING_WHEEL)
      switch (buttons[i]) {
      case ACCEL:
        Gamepad.setAccelerator(state);
        break;
      case BRAKE:
        Gamepad.setBrake(state);
        break;
      }
#endif
      last_button_states[i] = state;
    }
  }

  unsigned int new_x = analogRead(STEER_X);
#define DEADZONE 1 // if the change is only by one unit, dont bother
  if (new_x - last_x_value > DEADZONE || new_x - last_x_value < DEADZONE) {
    last_x_value = new_x;
#ifdef MODE_GAMEPAD
    Gamepad.setXAxis(new_x);
#elif defined(MODE_STEERING_WHEEL)
    Gamepad.setSteering(new_x);
#endif
  }
}
} // namespace Controller