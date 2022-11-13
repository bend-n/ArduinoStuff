/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include <Streaming.h>

namespace Infared {
#define RECV_PIN 2
struct {

} ir_map;
#define NO_INPUT 0x00

#define ESTOP 0xFFF807
#define STOP 0xFF32CD
#define UP 0xFF0AF5
#define LEFT 0xFF22DD
#define RIGHT 0xFF1AE5
#define DOWN 0xFFF00F

#define UP_LEFT 0xFF12ED
#define UP_RIGHT 0xFF2AD5
#define DOWN_LEFT 0xFFE01F
#define DOWN_RIGHT 0xFF9A65

#pragma region math
inline void lerp(float &from, const float to, const float weight) { from = from + (to - from) * weight; }
inline float lerpr(const float from, const float to, const float weight) { return from + (to - from) * weight; }
static int clamp(long value, long minv, long maxv) {
  if (value < minv)
    return minv;
  else if (value > maxv)
    return maxv;
  return value;
}
void kinda_round(float &n) {
  if (n > .9)
    n = 1;
  else if (n < -.9)
    n = -1;
  else if (n > -.1 and n < .1)
    n = 0;
}
inline int8_t mult(const float n) { return round(clamp(n * 100, -100, 100)); }
#pragma endregion

int8_t motors[2] = {0, 0};

void map(const unsigned long cmd) {
  static float forces = 0, torque = 0;

  const float large_weight = .8, weight = .5, low_weight = .3, speed = 1;

  switch (cmd) {
  case ESTOP:
    torque = 0;
    forces = 0;
  case NO_INPUT:
    lerp(forces, 0, large_weight);
    lerp(torque, 0, large_weight);
    break;
  case UP:
    lerp(forces, +speed, weight);
    break;
  case LEFT:
    lerp(torque, +speed, weight);
    break;
  case RIGHT:
    lerp(torque, -speed, weight);
    break;
  case UP_LEFT:
    lerp(forces, +speed, low_weight);
    lerp(torque, -speed, low_weight);
    break;
  case UP_RIGHT:
    lerp(forces, +speed, low_weight);
    lerp(torque, +speed, low_weight);
    break;
  case DOWN:
    lerp(forces, -speed, weight);
    break;
  case DOWN_LEFT:
    lerp(forces, -speed, low_weight);
    lerp(torque, -speed / 2, low_weight);
    break;
  case DOWN_RIGHT:
    lerp(forces, -speed, low_weight);
    lerp(torque, +speed / 2, low_weight);
    break;

  default:
    break;
  }
  kinda_round(forces);
  kinda_round(torque);
  const float turn_amount = abs(torque) / 2.5;
  const int8_t a = mult(lerpr(forces, torque, turn_amount)), b = mult(lerpr(forces, -torque, turn_amount));

  if (forces > 0) {
    motors[0] = a;
    motors[1] = b;
  } else {
    motors[1] = a;
    motors[0] = b;
  }
}

IRrecv irrecv(RECV_PIN);

decode_results results;
unsigned long last_result_time = 0, last_real_result = 0;

void begin() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == REPEAT)
      results.value = last_real_result;
    else
      last_real_result = results.value;
    map(results.value);
    last_result_time = millis();
    irrecv.resume();
  } else if (not(motors[0] == 0 and motors[1] == 0) and millis() - last_result_time > 200)
    // no results in a while (.2 seconds), lerpit down
    map(NO_INPUT);
}

inline int8_t motor_a() { return motors[0]; }
inline int8_t motor_b() { return motors[1]; }

} // namespace Infared