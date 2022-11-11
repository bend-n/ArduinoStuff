#define HEADER 'H'

const int MOVE_FORWARD[2] = {0, 2}; // 2 == -1 == up
const int MOVE_LEFT[2] = {2, 0};    // move left
const int MOVE_RIGHT[2] = {1, 0};   // move right
const int MOVE_BACK[2] = {0, 1};    // move back
const int MOVE_STOP[2] = {0, 0};    // stop

int8_t prev_a = 0;
int8_t prev_b = 0;

#include "Streaming.h"
#include "drive.h"

void setup() {
  Serial.begin(9600);
  Serial.println("initialized");
  Serial.setTimeout(10);
  begin();
}

void loop() {
  if (Serial.available() > 0) {
    String string = Serial.readString();
    string.trim();
    char header = string[0];
    if (header == HEADER) {
      int delimiter = string.indexOf(',');
      int8_t x = string.substring(1, delimiter).toInt();
      int8_t y = string.substring(delimiter + 1).toInt();
      processCommand(x, y);
    }
  }
}

// @param cmd the thing that tells it what to do, motor1, motorb
void processCommand(const int8_t a, const int8_t b) {
  if (a == prev_a || b == prev_b)
    return;

  prev_a = a, prev_b = b;

  if (a > 100 || a < -100 || b > 100 || b < -100) {
    Serial << "invalid command"
           << "[" << a << "," << b << "]" << endl;
  }
  if (a == 0) {
    // apply brakes to motora
    motor_a.brake();
  } else if (a < 0) {
    motor_a.backward(abs(a) + 155);
  } else {
    // positive number: 100 + 155 = 255
    motor_a.forward(a + 155);
  }
  if (b == 0) {
    // apply brakes to motorb
    motor_b.brake();
  } else if (b < 0) { // negative number: -100 + 355 = 255
    motor_b.backward(abs(b) + 155);
  } else {
    // apply speed to motorb
    motor_b.forward(b + 155);
  }
  Serial << "a: " << a << " b: " << b << endl;
}