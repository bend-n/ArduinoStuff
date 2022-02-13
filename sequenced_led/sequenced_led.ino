int pins[] = {9, 10, 11};

void setup() {
  Serial.begin(9600);
  for(int i = 0; i <= 2; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void fade(int pin) { 
  int brightness = 0;
  int fadeAmount = 7;
  bool up = true;
  while (true) {
    analogWrite(pin, brightness);

    brightness = brightness + fadeAmount;
    // wait
    delay(30);
    if (brightness <= 1 || brightness >= 252) {
      fadeAmount = -fadeAmount;
      up = !up;
      if (up) {
        analogWrite(pin, 0); // turn off the light
        break;
      }
    }
  }
}

void loop() {
  for(int i = 0; i <= 2; i++) {
    // Serial.print(i);
    // Serial.print(" | ");
    // Serial.println(pins[i]);
    // analogWrite(pins[i], 254);
    fade(pins[i]);
  }
}
