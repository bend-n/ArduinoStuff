#include "display/display.h"
#include "player.h"

void setup() {
  Serial.begin(9600);
  OLED::begin();
  Player::begin();
}

void loop() {}
