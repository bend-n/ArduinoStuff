#ifndef BUTTONS_H
#define BUTTONS_H

namespace Controller {
// #define MODE_STEERING_WHEEL
#define MODE_GAMEPAD
#define GAMEPAD_USE_TRIGGERS
// #define GAMEPAD_USE_BUTTONS

/// @brief sets up the pins
void begin();

/// @brief reads the pins, and sends it to the computer
void send();
}; // namespace Controller
#endif
