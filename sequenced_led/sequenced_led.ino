int pins[] = {9, 10, 11};

void setup() {
  Serial.begin(9600);
  for(int i = 0; i <= 2; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void fade(int pin, int length = 30, int hold = 1000, int times = 1) { 
  int brightness = 0;
  int fadeAmount = 7;
  int done_times = 0;
  bool up = true;
  while (true) {
    analogWrite(pin, brightness);

    brightness = brightness + fadeAmount;
    if (brightness > 254) { // dont know how to use max
      brightness = 255;
    }
    // wait
    delay(length);
    if (brightness <= 1 || brightness >= 252) {
      fadeAmount = -fadeAmount;
      up = !up;
      
      if (up) { //reached bottom, going back up again.
        done_times++;
        // Serial.println("going back up?");
        if (done_times == times) {
          analogWrite(pin, 0); // turn off the light
          break;
        }
      delay(hold);
      }
    }
  }
}

void loop() {
  for(int i = 0; i <= 2; i++) {
    int delay = 30;
    switch (i) {
      case 0 : fade(pins[i], 15, 2000); break; // red
      case 1 : fade(pins[i], 5, 200, 5); break; // yellow
      case 2 : fade(pins[i], 15, 5000); break; // green
    }
  }
}
