#define ENCODER_OPTIMIZE_INTERRUPTS
#include "rot.h"
#include "Encoder.h"

namespace Rotary {

const uint8_t CLOCK = 2;
const uint8_t DATA = 3;

const uint8_t SWITCH = 4;

namespace {
Encoder encoder(CLOCK, DATA);
}

void setup(const int start = 0) {
  pinMode(SWITCH, INPUT_PULLUP);
  set(start);
}

/// @brief check if button just pressed
bool button_just_pressed() {
  static uint8_t last_button_state = LOW;
  uint8_t button_state = digitalRead(SWITCH);
  if (button_state != last_button_state) {
    last_button_state = button_state;
    if (button_state == LOW)
      return true;
  }
  return false;
}

/// @brief resets the reading to 0 and returns the reading before reset
void set(const int n = 0) { encoder.write(n); }
/// @brief reads the encoder
/// @return encoder position
int read() { return encoder.read(); }
} // namespace Rotary