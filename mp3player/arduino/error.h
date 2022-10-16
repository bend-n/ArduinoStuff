#ifndef ERR_H
#define ERR_H

#include "display/display.h"

#define ERR_LIGHT 12

class Error {
public:
  Error(String err) {
    Serial.println("err: " + err);
    OLED::clear();
    OLED::println("err: " + err);
    OLED::flush();
    blink_err_light();
  };

private:
  void blink_err_light() {
    pinMode(ERR_LIGHT, OUTPUT);
    while (true) {
      digitalWrite(ERR_LIGHT, HIGH);
      delay(100);
      digitalWrite(ERR_LIGHT, LOW);
      delay(100);
    }
  }
};
#endif