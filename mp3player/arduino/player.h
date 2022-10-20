#ifndef PLAYER_H
#define PLAYER_H
#include "DFRobotDFPlayerMini.h"
#include "error.h"
#include <SoftwareSerial.h>

namespace Player {
DFRobotDFPlayerMini p;
SoftwareSerial s(10, 11); // RX, TX

void begin() {
  Serial.println(F("init p"));

  s.begin(9600);

  if (!p.begin(s))
    Error err(F("init p fail"));

  Serial.println(F("p online."));

  p.volume(5); // Set volume value. From 0 to 30
  p.play(1);   // Play the first mp3
  Serial.println(p.readFileCounts());
}
} // namespace Player
#endif