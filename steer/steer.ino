// #include "Streaming.h"
#include "buttons.h"

#define UPDATE_INTERVAL 5

void setup() { Controller::begin(); }

void loop() {
  unsigned long time = millis();
  Controller::send();
  time = millis() - time; // time elapsed in reading the inputs
  if (time < UPDATE_INTERVAL)
    // sleep till it is time for the next update
    delay(UPDATE_INTERVAL - time);
}
