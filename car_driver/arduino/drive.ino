#define MotorA 12 // left motor
#define BrakeMotorA 9
#define MotorASpeed 3

#define MotorB 13 // right motor
#define BrakeMotorB 8
#define MotorBSpeed 11

void begin() {
  // Setup Channel A
  pinMode(MotorA, OUTPUT);
  pinMode(BrakeMotorA, OUTPUT);

  // Setup Channel B
  pinMode(MotorB, OUTPUT);
  pinMode(BrakeMotorB, OUTPUT);
}

// @param direction LOW is backwards, HIGH is forward
// @param speed 0-255
void motor(int motorpin, int motorbrake, int motorspeed, int direction,
           int speed) {
  digitalWrite(motorpin, direction);
  digitalWrite(motorbrake, LOW);  // brake off
  analogWrite(motorspeed, speed); // speed up
}

void motorAForward(int speed) {
  motor(MotorA, BrakeMotorA, MotorASpeed, HIGH, speed);
}

void motorBForward(int speed) {
  motor(MotorB, BrakeMotorB, MotorBSpeed, HIGH, speed);
}

void motorBBackward(int speed) {
  motor(MotorB, BrakeMotorB, MotorBSpeed, LOW, speed);
}

void motorABackward(int speed) {
  motor(MotorA, BrakeMotorA, MotorASpeed, LOW, speed);
}

void brakeMotorA() {
  digitalWrite(brakeMotorA, HIGH); // engage brake
  analogWrite(MotorASpeed, 0);     // slow
}

void brakeMotorB() {
  digitalWrite(brakeMotorB, HIGH); // engage brake
  analogWrite(MotorBSpeed, 0);     // slow
}

void stop() {
  brakeMotorA();
  brakeMotorB();
}