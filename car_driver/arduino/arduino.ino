#define HEADER 'H'

const int MOVE_FORWARD[2] = {0, 2}; // 2 == -1 == up
const int MOVE_LEFT[2] = {2, 0};    // move left
const int MOVE_RIGHT[2] = {1, 0};   // move right
const int MOVE_BACK[2] = {0, 1};    // move back
const int MOVE_STOP[2] = {0, 0};    // stop

int8_t prev_a = 0, prev_b = 0;
bool isserial = false;

#include "Streaming.h"
#include "drive.h"
#include "infared.h"

void setup() {
  Serial.begin(9600);
  Infared::begin();
  Serial.println(F("initialized"));
  Serial.setTimeout(10);
  begin();
}

void loop() {
  int8_t a = 255, b = 255;
  if (Serial.available() > 0) {
    isserial = true;
    String string = Serial.readString();
    string.trim();
    char header = string[0];
    if (header == HEADER) {
      int delimiter = string.indexOf(',');
      a = string.substring(1, delimiter).toInt();
      b = string.substring(delimiter + 1).toInt();
    }
  } else if (not isserial) {
    Infared::loop();
    a = Infared::motor_a();
    b = Infared::motor_b();
  }
  if (a != 255 and b != 255)
    processCommand(a, b);
}

// @param cmd the thing that tells it what to do, motor1, motorb
void processCommand(const int8_t a, const int8_t b) {
  if (a > 100 || a < -100 || b > 100 || b < -100) {
    Serial << F("invalid command") << a << ',' << b << endl;
    return;
  }

  prev_a = a, prev_b = b;

  speed(a, b);
}