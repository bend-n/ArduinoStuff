#include "rot.h"
const uint8_t RED = 5;
const uint8_t BLUE = 6;
const uint8_t GREEN = 9;

void setup() { Rotary::setup(50); }

const uint8_t min_delay = 1;
void loop() {
  static uint8_t R, G, B;
  static uint8_t color = 0;
  hue_to_rgb(color, 255, R, G, B);
  analogWrite(RED, R);
  analogWrite(GREEN, G);
  analogWrite(BLUE, B);
  color++;
  // color %= 256; it wraps on its own!
  int result = Rotary::read();
  if (!Rotary::button_just_pressed()) {
    if (result > min_delay) {
      delay(result);
      return;
    }
  } else {
    delay(50);
    Rotary::set(50);
    return;
  }
  if (result != min_delay)
    Rotary::set(min_delay);
  delay(min_delay);
}

void hue_to_rgb(uint8_t hue, uint8_t brightness, uint8_t &R, uint8_t &B, uint8_t &G) {
  uint16_t scaled = hue * 6;
  uint8_t segment = scaled / 256;
  uint8_t offset = scaled - segment * 256;
  uint8_t complement = 0;
  uint8_t prev = (brightness * (255 - offset)) / 256;
  uint8_t next = (brightness * offset) / 256;
  switch (segment) {
  case 0:
    R = brightness;
    G = next;
    B = complement;
    break;
  case 1:
    R = prev;
    G = brightness;
    B = complement;
    break;
  case 2:
    R = complement;
    G = brightness;
    B = next;
    break;
  case 3:
    R = complement;
    G = prev;
    B = brightness;
    break;
  case 4:
    R = next;
    G = complement;
    B = brightness;
    break;
  case 5:
  default:
    R = brightness;
    G = complement;
    B = prev;
    break;
  }
}